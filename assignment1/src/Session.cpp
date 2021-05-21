//
// Created by Lenovo on 01/11/2020.
//
#include <iostream>
#include <fstream>
#include "../include/Session.h"
#include "../include/Agent.h"
#include "../include/json.hpp"
#include "queue"
#include "string"
#include <vector>

using  json=nlohmann::json;
using namespace std;

Session::Session(const std::string &path):g(),treeType(),agents(),infectQueue(queue<int>()),cycle(0) {
    ifstream i(path);
    json j;
    i >> j;
    g = Graph(j["graph"]);
    std::string tree=j["tree"];
    if(tree=="M")
        treeType=TreeType::MaxRank;
    if(tree=="R")
        treeType=TreeType::Root;
    if(tree=="C")
        treeType=TreeType::Cycle;
    for (auto &elem:j["agents"]) { //scan for the different agents
        if (elem[0] == "V") {
            addAgent(     Virus(elem[1]));
            g.setInfectVisited(elem[1]); // makes them a carrier(yellow)
        } else {
            addAgent(  ContactTracer());
        }
    }
}
    //destructor
Session::~Session() {
    clear(); // clearing the agents vector, implemented at the end of the cpp
}
//copy constructor
Session::Session(const Session &other):g(other.g),treeType(other.treeType),agents(),infectQueue(other.infectQueue),cycle(other.cycle) {
    copy(other);   //copying the agents from other to this, implemented at the end of the cpp
}
//move constructor
Session::Session(Session &&other) : g(other.g),treeType(other.treeType),agents(),infectQueue(other.infectQueue),cycle(other.cycle)  {
    steal(other);  // taking the value from other to us and then delete other
}
//copy assignment operator
Session & Session::operator=(const Session &other) {
    if(this==&other)
        return  *this;
    clear();  //clears the parameters of this before copying the other values
    int size=agents.size();
    g=other.g;
    treeType=other.treeType;
    for (int i=0;i<size;i++) {
        if (other.agents[i])
            addAgent(*other.agents[i]);
    }
    infectQueue=other.infectQueue;
    cycle=other.cycle;
    return *this;
}
Session & Session::operator=(Session &&other)   {
    if (&other!=this)
        clear();
    g=other.g;
    treeType=other.treeType;
    steal(other);
    infectQueue=other.infectQueue;
    cycle=other.cycle;
    other.agents.clear();
    return *this;
}
//so we can disconnect the node , we will need the reference of the graph
Graph& Session::getGraph()  {
    return g;
}
void Session::setGraph(const Graph &graph) {
    g=graph;
}
//to add a const agent by reference we will need to clone it and only then we can add him(cant just add const value here)
void Session::addAgent(const Agent &agent) {
     Agent* newAgent=agent.clone();
     agents.push_back(newAgent);
}
//if the queue is empty, to check if the contactTracer has something to work with
bool Session::QIsEmpty() const{
    return infectQueue.empty();
}

int Session::getCycle()const {
    return cycle;
}

   int Session::dequeueInfected(){
       int retValue=infectQueue.front();
       infectQueue.pop();
       return retValue;
}
void Session::enqueueInfected(int a) {
    g.infectNode(a); //when a node is officially infected, we are inserting it to the infect queue and turning him red
    infectQueue.push(a);
}
void Session::simulate() {
    int size=0;
    // we continue the loop as long as not every node is infected and as long we added new viruses(by means not all the connected component not all infected nor healthy)
while ((!g.allInfected())&&(size!=(int)agents.size())){
    size=agents.size();//a stopper for running only on red agents and not new viruses
    for(int i=0;i<size;++i){
        agents[i]->act(* this);
    }
   cycle++; //for case of cycleTree
}
nlohmann::json j;
std::vector<int>infectedVertices; // vector for output of all the infected nodes
    std::vector<bool>v=g.getIsInfect();
    for (int i=0;i<g.getSize();i++)
       if (v[i])
            infectedVertices.push_back(i);
j["infected"]=infectedVertices;
j["graph"]=g.getMatrix();
std::ofstream o("./output.json");
o<<j<<std::endl;
}

TreeType Session::getTreeType() const {return treeType;
}
//clearing all the pointers from the agents vector
void Session::clear() {
    int size=agents.size();
    for(int i=0; i<size;i++){
        if(agents[i]!= nullptr){
           delete agents[i];
            agents[i]= nullptr;
        }
    }
}
// coping the values from other to us, keeping other values, we are cloning the agents vector agents
void Session::copy(const Session &otherSession) {
    //this->setGraph(otherSession.g);
    //treeType=otherSession.treeType;
    int sizeAgents=agents.size();
    for (int i = 0; i < sizeAgents; ++i) {
        Agent* newAgent=otherSession.agents[i]->clone();
        agents.push_back(newAgent);
        delete newAgent;
    }
}
// taking the values from other to this, and then we delete the values from other to implement "steal"
void Session::steal(Session &otherSession) {
    int agentSize = agents.size();
    for (int i = 0; i < agentSize; ++i) {
        agents.push_back(otherSession.agents[i]);
        otherSession.agents[i] = nullptr;
    }
}









