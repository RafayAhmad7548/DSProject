#ifndef GRAPH_HPP
#define GRAPH_HPP

#include "linklist.hpp"
#include "hash_table.hpp"
#include "minheap.hpp"
#include "que.hpp"

template<typename T>
class Edge{
public:
    T to;
    int weight;
    bool blocked;
    Edge(T to, int weight=0, bool blocked=false) : to(to), weight(weight), blocked(blocked){}
    bool operator==(const Edge<T>& other) const{
        return to == other.to && weight == other.weight && blocked == other.blocked;
    }
};

template<typename  T>
class Graph{
public:
    HashTable<T, LinkList<Edge<T>>> adjList;

    Graph(){

    }
    ~Graph(){

    }

    void addVertex(T data){
        if(adjList.get(data) == nullptr){
            adjList.insert(data, LinkList<Edge<T>>());
        }
    }
    void addEdge(T from, T to, int weight){
        if(from != to && !adjList.get(from)->value.contains(Edge<T>(to, weight))){
            adjList.get(from)->value.insert(Edge<T>(to , weight));
        }
    }
    void removeVertex(T data){
        adjList.remove(data);
    }
    void removeEdge(T from, T to){
        adjList.get(from)->value.deletevalue(Edge<T>(to));
    }

    std::string dijkstra(T source, T destination) {
    // Initialize distances hash table
    HashTable<T, int> distances;
    // Hash table to store predecessors
    HashTable<T, T> predecessors;

    T* keys = adjList.getKeySet();
    for (int i = 0; i < adjList.count; ++i) {
        distances.insert(keys[i], std::numeric_limits<int>::max()); // Initialize all distances to infinity
    }
    distances.get(source)->value = 0; // Distance to source vertex is 0

    // Min heap for priority queue
    MinheapQue<T> pq;
    pq.push(source);

    while (!pq.isEmpty()) {
        T u = pq.top();
        pq.pop();

        int distU = distances.get(u)->value; // idher distance store karwa 'u' ka kisi tarha

        if (u == destination) {
            break; // Shortest path to destination found
        }

        // Get neighbors of u
        HashNode<T, LinkList<T>>* adjNode = adjList.get(u);
        if (adjNode) {
            NodeList<Edge<T>>* current = adjNode->value.head;
            while (current) {
                // Neighbor vertex and edge weight
                T v = current->value.vertex;
                int weight = current->value.weight;
                int distV = distances.get(v)->value;
                // Relaxation step
                if (distU + weight < distV) {
                    distances.get(v)->value = distU + weight;
                    predecessors.insert(v, u);
                    pq.push(v);
                }
                current = current->next;
            }
        }
    }

    // Reconstruct the shortest path using the predecessors hash table
    LinkList<T> path;
    T current = destination;

    if (distances.get(current)->value == std::numeric_limits<int>::max()) {
        return ""; 
    }

    while (current != source) {
        path.insertAtBeginning(current); // Insert at the beginning to reverse the path
        HashNode<T, T>* predNode = predecessors.get(current);
        if (predNode == nullptr) {// No path exists
            return ""; 
        }
        current = predNode->value;
    }
    path.insertAtBeginning(source); // Insert the source at the beginning

    // return path;
    std::string shortestpath = "";
    NodeList<T>* temp = path.head;
    while (temp != nullptr) {
        shortestpath += temp->value;
        temp = temp->next;
    }
    return shortestpath;
}
    void dfs(T start){
        bool* visited = new bool[adjList.count];
        for (int i = 0; i < adjList.count; i++) {
            visited[i] = false;
        }
        dfsActual(start, visited);
        delete[] visited;
    }
    void dfsActual(T vertex, bool visited[]){
        int index = adjList.hashFunction(vertex);
        visited[index] = true;
        // cout << vertex << " ";

        // Retrieve the adjacency list node for the current vertex
        HashNode<T, LinkList<Edge<T>>>* adjNode = adjList.get(vertex);
        if (adjNode) { // node exists
        // Get the head of the linked list containing neighbors
            NodeList<Edge<T>>* current = adjNode->value.head;
            while (current) {
                // Get the index of the neighboring vertex
                int currentIndex = adjList.hashFunction(current->value.to);
                if (!visited[currentIndex]) {
                    dfsActual(current->value.to, visited); // recursively perform DFS
                }
                // Move to the next neighbor in the list
                current = current->next;
            }
        }
    }
    void BFS(T start){
        bool *visited= new bool[adjList.count];  // Array to keep track of visited vertices
        for (int i=0;i<adjList.count;i++) 
            visited[i]=false;  // Mark all vertices as unvisited initially
        

        Queue<T> q;  // Create a queue for BFS
        visited[adjList.hashFunction(start)]=true;  // Mark the starting node as visited
        q.PUSH(start);  // Enqueue the starting node

        while (q.ISEMPTY()==false) 
        {
            T vertex=q.start_element();  
            // cout<<vertex<< " ";
            q.POP(); 

            // Retrieve the adjacency list node for the current vertex
            HashNode<T, LinkList<Edge<T>>> *adjNode=adjList.get(vertex);
            if (adjNode) 
            {  // node exists
                NodeList<Edge<T>> *curr=adjNode->value.head;
                while (curr) 
                {
                    int curr_Ind=adjList.hashFunction(curr->value.to);
                    if (visited[curr_Ind]==false)
                    {
                        visited[curr_Ind]=true;  // Mark the neighbor as visited
                        q.PUSH(curr->value.to);  // Enqueue the neighbor
                    }
                    curr=curr->next;  
                }
            }
        }
            delete[] visited;

    }
};

#endif // GRAPH_HPP