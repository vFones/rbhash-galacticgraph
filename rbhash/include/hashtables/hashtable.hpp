#ifndef _HASHTABLE_HPP_
#define _HASHTABLE_HPP_

#include <limits>
#include <vector>
#include <cmath>

#include <nodes/genericnode.hpp>


/*! Enum for state of single HashNode */
enum state { EMPTY, OCCUPIED, DELETED };

/**
 * @brief HashTable datastructure
 * @tparam D is the Data to store
 * @tparam HashFunction is the class that make the hashfunction
 *  to compute the index of node
 */
template <typename D>
class HashTable {
  private:
    std::vector<state> *_S; // array of states
    std::vector<GenericNode<D>*> *_T; // effective hashtable
    
    // using fmod -> double % int
    int _h1(double &k){return static_cast<int>(std::fmod(k, this->_m));} 
    int _h2(double &k){return 1 + static_cast<int>(std::fmod(k, this->_m-1));}
   
    int _m; // default capacity
    int _occ = 0; // number of occupied nodes

  public:
    HashTable( int size = 701 );
    ~HashTable();

    /**
     * @brief Get the capacity of hashtable
     * @return int 
     */
    int getSize();

    /**
     * @brief Get the current hashnode in hashtable
     * @return int 
     */
    int getQuantity();

    /**
     * @brief Get the state of single node
     * @param i
     * @return state 
     */
    state getState(int i);

    /**
     * @brief Get the Node object
     * @param i 
     * @return HashNode<D>* 
     */
    GenericNode<D>* getNode(int i);


    /**
     * @brief insert a data in HashTable 
     * @param k is the key
     * @param d is the value
     * @return int is the index, return -1 if there isn't space left
     */
    int insert(double &k, D &d);

    /**
     * @brief search a key in HashTable
     * @param k is the key
     * @return int is the index, return -1 if there isn't
     */
    int search(double &k);

    /**
     * @brief Overload of search method 
     * @param j is the index 
     * @return D is the value returned
     */
    D search(int &j);

    /**
     * @brief remove a Node with that key
     * @param k is the key
     * @return int is the index
     */
    int remove(double &k);

    /**
     * @brief Override of operator<< for print
     * @param Str ostream obj
     * @param c HashTable<D>
     * @return std::ostream&
     */
    friend std::ostream& operator<<(std::ostream &Str, HashTable<D> *c) {
      // put every HashNode<D> that there isn't EMPTY or DELETED
      for(auto i = 0; i < c->getSize(); i++)
        if(c->getState(i) == OCCUPIED)
          Str<<"\t"<<c->getNode(i);
      Str<<"\n\n";
      return Str;
    };
};



#endif //_HASHTABLE_HPP_