#ifndef __MAXHEAP_H_
#define __MAXHEAP_H_

#include <vector>
#include <iostream>
#include <stdexcept>

template<class T>
class MaxHeap {
private:
    // contiene los elementos del heap
    std::vector<T> data; 
    // capacidad maxima del heap
    int maxSize;
    // tamaño actual del heap   
    int size;   
    int parent(int i);
    int left(int i);
    int right(int i);

public:
    MaxHeap(int capacity);
    ~MaxHeap();
    bool empty();
    int getCapacity();
    void printMaxHeap();
    void push(T key);
    T top();
    void pop();
    int getSize();
    void sort();
    std::vector<T> getData();

};

template <class T> 
MaxHeap<T>::MaxHeap(int capacity) {
    std::cout << "--->Creando un MaxHeap: " <<  this << std::endl;
    size = 0;
    maxSize = capacity;
    data.resize(maxSize);
}

template <class T> 
MaxHeap<T>::~MaxHeap() {
    std::cout << "--->Liberando memoria del MaxHeap: " <<  this << std::endl;
    data.clear();
}

// Complex: O(1) 
template <class T> 
bool MaxHeap<T>::empty() {
    return (size <= 0);
}

// Complex: O(1) 
template <class T> 
int MaxHeap<T>::getCapacity() {
    return maxSize;
}

// Complex: O(size) 
template <class T> 
void MaxHeap<T>::printMaxHeap() {
    for (int i=0; i < size; i++)
        std::cout << data[i] << " ";
    std::cout << std::endl;
}

// Complex: O(1) 
template <class T> 
int MaxHeap<T>::parent(int i) {
    return (i-1)/2; 
}

// Complex: O(1) 
template <class T> 
int MaxHeap<T>::left(int i) {
    return (2*i + 1); 
}

// Complex: O(1) 
template <class T> 
int MaxHeap<T>::right(int i) {
    return (2*i + 2);
}

// Complex: O(log2(n))
template <class T> 
void MaxHeap<T>::push(T key) {
    if (size == maxSize) {
        throw std::out_of_range("Overflow: no se puede insertar la llave: " + key.getIp());
    }
    // Insertamos la nueva llave al final del vector
    int i = size;
    data[i] = key;
    size++;
    // Reparar las propiedades del max heap si son violadas
    while (i > 0 && data[i] > data[parent(i)]) {
        std::swap(data[i], data[parent(i)]);
        i = parent(i);
    }
}

// Complex: O(1)
template <class T> 
T MaxHeap<T>::top() {
    if (size < 1) {
        throw std::out_of_range("Fila priorizada vacia");
    }
    return data[0];
}

// Complex: O(log2(n))
template <class T> 
void MaxHeap<T>::pop() {
    if (size < 1) {
        throw std::out_of_range("Fila priorizada vacia");
    }
    std::swap(data[0], data[size-1]);
    data.erase(data.begin()+size-1);
    size--;
    int i = 0;
    // Reparar las propiedades del max heap si son violadas
    while (right(i) <= size-1) {
        int hijomay = (data[left(i)]>data[right(i)])? left(i): right(i);
        if(data[hijomay] > data[i]){
            std::swap(data[i], data[hijomay]);
        }
        i = hijomay;
    }

}

// Complex: O(1)
template <class T> 
int MaxHeap<T>::getSize() {
    return size;
}

// Complex: O(1)
template <class T> 
void MaxHeap<T>::sort() {
    int tempsize = size;
    while(tempsize > 0){
        std::swap(data[0], data[tempsize-1]);
        tempsize--;
        int i = 0;
        while (right(i) <= tempsize-1) {
            int hijomay = (data[left(i)]>data[right(i)])? left(i): right(i);
            if(data[hijomay] > data[i]){
                std::swap(data[i], data[hijomay]);
            }
            i = hijomay;
        }
    }
}

// Get data values. Complex: O(1)
template<class T>
std::vector<T> MaxHeap<T>::getData(){
    return data;
}


#endif // __MAXHEAP_H_