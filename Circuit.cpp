//
// Created by Sierra on 2019-06-13.
//

#include "Circuit.h"
//TODO: node should be abstract non inheriting from QGraphicsItem

Circuit::Circuit(CircuitObserver *o):observer(o) {
    matrix=new SparseMatrix();
}

Circuit::~Circuit() {
    std::list<Node*> toDestroy=nodes;
    for (auto &node : toDestroy) {
        delete node;
    }
}

void Circuit::setObserver(CircuitObserver *o) {
    observer=o;
    for (auto &component : components) {
        observer->addNotify(component);
        observer->addNotify(component->getNodes().first);
        observer->addNotify(component->getNodes().second);
    }
}

void Circuit::add(Component *c, Node* p, Node* n) {

    for (auto &component : components)
        if (c==component)
        throw "Already added to circuit";

    bool found=false;
    for (auto &node : nodes)
        if (*p==*node) {
            delete p;
            p = node;
            found=true;
        }
    if (found==false){
        if(!p->isGround())
        matrix->add();
        nodes.push_back(p);
        p->setObserver(this);
        observer->addNotify(p);
    }

    found= false;
    for (auto &node : nodes)
        if (*n==*node) {
            delete n;
            n = node;
            found=true;
        }
    if (found==false){
        if(!n->isGround())
        matrix->add();
        nodes.push_back(n);
        n->setObserver(this);
        observer->addNotify(n);
    }

    components.push_back(c);
    c->setObserver(this);
    observer->addNotify(c);

    c->connect(p, n);

    auto nonGrounds=nodes;
    for (auto &node:nodes)
        if(node->isGround())
            nonGrounds.remove(node);
    if(n->isGround()&&p->isGround())
    matrix->add(c);
    if(n->isGround()&&!p->isGround())
        matrix->add(c,getIndex(p,nonGrounds));
    if(!n->isGround()&&p->isGround())
        matrix->add(c,getIndex(n,nonGrounds));
    if(!n->isGround()&&!p->isGround())
        matrix->add(c,getIndex(p,nonGrounds),getIndex(n,nonGrounds));

}

void Circuit::checkLink(Node &n) {
    //TODO: should throw duplicated exception?
            Node* existing=nullptr;

    //The heart of link method: finds the one that is "identical for Node standards" but not the same node
    for (auto &node : nodes) {
        if (*node==n && node!=&n)
            existing=node;
    }

    if (existing != nullptr) {
        std::list<Component *> componentsToUpdate = n.getComponents();
        for (auto &component : componentsToUpdate) {
            nodePair nodes= component->getNodes();
            Node* keep;
            keep = nodes.first == &n ? nodes.second :nodes.first;
            if(*keep == n )
                delete component;
            else {
                component->connect(existing, keep);
                int componentIndex=getIndex(component,components);
                auto nonGrounds=this->nodes;
                for (auto &node:this->nodes)
                    if(node->isGround())
                        nonGrounds.remove(node);
                int pIndex=getIndex(existing,nonGrounds);
                int nIndex=getIndex(keep,nonGrounds);
                if(!existing->isGround()&&!keep->isGround())
                matrix->update(componentIndex,pIndex,nIndex);
                if(existing->isGround()&&!keep->isGround())
                    matrix->update(componentIndex,nIndex);
                if(!existing->isGround()&&keep->isGround())
                    matrix->update(componentIndex,pIndex);
                if(existing->isGround()&&keep->isGround())
                    matrix->update(componentIndex);
            }
            }
        delete &n;
    }
}

template <class T> int Circuit::getIndex(T *x,std::list<T*> v){
    int i=0;
    for (auto &e : v){
        if (e==x)
            return i;
        i++;
    }
    return 0;
}

void Circuit::removeNotify(Component *c) {
    matrix->removeComponent(getIndex(c,components));
    components.remove(c);
}

void Circuit::removeNotify(Node *n) {
    if(!n->isGround()) {
        auto nonGrounds = nodes;
        for (auto &node:nodes)
            if (node->isGround())
                nonGrounds.remove(node);
        matrix->removeNode(getIndex(n, nonGrounds));
    }
    nodes.remove(n);
}

void Circuit::moveNotify(Node &drag) {
    checkLink(drag);
}

void Circuit::print(){
    matrix->print();
}

void Circuit::solve(){
    std::vector<float> solution=matrix->solve();
    int i=0;
    for(auto &component:components){
        component->setVoltage(solution[components.size()-1-i]);
        component->setCurrent(solution[2*components.size()-1-i]);
        i++;
    }
    i=0;
    auto nonGrounds=nodes;
    for (auto &node:nodes)
        if(node->isGround()) {
            node->setVoltage(0);
            nonGrounds.remove(node);
        }
    for(auto& node:nonGrounds){
        node->setVoltage(solution[2*components.size()+i]);
        i++;
    }
}