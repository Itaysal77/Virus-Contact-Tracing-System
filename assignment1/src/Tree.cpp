
// Created by Lenovo on 01/11/2020.

#include "../include/Session.h"
#include "../include/Tree.h"
#include "queue"
//constructor
Tree::Tree(int rootLabel) : node(rootLabel),children(){}
//destructor
Tree::~Tree()  {
    clear();
    children.clear(); // so will need to clear the children vector as well, to the destructor will clear the whole tree
}
//copy constructor
Tree::Tree(const Tree &other):node(other.node),children() {
    copy(other);    //copy the vector with the pointers, implemented at the end of the cpp
}
//Move Constructor
Tree::Tree(Tree &&other)  : node(other.node),children() {
steal(other);    // allow us to steal the parameters from other, implemented at the end of the cpp
    }

// copy assignment operator
Tree & Tree::operator=(const Tree &other) {
    if(this==&other)
        return  *this;
    clear();   //clears the parameters of this before copying the other values
    node=other.node;
    this->copy(other);
    return *this;

}
//Move assignment operator
Tree & Tree::operator=(Tree &&other)  {
  if (&other!=this){
      clear();
      node=other.node;
      steal(other);
      }
  other.children.clear();
    return *this;
}
//instead of finding out the type of the tree every time we are calling createTree to do the work for us. efficient especially for bfs scan
Tree * Tree::createTree(const Session &session, int rootLabel) {
    if (session.getTreeType() == MaxRank)
        return new MaxRankTree(rootLabel);
    if (session.getTreeType() == Cycle)
        return new CycleTree(rootLabel, session.getCycle());
    else
        return new RootTree(rootLabel);
}

void Tree::addChild(const Tree &child) { // because we get const Tree we will call the clone because we cannot add normally to the children's vector
    Tree *newChild = child.clone();
    children.push_back(newChild);
}
//adding to children's vector by pointer
void Tree::addChild(Tree *child) {
    children.push_back(child);
}

MaxRankTree::MaxRankTree(int rootLabel) :Tree(rootLabel) {}
//cloning the tree and return a pointer to a new copy of the tree
MaxRankTree * MaxRankTree::clone()const {
    return new MaxRankTree(*this);
}
int Tree::getRootLabel() const  {
    return  node;
}
std::vector<Tree *> & Tree ::getChildren() {return children;}
int MaxRankTree::traceTree() {
    int max=-1;
    int rNode; //returned node index
    std::queue<Tree*> childQueue;
    Tree* curr;
    childQueue.push(this);
    while (!childQueue.empty()) { //as long as we have nodes to work with
        curr = childQueue.front();
        childQueue.pop();
        int numOfChildren = curr->getChildren().size();
        if (numOfChildren > max) {   // checking if we need to change the value of children
            max = curr->getChildren().size();
            rNode = curr->getRootLabel();
        }
        for (int i = 0; i < numOfChildren; ++i) {  //enqueueing all the tree pointers to find each children's  vector size
            childQueue.push(curr->getChildren()[i]);
        }
    }
    return rNode;
}
//int Tree::getRootLabel() const {return node;}
CycleTree::CycleTree(int rootLabel, int currCycle): Tree(rootLabel),currCycle(currCycle){}
//cloning the tree and return a pointer to a new copy of the tree
CycleTree * CycleTree::clone()const{
    return new CycleTree(*this);
}

 int CycleTree::traceTree() {
    CycleTree* currTree= this;
    int i=0;
    while (i<currCycle&&!currTree->children.empty()){
        currTree=(CycleTree*)currTree->children[0];
        i++;
    }
     return currTree->node;
 }

RootTree::RootTree(int rootLabel) :Tree(rootLabel){}
//cloning the tree and return a pointer to a new copy of the tree
RootTree * RootTree::clone()const {
    return new RootTree(*this);
}

int RootTree::traceTree() {
    return node;
        }
//std::vector<Tree *> & Tree::getChildren() {return children;}
Tree * Tree::bfs(Session & session,int rootNode)  {
    Tree* t= Tree::createTree(session,rootNode);
    std::queue<Tree*> nextNode;     //next node to take care of in the tree
    std::vector<bool> visited(session.getGraph().getSize(), false); // so we will know if the node is in the tree or not
    Graph p = session.getGraph(); // to search for neighbors
    nextNode.push(t);
    Tree* currNode;
    visited[rootNode]= true;
    while (!nextNode.empty()){
         currNode=nextNode.front();
        nextNode.pop();
        int size=p.getSize();
        for (int i = 0; i<size ; i++) {
            if(p.getMatrix()[currNode->node][i]== 1 && !visited[i]){   //if they are neighbors and the node free to use in the tree
                Tree* a=Tree::createTree(session,i);
                currNode->addChild(a);
                nextNode.push(a);
                visited[i]= true;
            }
        }
    }
    return  t; //return the root
}
// coping the values from other to us, keeping other values, we are cloning the children vector objects
void Tree::copy(const Tree& otherTree) {
    int size=otherTree.children.size();
    for (int i = 0; i < size; ++i) {
        Tree* child=otherTree.children[i]->clone();
        children.push_back(child);
    }
}
//clearing all the pointers from the tree
void Tree::clear() {
    int size=children.size();
    for(int i=0;i<size;i++){
        if(children[i]!= nullptr){
            delete children[i];
            children[i]= nullptr;
        }
    }
}
// taking the values from other to this, and then we delete the values from other to implement "steal"
void Tree::steal(Tree &otherTree) {

    int size=otherTree.children.size();
    for(int i=0;i<size;i++){
        children.push_back(otherTree.children[i]);
        otherTree.children[i]= nullptr;
    }
}

