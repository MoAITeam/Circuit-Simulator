//
// Created by Sierra on 2019-07-02.
//

#ifndef FIRSTSIMULATORTEST_NODEOBSERVER_H
#define FIRSTSIMULATORTEST_NODEOBSERVER_H


class Node;

class NodeObserver {
public:
    virtual void link(Node& n)=0;

};


#endif //FIRSTSIMULATORTEST_NODEOBSERVER_H
