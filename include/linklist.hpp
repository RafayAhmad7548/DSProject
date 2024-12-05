#ifndef LINKLIST_HPP
#define LINKLIST_HPP

template<typename T>
class NodeList
{
    public:
    NodeList *next;
    T value;
    int weight;
    
    NodeList(T va, int weight=0);  
};

template<typename T>
class LinkList
{
    public:
    NodeList<T> *head;
    LinkList(); 
    void insert(T v, int weight=0);
    void deletevalue(T val);
    bool contains(T val);
    void display(); 
};

template class LinkList<int>;
template class LinkList<double>;
template class LinkList<char>;

#endif // LINKLLIST_HPP