#include <fstream>        //initializing filestream and vector 
#include<vector>
#include "MyRBT.h"        //including files MyRBT.h and stringUtils.h 
#include "stringUtils.h"

void print(RBT *rbt, Heap *heap, int *args, string &output) {       //function to print output 
cout << "print: " << args[0] << endl;
output += rbt -> range(args[0], args[0]);
}

void printRange(RBT *rbt, Heap *heap, int *args, string &output) {      //function to print range of output
    cout << "printRange: " << args[0] << " " << args[1] << endl;
    output += rbt -> range(args[0], args[1]);
}

void insertRide(RBT *rbt, Heap *heap, int* args, string &output) {             //this function is used to insert the ride using node RBTNode and HeapNode
    cout << "insert: " << args[0] << " " << args[1] << " " << args[2] << endl;
    RBTNode* rnode = new RBTNode(nullptr, nullptr, nullptr, nullptr, RED, args[0], args[1], args[2]);
    HeapNode* hnode = new HeapNode(nullptr, args[0], args[1], args[2]);
rnode -> heapNode = hnode;
   hnode -> rbtNode = rnode;

    if(rbt -> findNode(rnode -> rideNumber, rbt -> root)) {      //check if a node with the same ride number as the new node already exists in the RBT. If such a node is found, it appends the string "Duplicate RideNumber\n" to the output string and returns immediately from the function.
        output += "Duplicate RideNumber\n";
        return;
    }

    rbt -> insert(rnode);   //insert
    heap -> push(hnode);    //push operation

    rbt -> printTree();   //print tree
    heap -> printHeap();  //print heap
}

void getNextRide(RBT *rbt, Heap *heap, string &output) {         //function that takes a pointer to an RBT object, a pointer to a Heap object, and a reference to a string output as arguments and returns nothing (void)
    cout << "getNextRide" << endl;

    if(heap -> getSize() == 0) {
        output += "No active ride requests\n";
        return;
    }
    HeapNode* deletedHeapNode = heap -> pop();                //removes the node with the minimum ride cost or trip duration from the heap by calling the pop function of the heap object. The removed node is then printed to the output string by calling its printHeapNode function. The corresponding node in the RBT is then deleted by calling the deleteNode function of the rbt object with the ride number of the removed heap node as an argument. Finally, the heap and RBT are printed to the standard output stream by calling their respective printHeap and printTree functions.
    deletedHeapNode -> printHeapNode(output);                           
    rbt -> deleteNode(deletedHeapNode -> rbtNode -> rideNumber);

    cout << endl;
    heap -> printHeap();
    rbt -> printTree();
}

void cancelRide(RBT *rbt, Heap *heap, int* args, string &output) {   //function cancels a ride by removing the corresponding node from both the RBT and the heap. 
    cout << "cancelRide: " << args[0] << endl;
    RBTNode* deletedRBTNode = rbt -> deleteNode(args[0]);
    heap -> remove(deletedRBTNode -> heapNode);   //calls the remove function of the heap object with the value of the heapNode member variable of the deleted RBT node as an argument. The function removes the corresponding node from the heap.

    heap -> printHeap();
    rbt -> printTree();
}

void updateTrip(RBT *rbt, Heap *heap, int* args, string &output) {      //This code defines the updateTrip function that takes a pointer to an RBT object, a pointer to a Heap object, a pointer to an integer array args, and a reference to a string output as arguments and returns nothing (void). 
    int newTD = args[1];                                               
    cout<< "updateTrip: " << args[0] << " " << newTD << endl;          
    RBTNode* node = rbt -> findNode(args[0], rbt -> root);
    if(node) {
        int existingTD = node -> tripDuration;
        if(newTD <= existingTD) {                               //The function updates the trip duration of a ride by finding the corresponding node in the RBT and updating its trip duration. If the new trip duration is less than or equal to the existing trip duration, the node is updated in place. 
            node -> tripDuration = newTD;
            heap -> update(node -> heapNode , node -> rideCost, newTD);
            heap -> printHeap();
            rbt -> printTree();
        } else if(existingTD < newTD && newTD <= 2 * existingTD) {     //If the new trip duration is greater than the existing trip duration but less than or equal to twice the existing trip duration, the ride is canceled and reinserted with an increased ride cost.
            cancelRide(rbt, heap, args, output);
            args[1] = node -> rideCost + 10;
            args[2] = newTD;
            insertRide(rbt, heap, args, output);
        } else if(newTD > 2 * existingTD) {               // If the new trip duration is greater than twice the existing trip duration, the ride is canceled.
            cancelRide(rbt, heap, args, output);
        }
    } else cout << "No trip to update" << endl;
}

void parseInput(RBT *rbt, Heap *heap, int argc, char **argv) {    //function reads input from a file specified by the second element of the argv array, processes each line of the file by calling the processOperation function with the appropriate arguments, and writes the output to a file named "output_file.txt
    fstream inputFile;
    inputFile.open(argv[1], ios::in);
    string output;

    if(inputFile.is_open()){          //calls the is_open member function of the inputFile object. If it returns true (i.e., if the file was successfully opened), this if block is executed.
        string fileLine;
        while(getline(inputFile, fileLine)){        //If the file was successfully opened, this while loop reads each line of the file into the variable fileLine using the global function getline.
            string operationPrefix = fileLine.substr(0, 3);   //For each line of the file, this line extracts a substring of length 3 starting from position 0 (i.e., the first three characters) and assigns it to the variable operationPrefix.
            processOperation(rbt, heap, fileLine, operationPrefix, output);
        }
        inputFile.close();        //process each line of the input file by calling the processOperation function with the appropriate arguments. After all lines have been processed, the input file is closed. Then, an output file named "output_file.txt" is opened for writing using an object of type ofstream. 
    }

    ofstream MyFile("output_file.txt");     //The contents of the output string are written to the output file using the << operator. Finally, the output file is closed.
    MyFile << output;
    MyFile.close();
}

int main(int argc, char **argv) {   //main function
    RBT *rbt = new RBT();
    Heap *heap = new Heap();

    if(argc >= 2) {          //The main function takes in command line arguments argc and argv. If the number of arguments (argc) is greater than or equal to 2, the function parseInput is called with the RBT, Heap, and command line arguments as parameters. If the number of arguments is less than 2, an error message is printed to the console stating that there are insufficient arguments and an input file should be provided.
        parseInput(rbt, heap, argc, argv);
        return 0;
    } else cout << "Insufficient arguments - Please provide input file" << endl;
    return 0;
//After the check for sufficient arguments, two pointers to RBTNode and HeapNode are declared but not initialized. Then several HeapNodes are created with different values and pushed onto the heap. The heap is then printed, a specific node is removed, and the heap is printed again.
    RBTNode *rnode; 
    HeapNode *hnode;
    heap -> push(new HeapNode(nullptr, 10,11,12));
    heap -> push(new HeapNode(nullptr, 20,9,12));
    heap -> push(new HeapNode(nullptr, 30,9,9));
    
    heap -> push(new HeapNode(nullptr, 20,8,12));
    HeapNode *h = new HeapNode(nullptr, 30,9,8);
    heap -> push(h);
    heap -> printHeap();heap -> remove(h);
    heap -> printHeap();

}


