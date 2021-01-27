#include "BST.hpp"
#include <iostream>
using namespace std;

// AVL tree is a self-balanced tree, for each node of a AVL tree
// heights of left and right subtree can differ by no more than 1.
// AVLTree clss inherits the BST class and overrides the insert and delete function
class AVLTree : public BST {

protected:
    TreeNode* TreeInsert(TreeNode* root, int key) override;
    //TreeNode* TreeDelete(TreeNode* root, int key) override;

private:
    TreeNode* TreeRebalance(TreeNode* root);

};

TreeNode* AVLTree :: TreeInsert(TreeNode* root, int key) {
    if (! root) root = new TreeNode(key); // insert new node here
    else if (root -> val == key) return root;  //if node has been inserted
    else if (root -> val > key) {root -> left = TreeInsert(root -> left, key); root = TreeRebalance(root);}
    else {root -> right = TreeInsert(root -> right, key); root = TreeRebalance(root);}
    //check balance
    
    return root;
}

TreeNode* AVLTree :: TreeRebalance(TreeNode* root) {
    if (TreeHeight(root->left) - TreeHeight(root->right) > 1 || TreeHeight(root->left) -TreeHeight(root->right) < -1) {
        if (TreeHeight(root->left) - TreeHeight(root->right) > 1) {     //need a right rotate
            if (TreeHeight(root->left->right) > TreeHeight(root->left->left)) root -> left = left_rotate(root->left);  //LR situation
            root = right_rotate(root);
        }else {                                                         //need a left rotate
            if (TreeHeight(root->right->left) > TreeHeight(root->right->right)) root ->right = right_rotate(root->right);  //RL situation
            root =left_rotate(root);
        }
    }
    return root;
}

/*
TreeNode* AVLTree :: TreeDelete(TreeNode* root, int key) {

}
*/


int main() {
    BST *tree = new AVLTree();
    cout << "preorder of an AVL tree:" << endl;
    tree -> TreeInsert(1);
    tree -> TreeInsert(3);
    tree -> TreeInsert(2);
    tree -> TreeInsert(4);
    tree -> TreeInsert(5);
    tree -> preorder_print();
    cout << "postorder of an AVL tree:" << endl;
    tree -> postorder_print();
}