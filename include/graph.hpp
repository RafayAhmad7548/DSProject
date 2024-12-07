#ifndef GRAPH_HPP
#define GRAPH_HPP

#include "linklist.hpp"
#include "hash_table.hpp"

template<typename  T>
class Graph{
public:
    HashTable<T, LinkList<T>> adjList;
    Graph();
    ~Graph();
    void addVertex(T data);
    void addEdge(T from, T to, int weight);
    void removeVertex(T data);
    void removeEdge(T from, T to);
    HashTable<T, int> dijkstra(T source);
};

template class Graph<char>;

#endif // GRAPH_HPP