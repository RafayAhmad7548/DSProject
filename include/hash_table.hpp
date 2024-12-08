#ifndef HASHTABLE_HPP
#define HASHTABLE_HPP

#include "linklist.hpp"
#include <QPoint>

template<typename K, typename V>
class HashNode{
public:
    K key;
    V value;
    QPoint center;
    int signalTime;
    int curSignalTime;
    bool signalState;
    HashNode(K key, V value) : key(key), value(value), signalState(true){}
};

template <typename K, typename V>
class HashTable {
    int tablesize;
    HashNode<K, V>** table;
    
    void resize(){
        int oldSize = tablesize;
        tablesize += 10;
        HashNode<K, V>** newTable = new HashNode<K, V>*[tablesize];
        for(int i = 0; i < tablesize; i++){
            newTable[i] = nullptr;
        }
        for(int i = 0; i < oldSize; i++){
            if(table[i] != nullptr){
                int hash = hashFunction(table[i]->key);
                newTable[hash] = table[i];
            }
        }
        delete[] table;
        table = newTable;
    }
public:
    int count;

    HashTable(){
        tablesize = 10;
        count = 0;
        table = new HashNode<K, V>*[tablesize];
        for(int i = 0; i < tablesize; i++){
            table[i] = nullptr;
        }
    }
    ~HashTable(){
        for (int i = 0; i < tablesize; i++) {
            delete table[i];
        }
        delete[] table;
    }
    
    int hashFunction(K key){
        return key % tablesize;
    }

    void insert(K key, V val){
        if(count == tablesize-1) resize();
        int hash = hashFunction(key);
        while (table[hash] != nullptr) {
            resize();
            hash = hashFunction(key);
        }
        HashNode<K, V>* newNode = new HashNode(key, val);
        table[hash] = newNode;
        count++;
    }

    HashNode<K, V>*& get(K key){
        int hash = hashFunction(key);
        return table[hash];
    }

    void remove(K key){
        HashNode<K, V>*& temp = get(key);
        delete temp;
        temp = nullptr;
        count--;
    }


    K* getKeySet(){
        K* arr = new K[count];
        for(int i=0, j=0;i<tablesize;i++){
            if(table[i] != nullptr){
                arr[j] = table[i]->key;
                j++;
            }
        }
        return arr;
    }

};

template<>
void HashTable<char, LinkList<char>>::remove(char key);


#endif // HASHTABLE_HPP