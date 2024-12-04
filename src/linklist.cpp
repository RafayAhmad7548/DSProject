#include <iostream>
#include "linklist.hpp"

template<typename T>
NodeList<T>::NodeList(T va)
{
    next=nullptr;
    value=va;
}

template<typename T>
LinkList<T>::LinkList() 
{
    head=nullptr;
}

template<typename T>
void LinkList<T>::insert(T v) 
{
    NodeList<T> *newnode=new NodeList<T>(v);
    
    if (head==nullptr) 
    {
        head=newnode;
        return;
    }
    else
    {
        NodeList<T> *temp=head;
    
        while (temp->next!=nullptr)
            temp=temp->next;

        temp->next=newnode;
    }
}

template<typename T>
void LinkList<T>::deletevalue(T val)  
{
    NodeList<T> *curr=head;
    NodeList<T> *prev=nullptr;
    
    if (curr==nullptr)
        return;
    
    while (curr!=nullptr && curr->value!=val)
    {
        prev=curr;
        curr=curr->next;
    }
      
    if (curr==head)
        head=head->next; 
    else
        prev->next=curr->next; 
    
    delete curr; 
}    

template<typename T>
void LinkList<T>::display()  
{
    NodeList<T> *temp=head;
    
    if (temp==nullptr)
        return;
    
    while (temp!=nullptr)
    {
        std::cout<<temp->value;
        if (temp->next!=nullptr) 
            std::cout<<" , "; 

        temp=temp->next;
    }
    std::cout<<std::endl;
}

