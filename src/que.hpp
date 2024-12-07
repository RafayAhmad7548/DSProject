#ifndef QUE_HPP
#define QUE_HPP

#include<iostream>

template<typename T>
class Node 
{
    public:
    T data;
    Node *next;

    Node(T val);
};

template <typename T>
class Queue 
{
    private:
    Node<T> *front;  
    Node<T> *rear;   

    public:
    Queue();               
    ~Queue();             

    void PUSH(const T &data);   
    void POP();                  
    T start_element() ;      
    bool ISEMPTY() ;        
    void clear();                
};

#endif //QUE_HPP
