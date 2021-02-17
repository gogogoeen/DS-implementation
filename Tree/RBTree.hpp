
// Red Black Tree 

// Red black tree treenode

// 2021/02/07 add parent pointer in struct node
# define RED "\033[1;31m"
# define RESET "\033[0m"

struct Node {       
    int val;
    bool isRed;
    Node *left;
    Node *right;
    Node *parent;
    //constructor
    Node () : val(0), left(nullptr), right(nullptr), parent(nullptr), isRed(true) {};
    Node (int x) : val(x), left(nullptr), right(nullptr), parent(nullptr), isRed(true) {};
};

class RBTree {
public:
    RBTree () { // create nil node
        neel = new Node();  
        neel -> isRed = false; 
        root = neel;
    }
    ~RBTree () {
        freeTree(root);
        delete neel;
    }
    bool RBTsearch(int key);
    void RBTinsert(int key);
    void RBTdelete(int key);
    void merge(RBTree tree);
    void preorder();
    void inorder();
    void postorder();
    void showTree();
protected:
    Node* rotateLeft(Node* root);
    Node* rotateRight(Node* root);
    bool RBTsearch(Node* node, int key);
    Node* RBTinsert(Node* root, int key, bool isLeft);
    Node* insertFix(Node* root, bool isLeft, bool insertLeft);
    Node* RBTdelete(Node* root, int key);
    void deletefix(Node* node);
    void twochild_del(Node* node);
    void preorder_print(Node* root);
    void inorder_print(Node* root);
    void postorder_print(Node* root);
    void showTree_print(Node* root, int depth);
    void freeTree(Node* node);
    //int getColor(Node *&);
    //void setColor(Node *&, int);
    //Node *minValueNode(Node *&);
    //Node *maxValueNode(Node *&);
    //Node* deleteBST(Node *&, int);
    //int getBlackHeight(Node *);
private:
    Node* root;
    Node* neel;
};
