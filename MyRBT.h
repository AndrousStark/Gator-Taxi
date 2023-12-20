#include "MyHeap.h"    // including the file MyHeap.h that is included in this file
#include <queue>       // initializing queue header
#define RED 0         // Initalizing red black tree variables and giving them initial values
#define BLACK 1
#define L 0
#define R 1

class RBTNode {                   //defining class RBTNode which will give initialize the default variables and will initalize them for this class with keyword "this"
public :
    RBTNode *leftChild, *rightChild, *parent;
    HeapNode *heapNode;
    bool color;
    int rideNumber, rideCost, tripDuration;

    // Initializes external nodes
    RBTNode() {
        this -> leftChild = nullptr;
        this -> rightChild = nullptr;
        this -> parent = nullptr;
        this -> heapNode = nullptr;
        this -> color = BLACK;
        this -> rideNumber = 0;
        this -> rideCost = 0;
        this -> tripDuration = 0;
    }
    //This function initializes the  non-external RBT nodes
    RBTNode(RBTNode *leftChild, RBTNode *rightChild, RBTNode *parent, HeapNode* heapNode,bool color, int rideNumber, int rideCost, int tripDuration) {
        this -> leftChild = leftChild != nullptr ?        // terneray operator is used to assign values to leftChild and rightChild
        leftChild : new RBTNode();
        this -> rightChild = rightChild != nullptr ?       
        rightChild : new RBTNode();
        this -> parent = parent;
        this -> heapNode = heapNode;
        this -> color = color;
        this -> rideNumber = rideNumber;
        this -> rideCost = rideCost;
        this -> tripDuration = tripDuration;
    }

    // This function initializes the non-external RBT nodes from an existing node
    RBTNode(RBTNode *node) {
        this -> leftChild = node -> leftChild != nullptr ?
            node -> leftChild : new RBTNode();
        this -> rightChild = node -> rightChild != nullptr ?
            node -> rightChild : new RBTNode();
        this -> parent = node -> parent;
        this -> heapNode = node -> heapNode;
        this -> color = node -> color;
        this -> rideNumber = node -> rideNumber;
        this -> rideCost = node -> rideCost;
        this -> tripDuration = node -> tripDuration;
    }
// this function as the name suggest copies heapnode except data
    void copyHeapNodeExceptData(RBTNode *node) {
        this -> leftChild = node -> leftChild;
        this -> rightChild = node -> rightChild;
        this -> parent = node -> parent;
        this -> heapNode = node -> heapNode;
        this -> color = node -> color;
    }
};

class RBT {          //defining class RBT
public:
    RBTNode *root;
    int treesize;   //initalizing treesize interger by defining here

    RBT() {
        root = nullptr;
        treesize = 0;      //initalized as 0
    }

    RBT(RBTNode *rbtNode) {
        root = rbtNode;
        treesize = 1;
    }

    int getTreesize(RBTNode *root) {      //it returns the size of tree
        if(!isExternalNode(root)) 
            return getTreesize(root -> leftChild) + getTreesize(root -> rightChild) + 1;
        return 0;
    }

    bool isExternalNode(RBTNode* node) {                // it takes a pointer to an RBTNode object as an argument and returns a boolean value. The function checks if the given node is an external node by checking if its rideNumber, tripDuration, and rideCost member variables are all equal to 0. If all three conditions are true, the function returns true, indicating that the node is an external node. Otherwise, it returns false
        return node -> rideNumber == 0 && node -> tripDuration == 0 && node -> rideCost == 0;
    }

    RBTNode* Nodefind(int key, RBTNode* node) {           //defines the function Nodefind that takes an integer key and a pointer to an RBTNode object node as arguments and returns a pointer to an RBTNode object.
        if(!node || isExternalNode(node)) return nullptr;   // checks if the given node is null or an external node. If either condition is true, the function returns null immediately.

        int RideNumbercurrent = node -> rideNumber;
        if(key == RideNumbercurrent) return node;      //checks if the given key is equal to the ride number of the current node. If so, it returns the current node.

        if(key > RideNumbercurrent) return Nodefind(key, node -> rightChild);      // checks if the given key is greater than the ride number of the current node. If so, it recursively calls itself with the right child of the current node as the new root of the subtree to search in.
        return Nodefind(key, node -> leftChild);
    }

    RBTNode* findParent(int key, RBTNode* node) {  //This  defines a recursive function findParent that takes in an integer key and a pointer to an RBTNode node as arguments. The function returns a pointer to an RBTNode.
        if(!node) return node;       
        if(key > (node -> rideNumber)) {           // If the node pointer is not null, the function checks if the key is greater than the rideNumber data member of the node
            if(isExternalNode(node -> rightChild)) return node;   //If it is, the function checks if the right child of the node is an external node by calling the isExternalNode function. If the right child is an external node, the function returns the current node.
            node = node -> rightChild;       // If the right child is not an external node, the node pointer is updated to point to its right child.
        } else {
            if(isExternalNode(node -> leftChild)) return node;  //If the key is not greater than the rideNumber data member of the node, the function performs similar operations on the left child of the node.
            node = node -> leftChild;
        }
        return findParent(key, node);  //After updating the node pointer, if necessary, the function calls itself recursively with the updated node pointer and returns its result.
    }

    void insert(RBTNode *p) {  // defines a function insert that takes a pointer to an RBTNode p as an argument and does not return anything. The function inserts the node p into a Red-Black Tree (RBT) data structure.
        int a = p -> rideNumber;
        treesize++;

        RBTNode *pp = findParent(a, root);

        if(pp == nullptr) {  //If pp is a null pointer, this means that the tree is empty and p is the first node being inserted. In this case, the function sets the root of the tree to p, sets the color of p to BLACK, and returns.
            root = p;
            p -> color = BLACK;
            return;
        } 

        p -> parent = pp;   //If pp is not a null pointer, this means that there is at least one node in the tree. The function sets the parent of p to pp. If the value of a is less than the value of the rideNumber data member of pp, then p is set as the left child of pp. Otherwise, it is set as its right child.
        if(a < pp -> rideNumber) pp -> leftChild = p;
        else pp -> rightChild = p;

        adjustRBT(p); //the function calls another function named adjustRBT with argument p. This function adjusts the tree to maintain its Red-Black Tree properties after inserting a new node.
    }

    RBTNode *findCommonAncestor(int r1, int r2, RBTNode *root) {  //defines a recursive function findCommonAncestor that takes in two integers r1 and r2, and a pointer to an RBTNode root as arguments. The function returns a pointer to an RBTNode.
        if(isExternalNode(root)) return root; //The first line of the function checks if the root node is an external node by calling the isExternalNode function. If it is, the function returns the root node.
        if(root -> rideNumber < r1) return findCommonAncestor(r1, r2, root -> rightChild);  //If the root node is not an external node, the function checks if the value of its rideNumber data member is less than the value of r1. If it is, the function calls itself recursively with arguments r1, r2, and the right child of the root node.
        if(root -> rideNumber > r2) return findCommonAncestor(r1, r2, root -> leftChild); // If the value of the rideNumber data member of the root node is not less than the value of r1, the function checks if it is greater than the value of r2. If it is, the function calls itself recursively with arguments r1, r2, and the left child of the root node.
        return root;
    }

    string range(int r1, int r2) {     // defines a function range that takes in two integers r1 and r2 as arguments and returns a string. 
        RBTNode *n1 = Nodefind(r1, root), *n2 = Nodefind(r2, root);
        RBTNode *ancestor = findCommonAncestor(r1, r2, root);   // calls the findCommonAncestor function with arguments r1, r2, and root. The result of this call is stored in a pointer to an RBTNode ancestor

        string output;
        if(!isExternalNode(ancestor))   //The function then declares a string variable output. If the ancestor node is not an external node, as determined by calling the isExternalNode function, the function calls another function named printInorder with arguments r1, r2, output, and ancestor. 
            printInorder(r1, r2, output, ancestor);
        else output += "(" + to_string(ancestor -> rideNumber) + "," + to_string(ancestor -> rideCost) + ","
            + to_string(ancestor -> tripDuration) + ")," ;

        return output.substr(0, output.length() - 1) + "\n";
    }

    void printInorder(int r1, int r2, string &output, RBTNode* node) {  //defines a recursive function printInorder that takes in two integers r1 and r2, a reference to a string output, and a pointer to an RBTNode node as arguments. The function does not return anything.
        int b = node -> rideNumber;     
        if(b < r1 || b > r2 || isExternalNode(node)) return; //function retrieves the value of the rideNumber data member of the node and stores it in an integer variable b. The next line checks if the value of b is less than r1, greater than r2, or if the node is an external node by calling the isExternalNode function. If any of these conditions are met, the function returns immediately.

        printInorder(r1, r2, output, node -> leftChild);      //If none of these conditions are met, the function calls itself recursively with arguments r1, r2, output, and the left child of the node. This performs an in-order traversal of the left subtree of the node
        output += "(" + to_string(node -> rideNumber) + "," + to_string(node -> rideCost) + "," + to_string(node -> tripDuration) + "),";  //After traversing the left subtree, the function appends a string representation of the values of the current node to the output string
        printInorder(r1, r2, output, node -> rightChild);
    }

    int getChildType(RBTNode* pp, RBTNode* p) {   //get child type
        if(pp -> rightChild == p) return R;
        return L;
    }

    RBTNode* getMaxNode(RBTNode *p, RBTNode *currMax) {    //get max node
        if(isExternalNode(p)) return currMax;
        else return getMaxNode(p -> rightChild, p);
    }

    RBTNode* deleteNode(int rideNumber) {       // defines a function deleteNode that takes in an integer rideNumber as an argument and returns a pointer to an RBTNode. The function  delete a node with the specified rideNumber from a Red-Black Tree (RBT) data structure.
        RBTNode *p = Nodefind(rideNumber, root);
        if(!p) return p;
//If the p pointer is not null, this means that a node with the specified rideNumber was found in the tree. The function then declares several pointers to RBTNodes: pp, which points to the parent of p; lc, which points to the left child of p; and rc, which points to the right child of p. It also declares a pointer to an RBTNode y, but its value is not initialized at this point.
        RBTNode *pp = p -> parent, *lc = p -> leftChild, *rc = p -> rightChild, *y;
        int pColor = p -> color;
        int noOfChildren = isExternalNode(lc) && isExternalNode(rc) ? 0 :  !isExternalNode(lc) && !isExternalNode(rc) ? 2 : 1;     // //The function retrieves the value of the color data member of p and stores it in an integer variable pColor. It also calculates the number of non-external children of p by calling the isExternalNode function on its left and right children and stores the result in an integer variable noOfChildren.

        if(noOfChildren == 0) {   // rest performs different operations depending on the value of noOfChildren. If it is 0, this means that both children of p are external nodes. 
            RBTNode *extNode = p -> rightChild;
            if(p == root) {    //In this case, the function declares a pointer to an RBTNode extNode that points to the right child of p. If p is the root of the tree, the root is set to null and the function returns p
                root = nullptr; //. Otherwise, if p is not the root, it checks if it is a left or right child of its parent by calling the getChildType function. 
                return p;
            } else {
                if(getChildType(pp, p) == R) pp -> rightChild = extNode;   //If it is a right child, its parent’s right child is set to point to extNode. If it is a left child, its parent’s left child is set to point to extNode. The value of the pointer y is then set to point to extNode.
                else pp -> leftChild = extNode;
                y = extNode;
            }
        } else if(noOfChildren == 1) {                 //If the value of noOfChildren is 1, this means that one of the children of p is an external node and one is not. In this case, the function performs several operations depending on whether or not p is the root of the tree and whether its left or right child is external.
            RBTNode *lc = p -> leftChild, *rc = p -> rightChild;
            if(p == root) {
                root = isExternalNode(lc) ? rc : lc;
            } else {
                if(!isExternalNode(rc) && getChildType(pp, p) == R) {    
                    pp -> rightChild = rc;
                } else if(!isExternalNode(lc) && getChildType(pp, p) == R) {
                    pp -> rightChild = lc;
                } else if(!isExternalNode(rc)) pp -> leftChild = rc;
                else pp -> leftChild = rc;
            }
            y = isExternalNode(lc) ? rc : lc;
        } else {   //If the value of noOfChildren is 2, this means that both children of p are not external nodes. In this case, the function calls another function named getMaxNode with arguments <EUGPSCoordinates>leftChild, p. The result of this call is stored in a pointer to an RBTNode <EUGPSCoordinates>MaxNode. It then performs several operations depending on whether or not <EUGPSCoordinates>MaxNode is equal to <EUGPSCoordinates>leftChild`. 
            RBTNode *LSTMaxNode = getMaxNode(p -> leftChild, p);
            if(LSTMaxNode != p -> leftChild) {
                LSTMaxNode -> parent -> rightChild = LSTMaxNode -> leftChild;
                y = LSTMaxNode -> parent -> rightChild;
            } else {
                LSTMaxNode -> parent -> leftChild = LSTMaxNode -> leftChild;
                y = LSTMaxNode -> parent -> leftChild;
            }
            
            pp = LSTMaxNode -> parent != p ? LSTMaxNode -> parent : LSTMaxNode;
            // LSTMaxNode -> copyHeapNodeExceptData(p);
            if(p == root) root = LSTMaxNode;
        }


        if(y == root || y -> color == RED) {  //checks if the pointer y, which was declared earlier in the function but not shown in this code snippet, is equal to the root of the tree or if its color is RED. If either of these conditions is true, the color of y is set to BLACK and the function returns p.
            y -> color = BLACK;
            return p;
        }
        y -> parent = pp;   //If neither of these conditions is true, the parent of y is set to pp, where pp is another pointer that was declared earlier in the function 
        
        if(pColor == BLACK) {   //The function then checks if the value of pColor, which was also declared earlier in the function but not shown in this code snippet, is equal to BLACK. If it is, the function calls another function named adjustRBTAfterDelete with arguments y and pp. This function adjusts the tree to maintain its Red-Black Tree properties after deleting a node.
            adjustRBTAfterDelete(y, pp);
        }
        treesize--; //The next line decrements the value of the treesize variable,  to keep track of the number of nodes in the tree. Finally, the function returns p.
        return p;
    }

    void adjustRBTAfterDelete(RBTNode *y, RBTNode* py) {  //code defines a function adjustRBTAfterDelete that takes in two pointers to RBTNodes y and py as arguments and does not return anything. The function  adjust a Red-Black Tree (RBT) data structure to maintain its properties after deleting a node.
        if(y == root) {   //checks if y is equal to the root of the tree. If it is, the color of y is set to BLACK and the function returns.
            y -> color = BLACK;
            return;
        }

        RBTNode *v = (getChildType(py, y) == L) ? py -> rightChild : py -> leftChild;  //If y is not equal to the root of the tree, the function declares a pointer to an RBTNode v that points to either the left or right child of py, depending on whether y is a left or right child of py. This is determined by calling the getChildType function with arguments py and y
        if(isExternalNode(v)) {  //The function then checks if v is an external node by calling the isExternalNode function. If it is, the function checks if y is not an external node. If it is not, its color is set to RED. The function then returns.
            if(!isExternalNode(y))
                y -> color = RED;
            return;
        }

        RBTNode *a = v -> leftChild, *b = v -> rightChild;         //If v is not an external node, the function declares two pointers to RBTNodes a and b that point to the left and right children of v, respectively. It also declares several integer variables: X, which stores the result of calling the getChildType function with arguments py and y; c, which stores the value of the color data member of v; and n, which stores a value that depends on whether or not the colors of a and b are RED.
        int X = getChildType(py, y), c = v -> color, 
        n = a -> color == RED ? (b -> color == RED ? 2 : 1) : b -> color == RED ? 1 : 0;

        // these are some of the cases .  The function performs different operations depending on the values of these variables.
        if(X == R && c == BLACK && n == 0) {
            cout << "RB0 case" << endl;
            RB0(y, py);
        } else if(X == R && c == BLACK && n == 1) {
            RB1Cases(y, py, a);
        } else if(X == R && c == BLACK && n == 2) {
            RB2(y, py);
        } else if(X == R && c == RED) {
            RRCases(py);
        }

        if(X == L && c == BLACK && n == 0) {
            cout << "LB0 case" << endl;
            LB0(y, py);
        } else if(X == L && c == BLACK && n == 1) {
            LB1Cases(y, py, b);
        } else if(X == L && c == BLACK && n == 2) {
            LB2(y, py);
        } else if(X == L && c == RED) {
            LRCases(py);
        }
    }

    void RB0(RBTNode *y, RBTNode *py) {  //defines a function RB0 that takes in two pointers to RBTNodes y and py as arguments and does not return anything. The function is a part of the process of adjusting a Red-Black Tree (RBT) data structure to maintain its properties after deleting a node.
        if(y == root) {   //checks if y is equal to the root of the tree. If it is, the color of y is set to BLACK and the function returns.
            y -> color = BLACK;
            return;
        }

        RBTNode *v = py -> leftChild;  //If y is not equal to the root of the tree, the function declares a pointer to an RBTNode v that points to the left child of py.

        if(py -> color == BLACK) {    //The function then checks if the color of py is BLACK. If it is, the color of v is set to RED. If it is not, the color of py is set to BLACK and the color of v is set to RED. The function then returns.
            v -> color = RED;
        } else {
            py -> color = BLACK;
            v -> color = RED;
            return;
        }
        adjustRBTAfterDelete(py, py -> parent);  //If the color of py was initially BLACK, the function calls itself recursively with arguments py and the parent of py. This continues the process of adjusting the tree after deleting a node.
    } 

    void RB1Cases(RBTNode *y, RBTNode *py, RBTNode *a) {   //defines a function RB1Cases that takes in three pointers to RBTNodes y, py, and a as arguments and does not return anything. The function is part of the process of adjusting a Red-Black Tree (RBT) data structure to maintain its properties after deleting a node.
        if(a == RED) {   //The function checks if the color of a is RED. If it is, the function calls another function named RB11 with arguments y and py. 
            cout << "RB11 case" << endl;
            RB11(y, py);
        } else {   //If it is not, the function calls another function named RB12 with the same arguments. 
            cout << "RB12 case" << endl;
            RB12(y, py);
        }
    }

    void RB11(RBTNode *y, RBTNode *py) {   //function declares two pointers to RBTNodes v and a. v points to the left child of py and a points to the left child of v.
        RBTNode *v = py -> leftChild, *a = v -> leftChild;  //The function then sets the color of a to BLACK, the color of v to the color of py, and the color of py to BLACK.
        a -> color = BLACK;
        v -> color = py -> color ;
        py -> color = BLACK;
        LLRotation(py);   
    }

    void RB12(RBTNode *y, RBTNode *py) {        // part of red black tree adjustment
        RBTNode *v = py -> leftChild, *w = v -> rightChild;
        w -> color = py -> color ;
        py -> color = BLACK;
        LRRotation(v, py);
    }

    void RB2(RBTNode *y, RBTNode *py) {       // function declares a pointer to an RBTNode w that points to the right child of the left child of py.The function then sets the color of w to the color of py and the color of py to BLACK.Finally, the function calls another function named LRRotation with arguments <EUGPSCoordinates>leftChildandpy`
        RBTNode* w = py -> leftChild -> rightChild;
        w -> color = py -> color;
        py -> color = BLACK;
        LRRotation(py -> leftChild, py);
    }

    void RRCases(RBTNode *py) {   //defines a function RRCases that takes in a pointer to an RBTNode py as an argument and does not return anything. The function is a part of the process of adjusting a Red-Black Tree (RBT) data structure to maintain its properties after deleting a node.
        RBTNode *v = py -> leftChild, *w = v -> rightChild;
        RBTNode *b = w -> leftChild, *c = w -> rightChild;   //The function then declares two more pointers to RBTNodes b and c. b points to the left child of w and c points to the right child of w.
        int n = c -> color == RED ? (b -> color == RED ? 2 : 1) : b -> color == RED ? 1 : 0;   //The function then calculates a value that depends on whether or not the colors of b and c are RED and stores it in an integer variable n.

        if(n == 0) {   //the function performs different operations depending on the value of n
            RR0(py, v, w);
        } else if(n == 1) {
            if(b -> color == RED) RR11(v, py, b);
            else RR12(py, v, w, c);
        } else {
            RR2(py, v, w, c);
        }
    }

    void RR0(RBTNode *py, RBTNode *v, RBTNode *b) {   // part of red black tree process
        LLRotation(py);
        v -> color = BLACK;
        b -> color = RED;
    }

    void RR11(RBTNode *y, RBTNode *py, RBTNode *b) {
        LRRotation(y, py);
        b -> color = BLACK;
    }

    void RR12(RBTNode *py, RBTNode *v, RBTNode *w, RBTNode *x) {
        RRRotation(w);
        LRRotation(v, py);
        x -> color = BLACK;
    }

    void RR2(RBTNode *py, RBTNode *v, RBTNode *w, RBTNode *x) {
        RRRotation(w);
        LRRotation(v, py);
        x -> color = BLACK;
    }

    void LB0(RBTNode *y, RBTNode *py) {  //defines a function LB0 that takes in two pointers to RBTNodes y and py as arguments and does not return anything.
        if(y == root) {
            y -> color = BLACK;
            return;
        }
        RBTNode *v = py -> rightChild;

        if(py -> color == BLACK) {  //The function then checks if the color of py is BLACK. If it is, it sets the color of v to RED. If it is not, it sets the color of py to BLACK and the color of v to RED. The function then returns.
            v -> color = RED;
        } else {
            py -> color = BLACK;
            v -> color = RED;
            return;
        }
        adjustRBTAfterDelete(py, py -> parent);  //If the color of py was initially BLACK, the function calls another function named adjustRBTAfterDelete with arguments py and the parent of py. This function  adjusts the tree to maintain its Red-Black Tree properties after deleting a node.
    }

    void LB1Cases(RBTNode *y, RBTNode *py, RBTNode *b) {  //function LB1Cases that takes in three pointers to RBTNodes y, py, and b as arguments and does not return anything. 
        if(b == RED) {
            cout << "LB11 case" << endl;
            LB11(y, py);
        } else {
            cout << "LB12 case" << endl;
            LB12(y, py);
        }
    }

    void LB11(RBTNode *y, RBTNode *py) {     // part of red black tree
        RBTNode *v = py -> rightChild, *b = v -> rightChild;
        b -> color = BLACK;
        v -> color = py -> color ;
        py -> color = BLACK;
        RRRotation(py);
    }

    void LB12(RBTNode *y, RBTNode *py) {     // part of red black tree
        RBTNode *v = py -> rightChild, *a = v -> leftChild;
        a -> color = py -> color ;
        py -> color = BLACK;
        RLRotation(v, py);
    }

    void LB2(RBTNode *y, RBTNode *py) {      // part of red black tree
        RBTNode* a = py -> rightChild -> leftChild;
        a -> color = py -> color;
        py -> color = BLACK;
        LRRotation(py -> rightChild, py);
    }

    void LRCases(RBTNode *py) {         //function LRCases that takes in a pointer to an RBTNode py as an argument and does not return anything. 
        RBTNode *v = py -> rightChild, *a = v -> leftChild;  //The function declares two pointers to RBTNodes v and a. v points to the right child of py and a points to the left child of v.
        RBTNode *b = a -> leftChild, *c = a -> rightChild;   //The function then declares two more pointers to RBTNodes b and c. b points to the left child of a and c points to the right child of a.
        int n = c -> color == RED ? (b -> color == RED ? 2 : 1) : b -> color == RED ? 1 : 0;  //The function then calculates a value that depends on whether or not the colors of b and c are RED and stores it in an integer variable n.

        if(n == 0) {  //The rest of the function performs different operations depending on the value of n
            LR0(py, v, a);
        } else if(n == 1) {
            if(c -> color == RED) LR11(v, py, c);
            else LR12(py, v, a, b);
        } else {
            LR2(py, v, a, b);
        }
    }

    void LR0(RBTNode *py, RBTNode *v, RBTNode *a) {  // part of red black tree
        RRRotation(py);
        v -> color = BLACK;
        a -> color = RED;
    }

    void LR11(RBTNode *v, RBTNode *py, RBTNode *c) { // part of red black tree
        RLRotation(v, py);
        c -> color = BLACK;
    }

    void LR12(RBTNode *py, RBTNode *v, RBTNode *w, RBTNode *b) {  // part of red black tree
        LLRotation(w);
        RLRotation(v, py);
        b -> color = BLACK;
    }

    void LR2(RBTNode *py, RBTNode *v, RBTNode *w, RBTNode *b) {  // part of red black tree
        LLRotation(w);
        RLRotation(v, py);
        b -> color = BLACK;
    }

    void adjustRBT(RBTNode* p) {    //defines a function adjustRBT that takes in a pointer to an RBTNode p as an argument and does not return anything
        if(!p || !p -> parent || !p -> parent -> parent) return;   //checks if p, its parent, or its grandparent are null. If any of these pointers are null, the function returns immediately.

        RBTNode *pp = p -> parent, *gp = pp -> parent;  //If none of these pointers are null, the function declares two pointers to RBTNodes pp and gp. pp points to the parent of p and gp points to the grandparent of p.
        if(pp -> color == BLACK) return;

        int X, Y, r;      //If the color of pp is not BLACK, the function declares three integer variables X, Y, and r. The value of X is set to either L or R, depending on whether pp is a left or right child of gp. The value of Y is set to either L or R, depending on whether p is a left or right child of pp. The value of r is set to the color of either the left or right child of gp, depending on the value of X.

        X = (gp -> leftChild == pp) ? L : R;
        Y = (pp -> leftChild == p) ? L : R;
        r = (X == L) ? gp -> rightChild -> color : gp -> leftChild -> color;

        if(r == RED) {           // The function then checks if the value of r is RED. If it is, it calls another function and perform rotations accordingly
            XYr(p);
            return;
        }

        if(X == L && Y == L) {   // part of rotation process
            LLRotation(gp);
            pp -> color = BLACK;
            gp -> color = RED;  
        } else if(X == R && Y == R) {
            RRRotation(gp);
            pp -> color = BLACK;
            gp -> color = RED;  
        } else if(X == L && Y == R) {
            LRRotation(pp, gp);
            p -> color = BLACK;
            gp -> color = RED;  
        } else {
            RLRotation(pp, gp);
            p -> color = BLACK;
            gp -> color = RED; 
        }
        
    }

    void XYr(RBTNode* p) {     //defines a function XYr that takes in a pointer to an RBTNode p as an argument and does not return anything.
        if(p == root) {   //checks if p is equal to the root of the tree. If it is, the color of p is set to BLACK and the function returns.
            p -> color = BLACK;
            return;
        }

        RBTNode *pp = p -> parent;   //If p is not equal to the root of the tree, the function declares a pointer to an RBTNode pp that points to the parent of p.
        if(p -> color == BLACK || pp -> color == BLACK) return;   //The function checks if either the color of p or the color of pp is BLACK. If either of these conditions is true, the function returns immediately.
        
        int X = (pp -> parent -> leftChild == pp) ? L : R;  //If neither of these conditions is true, the function declares an integer variable X and sets its value to either L or R, depending on whether pp is a left or right child of its parent. The function also declares two more pointers to RBTNodes gp and d. gp points to the parent of pp and d points to either the left or right child of gp, depending on the value of X.
        RBTNode *gp = pp -> parent, *d = (X == L) ? 
            gp -> rightChild : gp -> leftChild;

        d -> color = BLACK;
        pp -> color = BLACK;    //The function then sets the colors of d, pp , and gp to BLACK, BLACK, and RED, respectively.
        gp -> color = RED;

        if(gp == root) gp -> color = BLACK;
        adjustRBT(gp);
    }

    void LLRotation(RBTNode* gp) {
        RBTNode *ggp = gp -> parent, *pp = gp -> leftChild, *p = pp -> leftChild;    //declares three pointers of type RBTNode: ggp, pp, and p. It also initializes them to the parent of gp, the left child of gp, and the left child of pp, respectively.
        RBTNode *c = pp -> rightChild;  //declares a pointer of type RBTNode called c and initializes it to the right child of pp
        
        pp -> rightChild = gp;  //sets the right child of pp to be gp.
        gp -> leftChild = c;  //setting different values

        pp -> parent = ggp;
        gp -> parent = pp;

        if(!ggp) {    //checks if ggp is a null pointer. If it is, it sets the root to be equal to pp and returns from the function.
            root = pp;
            return;
        }

        if(ggp -> rightChild == gp) ggp -> rightChild = pp;    //block checks if the right child of ggp is equal to gp. If it is, it sets the right child of ggp to be equal to pp. Otherwise, it sets the left child of ggp to be equal to pp.
        else ggp -> leftChild = pp;    

        pp -> parent = ggp;   
    }

    void RRRotation(RBTNode* gp) {     //same as above but position of rightchild and leftchild is interchanged
        RBTNode *ggp = gp -> parent, *pp = gp -> rightChild, *p = pp -> rightChild;  
        RBTNode *c = pp -> leftChild, *b = p -> leftChild;
        
        pp -> leftChild = gp;
        gp -> rightChild = c;

        pp -> parent = ggp;
        gp -> parent = pp;

        if(!ggp) {
            root = pp;
            return;
        }

        if(ggp -> leftChild == gp) ggp -> leftChild = pp;
        else ggp -> rightChild = pp; 

        pp -> parent = ggp;
    }

    void LRRotation(RBTNode* pp, RBTNode *gp) {   //LR rotation
        RRRotation(pp);
        LLRotation(gp);
    }

    void RLRotation(RBTNode* pp, RBTNode *gp) {   //RL rotation
        LLRotation(pp);
        RRRotation(gp);
    }

    void printTree() {     //declares a queue of RBTNode pointers called q.
        queue<RBTNode*> q;
        q.push(root);    // pushes the root of the tree onto the queue.

        while(!q.empty()) {    //while loop that continues until the queue is empty.
            int size = q.size();   //declares an integer variable called size and initializes it to the size of the queue.
            while(size) {    //starts a nested while loop that continues until size is 0.
                RBTNode *node = q.front();   //declares a pointer of type RBTNode called node and initializes it to the front element of the queue.
                q.pop();   //pops the front element from the queue.
                if(!node) {
                    cout << "Empty tree" << endl;
                    return;
                }
                char color = node -> color ? 'b' : 'r';   //declares a character variable called color. It initializes it to 'b' if the color of node is true, and 'r' otherwise.

                if(node -> rideNumber > 0)      // checks if the rideNumber of node is greater than 0. If it is, it prints color, a hyphen, and rideNumber to standard output followed by a tab character.
                    cout << color << "-" << node -> rideNumber << "\t";
                if(node -> leftChild) q.push(node -> leftChild);   // two lines check if node has left and right children respectively. If it does, it pushes them onto the queue.
                if(node -> rightChild) q.push(node -> rightChild);
                size--;
            }
            cout << endl;
        }
    }
};
