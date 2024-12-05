#include <iostream>
#include "linklist.hpp"

template<typename T>
NodeList<T>::NodeList(T va, int weight)
{
    next=nullptr;
    value=va;
    this->weight=weight;
}

template<typename T>
LinkList<T>::LinkList() 
{
    head=nullptr;
}

template<typename T>
void LinkList<T>::insert(T v, int weight) 
{
    NodeList<T> *newnode=new NodeList<T>(v, weight);
    
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

    if (curr==nullptr)
        return;
      
    if (curr==head)
        head=head->next; 
    else
        prev->next=curr->next; 
    
    delete curr; 
}

template<typename T>
bool LinkList<T>::contains(T val){
    NodeList<T> *temp=head;
    while(temp != nullptr){
        if(temp->value == val) return true;
        temp = temp->next;
    }
    return false;
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

