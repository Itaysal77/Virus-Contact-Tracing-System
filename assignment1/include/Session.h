//
// Created by Lenovo on 01/11/2020.
//

#ifndef ASSIGNMENT1_SESSION_H
#define ASSIGNMENT1_SESSION_H


#include <vector>
#include <string>
#include "Graph.h"
#include "queue"

class Agent;

enum TreeType{
    Cycle,
    MaxRank,
    Root
};

class Session{
public:
    Session(const std::string& path) ;
  //  Session(){};
    void simulate();
    void addAgent(const Agent &agent);
    void setGraph(const Graph& graph);// dont forget to implement
    Graph &getGraph();
    void enqueueInfected(int);
    int dequeueInfected();
    TreeType getTreeType() const;
    bool QIsEmpty()const;
    int getCycle()const;
    //Destructor
    virtual ~Session();
    //Copy Constructor
    Session(const Session&other);
    //Move Constructor
    Session(Session&& other);
    //Copy Assignment operator
    Session& operator = (const Session& other);
    //Move Assignment operator
   Session& operator = (Session&& other);
    void copy(const Session& otherSession );
    void clear();
    void steal(Session &otherSession);
private:
    Graph g;
    TreeType treeType;
    std::vector<Agent*> agents;
    std::queue<int> infectQueue;
    int cycle;
};

#endif
