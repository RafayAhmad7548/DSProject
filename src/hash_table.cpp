#include <hash_table.hpp>

template<typename K, typename V>
HashNode<K, V>::HashNode(K key, V value) : key(key), value(value){}

template<typename K, typename V>
HashTable<K, V>::HashTable() {
    tablesize = 10;
    count = 0;
    table = new HashNode<K, V>*[tablesize];
    for(int i = 0; i < tablesize; i++){
        table[i] = nullptr;
    }
}

template<typename K, typename V>
int HashTable<K, V>::hashFunction(K key){
    return key % tablesize;
}

template<typename K, typename V>
void HashTable<K, V>::resize(){
    int oldSize = tablesize;
    tablesize += 10;
    HashNode<K, V>** newTable = new HashNode<K, V>*[tablesize];
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

template<typename K, typename V>
void HashTable<K, V>::insert(K key, V value) {
    int hash = hashFunction(key);
    if (table[hash] != nullptr) {
        resize();
        hash = hashFunction(key);
    }
    HashNode<K, V>* newNode = new HashNode(key, value);
    table[hash] = newNode;
    count++;
}

template<typename K, typename V>
HashNode<K, V>*& HashTable<K, V>::get(K key) {
    int hash = hashFunction(key);
    return table[hash];
}

template<typename K, typename V>
void HashTable<K, V>::remove(K key) {
    HashNode<K, V>*& temp = get(key);
    delete temp;
    temp = nullptr;
    count--;
}

template<typename K, typename V>
K* HashTable<K, V>::getKeySet(){
    K* arr = new K[count];
    for(int i=0, j=0;i<tablesize;i++){
        if(table[i] != nullptr){
            arr[j] = table[i]->key;
            j++;
        }
    }
    return arr;
}

template<typename K, typename V>
HashTable<K, V>::~HashTable() {
    for (int i = 0; i < tablesize; i++) {
        delete table[i];
    }
    delete[] table;
}