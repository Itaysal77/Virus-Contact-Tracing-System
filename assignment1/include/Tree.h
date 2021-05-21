//
// Created by Lenovo on 01/11/2020.
//

#ifndef ASSIGNMENT1_TREE_H
#define ASSIGNMENT1_TREE_H


#include <vector>

class Session;

class Tree{
public:
    Tree(int rootLabel);
    void addChild(const Tree& child);
    void addChild(Tree* child);
    static Tree* bfs(Session& session,int rootNode);
    virtual Tree* clone ()const=0;
   // std::vector<Tree*> &getChildren();
   // int getRootLabel() const;
    static Tree* createTree(const Session& session, int rootLabel);
    virtual int traceTree()=0;
    int getRootLabel() const;
    std::vector<Tree*> &getChildren();
    //Destructor
    virtual ~Tree();
    //Copy Constructor
    Tree(const  Tree&other);
    //Move Constructor
    Tree(Tree&& other);
    //Copy Assignment
    Tree& operator=(const Tree& other);
    //Move Assignment
    Tree& operator=(Tree&& other);
    void copy(const Tree& otherTree);
    void clear();
    void steal(Tree& otherTree);
protected:
    int node;
    std::vector<Tree*> children;
};

class CycleTree: public Tree{
public:
    CycleTree(int rootLabel, int currCycle);
    virtual CycleTree* clone()const;
    virtual int traceTree();

private:
    int currCycle;
};

class MaxRankTree: public Tree{
public:
    MaxRankTree(int rootLabel);
    virtual MaxRankTree* clone()const;
    virtual int traceTree();

};

class RootTree: public Tree{
public:
    RootTree(int rootLabel);
    virtual RootTree* clone()const;
    virtual int traceTree();

};

#endif
