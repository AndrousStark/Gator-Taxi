#include<string>    //initializing 2 libraries string and iostream
#include<iostream>

// Forward declaration of the operations
void print(RBT *rbt, Heap *heap, int *args, string &output);       //declares a function named print that takes a pointer to an RBT object, a pointer to a Heap object, a pointer to an integer array args, and a reference to a string output as arguments and returns nothing (void).
void printRange(RBT *rbt, Heap *heap, int *args, string &output);  //declares a function named printRange that takes a pointer to an RBT object, a pointer to a Heap object, a pointer to an integer array args, and a reference to a string output as arguments and returns nothing (void).
void insertRide(RBT *rbt, Heap *heap, int* args, string &output);  // declares a function named insertRide that takes a pointer to an RBT object, a pointer to a Heap object, a pointer to an integer array args, and a reference to a string output as arguments and returns nothing (void).
void getNextRide(RBT *rbt, Heap *heap, string &output);            //declares a function named getNextRide that takes a pointer to an RBT object, a pointer to a Heap object, and a reference to a string output as arguments and returns nothing (void).
void cancelRide(RBT *rbt, Heap *heap, int* args, string &output);  //declares a function named cancelRide that takes a pointer to an RBT object, a pointer to a Heap object, a pointer to an integer array args, and a reference to a string output as arguments and returns nothing (void).
void updateTrip(RBT *rbt, Heap *heap, int* args, string &output);  //declares a function named updateTrip that takes a pointer to an RBT object, a pointer to a Heap object, a pointer to an integer array args, and a reference to a string output as arguments and returns nothing (void).
void parseInput(RBT *rbt, Heap *heap, int argc, char **argv, string &output);  //same just its for parse input


void parseargs3(int *args, string line) {          //defines the function parseargs3 that takes a pointer to an integer array args and a string line as arguments and returns nothing (void).
    int i = line.find_first_of("(") + 1, len = line.size() - i;      //finds the index of the first opening parenthesis in the given string and calculates the length of the substring starting from the character after the opening parenthesis to the end of the string.
    string stragr = line.substr(i, len - 1);

    int firstComma = stragr.find_first_of(",");
    args[0] = stoi(stragr.substr(0, firstComma));

    int secondComma = stragr.find_last_of(",");
    if(secondComma == string::npos) return;                    //checks if there is no second comma in the extracted substring. If so, it returns immediately
    args[1] = stoi(stragr.substr(firstComma + 1, secondComma - firstComma));       // extracts the substring from just after the first comma to just before the last comma in the extracted substring, converts it to an integer using the stoi function, and stores it in the second element of the given integer array.
    args[2] = stoi(stragr.substr(secondComma + 1));           //extracts the substring from second comma till last
}

void parseargs2(int *args, string line) {                     //defines function parseargs2
    int i = line.find_first_of("(") + 1, len = line.size() - i; // finds the index of the first opening parenthesis in the given string and calculates the length of the substring starting from the character after the opening parenthesis to the end of the string.
    string stragr = line.substr(i, len - 1);

    int firstComma = stragr.find_first_of(",");        //same as first parseargs
    args[0] = stoi(stragr.substr(0, firstComma));
    args[1] = stoi(stragr.substr(firstComma + 1));    
}

void parseargs1(int *args, string line) {                  //defines function named parseargs1 that takes pointer to integer array args and string line as arguments and returns nothing (void)
    int i = line.find_first_of("(") + 1, len = line.size() - i;  //finds index of first opening parenthesis in given string and calculates length of substring starting from character after opening parenthesis to end of string. 10.
    args[0] = stoi(line.substr(i, len - 1));       //extracts substring starting from character after opening parenthesis to second last character of string, converts it to integer using stoi function and stores it in first element of given integer array
}

// this function process inputs given to parse parameter and calls operation functions  as required 
void processOperation(RBT *rbt, Heap *heap, string line, string operationPrefix, string &output) {   //defines function named processOperation that takes pointer to RBT object rbt, pointer to Heap object heap, string line, string operationPrefix and reference to string output as arguments and returns nothing (void)
    int args[3];
    if(operationPrefix == "Pri") {
        if(line.find(",") != string::npos) {      //If value of operationPrefix is equal to “Pri” then this line checks if given string contains comma character
            parseargs2(args, line);              //this line calls parseargs2 function with args array and given string as arguments. 
            printRange(rbt, heap, args, output); //if value of operationPrefix is equal to “Pri” and given string contains comma character then this line calls printRange function with rbt object pointer heap object pointer args array and output reference as arguments. 
        } else {                                 // if value of operationPrefix is equal to “Pri” but given string does not contain comma character then this else block is executed
            parseargs1(args, line);              //value of operationPrefix is equal to “Pri” but given string does not contain comma character then this line calls parseargs1 function with args array and given string as arguments
            print(rbt, heap, args, output);   
        }
    } else if(operationPrefix == "Ins") {        //line checks if the value of operationPrefix is equal to "Ins"
        parseargs3(args, line);
        insertRide(rbt, heap, args, output);
    } else if(operationPrefix == "Upd") {           // line checks if value of operationPrefix is equal to “Upd”
        parseargs2(args, line);
        updateTrip(rbt, heap, args, output);
    } else if(operationPrefix == "Can") {           //checks if value of operationPrefix is equal to “Can”
        parseargs1(args, line);
        cancelRide(rbt, heap, args, output);
    } else if(operationPrefix == "Get") {
        getNextRide(rbt, heap, output);          //If value of operationPrefix is equal to “Get” then this line calls getNextRide function with rbt object pointer heap object pointer and output reference as arguments.
    }
}
