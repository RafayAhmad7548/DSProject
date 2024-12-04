#include "linklist.hpp"
#include "hash_table.hpp"

template<typename  T>
class Graph{
    HashTable<LinkList<T>> adjList;
public:
    Graph();
    void addVertex(T data);
    void addEdge(T from, T to);
    void removeVertex(T data);
    void removeEdge(T from, T to);
};