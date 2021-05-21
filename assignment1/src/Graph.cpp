//
// Created by Lenovo on 01/11/2020.
//

#include "../include/Graph.h"
Graph::Graph(std::vector<std::vector<int>> matrix) : isInfect(matrix.size(), false),edges(matrix), cVirus(0),infectVisit(matrix.size(),false){
}

Graph::Graph():isInfect(),edges(), cVirus(0),infectVisit(){} //empty constructor for g in session constructor
//getting size of the graph
int Graph::getSize() const {
    int size= (int) edges[0].size();
    return size;
}
std::vector<std::vector<int>> & Graph::getMatrix()  {return edges;
}
//checks if the node is in Virus(red) status
bool Graph::isInfected(int nodeInd) {
    if (isInfect[nodeInd])
        return true;
    else
        return false;
}
//switching isInfect vector status to true- node is a virus
void Graph::infectNode(int nodeInd) {
    isInfect[nodeInd]= true;
    cVirus++;
}
//checks if all the nodes are infected
bool Graph::allInfected() const {
    if(cVirus==getSize())
        return true;
    return false;
}
//for act in contactTracer, remove all the node edges in the graph
void Graph::disconnectNode(int nodeInd) {
    for(int i=0;i<getSize();i++) {
        edges[nodeInd][i] = 0;
        edges[i][nodeInd]=0;
    }
}
//for act in Virus, searching the nearest neighbor that is not virus(red) nor a carrier(yellow)
int Graph::searchNearNeighbor(int nodeInd) {
    for (int i = 0; i <getSize(); ++i)
        if (edges[nodeInd][i]==1&&!infectVisit[i]) { // neighbor and was not infected yet
            infectVisit[i]= true;   //change to yellow(carrier)
            return i;
        }
    return nodeInd;//to know that he does not have a neighbor to go to
}
//to make it a carrier(using in session constructor to automatically make virus node yellow
void Graph::setInfectVisited(int NodeInd) {
    infectVisit[NodeInd]= true;
}
//return the infected(red) nodes
std::vector<bool> & Graph::getIsInfect() {
    return isInfect;
}