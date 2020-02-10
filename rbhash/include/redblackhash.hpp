#ifndef _REDBLACKHASH_HPP_
#define _REDBLACKHASH_HPP_

#include <trees/redblacktree.hpp>
#include <hashtables/hashtable.hpp>

/**
 * @brief Red Black Hash 
 * @details data structure that use a Red Black to stores in every node
 * an Hashtables. 
 * Key 1 is the int used to indexes a red black, Key 2 is the int to indexes
 * a single cell of an hashtable. D d is the data to store in hashtables
 * @tparam D data to store in hashtables
 */

template <typename D>
class RedBlackHash {
  private:
    RedBlackTree<HashTable<D> *> *_rb;
    int _size;

  public:
    RedBlackHash(int s = 9973);
    ~RedBlackHash(){};
    
    //redblack getter
    RedBlackTree<HashTable<D> *> *getRBHashTree(){return this->_rb;};
    
    bool insert(int k1, int k2, D d);
    RedBlackNode<HashTable<D> *>* search(int k1, int k2, D d);
    bool remove(int k1, int k2, D d);

    // print chaining
    friend std::ostream& operator<<(std::ostream &Str, RedBlackHash<D> *rh) {
      Str<<rh->getRBHashTree()<<"\n";
      return Str;
    };
};

#endif //_REDBLACKHASH_HPP_