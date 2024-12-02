#include<iostream>
using namespace std;

template<typename T>
class NodeList
{
public:
    NodeList *next;
    T value;
    
    NodeList(T va)
    {
        next=NULL;
        value=va;
    }
};

template<typename T>
class LinkList
{
    public:
    NodeList<T> *head;

    LinkList(); 
    void insert(T v);  
    void deletevalue(T val); 
    void display(); 
};

template class LinkList<int>;
template class LinkList<double>;
template class LinkList<string>;

