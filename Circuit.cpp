//
// Created by Sierra on 2019-06-13.
//

#include "Circuit.h"
#include "ModelException.h"

Circuit::Circuit(CircuitObserver *o):observer(o) {
    matrix=new SparseMatrix();
}

Circuit::~Circuit() {
    std::vector<Node*> toDestroy=nodes;
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
        throw new ModelException("duplicated component won't add it...");

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
        if(observer!=nullptr)
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
        if(observer!= nullptr)
            observer->addNotify(n);
    }

    components.push_back(c);
    c->setObserver(this);
    if(observer!= nullptr)
        observer->addNotify(c);

    c->connect(p, n);

    matrix->add(c->behavior,getIndex(p,nonGround()),getIndex(n,nonGround()));

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

                matrix->update(componentIndex,getIndex(existing,nonGround()),getIndex(keep,nonGround()));
            }
            }
        delete &n;
    }
}

template <class T> int Circuit::getIndex(T *x,std::vector<T*> v){
    int result, count=0, instances=0;
    for (auto &e : v){
        if (e==x) {
            result=count;
            instances++;
        }
        count++;
    }
    if (instances==1)
        return result;
    if (instances>1)
        throw new ModelException("getIndex found duplicated, unexpected behavior");
    if (instances==0)
    return notFound;
}

std::vector<Node*> Circuit::nonGround(){
    std::vector<Node*> nonGrounds=nodes;
    auto node=nonGrounds.begin();
    while (node!=nonGrounds.end()) {
        if ((*node)->isGround())
            node = nonGrounds.erase(node);
        else
            node++;
    }
    return nonGrounds;
}

void Circuit::removeNotify(Component *c) {
    matrix->removeComponent(getIndex(c,components));
    auto toRemove=std::remove(components.begin(),components.end(),c);
    //TODO check if more than one is being removed
    components.erase(toRemove,components.end());
}

void Circuit::removeNotify(Node *n) {
    if (!n->isGround())
        matrix->removeNode(getIndex(n, nonGround()));
    auto toRemove = std::remove(nodes.begin(), nodes.end(), n);
    //TODO check if more than one is being removed
    nodes.erase(toRemove,nodes.end());
}
void Circuit::moveNotify(Node &drag) {
    checkLink(drag);
}

void Circuit::print(){
    matrix->print();
}

void Circuit::solve(){
    std::vector<float> solution=matrix->solve();
    auto comp=components.begin();
    while(comp!=components.end()){
        (*comp)->setVoltage(solution[components.size()-1-(comp-components.begin())]);
        (*comp)->setCurrent(solution[2*components.size()-1-(comp-components.begin())]);
        comp++;
    }
    auto nonGrounds=nonGround();
    auto node=nonGrounds.begin();
    while(node!=nonGrounds.end()){
        (*node)->setVoltage(solution[2*components.size()+(node-nonGrounds.begin())]);
        node++;
    }
}