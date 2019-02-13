//Hailey Dhanens Feb 2, 2019

#include <string>


enum nodeType {split, leaf};
using namespace std;

class Node{
    
    // identifies that the node will represent a descision or a final classification
    nodeType type;

    //if node type is split, splitVal is a number, while classification is null, while if it is a leaf, classification is a string while splitVal is null
    double* splitVal;
    string* classification;
    
    Node * lNode;
    Node * rNode;

    Node(double d){

        type = split;
        
        splitVal = new double;
        *splitVal = d;
        classification = nullptr;
        lNode = nullptr;
        rNode = nullptr;
    }
    Node(string name){
        type = classification;

        splitVal = nullptr;
        classification = new string;
        *classification = name;
        lNode = nullptr;
        rNode = nullptr;
    }

    ~Node(){
        if(lNode != nullptr) delete lNode;
        if(rNode != nullptr) delete rNode;
        if(splitVal != nullptr) delete splitVal;
        if(classification != nullptr) delete classification;
        splitVal= 0;
    }
    
    // creates a split node that splits the data at the value d as the right child of our node. should we add a parameter type string? 
    int addR(double d){
        if(rNode != nullptr) return 1;

        rNode = new Node(d);
        return 0;
    }

    int addL(double d){
        if(lNode != nullptr) return 1;

        lNode = new Node(d);
        return 0;
    }

    int addR(string str){

        if(rNode != nullptr) return 1;

        rNode = new Node(str);
        return 0;
    }

    int addl(string str){
        if(lNode != nullptr) return 1;
        lNode = new Node(str);
    }

    nodeType getType(){
        return type;
    }
    nodeType getLType(){
        return *lNode.getType();
    }
    nodeType getRType(){
        return *rNode.getType();
    }

    Node* getlNode(){
        return lNode;
    }

    Node* getrNode(){
        return rNode;
    }

};