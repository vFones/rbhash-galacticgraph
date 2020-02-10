#ifndef _REDBLACKNODE_HPP_
#define _REDBLACKNODE_HPP_

#include <nodes/abstractbinarynode.hpp>
#include <nodes/color.hpp>

/**
 * @brief Red Black Node
 * @details Inherites from Binary Node and using
 * CRTP for a dynamic inheritance. Also extending Color
 * @tparam D 
 */
template <typename D>
class RedBlackNode : public AbstractBinaryNode<D, RedBlackNode<D>>, public Color {
  public:
    RedBlackNode() : Color(BLACK) {};
    RedBlackNode(double &k) : AbstractBinaryNode<D, RedBlackNode<D>>(k), Color(BLACK) {};
    RedBlackNode(double &k, D &d) : AbstractBinaryNode<D, RedBlackNode<D>>(k, d), Color(BLACK) {};
    ~RedBlackNode() {
      if(this->_left==nullptr)
        delete this->_left;
      if(this->_right==nullptr)
        delete this->_right;
      if(this->_parent==nullptr)
        delete this->_parent;
    };

    friend std::ostream& operator<<(std::ostream &Str, RedBlackNode<D> &c) {
      if(c.isRed())
        Str<<"\033[31m";
      Str<<"("<<c.getKey()<<") : \n"<<c.getData()<<"\033[0m";
      return Str;
    }

    friend std::ostream& operator<<(std::ostream &Str, RedBlackNode<D> *c) {
      if(c->isRed())
        Str<<"\033[31m";
      Str<<"("<<c->getKey()<<") : \n"<<c->getData()<<"\033[0m";
      return Str;
    }
};


#endif //_REDBLACKNODE_HPP_
