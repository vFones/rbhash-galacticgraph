#ifndef _PARSER_HPP_
#define _PARSER_HPP_

#include <string>
#include <redblackhash.hpp>

/**
 * @brief Parser for Red Black Hashtable
 * @details Used to fill from a file an hashtable.
 *  Also providing method for C.R.D. (create, retrieve, delete) tuples
 *  tuples must be in format <int> keys and <string> data -> key1:key2:data
 */
class Parser {
  private:
    int _hashsize;
    std::string _filename;
    RedBlackHash<std::string> *_rh;

  public:
    Parser(const std::string fn, int hashsize = 9973);
    ~Parser(){};
    
    //  tuples must be in format <int> keys and <string> data -> key1:key2:data
    bool insert(std::string str);

    //  tuples must be in format <int> keys and <string> data -> key1:key2:data
    bool search(std::string str);

    //  tuples must be in format <int> keys and <string> data -> key1:key2:data
    bool remove(std::string str);
    
    //printing data structure
    void print();
};

#endif //_PARSER_HPP_