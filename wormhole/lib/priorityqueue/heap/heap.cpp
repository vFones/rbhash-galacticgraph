#include <priorityqueue/heap/heap.hpp>

template <class T>
void Heap<T>::insert(T el, int key) {
  this->A.push_back( std::make_pair(el, key) );
}

template <class T>
std::pair<T, int> Heap<T>::at(int i) {
  return this->A.at(i);
}

template <class T>
void Heap<T>::set(int i, std::pair<T, int> el) {
  this->A.at(i) = el;
}

template <class T>
void Heap<T>::swap(int i, int j){
  std::iter_swap(this->A.begin()+i, this->A.begin()+j);
}

template <class T>
void Heap<T>::popBack(){
  this->A.pop_back();
}

template <class T>
void Heap<T>::resize(int x){
  this->A.resize(x);
}


template <class T>
void Heap<T>::postOrder(int index){
  if(index < Heap<T>::getHeapSize()){
    postOrder(Heap<T>::left(index));
    postOrder(Heap<T>::right(index));
    std::cout << this->A.at(index).first << " ";
  }
}


template <class T>
void Heap<T>::printHeap(){
  for(auto i=0; i < heapSize; i++) {
    std::cout << "[" << this->A.at(i).second << "]";
    std::cout << this->A.at(i).first << " ";
  }
  std::cout << std::endl;
}


template <class T>
void Heap<T>::printA(){
  for(auto i=0; i < this->A.size(); i++){
    std::cout << "[" << this->A.at(i).second << "]";
    std::cout << this->A.at(i).first << " ";
  }
  std::cout << std::endl;
}


// return index
template <class T>
int Heap<T>::find(T el) {
  auto it = std::find_if( this->A.begin(), this->A.end(), \
                          [&el](std::pair<T, int> &i) {
                                  return el == i.first;
                              }
                        );

  if(it != this->A.end())
    return std::distance(this->A.begin(), it);
  else
    return -1;
}