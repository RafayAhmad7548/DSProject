#include "linklist.h"

template<typename T>
NodeList<T>::NodeList(T va)
{
    next=NULL;
    value=va;
}

template<typename T>
LinkList<T>::LinkList() 
{
    head=NULL;
}

template<typename T>
void LinkList<T>::insert(T v) 
{
    NodeList<T> *newnode=new NodeList<T>(v);
    
    if (head==NULL) 
    {
        head=newnode;
        return;
    }
    else
    {
        NodeList<T> *temp=head;
    
        while (temp->next!=NULL)
        temp=temp->next;

        temp->next=newnode;
    }
}

template<typename T>
void LinkList<T>::deletevalue(T val)  
{
    NodeList<T> *curr=head;
    NodeList<T> *prev=NULL;
    
    if (curr==NULL)
    return;
    
    while (curr!=NULL && curr->value!=val)
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
    
    if (temp==NULL)
    return;
    
    while (temp!=NULL)
    {
        cout<<temp->value;
        if (temp->next!=NULL) 
        cout<<" , "; 

        temp=temp->next;
    }
    cout<<endl;
}

