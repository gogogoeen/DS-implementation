#include <iostream>
#include "BST.hpp"
using namespace std;


int main() {
    BST *tree = new BST();

    tree -> TreeInsert(15);
    tree -> TreeInsert(10);
    tree -> TreeInsert(12);
    tree -> TreeInsert(25);
    tree -> TreeInsert(17);
    tree -> TreeInsert(20);
    tree -> showTree();
    tree -> inorder_print();
    cout << "left rotation" << endl;
    //tree -> left_rotate();
    tree -> inorder_print();
    cout << "right rotation" << endl;
   // tree -> right_rotate();
    tree -> inorder_print();
    cout << "afterdeletion" << endl;
    tree -> TreeDelete(15);
    tree -> inorder_print();
    
}