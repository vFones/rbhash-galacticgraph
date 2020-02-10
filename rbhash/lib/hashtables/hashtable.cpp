#include <iostream> // cerr

#include <hashtables/hashtable.hpp>


//creating GenericNode vector and state vector
template <typename D>
HashTable<D>::HashTable(int size) : _m(size) {
  this->_T = new std::vector<GenericNode<D>*>(this->_m, nullptr);
  this->_S = new std::vector<state>(this->_m, EMPTY); //init with EMPTY state
}


//destructing hashnodes
template <typename D>
HashTable<D>::~HashTable() {
  for(auto t = 0; t != this->_m; t++)
    if(this->_S->at(t) != EMPTY)
      delete this->_T->at(t);
  
  delete []_T;
  delete []_S;
}


//getter hash table size
template <typename D>
int HashTable<D>::getSize() {
  return this->_m;
}


//return the state of a indexed (j) GenericNode
template <typename D>
state HashTable<D>::getState(int i) {
  if(i >= 0 && i < this->_m)
    return this->_S->at(i);
  return DELETED;
}


// return an GenericNode indexed by i
template <typename D>
GenericNode<D>* HashTable<D>::getNode(int i) {
  if(i >= 0 && i < this->_m)
    return this->_T->at(i); // return nullptr if is not
    //allocated
  return nullptr; // return this null if there i is not valid
}

// open addressable hashtable
template <typename D>
int HashTable<D>::insert(double &k, D &d) {
  int i = 0;
  int index = this->_h1(k);
  int j = index;
  while(i != this->_m) {
    if(this->_S->at(j) != OCCUPIED) {
      this->_T->at(j) = new GenericNode<D>(k, d);
      this->_S->at(j) = OCCUPIED; // set STATE
      this->_occ++;
      return j;
    }
    else
      j = ( index + (i++) * this->_h2(k)) % this->_m; // double HashFunction
  }

  std::cerr<<"HashTable: overflow."<<std::endl;
  return -1; // no space left
}


// searching in a open addressable hash table
template <typename D>
int HashTable<D>::search(double &k) {
  int i = 0;
  int index = this->_h1(k);
  int j = index;
  while(i != this->_m) {
    if(this->_S->at(j) == OCCUPIED && this->_T->at(j)->getKey() == k)
      return j;
    else
      j = ( index + (i++) * this->_h2(k)) % this->_m; // double HashFunction
  }
  return -1; // there is no Hash Node with that key
}


// return data of Hash Node 
template <typename D>
D HashTable<D>::search(int &j) {
  if(this->_S->at(j)==OCCUPIED)
    return this->_T->at(j)->getData();
  else
    return nullptr;
}


// remove an Hash Node
template <typename D>
int HashTable<D>::remove(double &k) {
  int j = this->search(k);
  if(j > -1 && this->_S->at(j) != DELETED) {
    this->_S->at(j) = DELETED;
    delete this->_T->at(j);
    this->_occ--;
  }
  return j;  
}


template <typename D>
void HashTable<D>::printKeys() {
  for(auto i = 0; i < this->_m; i++)
    if(this->_S->at(i) == OCCUPIED)
      std::cout<<this->_T->at(i)->getKey()<<" ";
  std::cout<<"\n\n";
}

// return the current quantity of hashnodes
template <typename D>
int HashTable<D>::getQuantity() {
  return this->_occ;
}

