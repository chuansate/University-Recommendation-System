#ifndef REDBLACKTREE_H
#define REDBLACKTREE_H
#include <iostream>
#include <string>
using namespace std;

typedef struct UNIVERSITY {
    string rank;
    string inst_name;
    string loc_code;
    string loc;
    string arcode;
    string arrank;
    string erscore;
    string errank;
    string fsrscore;
    string fsrrank;
    string cpfscore;
    string cpfrank;
    string lfrscore;
    string lfrrank;
    string lsrscore;
    string lsrrank;
    string lrnscore;
    string lrnrank;
    string gerscore;
    string gerrank;
    string scorescaled;
}University;

typedef struct NODE {
    University univ;
    NODE* parent;
    NODE* left;
    NODE* right;
    int colour;
}Node;

typedef Node* NodePtr;

class RedBlackTree {
private:
    NodePtr root;
    NodePtr TNULL; // TNULL are the two nodes attached to newly inserted node

    void initializeNULLNode(NodePtr, NodePtr);
    void preOrderHelper(NodePtr);
    void inOrderHelper(NodePtr);
    
    void postOrderHelper(NodePtr);
    void leftRotate(NodePtr);
    void rightRotate(NodePtr);
    
    void insertFix(NodePtr);
public:
    RedBlackTree();
    void insert(string, string, string, string, string, string, string, string, string, string, string, string, string, string, string, string, string, string, string, string, string);
    void inOrderPrint();
    NodePtr searchTreeHelper(NodePtr, string);
    NodePtr searchTree(string);
    NodePtr getTNULL();
};


#endif