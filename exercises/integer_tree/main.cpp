#include <iostream>

#include "IntTree.h"

using namespace std;

int main() {
    
    cout << "Crating a random full tree of height 2." << endl;
    int height = 2;
    IntTree myFullTree(height);
    
    cout << "Inorder traversal: " << endl;
    myFullTree.print();
    
    cout << "Full tree sideways: " << endl;
    myFullTree.printSideways();

    cout << "Height of the full binary tree is " << myFullTree.height() << endl;

    int val = 8;
    cout << "Does the tree contains the value " << val << "? " << (myFullTree.contains(val) ? "yes" : "no") << endl;

    // Write code to test other methods ...

    return 0;
}
