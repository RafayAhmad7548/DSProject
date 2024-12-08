#include "que.hpp"

template <typename T>
Node<T>::Node(T val) 
{
    data=val;
    next=nullptr;
};


template <typename T>
Queue<T>::Queue()
{
    front=nullptr;
    rear=nullptr;
} 


template <typename T>
Queue<T>::~Queue()
{
    clear();
}

template <typename T>
void Queue<T>::PUSH(const T &data) 
{
    Node<T> *newNode=new Node<T>(data);  
    if (rear==nullptr) 
    front=rear=newNode;      
    else 
    {
        rear->next=newNode;         
        rear=newNode;               
    }
}

template <typename T>
void Queue<T>::POP()
{
    if (front!=nullptr) 
    {
        Node<T> *temp=front;
        front=front->next;  
        if (front==nullptr) 
            rear=nullptr;   
        
        delete temp;                
    }
}

template <typename T>
T Queue<T>::start_element() 
{
    return front->data;
}

template <typename T>
bool Queue<T>::ISEMPTY()  
{
    return front==nullptr;
}

template <typename T>
void Queue<T>::clear() 
{
    while (ISEMPTY()==false) 
        POP();
}

template class Queue<int>;
template class Queue<float>;
template class Queue<char>;
