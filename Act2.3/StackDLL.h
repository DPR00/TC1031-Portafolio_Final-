#ifndef _STACKLL_H_
#define _STACKLL_H_

#include <climits>
#include "StackNode.h"

template <class T>
class StackDLL {
    private:
    StackNode<T>* top;
    int numElements;

    public:
    StackDLL();
    ~StackDLL();
    int getNumElements();
    void printStack();

    void push(T value);
    T pop();
    T getTop();
    bool isEmpty();

};

template<class T>
StackDLL<T>::StackDLL() {
    // std::cout << "--->Creando un Stack vacio: " <<  this << std::endl;
    top = NULL;
    numElements = 0;
}

template<class T>
StackDLL<T>::~StackDLL() {
    //std::cout << "--->Liberando memoria del stack: " << this << std::endl;
    StackNode<T> *p, *q;
    p = top;
    while (p != NULL) {
        q = p->next;
        delete p;
        p = q;
    }
    top = NULL;
    numElements = 0;
}

template<class T>
int StackDLL<T>::getNumElements() {
    return numElements;
}

template<class T>
void StackDLL<T>::printStack() {
    StackNode<T> *ptr = top;
    while (ptr != NULL) {
        std::cout << ptr->data << " ";
        ptr = ptr->next;
    }
    std::cout << std::endl;
}

template<class T>
void StackDLL<T>::push(T value) {
    StackNode<T> *newNode = new StackNode<T>(value);
    newNode->next = top;
    top = newNode;
    numElements++;
}

template<class T>
T StackDLL<T>::pop() {
    T value;
    if (top != NULL) {
        StackNode<T> *p = top;
        value = top->data;
        top = p->next;
        delete p;
        numElements--;
    }
    return value;
}

template<class T>
T StackDLL<T>::getTop() {
    T value = -1;
    if (top != NULL) {
        value = top->data;
    }
    return value;
}

template<class T>
bool StackDLL<T>::isEmpty() {
    bool result = false;
    if (top == NULL)
        result = true;
    return result;
}
#endif // _STACKLL_H_