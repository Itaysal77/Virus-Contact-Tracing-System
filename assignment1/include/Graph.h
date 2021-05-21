//
// Created by Lenovo on 01/11/2020.
//

#ifndef ASSIGNMENT1_GRAPH_H
#define ASSIGNMENT1_GRAPH_H


#include <vector>
#include "string"
class Graph{
public:
    Graph(std::vector<std::vector<int>> matrix);
    Graph();
    int getSize()const;
    void infectNode(int nodeInd);
    bool isInfected(int nodeInd);
    bool allInfected() const;
    void disconnectNode(int nodeInd);
    std::vector<std::vector<int>>& getMatrix();
    int searchNearNeighbor(int nodeInd);
    void setInfectVisited(int);

    std::vector<bool> & getIsInfect();


private:
    std::vector<bool> isInfect; //vector if infected nodes(red)
    std::vector<std::vector<int>> edges;
    int cVirus;
    std::vector<bool> infectVisit; // vector of all the nodes thar has been visited, either carrier or infected
};

#endif
