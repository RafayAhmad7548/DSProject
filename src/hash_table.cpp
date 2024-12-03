#include <hash_table.h>

template <typename T>
HashNode<T> :: HashNode(T v){
    value = v; 
}

template <typename T>
int HashTable<T> :: hashFunction(T key){
        return key % tablesize;
    }

template <typename T>
HashTable<T>::HashTable() {
    tablesize = 10;
    count = 0;
    table = new HashNode<T>*[tablesize];
    for(int i = 0; i < tablesize; i++)
        table[i] = nullptr;
}

template <typename T>
void HashTable<T> :: resize(){
    int oldSize = tablesize;
    tablesize += 10;
    HashNode<T>** newTable = new HashNode<T>*[tablesize];
    for(int i = 0; i < tablesize; i++){
        newTable[i] = nullptr;
    }
    for(int i = 0; i < oldSize; i++){
        HashNode<T>* node = table[i];
        delete table[i];
    }
    delete[] table;
    table = newTable;
}
template <typename T>
void HashTable<T> :: insert(T value) {
    int hash = hashFunction(value);
    if (table[hash] != nullptr) {
        resize();
        hash = hashFunction(value);
    }
    HashNode<T>* newNode = new HashNode<T>(value);
    //newNode->next = table[hash];
    table[hash] = newNode;
    count++;
}

template <typename T>
HashNode<T>*& HashTable<T> :: search(T key) {
        int hash = hashFunction(key);
        return table[hash];
    }

template <typename T>
void HashTable<T> :: remove(T key) {
        HashNode<T>* temp = search(key);
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