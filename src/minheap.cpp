#include<iostream>
#include "minheap.hpp"

void MinheapQue::swap(int &a,int &b) 
{
    int temp=a;
    a=b;
    b=temp;
}
MinheapQue::MinheapQue(int start_size)
{
    capacity=start_size;
    size=0;
    heap=new int[capacity];
}

MinheapQue::~MinheapQue() 
{
    delete[] heap;
}

void MinheapQue::heapifyUp(int ind) 
{
    while (ind > 0) 
    {
        int parent=(ind-1)/2;

        if (heap[parent] <= heap[ind])
            break;

        swap(heap[parent], heap[ind]);
        ind=parent;
    }
}

void MinheapQue::heapifyDown(int ind) 
{
    int left;
    int right;
    int small;
    while (2*ind+1<size) 
    { 
        left=2*ind + 1;
        right=2*ind + 2;
        small=ind;

        
        if (left<size && heap[left]<heap[small]) 
            small=left;
        
        if (right<size && heap[right]<heap[small]) 
            small=right;
    
        if (small==ind)
            break;

        swap(heap[ind],heap[small]);
        ind=small;
    }
}


void MinheapQue::resizeHeap(int new_size) 
{
    int *newHeap=new int[new_size];
    for (int i=0;i<size;i++) 
        newHeap[i]=heap[i];
    
    delete[] heap;
    heap=newHeap;
    capacity=new_size;
}

void MinheapQue::push(int value) 
{
    if (size==capacity) 
        resizeHeap(capacity*2); 
    
    heap[size]=value;
    heapifyUp(size);
    size++;
}

void MinheapQue::pop() 
{
    if (size==0) 
        return;
    
    heap[0]=heap[size-1];
    size--;
    heapifyDown(0);
}

int MinheapQue::top()  
{
    if (size==0) 
        return -1; 
    
    return heap[0];
}


bool MinheapQue::isEmpty()  
{
    return size==0;
}


void MinheapQue::display()  
{
    if (size==0) 
        return;
    
    std::cout<<"Min Heap: ";
    
    for (int i=0;i<size;i++) 
        std::cout<<heap[i]<<" ";
    
    std::cout<<std::endl;
}
