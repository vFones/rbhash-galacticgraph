#ifndef _HEAP_HPP_
#define _HEAP_HPP_

#include <iostream>
#include <algorithm>
#include <utility>
#include <deque>

/** Heap Data Structure */
template <class T> // object inside this DS are templates
class Heap {
  private:
    int heapSize;

  protected:// made attributes protected 'cause
            // we need in Priority Queues
    std::deque< std::pair<T, int> > A;

  public:
    Heap() : heapSize(0){};
    ~Heap(){};

    int find(T el);

    // inserting elements using std::pair
    void insert(T el, int key); // must use Int for key and T for obj to store.


    int parent(int i){return (i-1)/2;};
    int left(int i){return (2*i + 1);};
    int right(int i){return (2*i + 2);};

    /**
     * override of deque positional operators
     * must use this for access at deque (e.g. Priority Queue)
     * return std::pair from position at i
    */
    std::pair<T, int> at(int i);
    
    /**
     * override of deque positional operators
     * must use this for access at deque (e.g. Priority Queue)
     * set pair<key, T element> at position i
     */
    void set(int i, std::pair<T, int> el);

    /**
     * override of deque positional operators
     * must use this for access at deque (e.g. Priority Queue)
     * swap elements using index (wrapper to std::iter_swap)
     */
    void swap(int i, int j);

    /**
     * override of deque positional operators
     * must use this for access at deque (e.g. Priority Queue)
     * wrapper to pop_back()
     */
    void popBack();
    
    /**
     * override of deque positional operators
     * must use this for access at deque (e.g. Priority Queue)
     * wrapper to resize()
     */
    void resize(int x);

    int getHeapSize(){return heapSize;}
    void setHeapSize(int s){heapSize = s;}
    
    void incrHeapSize(){heapSize++;}
    void decrHeapSize(){heapSize--;}
    
    /** Print the heap using heapSize as upperbound */
    void printHeap();
    
    /** Print all the A deque */
    void printA();

    /** Virtual method to implement in max Heap and min heap */ 
    virtual void buildHeap() = 0;// pure specifier = 0, same as {}
    
    /** Virtual method to implement in max Heap and min heap */
    virtual void heapify(int i) = 0;// pure specifier = 0, same as {}
    
    /** Virtual method to implement in max Heap and min heap */
    virtual void heapSort() = 0;// pure specifier = 0, same as {}
    
    /** Print in postOrder starting from index */ 
    void postOrder(int index);
};


#endif //_HEAP_HPP_