//
// Created by Sierra on 2019-06-13.
//

#include "Circuit.h"
#include "ModelException.h"

Circuit::Circuit(CircuitObserver *o):observer(o) {

}

Circuit::~Circuit() {
    std::vector<Component*> toDestroy=components;
    for (auto &c : toDestroy) {
        delete c;
    }
}

void Circuit::setObserver(CircuitObserver *o) {
    observer=o;
    for (const auto &component : components) {
        observer->addNotify(component);
        observer->addNotify(component->getNodes().first);
        observer->addNotify(component->getNodes().second);
    }
}

void Circuit::add(Component *c, Node*& p, Node*& n) {

    for (auto &component : components)
        if (c==component)
            throw ModelException("duplicated component won't add it...");

    if(*p==*n) {
        throw ModelException("Connecting component to the same node, component won't be connected...");
    }

    bool found=false;
    for (auto &node : nodes)
        if (*p==*node) {
            delete p;
            p = node;
            found=true;
        }
    if (!found){
        if(!p->isGround()) {
            matrix.add();
        }

        nodes.push_back(p);
        p->setObserver(this);

        if(observer!=nullptr) {
            observer->addNotify(p);
        }
    }

    found= false;
    for (auto &node : nodes)
        if (*n==*node) {
            delete n;
            n = node;
            found=true;
        }
    if (!found){
        if(!n->isGround()) {
            matrix.add();
        }

        nodes.push_back(n);
        n->setObserver(this);

        if(observer!= nullptr) {
            observer->addNotify(n);
        }
    }

    for(auto& component:components){
        nodePair toCheck=component->getNodes();
        if(((p==toCheck.first)||(p==toCheck.second))&&((n==toCheck.first)||(n==toCheck.second))) {
            delete component;
        }
    }

    components.push_back(c);
    c->setObserver(this);
    if(observer!= nullptr)
        observer->addNotify(c);

    int a=getIndex(p,nonGround());   //find the indexes of comp'sourceType nodes in the list
    int b=getIndex(n,nonGround());

    c->connect(p, n);
    if(c->dependent==nullptr)
        matrix.add(c->behavior,a,b); //here indexes of nodes are necessary
    else
        matrix.add(c->behavior,getIndex(c->dependent,components),c->getSourceType(),a,b);

}

void Circuit::checkLink(Node &n) {

    Node* existing=nullptr;
    int instances=0;

    //The heart of link method: finds the one that is "identical for Node standards" but not the same node
    for (auto &node : nodes) {
        if (*node==n && node!=&n) {
            existing = node;
            instances++;
        }
    }

    if (instances>1)
        throw ModelException("found more than one node to connect to, unexpected behavior");

    if (existing != nullptr) {
        std::list<Component *> componentsToUpdate = n.getComponents();
        for (auto &component : componentsToUpdate) {
            nodePair pair= component->getNodes();
            Node* keep;
            keep = pair.first == &n ? pair.second :pair.first;
            if(*keep == n )
                delete component;
            else {
                component->connect(existing, keep);
                int componentIndex=getIndex(component,components);

                matrix.update(componentIndex,getIndex(existing,nonGround()),getIndex(keep,nonGround()));
            }
        }
        delete &n;
    }
}

template <class T> int Circuit::getIndex(T *x,std::vector<T*> v){
    int result=notFound, count=0, instances=0;
    for (auto &e : v){
        if (e==x) {
            result=count;
            instances++;
        }
        count++;
    }
    if (instances<=1)
        return result;
    else
        throw ModelException("getIndex found duplicated, unexpected behavior");
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
    matrix.removeComponent(getIndex(c,components));

    for(auto &component : components)
        if(component->dependent==c)
            component->dependent=nullptr;

    //Implementation of the erase-remove idiom

    auto removeTail=std::remove(components.begin(),components.end(),c); //moves to the end
    if(components.end()-removeTail>1)
        throw ModelException("found more than one component to remove when expected one, undefined behavoir");
    components.erase(removeTail,components.end()); //destroys
}

void Circuit::removeNotify(Node *n) {
    if (!n->isGround())
        matrix.removeNode(getIndex(n, nonGround()));
    auto removeTail = std::remove(nodes.begin(), nodes.end(), n);
    if(nodes.end()-removeTail>1)
        throw ModelException("found more than one node to remove when expected one, undefined behavoir");
    nodes.erase(removeTail,nodes.end());
}
void Circuit::update(Node &drag) {
    checkLink(drag);
}

void Circuit::print(){
    matrix.print();
}

void Circuit::solve(){
    bool atLeastOneGround=false;
    for (auto &n : nodes) {
        if (n->isGround())
            atLeastOneGround = true;
    }

    if(!atLeastOneGround)
        throw ModelException("No ground selected!");

    std::vector<float> solution=matrix.solve();
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

void Circuit::update(ActiveComponent *component,float value) {
    component->setValue(value);
    matrix.update(getIndex((Component*)component,components),component->behavior);
}