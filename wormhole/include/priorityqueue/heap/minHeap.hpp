#ifndef _MINHEAP_HPP_
#define _MINHEAP_HPP_

#include <priorityqueue/heap/heap.hpp>

/** MinHeap using all attributes and methods from Heap */
template <class T>
class MinHeap : public Heap<T> {
  public:
    /** build a MinHeap from elements inserted in A[n] in O(n) */
    void buildHeap();

    /** Min heapify procedure makes magic, threating A[n] as a BT.
     * O(log n) */
    void heapify(int i);

    /** creasily (Heap)sorting A[n] in O(n*logn) */
    void heapSort();
};

#endif //_MINHEAP_HPP_
