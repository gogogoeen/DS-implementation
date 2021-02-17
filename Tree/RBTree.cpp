# include <iostream>
# include "RBTree.hpp"
using namespace std;

// implement of the red black tree



// RedBlackTree Insertion
// https://www.geeksforgeeks.org/red-black-tree-set-2-insert/
// https://reurl.cc/OXE46R
// RedBlackTree Deletion
// https://reurl.cc/WEq18O
 
//2021/02/07 add insert (not check yet)



// search a node in the Red Black Tree
bool RBTree :: RBTsearch(int key) {
    return RBTsearch(root, key);
}

bool RBTree :: RBTsearch(Node* node, int x) {
    if (node == neel) return false;
    else if (node -> val > x) return RBTsearch(node -> left, x);
    else if (node -> val < x) return RBTsearch(node -> right, x);
    return true;
}



// intsert a node in the Red Black Tree
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
        // adjustment (change color or rotate)
        node = insertFix(node, isLeft, insertleft);
    }else if (node -> val < key) {  // insert at the right subtree
        node -> right = RBTinsert(node -> right, key, false);
        node -> right -> parent = node;
        insertleft = false;
        // adjustment (change color or rotate)
        node = insertFix(node, isLeft, insertleft);
    }
    
    return node;
}

Node* RBTree :: insertFix(Node* node, bool isLeft, bool insertleft) {
    if (node -> isRed && (node -> left -> isRed || node -> right -> isRed)) {    // double red, need adjustment
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
    }else { // if the child and the grandchild of the node are red
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


void RBTree :: RBTdelete(int x) {
    root = RBTdelete(root, x);
    root -> isRed = false; // mark the tree root as black
    root -> parent = neel; // root parent set to nil
}


// delete root having problem
// delete node with two child having problem
// maybe change merging process 
Node* RBTree :: RBTdelete(Node* node, int x) {
    if (node == neel) return node;     // there is no node with value x in the tree
    if (node -> val == x) {         // find the node to be delete
        bool isBlack = ! node -> isRed;
        Node *ptr = neel;
        if (node -> left != neel && node -> right != neel) {twochild_del(node);  return node;}  // node with two child  
        else if (node -> left == neel && node -> right != neel) ptr = node -> right;    //only right child
        else if (node -> right == neel && node -> left != neel)  ptr = node -> left;    // only left child
        ptr -> parent = node -> parent;    // change the parent after deletion
        if (isBlack) deletefix(ptr);  // if the delete node is black, RBTree need to be fixed
        delete node;
        return ptr;
    }else if (node -> val > x) node -> left = RBTdelete(node -> left, x);
    else node -> right = RBTdelete(node -> right, x);
    return node;
}

// twochild_del is the helper function when delete Node with two children
// the method is to swap the value of the Node and its "successor" and
// let the successor be the delete node. return value is the Node pointer child of 
// the deleted node (successor to the origin delete node). And have one more parameter 
// "target" which is used to save the delete node

void RBTree :: twochild_del(Node* node) {
    Node *ptr = node -> right, *prev = neel;
    while (ptr -> left != neel) {    // find left most node (successor of node)
        prev = ptr;
        ptr = ptr -> left;
    }
    if (prev != neel) {
        prev -> left = ptr -> right; 
        ptr -> right -> parent = prev;
    }else {
        node -> right = ptr -> right;
        ptr -> right -> parent = node;
    }
    swap(node -> val, ptr -> val);  // swap the node and successor
    if (!ptr -> isRed) deletefix(ptr -> right);  // if the deleted node is black, then need fix
    delete ptr;
}

void RBTree :: deletefix(Node* node) {
    while (node != root && !node -> isRed) {
        bool isLeft = node -> parent -> left == node ? true : false; // check node is left or right
        Node* sibling = isLeft ? node -> parent -> right : node -> parent -> left;
        if (sibling -> isRed) {                // case 1 : sibling is red
            sibling -> isRed = false;
            node -> parent -> isRed = true;
            node -> parent = isLeft ? rotateLeft(node -> parent) : rotateRight(node -> parent);
        }else if (!sibling -> isRed && !sibling -> left ->isRed && !sibling -> right -> isRed) {
            sibling -> isRed = true;           // case 2 : sibling is black and both sibling's children are black
            node = node -> parent;
        }else if  (!sibling -> isRed && (!sibling -> right -> isRed && sibling -> left -> isRed && isLeft)
                    || sibling -> right -> isRed && !sibling -> left -> isRed && !isLeft) {
            if (isLeft)                       // case 3 : sibling black, sibling left child red, sibling right child black
                sibling -> left -> isRed = false;
            else
                sibling -> right -> isRed = false; 
            sibling -> isRed = true;
            sibling = isLeft ? rotateRight(sibling) : rotateLeft(sibling);
        }else {                                // case 4 : sibling black, sibling right child red
            sibling -> isRed = node -> parent -> isRed;
            node -> parent -> isRed = false;
            if (isLeft)
                sibling -> right -> isRed = false;
            else 
                sibling -> left -> isRed = false;
            node -> parent = isLeft ? rotateLeft(node -> parent) : rotateRight(node -> parent);   
            node = root;
        }
    }
    node -> isRed = false;  // case 0 : when current is red or root, change it to black
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

void RBTree :: freeTree(Node* node) {
    if (node != neel) {
        freeTree(node -> left);
        freeTree(node -> right);
        delete node;
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
    tree -> RBTinsert(4);
    cout << "show tree" << endl;
    tree -> showTree();
   

    tree -> RBTdelete(11);
    cout << "delete test" << endl;
    cout << "show tree" << endl;
    tree -> showTree();
    tree -> RBTdelete(2);
    cout << "delete test" << endl;
    cout << "show tree" << endl;
    tree -> showTree();
    tree -> RBTdelete(7);
    cout << "delete test" << endl;
    cout << "show tree" << endl;
    tree -> showTree();
   
    
}


