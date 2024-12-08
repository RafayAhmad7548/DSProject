#ifndef LINKLIST_HPP
#define LINKLIST_HPP

#include <iostream>

template<typename T>
class NodeList
{
    public:
    T value;
    NodeList *next;
    
    NodeList(T va) : value(va), next(nullptr){}
};

template<typename T>
class LinkList
{
    public:
    NodeList<T> *head;
    int size;

    LinkList(){
        head=nullptr;
    } 

    void insert(T v){
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
        size++;
    }

    void insertAtBeginning(T v) {
    NodeList<T>* newnode = new NodeList<T>(v);
    newnode->next = head;
    head = newnode;
    size++;
    }
    void deletevalue(T val){
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
        size--;
    }

    bool contains(T val){
        NodeList<T> *temp=head;
        while(temp != nullptr){
            if(temp->value == val) return true;
            temp = temp->next;
        }
        return false;
    }

    void display(){
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
};


#endif // LINKLIST_HPP