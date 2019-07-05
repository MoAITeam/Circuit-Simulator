//
// Created by Sierra on 2019-07-02.
//

#ifndef FIRSTSIMULATORTEST_NODEOBSERVER_H
#define FIRSTSIMULATORTEST_NODEOBSERVER_H


class Node;

//Actually notifies change of state (previously implemented with Qt Slots)
class NodeObserver {
public:
    virtual void moveNotify(Node &n)=0; //TODO should only comunicate new position
    virtual void removeNotify(Node *n)=0;

};


#endif //FIRSTSIMULATORTEST_NODEOBSERVER_H
