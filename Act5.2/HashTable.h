#ifndef __HASH_TABLE_H_
#define __HASH_TABLE_H_

#include <iostream>
#include <vector>
#include <stdexcept>
#include "HashNode.h"

template<class K, class T>
class HashTable {
  private:
    std::vector<HashNode<K,T>> table;
    int size;
    int maxSize; // preferible un numero primo
    int collisions;

  public:
    HashTable(int selectedMaxSize);
    int getHashIndex(K keyVal);
    int getHashIndexInt(int keyVal);
    int getSize();
    void print();
    void add(K keyVal, T value);
    int find(K keyVal);
    int getNumCollisions();
    T getDataAt(int index);
    void remove(K keyVal);
    T getIPSummary(K keyVal);

};

// Constructor function
template<class K, class T>
HashTable<K, T>::HashTable(int selectedMaxSize) {
  maxSize = selectedMaxSize;
  size = 0;
  collisions = 0;
  table = std::vector<HashNode<K,T>>(maxSize);
}

// Function to get the hash index when the parameter is string
// Complex: O(1). The loop has only 3 iterations.
// Own source (Trial and error prove)
template<class K, class T>
int HashTable<K, T>::getHashIndex(K keyVal) {
  if(typeid(keyVal) == typeid(string)){
    string delimiter = ".";
    size_t pos = 0;
    string token;
    int suma=0;
    string tempKey = keyVal;
    while ((pos = tempKey.find(delimiter)) != string::npos) {
        token = tempKey.substr(0, pos);
        suma += stoi(token);
        tempKey.erase(0, pos + delimiter.length());
    }
    suma *= stoi(tempKey);
    return suma%maxSize;
  }
}

// Function to get the hash index when the parameter is int
// Complex: O(1). The loop has only 3 iterations.
template<class K, class T>
int HashTable<K, T>::getHashIndexInt(int keyVal) {
  return keyVal%maxSize;
}

// Function to get the size of the Hash Table.
// Complex: O(1). The loop has only 3 iterations.
template<class K, class T>
int HashTable<K, T>::getSize() {
  return size;
}

// Function to print the Hash Table
// Complex: O(n).
template<class K, class T>
void HashTable<K,T>::print() {
  std::cout << "Content of the hash table: " << std::endl;
  for (int i = 0; i < maxSize; i++) {
    // status:  0 empty, 1 used, 2 deleted
    if (table[i].getStatus() == 1) // Cell is used
      std::cout << "Cell: " << i << " Key: " << table[i].getKey() << ", Value: " << table[i].getData() << ", Overflow.size: " << table[i].getOverflowSize() << std::endl;
  }
}

// Function to add a new value in the Hash Table
// Complex: O(n*k).
template<class K, class T>
void HashTable<K,T>::add(K keyVal, T value) {
  if (size == maxSize) {
    throw std::out_of_range("Hash Table is full");
  }
  // Compute the index of the table using a key and a hash function
  int hashVal = getHashIndex(keyVal); 
  HashNode<K, T> node = table[hashVal];
  // status:  0 empty, 1 used, 2 deleted
  if (node.getStatus() != 1) { // Cell is free
    node.setKey(keyVal);
    node.setData(value);
    table[hashVal] = node;
  }
  else { // Cell is already taken
    // Find next free space using quadratic probing
    // https://www.geeksforgeeks.org/quadratic-probing-in-hashing/
    int i = 1;
    int currentHashVal = getHashIndexInt(hashVal + i * i);
    HashNode<K, T> currentNode = table[currentHashVal];
    while (currentNode.getStatus() == 1) { // Cell is used
      i++;
      currentHashVal = getHashIndexInt(hashVal + i * i);
      currentNode = table[currentHashVal];
      collisions += currentNode.getOverflowSize();  
    }
    // A free cell was found
    currentNode.setKey(keyVal);
    currentNode.setData(value);
    node.addToOverflow(currentHashVal);
    table[currentHashVal] = currentNode;
    table[hashVal] = node;
  }
  size++;
}  

// Function to find a value in the hash table
// Complex: O(k), where k is number of collision
template<class K, class T>
int HashTable<K,T>::find(K keyVal) {
  int hashVal = getHashIndex(keyVal); 
  HashNode<K, T> node = table[hashVal];
  // status:  0 empty, 1 used, 2 deleted
  if (node.getStatus() == 1) { // Cell is used
    if (node.getKey() == keyVal) {
      return hashVal;
    }
    for (int i = 0; i < node.getOverflowSize(); i++) {
      int overflowIndex = node.getOverflowAt(i);
      if (table[overflowIndex].getKey() == keyVal) {
        return overflowIndex;
      }
    }
    return -1;
  }
  return -1;
}

// Function to get the number of collisions
// Complex: O(1).
template<class K, class T>
int HashTable<K,T>::getNumCollisions() {
  return collisions;
}

// Function to get the data at certain position.
// Complex: O(1).
template<class K, class T>
T HashTable<K,T>::getDataAt(int index) {
  return table[index].getData();
}

// Function to remove an element in the Hash.
// Complex: O(k).
template<class K, class T>
void HashTable<K,T>::remove(K keyVal) {
  int pos, hashVal;
  pos = find(keyVal);
  if (pos == -1) {
    throw std::invalid_argument("Element does not exist in hash table");
  }
  hashVal = getHashIndex(keyVal);
  if (pos != hashVal) {
    HashNode<K, T> node = table[hashVal];
    node.removeFromOverflow(pos);
    table[hashVal] = node;
  }
  table[pos].clearData(); 
}


// Function to get the summary of an IP
// Complex: O(k), where k is number of collision
template<class K, class T>
T HashTable<K,T>::getIPSummary(K keyVal) {

  int idx = find(keyVal);
  if(idx != -1){
    T data = getDataAt(idx);
    return data;
  }
  else{
    return {};
  }

}


#endif // __HASH_TABLE_H_