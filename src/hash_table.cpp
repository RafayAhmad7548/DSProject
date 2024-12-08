#include "hash_table.hpp"
#include "graph.hpp"

template<>
void HashTable<char, LinkList<Edge<char>>>::remove(char key){
    HashNode<char, LinkList<Edge<char>>>*& temp = get(key);
    delete temp;
    temp = nullptr;
    count--;
    for(int i=0;i<tablesize;i++){
        if(table[i] != nullptr){
            table[i]->value.deletevalue(key);
        }
    }
}