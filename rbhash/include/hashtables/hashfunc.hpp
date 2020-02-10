#ifndef _HASHFUNC_HPP_
#define _HASHFUNC_HPP_

#include <cmath> 

/**
 * HashFunction class, used for a custom hashfunction
 */
class HashFunction {
  public:
    /**
     * Override of () operator
     * @param k is the key used to compute the index
     * @param i is the iterator used to compute index
     * @param m is the size of hashtable
     * @return is the index that will be used as
     *  index for hashtable 
     */
    int operator() (double k, int i, int m);
};

#endif //_HASHFUNC_HPP_