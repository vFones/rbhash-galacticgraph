#include <priorityqueue/heap/minHeap.hpp>
#include "heap.cpp"

template <class T>
void MinHeap<T>::heapify(int i){
  if( i >= 0 ){
    int min = 0;
    int l = Heap<T>::left(i);
    int r = Heap<T>::right(i);

    //check if l exist and then look for a min
    if( l <= this->getHeapSize()-1 && \
        this->A.at(i).second > this->A.at(l).second )
      min = l;
    else
      min = i;
    
    // if not l neither i is min t then r is
    if( r <= this->getHeapSize()-1 && \
        this->A.at(min).second > this->A.at(r).second )
      min = r;

    //if max is not i then swap and re-run heapify recusively
    if(min != i){
      this->swap(i, min);
      this->heapify(min);
    }
  }
}


template <class T>
void MinHeap<T>::buildHeap(){
  // set HeapSize at first run
  this->setHeapSize(this->A.size());

  // run heapify starting from middle going up
  for(auto j = (this->getHeapSize()/2); j >= 0; j--)
    this->heapify(j);
}


template <class T>
void MinHeap<T>::heapSort(){
  // build a Min heap at first
  this->buildHeap();
  
  for(auto j = this->A.size()-1; j > 0; j--){
    // Since A[0] is the greatest put it in last pos
    this->swap(0, j);
    this->decrHeapSize();
    this->heapify(0);
  }
}
