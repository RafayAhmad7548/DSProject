#include "graph.hpp"
#include "linklist.hpp"
#include"minheap.hpp"

template<typename  T>
Graph<T>::Graph(){

}
template<typename T>
Graph<T>::~Graph(){

}

template<typename  T>
void Graph<T>::addVertex(T data){
    if(adjList.get(data) == nullptr){
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

template<typename T>
HashTable<T, int> Graph<T>::dijkstra(T source) {
    // Initialize distances hash table
    HashTable<T, int> distances;
    T* keys = adjList.getKeySet();
    for (int i = 0; i < adjList.count; ++i) {
        distances.insert(keys[i], std::numeric_limits<int>::max()); // initialize all distances to infinity
    }
    distances.get(source)->value = 0; // distance to source vertex = 0

    // Min heap for priority queue
    MinheapQue pq;
    pq.push(source);

    while (!pq.isEmpty()) {
        T u = pq.top();
        pq.pop();

        int distU = distances.get(u)->value;

        // Get neighbors of u
        auto adjNode = adjList.get(u); // get adjecency list of curr node
        if (adjNode) {
            LinkList<T>& neighbors = adjNode->value;
            NodeList<T>* current = neighbors.head;
            while (current) {
                 // Neighbor vertex and edge weight
                T v = current->value;
                int weight = current->weight;
                int distV = distances.get(v)->value;
                // Relaxation step
                if (distU + weight < distV) {
                    distances.get(v)->value = distU + weight;
                    pq.push(v);
                }
                current = current->next;
            }
        }
    }
    return distances;
}


template<typename T>
void Graph<T>::dfs(T start) {
    bool* visited = new bool[adjList.count];
    for (int i = 0; i < adjList.count; i++) {
        visited[i] = false;
    }
    dfsActual(start, visited);
    delete[] visited;
}

template<typename T>
void Graph<T>::dfsActual(T vertex, bool visited[]) {
    int index = adjList.hashFunction(vertex);
    visited[index] = true;
    cout << vertex << " ";

    // Retrieve the adjacency list node for the current vertex
    HashNode<T, LinkList<T>>* adjNode = adjList.get(vertex);
    if (adjNode) { // node exists
    // Get the head of the linked list containing neighbors
        NodeList<T>* current = adjNode->value.head;
        while (current) {
            // Get the index of the neighboring vertex
            int currentIndex = adjList.hashFunction(current->value);
            if (!visited[currentIndex]) {
                dfsActual(current->value, visited); // recursively perform DFS
            }
            // Move to the next neighbor in the list
            current = current->next;
        }
    }
}