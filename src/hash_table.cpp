#include <hash_table.hpp>
#include "linklist.hpp"

// template <typename T>
// T :: Tv){
//     value = v; 
// }
template <typename T>
HashTable<T>::HashTable() {
    tablesize = 10;
    count = 0;
    table = new T*[tablesize];
    for(int i = 0; i < tablesize; i++)
        table[i] = nullptr;
}

template<>
int HashTable<LinkList<char>>::hashFunction(LinkList<char> key){
    return key.head->value % tablesize;
}

template <typename T>
int HashTable<T> :: hashFunction(T key){
    return key % tablesize;
}

template <typename T>
void HashTable<T> :: resize(){
    int oldSize = tablesize;
    tablesize += 10;
    T** newTable = new T*[tablesize];
    for(int i = 0; i < tablesize; i++){
        newTable[i] = nullptr;
    }
    for(int i = 0; i < oldSize; i++){
        newTable[i] = table[i];
        delete table[i];
    }
    delete[] table;
    table = newTable;
}
template <typename T>
void HashTable<T> :: insert(T key) {
    int hash = hashFunction(key);
    if (table[hash] != nullptr) {
        resize();
        hash = hashFunction(key);
    }
    T* newNode = new T();
    table[hash] = newNode;
    count++;
}

template <typename T>
T*& HashTable<T> :: search(T key) {
    int hash = hashFunction(key);
    return table[hash];
}

template <typename T>
void HashTable<T> :: remove(T key) {
    T* temp = search(key);
    delete temp;
    temp = nullptr;
}

template <typename T>
HashTable<T> :: ~HashTable() {
    for (int i = 0; i < tablesize; i++) {
        delete table[i];
    }
    delete[] table;
}