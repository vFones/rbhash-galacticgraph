#include <trees/redblacktree.hpp>
#include <other/debug.hpp>

#include "binarysearchtree.cpp" // include for templated implementation workaround


// left rotate a node for balancing
template <typename D, class Node> // aka move down
void RedBlackTree<D, Node>::leftRotate(Node *x) { // O(1) op keeping BST property
  Node *y = x->getRight();  // set y
  x->setRight(y->getLeft());    // move l-subtree of y to r-subtree of x

  if ( y->getLeft() != this->NIL )
    y->getLeft()->setParent(x);
  
  y->setParent(x->getParent()); // link fathers

  if ( x->getParent() == this->NIL )
    this->_root = y;            // if is X was root
  else if ( x == x->getParent()->getLeft() )
    x->getParent()->setLeft(y);
  else
    x->getParent()->setRight(y);

  y->setLeft(x);
  x->setParent(y);
}


//rotate a node to right (aka move down) keeping BST property
template <typename D, class Node>
void RedBlackTree<D, Node>::rightRotate(Node *x) {
  Node *y = x->getLeft(); 
  x->setLeft(y->getRight());

  if ( y->getRight() != this->NIL ) 
    y->getRight()->setParent(x);
  
  y->setParent(x->getParent());

  if ( x->getParent() == this->NIL )
    this->_root = y;
  else if ( x == x->getParent()->getLeft() ) 
    x->getParent()->setLeft(y); 
  else
    x->getParent()->setRight(y);
  
  y->setRight(x);
  x->setParent(y);
}


template <typename D, class Node>
void RedBlackTree<D, Node>::insertFix(Node *x) { // O(log n)
  Node *y;
  while(x->getParent()->isRed()) {
    if(x->getParent() == x->getParent()->getParent()->getLeft()) {
      y = x->getParent()->getParent()->getRight();
      if(y->isRed()) { // CASE 1: parent of x and uncle are RED
        x->getParent()->setBlack();
        y->setBlack(); // change their color and 
        x->getParent()->getParent()->setRed();
        x = x->getParent()->getParent(); // move point to grand father
      } else { // CASE 2: uncle is BLACK
          if(x == x->getParent()->getRight()) { // x is right son
            x = x->getParent(); // move upper
            leftRotate(x);  // then rotate so x became left son
          } // CASE 3: // uncle is BLACK but x is left son
          x->getParent()->setBlack();
          x->getParent()->getParent()->setRed();
          rightRotate(x->getParent()->getParent()); // compression aka same BH
      }
    } else {
      y = x->getParent()->getParent()->getLeft();
      if(y->isRed()) { // CASE 1: parent of x and uncle are RED
        x->getParent()->setBlack();
        y->setBlack(); // change their color and 
        x->getParent()->getParent()->setRed();
        x = x->getParent()->getParent(); // move point to grand father
      } else { // CASE 2: uncle is BLACK
          if(x == x->getParent()->getLeft()) { // x is left son
            x = x->getParent(); // move upper
            rightRotate(x);  // then rotate so x became right son
          } // CASE 3: // uncle is BLACK but x is left son
          x->getParent()->setBlack();
          x->getParent()->getParent()->setRed();
          leftRotate(x->getParent()->getParent()); // compression aka same BH
      }
    }
  }
  this->_root->setBlack();
}


template <typename D, class Node>
Node* RedBlackTree<D, Node>::insertNode(double &k, D &d) {
  auto z = BinarySearchTree<D, Node>::insertNode(k, d); // BST insert
  z->setRed(); // set flag as red
  this->insertFix(z); // fix property
  return z;
}


template <typename D, class Node>
void RedBlackTree<D, Node>::deleteFix(Node *x) {
  Node *w;
  
  while( x != this->_root && x->isBlack() ) {
    if( x == x->getParent()->getLeft() ) {
      w = x->getParent()->getRight();

      if ( w->isRed() ) { //////////// 
        w->setBlack();  //////////  CASE
        x->getParent()->setRed(); //// 1
        leftRotate(x->getParent());
        w = x->getParent()->getRight();
      }

      if ( w->getLeft()->isBlack() &&  w->getRight()->isBlack() ) {
        w->setRed();          ////// CASE
        x = x->getParent();   //////  2
      }
      else { ///////
        if ( w->getRight()->isBlack() ) {
          w->getLeft()->setBlack(); //// CASE
          w->setRed();              ////   3
          rightRotate(w);           ////
          w = x->getParent()->getRight();
        }
        ///////   CASE 
        w->setColor(x->getParent()->getColor());
        x->getParent()->setBlack(); ////
        w->getRight()->setBlack(); /////   4
        leftRotate(x->getParent()); ////
        x = this->_root; ///////////////
      }
    }
    else { // same as upper code but swapped left and right
      w = x->getParent()->getLeft();

      if ( w->isRed() ) { ////////
        w->setBlack();     //////////  CASE
        x->getParent()->setRed();/////
        rightRotate(x->getParent());/// 1
        w = x->getParent()->getLeft();//
      }

      if ( w->getRight()->isBlack() && w->getLeft()->isBlack() ) {
          w->setRed(); //////// CASE
          x = x->getParent();//// 2
      }
      else {
        if ( w->getLeft()->isBlack() ) { //
          w->getRight()->setBlack(); /////
          w->setRed(); //////////// CASE
          leftRotate(w); //////////   3
          w = x->getParent()->getLeft();//
        }
        /////////////////  CASE 4
        w->setColor(x->getParent()->getColor());
        x->getParent()->setBlack();
        w->getLeft()->setBlack();
        rightRotate(x->getParent());
        x = this->_root;
      }
    }
  }
  x->setBlack(); // (Cormen pag. 270)
}


// delete a node if exist and fixup
template <typename D, class Node>
bool RedBlackTree<D, Node>::deleteNode(double &k) {
  auto z = this->search(k);
  
  auto y = z;
  auto y_original_color = y->getColor();

  if(z == this->NIL)
    return false;
  
  Node *x;
  
  // when deleting z, y will be the "successor"
  // so must check if is respecting RB property
  // saving his color
  if( y->getLeft() == this->NIL ) {
    x = z->getRight();
    this->transplant(z, z->getRight());
  }
  else if( z->getRight() == this->NIL ) {
    x = z->getLeft();
    this->transplant(z, z->getLeft());
  }
  else {
    // y has no left child
    y = this->minimum(z->getRight());
    y_original_color = y->getColor();

    // we track the color of new positional node
    x = y->getRight();

    if( y->getParent() == z ) //y righson of z
      x->setParent(y);
    else { // must inherit right son of z
      this->transplant(y, y->getRight());
      y->setRight(z->getRight());
      y->getRight()->setParent(y);
    }

    // inherit left son of z
    this->transplant(z, y);
    y->setLeft(z->getLeft());
    y->getLeft()->setParent(y);

    // y is the old z and so got same color
    y->setColor(z->getColor());
  }
  
  
  //  fix black root
  //  fix two red nodes 
  //  fix Black High lose
  if(y_original_color == BLACK)
    deleteFix(x);
  
  delete z;
  return true;
}


template <typename D, class Node>
void RedBlackTree<D, Node>::print() {
  this->inorder(this->_root, [](Node *tmp) {
    std::cout<<tmp; });
}
