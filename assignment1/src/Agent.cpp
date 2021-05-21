//
// Created by Lenovo on 01/11/2020.
//

#include "../include/Agent.h"
#include "../include/Tree.h"
//constructor
Agent::Agent(){}
//default destructor to coop with the session agents vector
Agent::~Agent(){}
//Virus constructor
Virus::Virus(int nodeInd) :  nodeInd(nodeInd){}
//contactTracer constructor
ContactTracer::ContactTracer() {}
//clone the contactTracer, to match addChild when receiving const child
ContactTracer * ContactTracer::clone()const {
    return new ContactTracer(*this);
}
//clone the Virus, to match addChild when receiving const child
Virus * Virus::clone()const {
    return new Virus(*this);
}
void Virus::act(Session &session) {

    if (!session.getGraph().isInfected(nodeInd))   // if we are acting with a node that just became virus for the first time
        session.enqueueInfected(nodeInd);   // add to the infected queue, so it will be the next for the contactTracer,and changing it to virus status
    int nextVirus = session.getGraph().searchNearNeighbor(nodeInd);  //searches for the next node to infect in the graph
        if (nextVirus != nodeInd) {   //if we found node to infect
            session.addAgent( Virus(nextVirus));
    }
}
void ContactTracer::act(Session &session) {
    if (!session.QIsEmpty()){ //if there is a virus to work on, else do nothing
      Tree * t;
       t=Tree::bfs(session,session.dequeueInfected()); //builds bfs tree
       session.getGraph().disconnectNode(t->traceTree()); //disconnecting the node we found by the traceTree action
       delete t;  //deleting the memory we are responsible for

    }
}

