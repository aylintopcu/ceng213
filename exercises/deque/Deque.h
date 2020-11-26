#ifndef _DEQUE
#define _DEQUE

#include "DequeException.h"
#include <iostream>
using namespace std;

/*
A deque is a data structure consisting of a list of items, on which the following operations are possible:

push(x): Insert item x on the front end of the deque.
pop(): remove the front item from the deque and return it.
inject(x): Insert item x on the back end of the deque.
eject(): Remove the back item from the deque and return it.

Write the implementation of deque using a circular array.
*/


const int MAX_DEQUE = 100;

class Deque {
public:
    Deque();  // default constructor; copy constructor and destructor are supplied by the compiler

    bool isEmpty() const;	// Determines if deque is empty.
    void push(const int& newItem); // Adds an item to the front of a deque.
    int pop();		   // Removes and returns the front item of a deque.
    void inject(const int& newItem); // Adds an item to the back of a deque.
    int eject();      // Removes and returns the back item from the deque.

    bool isFull(); // Determines if deque is full.
    int getFront(); // Return front element of Deque
    int getBack(); // Return rear element of Deque

private:
    int items[MAX_DEQUE];  	// array of items
    int front;         		// index to front of deque
    int back;                // index to back of deque
    int size;
};


Deque::Deque(){// default constructor
   // TODO:
   front = -1;
   back = 0;
   size = 0;
}

bool Deque::isFull() {
    // TODO: 
    return size == MAX_DEQUE - 1;
}

bool Deque::isEmpty() const {
   // TODO: 
    return size == 0;
}

int Deque::getFront() {
    // TODO:
    return items[front];
}

int Deque::getBack() {
    // TODO:
    return items[back];
}

int Deque::pop() {
    // TODO:
    int deleted; 
    
    if (isEmpty())
    {
        throw DequeException("EMPTY");
    }
    else
    {
        deleted = items[front];
        front += 1;
        size--;
    }
    
    return deleted;
}

void Deque::push(const int& newItem) {
    // TODO:
    if (isFull())
    {
        throw DequeException("FULL");
    }
    else
    {
        if (isEmpty()) 
        { 
            front = 0; 
            back = 0; 
        }
        else
        {
            front -= 1;
        }
        
        items[front] = newItem;
        size++;
    }
}


int Deque::eject() {
    // TODO:
    int deleted; 
    
    if (isEmpty())
    {
        throw DequeException("EMPTY");
    }
    else
    {
        deleted = items[back];
        back -= 1;
        size--;
    }
    
    return deleted;
 }

void Deque::inject(const int& newItem) {
    // TODO:
    if (isFull())
    {
        throw DequeException("FULL");
    }
    else
    {
        if (isEmpty()) 
        { 
            front = 0; 
            back = 0; 
        }
        else
        {
            back += 1;
        }
        
        items[back] = newItem;
        size++;
    }
}
#endif // _EXCEPTION

