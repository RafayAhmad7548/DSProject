#ifndef HASHTABLE_HPP
#define HASHTABLE_HPP

#include "linklist.hpp"

template<typename K, typename V>
class HashNode{
public:
    K key;
    V value;
    HashNode(K key, V value);
};

template <typename K, typename V>
class HashTable {
    int tablesize;
    HashNode<K, V>** table;
    
    int hashFunction(K key);
    void resize();
public:
    int count;
    HashTable();
    ~HashTable();
    
    void insert(K key, V val);
    HashNode<K, V>*& get(K key);
    void remove(K key);

};

template class HashTable<char, LinkList<char>>;

#endif // HASHTABLE_HPP