#ifndef MIN_HEAP_HPP
#define MIN_HEAP_HPP

class MinheapQue 
{
    private:
    int *heap;      
    int size;      
    int capacity;   

    void swap(int &a,int &b);
    void heapifyUp(int ind);
    void heapifyDown(int ind);
    void resizeHeap(int newCapacity);

    public:
    MinheapQue(int start_size=10);
    ~MinheapQue();
    void push(int value);
    void pop();
    int top() ;
    bool isEmpty() ;
    void display() ;
};

#endif 
