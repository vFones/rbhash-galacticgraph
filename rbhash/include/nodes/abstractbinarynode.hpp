#ifndef _IBNODE_HPP_
#define _IBNODE_HPP_

#include <iostream>

#include <nodes/genericnode.hpp>

/**
 * @brief AbstractBinaryNode
 * @details Using CRTP as base (Used in RBNode for example)
 * https://en.wikipedia.org/wiki/Curiously_recurring_template_pattern
 * @tparam D data template for value to store in node
 * @tparam N template for CRTP pattern
 */
template <typename D, class Node>
class AbstractBinaryNode : public GenericNode<D> {
  protected:
    // since is a Binary Node we got a parent and only 2 child
    Node* _parent = nullptr; // defaults values
    Node* _left = nullptr;
    Node* _right = nullptr;

  public:
    AbstractBinaryNode() : GenericNode<D>() {};
    AbstractBinaryNode(double &k) : GenericNode<D>(k) {};
    AbstractBinaryNode(double &k, D &d) : GenericNode<D>(k, d) {};
    virtual ~AbstractBinaryNode() {};

    //various setter and getter
    Node* getParent(){ return this->_parent; };
    void setParent(Node* parent){ this->_parent=parent; };

    Node* getRight(){ return this->_right; };
    void setRight(Node* right){ this->_right=right; };

    Node* getLeft(){ return this->_left; };
    void setLeft(Node* left){ this->_left=left; };
};

#endif //_IAbstractBNode_HPP_