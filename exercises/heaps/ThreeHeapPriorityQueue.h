#ifndef THREEHEAPPRIORITYQUEUE_H
#define THREEHEAPPRIORITYQUEUE_H

#include <iostream>
#include <vector>

#include "UnderflowException.h"

using namespace std;

/* TODO : Q5 */
/* Modify the HeapPriorityQueue class to make it into a three-heap.
 * A three-heap is similar to a binary heap, except that each node is
 * considered to have three children rather than two children.
 * A three-heap is a wider tree though not as tall as a binary heap.
 * The heap can still be represented as an array, but the algorithms for
 * traversing it must be modified to consider all three children
 * when bubbling as appropriate.
 */

template <class T>
class ThreeHeapPriorityQueue {
public:
    // Public member functions:

    ThreeHeapPriorityQueue(int capacity = 100);

    bool isEmpty() const;

    const T& peek() const;

    void add(const T &x);

    T remove();

    void print();

private:
    // Private member variables:

    int theSize;    // Number of elements in heap.
    vector<T> arr;  // The heap array.

    // Private member functions:

    void buildHeap();

    void bubbleDown(int hole);
};

/* TODO : Q5 */
template <class T>
ThreeHeapPriorityQueue<T>::ThreeHeapPriorityQueue(int c) {
    theSize = 0;
    arr.push_back(0);
}

/* TODO : Q5 */
template <class T>
bool ThreeHeapPriorityQueue<T>::isEmpty() const {
    return theSize == 0;
}

/* TODO : Q5 */
template <class T>
const T& ThreeHeapPriorityQueue<T>::peek() const {
    return arr[0];
}

/* TODO : Q5 */
template <class T>
void ThreeHeapPriorityQueue<T>::add(const T &x) {
    if (theSize == ((int) arr.size()))
        arr.resize(arr.size() * 3);

    // Percolate up
    theSize++;
    int hole = theSize - 1;
    for( ; hole > 0 && x < arr[(hole - 1) / 3]; hole = (hole - 1) / 3)
        arr[hole] = arr[(hole - 1) / 3];
    arr[hole] = x;
}

/* TODO : Q5 */
template <class T>
T ThreeHeapPriorityQueue<T>::remove() {
    if(isEmpty())
        throw UnderflowException( );

    T tmp = arr[0];
    arr[0] = arr[theSize];
    theSize--;
    bubbleDown(0);
    return tmp;
}

/* TODO : Q5 */
template <class T>
void ThreeHeapPriorityQueue<T>::bubbleDown(int hole) {
    int child;
    T tmp = arr[hole];

    for( ; hole * 3 + 1 < theSize; hole = child) {
        child = hole * 3 + 1;
        if(child != theSize - 1 && arr[child + 1] < arr[child])
            child++;
        if(child != theSize - 1 && arr[child + 1] < arr[child])
            child++;
        if(arr[child] < tmp)
            arr[hole] = arr[child];
        else
            break;
    }
    arr[hole] = tmp;
}

/* TODO : Q5 */
template <class T>
void ThreeHeapPriorityQueue<T>::buildHeap() {
    for(int i = (theSize - 2) / 3; i > 0; --i)
        bubbleDown(i);
}

/* TODO : Q5 */
template <class T>
void ThreeHeapPriorityQueue<T>::print() {
    for(int i = 0; i < theSize; ++i)
        cout << arr[i] << " " ;
    cout << endl;
}

#endif //THREEHEAPPRIORITYQUEUE_H
