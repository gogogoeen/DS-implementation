#include "BST.hpp"
#include <iostream>
using namespace std;
// implementation of a binary tree class


// measuring the tree height
int BST :: TreeHeight() {
    return TreeHeight(root);
}

int BST :: TreeHeight(TreeNode* root) {
    if (!root) return 0;
    else return 1 + max(TreeHeight(root -> left), TreeHeight(root -> right)); 
}


// to check whether node with value x is in the tree
bool BST :: TreeSearch(int x) {
    return TreeSearch(root, x);
}

bool BST :: TreeSearch(TreeNode* root, int x) {
    if (! root) return false;
    if (root -> val == x) return true;
    return  root -> val > x ? TreeSearch(root -> left, x) : TreeSearch(root -> right, x);
}


// insert a new item into a Tree
void BST :: TreeInsert(int x) {
    root = TreeInsert(root, x);
}

TreeNode* BST :: TreeInsert(TreeNode* root, int x) {
    if (! root) root = new TreeNode(x); // insert new node here
    if (root -> val == x) return root;  //if node has been inserted
    if (root -> val > x) root -> left = TreeInsert(root -> left, x);
    else root -> right = TreeInsert(root -> right, x);
    return root;
}


// delete a specific node in a Tree
void BST :: TreeDelete(int x) {
    root = TreeDelete(root, x);
}


TreeNode* BST :: TreeDelete(TreeNode* root, int x) {
    if (! root) return nullptr;     // there is no node with value x in the tree
    if (root -> val == x) {         // find the node to be delete
        TreeNode *ptr = nullptr;
        if (root -> left && root -> right) ptr = joinTree(root -> left, root -> right);    
        else if (! root -> left && root -> right) ptr = root -> right;
        else if (! root -> right && root -> left)  ptr = root -> left;
        delete root;
        return ptr;
    }else if (root -> val > x) root -> left = TreeDelete(root -> left, x);
    else root -> right = TreeDelete(root -> right, x);
    return root;
}

TreeNode* BST :: joinTree(TreeNode* root1, TreeNode* root2) {
    if (! root1 && root2) return root2;
    else if (root1 && ! root2) return root1;
    else {  // if both root1 and root2 exist, merge two of them
        TreeNode *ptr = root2, *parent = nullptr;
        while (ptr -> left != nullptr) {    // find left most node of root2 to be the new merge root
            parent = ptr;
            ptr = ptr -> left;
        }
        if (parent) {
            parent -> left = ptr -> right; // unlink the merge root from root2, and put the right subtree (merge node) to the cut place
            ptr -> right = root2;
        }
        ptr -> left = root1;
        return ptr;
    }
}


// delete the whole tree
void BST :: FreeTree() {
    FreeTree(root);
}

void BST :: FreeTree(TreeNode* root) {
    if (! root) return;
    FreeTree(root -> left);
    FreeTree(root -> right);
    delete root;
}

// print BST tree in preorder traversal
void BST :: preorder_print() {
    preorder_print(root);
}

void BST :: preorder_print(TreeNode* root) {
    if (! root) return;
    cout << root -> val << endl;
    preorder_print(root -> left);
    preorder_print(root -> right);
}


// print BST tree in inorder traversal
void BST :: inorder_print() {
    inorder_print(root);
}

void BST :: inorder_print(TreeNode* root) {
    if (! root) return;
    inorder_print(root -> left);
    cout << root -> val << endl;
    inorder_print(root -> right);
}

// print BST tree in postorder traversal
void BST :: postorder_print() {
    postorder_print(root);
}

void BST :: postorder_print(TreeNode* root) {
    if (! root) return;
    postorder_print(root -> left);
    postorder_print(root -> right);
    cout << root -> val << endl;
}

// left rotate the tree
void BST :: left_rotate() {
    root = left_rotate(root);
}

TreeNode* BST :: left_rotate(TreeNode* root) {
    TreeNode *ptr = root -> right;
    root -> right = ptr -> left;
    ptr -> left = root;
    return ptr;
}

// right rotate the tree
void BST :: right_rotate() {
    root = right_rotate(root);
}

TreeNode* BST :: right_rotate(TreeNode* root) {
    TreeNode *ptr = root -> left;
    root -> left = ptr -> right;
    ptr -> right = root;
    return ptr;
}





