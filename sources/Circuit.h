//
// Created by Sierra on 2019-06-13.
//

#ifndef FIRSTSIMULATORTEST_CIRCUIT_H
#define FIRSTSIMULATORTEST_CIRCUIT_H

#include "ActiveComponent.h"
#include "Node.h"
#include <vector>
#include "CircuitObserver.h"
#include "SparseMatrix.h"


class Circuit: public ComponentObserver, public NodeObserver{
public:
    Circuit(CircuitObserver* o=nullptr);
    ~Circuit();
    void clear();

    void add(Component *c, Node*& p, Node*& n, bool link=true);
    void setObserver(CircuitObserver* graphics);

    void update(Node *drag) override;
    void update(ActiveComponent* component,float value);

    void removeNotify(Component *c) override;
    void removeNotify(Node *n) override;

    void print();
    void solve();

    std::vector<Component*> getComponents();
    SparseMatrix* getMatrix();

private:

    Node* getNode(Node* n);
    void addNode(Node* n);
    void checkLink(Node *n);
    bool overlaps(Node *p, Node *n);
    template <typename T> int getIndex(T*x,std::vector<T*> v);

    CircuitObserver* observer;
    std::vector<Component*> components;
    std::vector<Node*> nodes;
    std::vector<Node*> notGrounds;
    SparseMatrix matrix;
};


#endif //FIRSTSIMULATORTEST_CIRCUIT_H
