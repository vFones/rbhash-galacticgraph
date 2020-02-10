#include <trees/binarysearchtree.hpp>
#include <other/debug.hpp>

// binary search tree constructor
template<typename D, class Node>
BinarySearchTree<D, Node>::BinarySearchTree() {
  //allocating NIL and pointing root to NIL
  this->NIL = new Node();

  this->NIL->setParent(this->NIL);
  this->NIL->setLeft(this->NIL);
  this->NIL->setRight(this->NIL);

  this->_root = this->NIL;
  this->_root->setParent(this->NIL);
  this->_root->setLeft(this->NIL);
  this->_root->setRight(this->NIL);
}

// Binary Search Tree destructor (using post order)
template<typename D, class Node>
BinarySearchTree<D, Node>::~BinarySearchTree() {
  this->NIL = nullptr;
  postorder(this->_root, [](Node *tmp){delete tmp;});
}

// inserting a node in Binary Search Tree
template<typename D, class Node>
Node* BinarySearchTree<D, Node>::insertNode(double &k, D &d) {
  Node *z = new Node(k, d);

  auto curr = this->_root;
  auto prev = this->NIL;

  // going doing checking if must be left or right
  while(curr != this->NIL){
    prev = curr;
    curr = z->getKey() < curr->getKey() ? curr->getLeft() : curr->getRight();
  }

  // set parent to previuosly saved node
  z->setParent(prev);

  // checking if is left son or right son
  if(prev == this->NIL) // or root
    this->_root = z; 
  else if(z->getKey() < prev->getKey())
    prev->setLeft(z);
  else
    prev->setRight(z);
  
  // new allocated node got NIL as children
  z->setLeft(this->NIL);
  z->setRight(this->NIL);

  return z;
}

// delete a node
template<typename D, class N>
bool BinarySearchTree<D, N>::deleteNode(double &k) {
  // must search 
  auto z = this->search(k);
  if(z == nullptr)
    return false; // if cannot find return false
  
  auto y = z;

  if( z->getLeft() == this->NIL )       // if no left son
    this->transplant(z, z->getRight()); // right goes in Z
  else if( z->getRight() == this->NIL ) // if no right son
    this->transplant(z, z->getLeft());  // left goes in Z
  else {
    y = this->minimum(z->getRight());     // search for successor
    if( y->getParent() != z ) {           // if Y is not Z father
      this->transplant(y, y->getRight()); // swap Y with Y->R
      y->setRight(z->getRight());
      y->getRight()->setParent(y);
    }
    this->transplant(z, y);               // swap Z with Y
    y->setLeft(z->getLeft());             // attach Z-> L to Y
    y->getLeft()->setParent(y);
  }

  delete z;
  return true;
}


// transplant a node attaching father
template <typename D, class Node>
void BinarySearchTree<D, Node>::transplant(Node *u, Node *v) {  
  if( u->getParent() == this->NIL)
    this->_root = v;
  else if(u->getParent()->getLeft() == u)
    u->getParent()->setLeft(v);
  else
    u->getParent()->setRight(v);

  // unconditioned assignement since using NIL node
  v->setParent(u->getParent());
}


template <typename D, class Node>
Node* BinarySearchTree<D, Node>::search(double &key) {
  auto tmp = this->_root;

  // while down to NIL or key found
  while(tmp != this->NIL && tmp->getKey() != key)
    tmp = key < tmp->getKey() ? tmp->getLeft() : tmp->getRight();
  
  return tmp;
}


// return minimum node
template <typename D, class Node>
Node* BinarySearchTree<D, Node>::minimum(Node *a) {
  auto tmp = a;

  // going down to left
  while(tmp->getLeft() != this->NIL)
    tmp = tmp->getLeft();
  return tmp;
}


// return maximum
template <typename D, class Node>
Node* BinarySearchTree<D, Node>::maximum(Node *a) {
  auto tmp = a;

  //going down to right
  while(tmp->getRight() != this->NIL)
    tmp = tmp->getRight();
  return tmp;
}


template <typename D, class Node>
Node* BinarySearchTree<D, Node>::successor(Node *x) {
  auto tmp = x;
  auto y = x->getRight();
  
  // if there is a right tree, return minimum
  if(y != this->NIL)
    return minimum(y);
  
  y = tmp->getParent();
  // goes up until tmp is left son or root found (=NIL)
  while(y != this->NIL && y->getRight() == tmp){
    tmp = y;
    y = y->getParent();
  }
  return y;
}


template <typename D, class Node>
Node* BinarySearchTree<D, Node>::predecessor(Node *x) {
  auto tmp = x;
  auto y = x->getLeft();
  
  // if there are left branch, return max
  if(y != this->NIL)
    return maximum(y);
  
  y = tmp->getParent();
  // goes up until tmp is right son or root found (=NIL)
  while(y != this->NIL && y->getLeft() == tmp){
    tmp = y;
    y = y->getParent();
  }
  return y;
}

 
template <typename D, class Node>
void BinarySearchTree<D, Node>::inorder(Node *tmp, void(*lambda)(Node*)) {  
  if(tmp != this->NIL) {
    inorder(tmp->getLeft(), lambda);
    lambda(tmp); // [Catcher](Tmp){/*implementation*/}
    inorder(tmp->getRight(), lambda);
  }
}


template <typename D, class Node>
void BinarySearchTree<D, Node>::postorder(Node *tmp, void(*lambda)(Node*)) {  
  if(tmp != this->NIL) {
    lambda(tmp); // [Catcher](Tmp){/*implementation*/}
    postorder(tmp->getLeft(), lambda);
    postorder(tmp->getRight(), lambda);
  }
}