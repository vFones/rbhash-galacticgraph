#ifndef _MINPRIORITYQUEUE_HPP_
#define _MINPRIORITYQUEUE_HPP_

#include <priorityqueue/heap/minHeap.hpp>

/**
 * min priority queue created using a Min Heap 
 */
template <class T>
class MinPriorityQueue {
  private:
    MinHeap<T> A; // used for operations

  public:
    MinPriorityQueue(){};
    ~MinPriorityQueue(){};

    /** Insert an element with his key in O(log n) */
    void insert(T el, int key);
    
    /** get minimum in O(1) */
    std::pair<T, int> minimum();

    /** Extract the minimum in O(log n) */
    std::pair<T, int> extractMin();

    /** decrease the priority of an element by a key value */
    void decreasePriority(T el, int key);

    /** Printing the priority queue */
    void print(){this->A.printHeap();};
    void printAll(){this->A.printA();};

    /** return size of priority queue */
    int getPQSize(){return A.getHeapSize();};
};

#endif // _MINPRIORITYQUEUE_HPP_
