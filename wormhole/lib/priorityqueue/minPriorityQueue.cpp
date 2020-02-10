#include <priorityqueue/minPriorityQueue.hpp>
#include <other/debug.hpp>

#include "heap/minHeap.cpp"

#include <cassert>

// insert new T el and decrease his priority for
// correct positioning
template<class T>
void MinPriorityQueue<T>::insert(T el, int priority){
  this->A.insert(el, priority);
  this->A.incrHeapSize();
  decreasePriority(el, priority);
}


// return minimum in queue
template <class T>
std::pair<T, int> MinPriorityQueue<T>::minimum(){
  return this->A.at(0);
}


// extract minimum
template <class T>
std::pair<T, int> MinPriorityQueue<T>::extractMin(){
  std::pair<T, int> min;
  if(this->A.getHeapSize() < 1)
    return min;

  min = this->A.at(0);
  this->A.swap(0, this->A.getHeapSize()-1);
  this->A.decrHeapSize();
  // no need to delete if there are no new element inserted
  // this->A.popBack();

  // restore property
  this->A.heapify(0);

  return min;
}



template <class T>
void MinPriorityQueue<T>::decreasePriority(T el, int priority){
  int i = this->A.find(el);
  if(i == -1)
    return;

  if(priority > this->A.at(i).second){
    IFDEBUG debug_print << "no need to decrease" << std::endl;
    return;
  }

  // set new priority
  this->A.set(i, std::make_pair(A.at(i).first, priority));
  
  // move down untill father is lower
  while(  i > 0 && this->A.at(this->A.parent(i)).second > this->A.at(i).second ) {
    this->A.swap(this->A.parent(i), i);
    i = this->A.parent(i);
  }
}
