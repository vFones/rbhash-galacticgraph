#include <iostream>

#include <redblackhash.hpp>

#include "hashtables/hashtable.cpp"
#include "trees/redblacktree.cpp"


template <typename D>
RedBlackHash<D>::RedBlackHash(int size) : _size(size) {
  this->_rb = new RedBlackTree<HashTable<D> *>;
}


template <typename D>
bool RedBlackHash<D>::insert(int k1, int k2, D d) {
  auto key1 = static_cast<double>(k1);
  auto key2 = static_cast<double>(k2);

  auto node = this->_rb->search(key1);

  if(node == this->_rb->getNil()) {                 // if it's a new node
    auto hashtable = new HashTable<D>(this->_size); // allocate hashtable
    node = this->_rb->insertNode(key1, hashtable);  // insert this new hashtable 
    node->getData()->insert(key2, d);               // insert string
    return true;
  }
  else
    if(node->getData()->search(key2) < 0)           // if there isnt already a key2
      if(node->getData()->insert(key2, d) >= 0)     // and also there is space
        return true;
  
  // if here means that there is already a key or there is no space
  return false;
}


template <typename D>
bool RedBlackHash<D>::search(int k1, int k2, D d) {
  auto key1 = static_cast<double>(k1);
  auto key2 = static_cast<double>(k2);

  auto node = this->_rb->search(key1);
  
  if(node != this->_rb->getNil()) {
    auto j = node->getData()->search(key2); 
    if( j >= 0) {
      if(node->getData()->search(j) == d )
        return true;
      else
        std::cerr<<"no value in node["<<key1<<"] hash["<<key2<<"]-> "<<d<<"\n"<<
          "maybe you were looking for: "<<node->getData()->search(j) <<std::endl;
    }
    else
      std::cerr<<"no hashtable with key2 = ["<<k2<<"]"<<std::endl;
  }
  else
    std::cerr<<"no node with key1 = ["<<k1<<"]"<<std::endl;

  return false;
}


template <typename D>
bool RedBlackHash<D>::remove(int key1, int key2, D data) {
  // if tuple is correct
  if(this->search(key1, key2, data)) {
    auto k1 = static_cast<double>(key1);
    auto k2 = static_cast<double>(key2);

    // search for a RB node
    auto node = this->_rb->search(k1);
    // if hashtable got only one value (key1)
    if(node->getData()->getQuantity() == 1)
      this->_rb->deleteNode(k1); // delete RB node
    else
      node->getData()->remove(k2); // just remove value

    return true;
  }
  return false;
}