#ifndef LINKEDLIST_H
#define LINKEDLIST_H


#include <iostream>

#include "Node.h"

template<class T>
class LinkedList {
public: // DO NOT CHANGE THIS PART.
    LinkedList();
    LinkedList(const T arr[], int arrSize);
    LinkedList(const LinkedList<T> &obj);

    ~LinkedList();

    Node<T> *getFirstNode() const;
    Node<T> *getLastNode() const;
    Node<T> *getNode(const T &data) const;

    int getNumberOfNodes() const;
    bool isEmpty() const;
    bool contains(Node<T> *node) const;

    void insertAtTheHead(const T &data);
    void insertAtTheTail(const T &data);
    void insertSorted(const T &data);

    void removeNode(Node<T> *node);
    void removeNode(const T &data);
    void removeAllNodes();

    void print() const;

    T *toArray() const;

    LinkedList<T> &operator=(const LinkedList<T> &rhs);

private: // YOU MAY ADD YOUR OWN UTILITY MEMBER FUNCTIONS HERE.

private: // DO NOT CHANGE THIS PART.
    Node<T> *head;
    Node<T> *tail;
};

template<class T>
LinkedList<T>::LinkedList() {
    /* TODO */
    head = NULL;
    tail = NULL;
}

template<class T>
LinkedList<T>::LinkedList(const T arr[], int arrSize) {
    /* TODO */
    head = NULL;
    tail = NULL;
    
    int i;
    
    for (i = 0; i < arrSize; i++)
    {
        if (i == 0)
        {
            insertAtTheHead(arr[0]);
        }
        else
        {
            insertAtTheTail(arr[i]);
        }
    }
}

template<class T>
LinkedList<T>::LinkedList(const LinkedList<T> &obj) {
    /* TODO */
    head = NULL;
    tail = NULL;
    
    if (obj.head)
    {
        *this = obj;
    }
}

template<class T>
LinkedList<T>::~LinkedList() {
    /* TODO */
    removeAllNodes();
}

template<class T>
Node<T> *LinkedList<T>::getFirstNode() const {
    /* TODO */
    return head;
}

template<class T>
Node<T> *LinkedList<T>::getLastNode() const {
    /* TODO */
    return tail;
}

template<class T>
Node<T> *LinkedList<T>::getNode(const T &data) const {
    /* TODO */
    Node<T> *temp = head;
    
    while (temp)
    {
        if (temp->data == data)
        {
            return temp;
        }
        temp = temp->next;
    }
    return NULL;
}

template<class T>
int LinkedList<T>::getNumberOfNodes() const {
    /* TODO */
    int num_of_nodes = 0;
    Node<T> *temp = head;
    
    while (temp)
    {
        num_of_nodes++;
        temp = temp->next;
    }
    
    return num_of_nodes;
}

template<class T>
bool LinkedList<T>::isEmpty() const {
    /* TODO */
    if (head)
    {
        return false;
    }
    return true;
}

template<class T>
bool LinkedList<T>::contains(Node<T> *node) const {
    /* TODO */
    Node<T> *temp = head;
    
    while (temp)
    {
        if (temp == node)
        {
            return true;
        }
        temp = temp->next;
    }
    return false;
}

template<class T>
void LinkedList<T>::insertAtTheHead(const T &data) {
    /* TODO */
    Node<T> *node = new Node<T>(data, NULL, head);
    
    if (!isEmpty())
    {
        head->prev = node;
    }
    else
    {
        tail = node;
    }
    head = node;
}

template<class T>
void LinkedList<T>::insertAtTheTail(const T &data) {
    /* TODO */
    Node<T> *node = new Node<T>(data, tail, NULL);
    
    if (!isEmpty())
    {
        tail->next = node;
    }
    else
    {
        head = node;
    }
    tail = node;
}

template<class T>
void LinkedList<T>::insertSorted(const T &data) {
    /* TODO */
    if (head == NULL || head->data >= data)
    {
        insertAtTheHead(data);
    }
    else
    {
        Node<T> *temp = head;
        
        while (temp->next && temp->next->data < data)
        {
            temp = temp->next;
        }
        temp->next = new Node<T>(data, temp, temp->next);
        temp->next->next->prev = temp->next;
    }
}

template<class T>
void LinkedList<T>::removeNode(Node<T> *node) {
    /* TODO */
    if (node && !isEmpty() && contains(node))
    {
        if (getNumberOfNodes() == 1)
        {
            head = NULL;
            tail = NULL;
        }
        else if (head == node)
        {
            head = head->next;
            head->prev = NULL;
        }
        else if (tail == node)
        {
            tail = tail->prev;
            tail->next = NULL;
        }
        else
        {
            node->prev->next = node->next;
            node->next->prev = node->prev;
        }
        node->next = NULL;
        node->prev = NULL;
        delete node;
    }
}

template<class T>
void LinkedList<T>::removeNode(const T &data) {
    /* TODO */ 
    Node<T> *temp = head;
    
    while (temp)
    {
        if (temp->data == data)
        {
            removeNode(temp);
            break;
        }
        temp = temp->next;
    }
}

template<class T>
void LinkedList<T>::removeAllNodes() {
    /* TODO */
    Node<T> *temp = head;
    
    while (!isEmpty())
    {
        head = head->next;
        delete temp;
        temp = head;
    }
    head = NULL;
    tail = NULL;
}

template<class T>
void LinkedList<T>::print() const {
    std::cout << "Printing the linked list ..." << std::endl;

    if (this->isEmpty()) {
        std::cout << "empty" << std::endl;
        return;
    }

    Node<T> *node = this->head;

    while (node) {
        std::cout << *node << std::endl;
        node = node->next;
    }
}

template<class T>
T *LinkedList<T>::toArray() const {
    /* TODO */
    int size = getNumberOfNodes(), index = 0;
    
    if (size == 0)
    {
        return NULL;
    }
    
    T *array = new T[size];
    Node<T> *temp = head;
    
    while (temp)
    {
        array[index] = temp->data;
        temp = temp->next;
        index++;
    }
    return array;
}

template<class T>
LinkedList<T> &LinkedList<T>::operator=(const LinkedList<T> &rhs) {
    /* TODO */
    if (rhs.head)
    {
        if (this != &rhs)
        {
            removeAllNodes();
            insertAtTheHead(rhs.head->data);
            
            Node<T> *rhs_temp = rhs.head->next;
            
            while (rhs_temp)
            {
                insertAtTheTail(rhs_temp->data);
                rhs_temp = rhs_temp->next;
            }
        }
    }
    else
    {
        removeAllNodes();
    }
    return *this;
}


#endif //LINKEDLIST_H
