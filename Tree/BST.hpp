#include <iostream>
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode* left, TreeNode* right) : val(x), left(left), right(right) {}
};

// class of a binary tree
class BST {
public:
    BST() : root(nullptr){};
    ~BST(){FreeTree();}

    // measuring the tree height
    int TreeHeight(); 
    // to check whether node with value x is in the tree
    bool TreeSearch(int key);
    // insert a new item into a Tree
    void TreeInsert(int key);
    // delete a specific node in a Tree
    void TreeDelete(int key);
    // delete the whole tree
    void FreeTree();
    // print tree in preorder
    void preorder_print();
    // print tree in inorder
    void inorder_print();
    // print tree in postorder
    void postorder_print();   
    // left rotate the tree
    void left_rotate();
    // right rotate the tree
    void right_rotate();

protected: 
    TreeNode *root;
    int TreeHeight(TreeNode* root);
    bool TreeSearch(TreeNode* root, int key); 
    virtual TreeNode* TreeInsert(TreeNode* root, int key);
    virtual TreeNode* TreeDelete(TreeNode* root, int key);
    void FreeTree(TreeNode* root);
    TreeNode* joinTree(TreeNode* root1, TreeNode* root2);
    void preorder_print(TreeNode* root);
    void inorder_print(TreeNode* root);
    void postorder_print(TreeNode* root);  
    TreeNode* left_rotate(TreeNode* root);
    TreeNode* right_rotate(TreeNode* root); 
    
};


