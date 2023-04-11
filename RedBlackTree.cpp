#include "RedBlackTree.h"

int univ_index = 1;
RedBlackTree::RedBlackTree() {
    TNULL = new Node;
    TNULL->colour = 0; //black
    TNULL->left = nullptr;
    TNULL->right = nullptr;
    root = TNULL; 
}

void RedBlackTree::initializeNULLNode(NodePtr node, NodePtr parent) {
    node -> univ = {"", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", ""};
    node -> parent = parent;
    node -> left = nullptr;
    node -> right = nullptr;
    node -> colour  = 0; //black
}

// Inserting a node
void RedBlackTree::insert( string rank, string inst_name, string loc_code, string loc, string arcode, string arrank, string erscore, string errank, string fsrscore, string fsrrank, string cpfscore, string cpfrank, string lfrscore, string lfrrank, string lsrscore, string lsrrank, string lrnscore, string lrnrank, string gerscore, string gerrank, string scorescaled) {

    NodePtr node = new Node; // creating a new node, colour it as red
    node->parent = nullptr;
    node->univ = { rank, inst_name, loc_code, loc, arcode, arrank, erscore, errank, fsrscore, fsrrank, cpfscore, cpfrank, lfrscore, lfrrank, lsrscore, lsrrank, lrnscore, lrnrank, gerscore, gerrank, scorescaled};
    node->left = TNULL;
    node->right = TNULL;
    node->colour = 1; //red

    NodePtr y = nullptr;
    NodePtr x = this->root;

    while (x != TNULL) {
        y = x;
        if (node->univ.inst_name < x->univ.inst_name) {
            x = x->left;
        } else {
            x = x->right;
        }
    }

    node->parent = y;
    if (y == nullptr) {
        root = node;
    } else if (node->univ.inst_name < y->univ.inst_name) {
        y->left = node;
    } else {
        y->right = node;
    } 

    if (node->parent == nullptr) {
        //colour it as black becoz it has no parent, means it is the root
        node->colour = 0; 
        return;
    }

    if (node->parent->parent == nullptr) {
        return;
    }
    
    insertFix(node);
}

NodePtr RedBlackTree::searchTreeHelper(NodePtr node, string key) {
    if (node == TNULL || key == node->univ.inst_name) {
        return node;
    }

    // if searched name `key` is smaller than current node, traverse its left subtree.
    if (key < node->univ.inst_name) {
        return searchTreeHelper(node->left, key);
    }
    return searchTreeHelper(node->right, key);
}

NodePtr RedBlackTree::searchTree(string k) {
    return searchTreeHelper(this->root, k);
}

// For balancing the tree after insertion
void RedBlackTree::insertFix(NodePtr k) {
    NodePtr u;
    while (k->parent->colour == 1) {
        if (k->parent == k->parent->parent->right) {
            u = k->parent->parent->left;
            if (u->colour == 1) {
                u->colour = 0;
                k->parent->colour = 0;
                k->parent->parent->colour = 1;
                k = k->parent->parent;
            } else {
                if (k == k->parent->left) {
                    k = k->parent;
                    rightRotate(k);
                }
                k->parent->colour = 0;
                k->parent->parent->colour = 1;
                leftRotate(k->parent->parent);
            }
        } else {
            u = k->parent->parent->right;

            if (u->colour == 1) {
                u->colour = 0;
                k->parent->colour = 0;
                k->parent->parent->colour = 1;
                k = k->parent->parent;
            } else {
                if (k == k->parent->right) {
                    k = k->parent;
                    leftRotate(k);
                }
                k->parent->colour = 0;
                k->parent->parent->colour = 1;
                rightRotate(k->parent->parent);
            }
        }
        if (k == root) {
            break;
        }
    }
    root->colour = 0;
}

void RedBlackTree::leftRotate(NodePtr x) {
    NodePtr y = x->right;
    x->right = y->left;
    if (y->left != TNULL) {
        y->left->parent = x;
    }
    y->parent = x->parent;
    if (x->parent == nullptr) {
        this->root = y;
    } else if (x == x->parent->left) {
        x->parent->left = y;
    } else {
        x->parent->right = y;
    }
    y->left = x;
    x->parent = y;
}

void RedBlackTree::rightRotate(NodePtr x) {
    NodePtr y = x->left;
    x->left = y->right;
    if (y->right != TNULL) {
        y->right->parent = x;
    }
    y->parent = x->parent;
    if (x->parent == nullptr) {
        this->root = y;
    } else if (x == x->parent->right) {
        x->parent->right = y;
    } else {
        x->parent->left = y;
    }
    y->right = x;
    x->parent = y;
}



// Preorder
void RedBlackTree::preOrderHelper(NodePtr node) {
    if (node != TNULL) {
        cout << node->univ.rank << " ";
        preOrderHelper(node->left);
        preOrderHelper(node->right);
    }
}

// Inorder
void RedBlackTree::inOrderHelper(NodePtr node) {
    if (node != TNULL) {
        inOrderHelper(node->left);
        cout <<  univ_index << ". " << node->univ.inst_name << ", rank = " << node->univ.rank << ", location = " << node->univ.loc << endl;
        univ_index++;
        inOrderHelper(node->right);
    }
}

void RedBlackTree::inOrderPrint() {
    inOrderHelper(this->root);
}

// Post order
void RedBlackTree::postOrderHelper(NodePtr node) {
    if (node != TNULL) {
        postOrderHelper(node->left);
        postOrderHelper(node->right);
        cout << node->univ.rank << " ";
    }
}

NodePtr RedBlackTree::getTNULL() {
    return TNULL;
}
