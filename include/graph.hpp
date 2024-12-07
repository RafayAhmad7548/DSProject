#ifndef GRAPH_HPP
#define GRAPH_HPP

#include "linklist.hpp"
#include "hash_table.hpp"
#include"minheap.hpp"
#include "que.hpp"

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
    void dfs(T start);
    void dfsActual(T vertex, bool visited[]);
    void BFS(T start);
};

template class Graph<char>;

#endif // GRAPH_HPP