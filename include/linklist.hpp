#ifndef LINKLIST_HPP
#define LINKLIST_HPP

template<typename T>
class NodeList
{
    public:
    NodeList *next;
    T value;
    
    NodeList(T va);  
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
template class LinkList<char>;

#endif // LINKLLIST_HPP