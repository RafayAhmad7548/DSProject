#include "graph.hpp"

template<typename  T>
Graph<T>::Graph(){

}

template<typename  T>
void Graph<T>::addVertex(T data){
    adjList.insert(LinkList<T>(data));
}

template<typename  T>
void Graph<T>::addEdge(T from, T to){
    adjList.search(from).insert(to);
}