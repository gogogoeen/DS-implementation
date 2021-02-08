# include <iostream>
# include "RBTree.hpp"
using namespace std;

// implement of the red black tree
// https://www.geeksforgeeks.org/red-black-tree-set-2-insert/
// http://alrightchiu.github.io/SecondRound/re
// d-black-tree-insertxin-zeng-zi-liao-yu-fixupxiu-zheng.html
 
//2021/02/07 add insert (not check yet)

// intsert
void RBTree :: RBTinsert(int key) {
    root = RBTinsert(root, key, false);
    root -> isRed = false; // mark the tree root as black
    root -> parent = neel; // root parent set to nil
}

Node* RBTree :: RBTinsert(Node* node, int key, bool isLeft) {
    if (node == neel) {
        Node* newNode = new Node(key);  // insert the TreeNode
        newNode -> left = neel;
        newNode -> right = neel;
        return newNode;
    }
    bool insertleft= true;
    if (node -> val > key) {    // insert at the left subtree
        node -> left = RBTinsert(node -> left, key, true);
        node -> left -> parent = node;
        insertleft = true;
    }else if (node -> val < key) {
        node -> right = RBTinsert(node -> right, key, false);
        node -> right -> parent = node;
        insertleft = false;
    }
    // adjustment (change color or rotate)
    if (node -> isRed && (node -> left -> isRed || node -> right -> isRed)) {    
        
        Node *uncle = isLeft ? node -> parent -> right : node -> parent -> left;
        if (uncle -> isRed) {   // uncle is red, need change color
            
            node -> isRed = false;
            uncle -> isRed = false;
            node -> parent -> isRed = true;
            
        }else {         // uncle is black, need rotation
            if (isLeft) {
                if (!insertleft) node = rotateLeft(node);   // left right case                
            }else {
                if (insertleft) node = rotateRight(node);   // right left case
            }
        }
        
    }else {
        if (insertleft && node -> left -> left && node -> left -> isRed && node -> left -> left -> isRed) {
            node -> isRed = true;
            node -> left -> isRed = false;
            node = rotateRight(node);
        }else if (!insertleft && node -> right -> right && node -> right -> isRed && node -> right -> right -> isRed) {
            node -> isRed = true;
            node -> right -> isRed = false;
            node = rotateLeft(node);
        }
    }
    return node;
}

// print BST tree in preorder traversal
void RBTree :: preorder() {
    preorder_print(root);
}

void RBTree :: preorder_print(Node* node) {
    if (node == neel) return;
    cout << node -> val << endl;
    preorder_print(node -> left);
    preorder_print(node -> right);
}


// print BST tree in inorder traversal
void RBTree :: inorder() {
    inorder_print(root);
}

void RBTree :: inorder_print(Node* node) {
    if (node == neel) return;
    inorder_print(node -> left);
    cout << node -> val << endl;
    inorder_print(node -> right);
}

// print BST tree in postorder traversal
void RBTree :: postorder() {
    postorder_print(root);
}

void RBTree :: postorder_print(Node* node) {
    if (node == neel) return;
    postorder_print(node -> left);
    postorder_print(node -> right);
    cout << node -> val << endl;
}




//2021/02/07 add parent pointer
Node* RBTree :: rotateLeft (Node* node) {
    Node* newroot = node -> right;
    node -> right = newroot -> left;
    newroot -> parent = node -> parent;
    node -> parent = newroot;
    node -> right -> parent = node;
    newroot -> left = node;
    return newroot;
}

Node* RBTree :: rotateRight (Node* node) {
    Node* newroot = node -> left;
    node -> left = newroot -> right;
    newroot -> parent = node -> parent;
    node -> parent = newroot;
    node -> left -> parent = node;
    newroot -> right = node;
    return newroot;
}

// display Red Black Tree sideways

void RBTree :: showTree() {
   showTree_print(root, 0);
}

void RBTree :: showTree_print(Node* t, int depth) {
    if (t != neel) {
        showTree_print(t -> right, depth+1);
        int i;
        for (i = 0; i < depth; i++) {
	        cout << '\t';            // TAB character
        }
        if (t -> isRed) 
            cout << RED << t -> val << RESET << endl;
        else
	        cout << t -> val << endl;
        showTree_print(t -> left, depth+1);
   }
}




int main () {
    RBTree* tree = new RBTree();
    tree -> RBTinsert(11);
    tree -> RBTinsert(2);
    tree -> RBTinsert(14);
    tree -> RBTinsert(15);
    tree -> RBTinsert(1);
    tree -> RBTinsert(7);
    tree -> RBTinsert(5);
    tree -> RBTinsert(8);
    cout << "show tree" << endl;
    tree -> showTree();
    tree -> RBTinsert(4);
    cout << "show tree" << endl;
    tree -> showTree();
    
    /*
    tree -> RBTinsert(4);
    cout << "show tree" << endl;
    tree -> showTree();
    */
}


