//
// Created by Lenovo on 01/11/2020.
//

#ifndef ASSIGNMENT1_AGENT_H
#define ASSIGNMENT1_AGENT_H

#include <vector>
#include "../include/Session.h"

class Agent{
public:
    Agent();
    virtual ~Agent();
    virtual Agent* clone()const=0;
    virtual void act(Session &session)=0;


};

class ContactTracer: public Agent{
public:
    ContactTracer();
    virtual ContactTracer* clone()const;
    virtual void act(Session&session);
};


class Virus: public Agent{
public:
    Virus(int nodeInd);
    virtual Virus* clone()const;
    virtual void act(Session &session);
private:
    const int nodeInd;
};

#endif
