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

// Funcion empty():
//   Verifica si el Heap esta vacio.
// Complex: O(1) 
template <class T> 
bool MaxHeap<T>::empty() {
    return (size <= 0);
}

// Funcion getCapacity():
//   Devuelve la capacidad maxima del heap.
// Complex: O(1) 
template <class T> 
int MaxHeap<T>::getCapacity() {
    return maxSize;
}

// Funcion printMaxHeap():
//   Imprime el Heap como vector.
// Complex: O(size) 
template <class T> 
void MaxHeap<T>::printMaxHeap() {
    for (int i=0; i < size; i++)
        std::cout << data[i] << " ";
    std::cout << std::endl;
}

// Funcion parent():
//   Devuelve el index del nodo padre.
// Complex: O(1) 
template <class T> 
int MaxHeap<T>::parent(int i) {
    return (i-1)/2; 
}

// Funcion left():
//   Devuelve el index del hijo de la izquierda.
// Complex: O(1) 
template <class T> 
int MaxHeap<T>::left(int i) {
    return (2*i + 1); 
}

// Funcion right():
//   Devuelve el index del hijo de la derecha.
// Complex: O(1) 
template <class T> 
int MaxHeap<T>::right(int i) {
    return (2*i + 2);
}

// Funcion push():
//   Agrega un valor en el MaxHeap
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

// Funcion top():
//   Devuelve el valor del nodo raiz
// Complex: O(1)
template <class T> 
T MaxHeap<T>::top() {
    if (size < 1) {
        throw std::out_of_range("Fila priorizada vacia");
    }
    return data[0];
}

// Funcion pop():
// Elimina el valor del nodo raiz.
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

// Funcion getSize():
//   Devuelve el tamaño actual del MaxHeap
// Complex: O(1)
template <class T> 
int MaxHeap<T>::getSize() {
    return size;
}


// Funcion sort():
//   Ordena los elementos del MAxHeap con el agoritmo HeapSort.
// Complex: O(nlog(n))
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

// Funcion getData():
//   Devuelve los datos del Heap como vector.
// Complex: O(1)
template<class T>
std::vector<T> MaxHeap<T>::getData(){
    return data;
}


#endif // __MAXHEAP_H_