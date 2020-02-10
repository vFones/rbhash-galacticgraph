#ifndef _REDBLACKTREE_HPP_
#define _REDBLACKTREE_HPP_

#include <trees/binarysearchtree.hpp>
#include <nodes/redblacknode.hpp>


/**
 * @brief Red Black tree
 * @details Templated Red Black tree that 
 * inherites from Binary Search tree <Data, RBnode>
 * @tparam D data
 */
template <typename D, class Node = RedBlackNode<D>>
class RedBlackTree : public BinarySearchTree<D, Node>{
  private:
    // insert and delete Fix for restoring RB property
    void insertFix(Node *x);
    void deleteFix(Node *x);

    // left Rotate and right Rotate for balancing method
    void leftRotate(Node *x);
    void rightRotate(Node *x);

  public:
    RedBlackTree(){};
    ~RedBlackTree();

    //create and insert RBNode, with rb fixes
    Node* insertNode(double &k, D &d) override;

    //delete RBNode if exist
    bool deleteNode(double &k) override;

    // inorder print
    void print();

    //override for correct print
    friend std::ostream& operator<<(std::ostream &Str, RedBlackTree<D> *rb) {
      rb->print();
      return Str;
    };
};

#endif //_REDBLACKTREE_HPP_