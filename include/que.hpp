#ifndef QUE_HPP
#define QUE_HPP

template<typename T>
class Node 
{
    public:
    T data;
    Node *next;

    Node(T val){
        data=val;
        next=nullptr;
    }
};

template <typename T>
class Queue 
{
    private:
    Node<T> *front;  
    Node<T> *rear;   

    public:
    Queue(){
        front=nullptr;
        rear=nullptr;
    }
    ~Queue(){
        clear();
    }

    void PUSH(const T &data){
        Node<T> *newNode=new Node<T>(data);  
        if (rear==nullptr) 
        front=rear=newNode;      
        else 
        {
            rear->next=newNode;         
            rear=newNode;               
        }
    }
    void POP(){
        if (front!=nullptr) 
        {
            Node<T> *temp=front;
            front=front->next;  
            if (front==nullptr) 
                rear=nullptr;   
            
            delete temp;                
        }
    }
    T start_element(){
        return front->data;
    }
    bool ISEMPTY(){
        return front==nullptr;
    }
    void clear(){
        while (ISEMPTY()==false) 
            POP();
    }
};

#endif //QUE_HPP
