#ifndef _BINARYSEARCHTREE_HPP_
#define _BINARYSEARCHTREE_HPP_


/**
 * @brief Binary Search Tree 
 * @details BST inherites from a Generic tree.
 *  ndr. must use a Binary Node as template argument
 * @tparam D data to store in nodes
 * @tparam N node argument
 */
template <typename D, class Node>
class BinarySearchTree {
  protected:
    //generic nil node for space optimization
    Node *NIL = nullptr;
    Node *_root = nullptr;

    //transplant a node and link father
    void transplant(Node *x, Node *y);

  public:
    BinarySearchTree();
    ~BinarySearchTree();

    // inserting
    virtual Node* insertNode(double &k, D &d);
    
    // deleting
    virtual bool deleteNode(double &k);
    
    //search of a node with a key
    Node* search(double &k);

    //setter getter for NIL
    Node* getNil() { return this->NIL; }
    Node* getRoot() { return this->_root; }
    void setRoot(Node *x) { this->_root = x; }

    // minimum in a subtree
    Node* minimum(Node *x);

    //maximum of a subtree
    Node* maximum(Node *x);

    //successor of a node
    Node* successor(Node *x);

    //predecessor of a node
    Node* predecessor(Node *x);
    

    // visit (using pointer function -> c++11 lamba)
    void inorder(Node *z, void(*lambda)(Node *));
    //mainly use postoder for distructor
    void postorder(Node *z, void(*lambda)(Node *));

};

#endif //_BINARYSEARCHTREE_HPP_
