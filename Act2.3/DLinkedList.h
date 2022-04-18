#ifndef _DLINKEDLIST_H_
#define _DLINKEDLIST_H_

#include <stdexcept>
#include "DLLNode.h"
#include "StackDLL.h"

using std::cout;
using std::endl;
using std::out_of_range;

template <class T>
class DLinkedList {
    private:
      DLLNode<T> *head;
      DLLNode<T> *tail;
      int numElements;

    public:
      DLinkedList();
      ~DLinkedList();
      int getNumElements();
      void printList();
      void printLastNode();
      void addFirst(T value);
      void addLast(T value);
      bool deleteData(T value);
      bool deleteAt(int position);
      T getData(int position);
      void clear();
      int findRegistro(time_t date);
      void sort();
      DLinkedList<T> getReversedSublist(int inicio, int fin);
      int getNumSublist(DLLNode<T>* inicio, DLLNode<T>* fin);
      void swap(T &val1, T &val2);
      DLLNode<T>* partition(DLLNode<T> *low, DLLNode<T> *high);
      void quickSort(DLLNode<T> *low, DLLNode<T> *high);
      T& operator [](const int&);
      
};

template<class T>
DLinkedList<T>::DLinkedList() {
    // cout << "--->Creando una lista vacia" << endl;
    head = nullptr;
    tail = nullptr;
    numElements = 0;
}

template<class T>
DLinkedList<T>::~DLinkedList() {
    // cout << "--->Liberando memoria de la lista ligada" << endl;
  DLLNode<T> *p, *q;
  p = head;
  while (p != nullptr) {
    q = p->next;
    delete p;
    p = q;
  }
  head = nullptr;
  tail = nullptr;
  numElements = 0;
}

//getNumElements
template<class T>
int DLinkedList<T>::getNumElements() {
  return numElements;
}

//printList
template<class T>
void DLinkedList<T>::printList() {
  DLLNode<T> *ptr = head;
  while (ptr != nullptr) {
      cout << ptr->data << " ";
      ptr = ptr->next;
  }
  cout << endl;
}

//printLastNode
template<class T>
void DLinkedList<T>::printLastNode() {
  cout << tail->data << endl;
}

//addFirst
template<class T>
void DLinkedList<T>::addFirst(T value) {
  DLLNode<T> *newDLLNode = new DLLNode<T>(value);
  // Si la lista está vacia
  if (head == nullptr && tail == nullptr) {
    head = newDLLNode;
    tail = newDLLNode;
  }
  else {
    newDLLNode->next = head;
    head->prev = newDLLNode;
    head = newDLLNode;
  }
  numElements++;
}

//addLast
template<class T>
void DLinkedList<T>::addLast(T value) {
  if (head == nullptr && tail == nullptr) {
    addFirst(value);
  }
  else {
    DLLNode<T> *newDLLNode = new DLLNode<T>(value);
    tail->next = newDLLNode;
    newDLLNode->prev = tail; 
    tail = newDLLNode;
    numElements++;
  }
}

//deleteData
template<class T>
bool DLinkedList<T>::deleteData(T value) {
  // Si la lista esta vacia 
  if (head == nullptr && tail == nullptr) {
    return false;
  }
  else {
    DLLNode<T> *p, *q;
    p = head;
    q = nullptr;
    // buscar value en la lista
    while (p != nullptr && p->data != value) {
      q = p;
      p = p->next;
    }
    // Si no existe value en la lista
    if (p == nullptr)
      return false;
    // Si debe borrarse el primer elemento
    if (p->prev == nullptr) {
      head = p->next;
      if (head != nullptr)
        head->prev = nullptr;
    }
    else if (p->next == nullptr) { 
      // Si debe borrarse el último elemento
      q->next = nullptr;
      tail = q;
    }
    else {
      // Cualquier otro elemento entre la lista 
      q->next = p->next;
      p->next->prev = q;
    }
    delete p;
    numElements--;
    return true;
  }
}

//deleteAt
template<class T>
bool DLinkedList<T>::deleteAt(int position) {
  if (position < 0 || position >= numElements) {
    throw out_of_range("Indice fuera de rango");
  }
  else if (position == 0) { // Si debe borrarse el primer elemento
    DLLNode<T> *p = head;
    // Si la lista contiene solo un nodo
    if (head != nullptr && head->next == nullptr) {
      head = tail = nullptr;  
    }
    else {
      head = p->next;
      head->prev = nullptr;
    }
    delete p;
    numElements--;
    return true; 
  }
  else { // Si la lista contiene mas de un nodo
    DLLNode<T> *p = head, *q = nullptr;
    int index = 0;
    // Se busca el indice del elemento a borrar
    while (index != position) {
      q = p;
      p = p->next;
      index++;
    }
    // Si debe borrarse el último elemento
    if (p->next == nullptr) {
      q->next = nullptr;
      tail = q;
    }
    else { // Cualquier otro elemento en medio de la lista 
      q->next = p->next;
      p->next->prev = q;
    }
    delete p;
    numElements--;
    return true;
  }
}

//getData
template<class T>
T DLinkedList<T>::getData(int position) {
  if (position < 0 || position >= numElements) {
    throw out_of_range("Indice fuera de rango");
  }
  else {
    if (position == 0)
      return head->data;
    DLLNode<T> *p = head;
    int index = 0;
    while (p != nullptr) {
      if (index == position)
        return p->data;
      index++;
      p = p->next;
    }
    //return -1;
  }
}

// clear
template<class T>
void DLinkedList<T>::clear(){

  if (head == nullptr && tail == nullptr) {
    cout << "Lista vacia ..." << endl;
  }
  else{
    DLLNode<T> *p, *q;

    q = head;
    p = head->next;
    while (p->next!=nullptr){
      DLLNode<T> *temp = p;
      q-> next = p->next;
      p->next->prev = q;
      delete temp;
      numElements--;
      p = q->next;
    }
    head = nullptr;
    tail = nullptr;
    delete head;
    numElements--;
    delete tail;
    numElements--;
  }
}

// getNumElements from a sublist
template<class T>
int DLinkedList<T>::getNumSublist(DLLNode<T>* start, DLLNode<T>* end) {
    int num = -1;
    DLLNode<T> *p = start;
    if (start != NULL && end != NULL) { 
      num = 1;
      while (p != NULL) {
        if (p == end) break;
        p = p->next;
        num++;
      }
    }
    return num;
}

// sort
template<class T>
void DLinkedList<T>::swap(T &val1, T &val2) {
  T temp = val1;
  val1 = val2;
  val2 = temp;
}

// partiton for iterative quick sort
template<class T>
DLLNode<T>* DLinkedList<T>::partition(DLLNode<T> *low, DLLNode<T> *high){

  if(high != NULL && low != high && low != high->next){
    T pivot = high->data;
    DLLNode<T> *i = low->prev;
    for(DLLNode<T> *j = low; j!= high; j = j->next){
      if((j->data).getDate() <= (pivot).getDate()){
        if(i == NULL) i=low;
        else i = i->next;
        swap(i->data, j->data);
      }
    }
    if(i == NULL) i=low;
    else i = i->next;  
    swap(i->data, high->data);
    return i;
  }
  else{
    return NULL;
  }
}

// iterative quicksort
template<class T>
void DLinkedList<T>::quickSort(DLLNode<T> *low, DLLNode<T> *high) {
  StackDLL<DLLNode<T>*> stack;
  low = head;
  high = tail;
  stack.push(low);
  stack.push(high);
  while (!stack.isEmpty()) {
    high = stack.pop();
    low = stack.pop();
    DLLNode<T>* pivot = partition(low, high);
    if (pivot != NULL) {
      // Si hay elementos en la parte izquierda de la particion
      if (getNumSublist(low, pivot->prev) > 1) {
        stack.push(low);
        stack.push(pivot->prev);
      }
      // Si hay elementos en la parte derecha de la particion
      if (getNumSublist(pivot->next, high) > 1) {
        stack.push(pivot->next);
        stack.push(high);
      }
    }
  }
}

/* =========== sort ===============
* Descrition: Function that SORT registers
* in a double linked list of registers using
* the iterative quick sort algorithm.
* - Complex: O(n*log(n)) average and O(n^2) worst
*/template<class T>
void DLinkedList<T>::sort(){
  quickSort(head, tail);
}

// Overload operator []
template<class T>
T& DLinkedList<T>::operator[](const int &position) {
    DLLNode<T> *p = head;
    if(position == 0) return p->data;
    else{
        int index = 0;
        // Buscar value en la lista
        while (p != nullptr){
            if (index == position){
                return p->data;
                break;
            }
            index++;
            p = p->next;
        }
        // Si value no existe en la lista
        if (p == nullptr) throw out_of_range("Posicion fuera de los limites de la lista");
    }
}

/* =========== FIND REGISTRO ===============
* Descrition: Function that FIND registers
* in a vector of registers using the binary
* search.
* - Complex: O(log2(n))
*/
template<class T>
int DLinkedList<T>::findRegistro(time_t date){

  int low = 0;
  int high = getNumElements() - 1;

  while (low <= high) {
    int m = low + (high - low) / 2;
    if (date == (getData(m)).getDate()) return m; // Sobrecarga de operador
    else if (date < (getData(m)).getDate()) 
      high = m - 1;
    else 
      low = m + 1;
  }
  return -1;
}

#endif // _DLINKEDLIST_H_