#include "graph.hpp"
#include "linklist.hpp"

template<typename  T>
Graph<T>::Graph(){

}
template<typename T>
Graph<T>::~Graph(){

}

template<typename  T>
void Graph<T>::addVertex(T data){
    if(adjList.get(data) != nullptr){
        adjList.insert(data, LinkList<T>());
    }
}

template<typename  T>
void Graph<T>::addEdge(T from, T to, int weight){
    if(from != to && !adjList.get(from)->value.contains(to)){
        adjList.get(from)->value.insert(to, weight);
    }
}

template<typename T>
void Graph<T>::removeVertex(T data){
    adjList.remove(data);
}

template<typename T>
void Graph<T>::removeEdge(T from, T to){
    adjList.get(from)->value.deletevalue(to);
}