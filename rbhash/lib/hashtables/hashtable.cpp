#include <hashtables/hashtable.hpp>

#include <iostream> // cerr


//creating GenericNode vector and state vector
template <typename D, class HF>
HashTable<D, HF>::HashTable(int size) : _m(size) {
  this->_T = new std::vector<GenericNode<D>*>(this->_m, nullptr);
  this->_S = new std::vector<state>(this->_m, EMPTY); //init with EMPTY state
}


//destructing hashnodes
template <typename D, class HF>
HashTable<D, HF>::~HashTable() {
  for(auto t = 0; t != this->_m; t++)
    if(this->_S->at(t) != EMPTY)
      delete this->_T->at(t);
  
  delete []_T;
  delete []_S;
}


//getter hash table size
template <typename D, class HF>
int HashTable<D, HF>::getSize() {
  return this->_m;
}


//return the state of a indexed (j) GenericNode
template <typename D, class HF>
state HashTable<D, HF>::getState(int i) {
  if(i >= 0 && i < this->_m)
    return this->_S->at(i);
  return DELETED;
}


// return an GenericNode indexed by i
template <typename D, class HF>
GenericNode<D>* HashTable<D, HF>::getNode(int i) {
  if(i >= 0 && i < this->_m)
    return this->_T->at(i); // return nullptr if is not
    //allocated
  return nullptr; // return this null if there i is not valid
}

// open addressable hashtable
template <typename D, class HF>
int HashTable<D, HF>::insert(double &k, D &d) {
  int i = 0;
  int j = 0;
  while(i != this->_m) {
    j = _h(k, i, this->_m); // HashFunction
    if(this->_S->at(j) != OCCUPIED) {
      this->_T->at(j) = new GenericNode<D>(k, d);
      this->_S->at(j) = OCCUPIED; // set STATE
      this->_occ++;
      return j;
    }
    else 
      i++;
  }

  std::cerr<<"HashTable: overflow."<<std::endl;
  return -1; // no space left
}


// searching in a open addressable hash table
template <typename D, class HF>
int HashTable<D, HF>::search(double &k) {
  int i = 0;
  int j = 0;
  while(i != this->_m) {
    j = _h(k, i, this->_m); // Hash Function
    if(this->_S->at(j) == OCCUPIED && this->_T->at(j)->getKey() == k)
      return j;
    else
      i++;
  }
  return -1; // there is no Hash Node with that key
}


// return data of Hash Node 
template <typename D, class HF>
D HashTable<D, HF>::search(int &j) {
  if(this->_S->at(j)==OCCUPIED)
    return this->_T->at(j)->getData();
  else
    return nullptr;
}


// remove an Hash Node
template <typename D, class HF>
int HashTable<D, HF>::remove(double &k) {
  int j = this->search(k);
  if(j > -1 && this->_S->at(j) != DELETED) {
    this->_S->at(j) = DELETED;
    delete this->_T->at(j);
    this->_occ--;
  }
  return j;  
}


// return the current quantity of hashnodes
template <typename D, class HF>
int HashTable<D, HF>::getQuantity() {
  return this->_occ;
}

