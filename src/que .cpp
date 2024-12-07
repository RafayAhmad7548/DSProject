#include "que.hpp"

template <typename T>
Node<T>::Node(T val) 
{
    data=val;
    next=NULL;
};


template <typename T>
Queue<T>::Queue()
{
    frony=NULL;
    rear=NULL;
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
    if (rear==NULL) 
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
    if (front!=NULL) 
    {
        Node<T> *temp=front;
        front=front->next;  
        if (front==NULL) 
        rear=NULL;   
        
        delete temp;                
    }
}

template <typename T>
T Queue<T>::start_element() 
{
    if (front!=NULL) 
    return front->data;    
}

template <typename T>
bool Queue<T>::ISEMPTY()  
{
    return front==NULL;
}

template <typename T>
void Queue<T>::clear() 
{
    while (ISEMPTY()==false) 
    POP();
}

template class Queue<int>;
template class Queue<float>;
template class Queue<std::string>;
