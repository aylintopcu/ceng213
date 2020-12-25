#include <iostream>

#include "heap_functions.h"
#include "HeapPriorityQueue.h"

using namespace std;

int main() {
    
    cout << "Crating a heap and populating it with a list of numbers." << endl;
    HeapPriorityQueue<int> heap;
    int numbers[] = {42, 17, 9, 42, 35, -1, 88};
    for(int i = 0; i < 7; i++) {
        heap.add(numbers[i]);
        cout << "Adding the number " << numbers[i] << " to the heap." << endl;
    }

    cout << "Peek: " << heap.peek() << endl;
    
    cout << "Removing numbers until the heap gets empty: ";
    while(!heap.isEmpty()) {
        cout << heap.remove() << " ";
    }
    cout << endl;
    
    return 0;
}
