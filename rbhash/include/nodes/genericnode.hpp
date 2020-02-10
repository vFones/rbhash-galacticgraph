#ifndef _GENERICNODE_HPP_
#define _GENERICNODE_HPP_

#include <string>
#include <iostream>

#include <other/item.hpp>

/**
 * @brief Generic Node class
 * @tparam N template base class
 */
template <typename D>
class GenericNode : public Item<D> {
  public:
    GenericNode() : Item<D>() {};
    GenericNode(double &k) : Item<D>(k) {};
    GenericNode(double &k, D &d) : Item<D>(k, d){};
    ~GenericNode() {};
    std::string toString(){return "["+std::to_string((int)this->getKey())+"] : "+
      std::string(this->getData())+"\n";}

    friend std::ostream& operator<<(std::ostream &Str, GenericNode<D> &c){
      Str<<c.toString(); return Str; }

    friend std::ostream& operator<<(std::ostream &Str, GenericNode<D> *c){
      Str<<c->toString(); return Str; }
};

#endif //_GENERICNODE_HPP_