/*
 * rbbst.h
 *
 * Date        Author    Notes
 * =====================================================
 * 2014-04-14  Kempe     Initial version
 * 2015-04-06  Redekopp  Updated formatting and removed
 *                         KeyExistsException
 */

#include <iostream>
#include <exception>
#include <cstdlib>
#include "bst.h"
 #include <iostream>

/* -----------------------------------------------------
 * Red-Black Nodes and Search Tree
 ------------------------------------------------------*/

enum Color {red, black};

template <class KeyType, class ValueType>
class RedBlackNode : public Node<KeyType, ValueType>
{
public:
  RedBlackNode (KeyType k, ValueType v, RedBlackNode<KeyType, ValueType> *p)
    : Node<KeyType, ValueType> (k, v, p)
    { color = red; }
  
  virtual ~RedBlackNode () {}
  
  Color getColor () const
    { return color; }
  
  void setColor (Color c)
    { color = c; }
  
  virtual RedBlackNode<KeyType, ValueType> *getParent () const
    { return (RedBlackNode<KeyType,ValueType>*) this->_parent; }
  
  virtual RedBlackNode<KeyType, ValueType> *getLeft () const
    { return (RedBlackNode<KeyType,ValueType>*) this->_left; }
  
  virtual RedBlackNode<KeyType, ValueType> *getRight () const
    { return (RedBlackNode<KeyType,ValueType>*) this->_right; }

	RedBlackNode<KeyType, ValueType> * getUncle()
	{
		if(this->getParent()==NULL || this->getParent()->getParent()==NULL)
			return NULL;

		if(this->getGrandParent()->getLeft() == this->getParent())
			return this->getParent()->getParent()->getRight();
		return this->getParent()->getParent()->getLeft();
	}

	RedBlackNode<KeyType, ValueType> * getGrandParent()
	{
		if(this->getParent()==NULL || this->getParent()->getParent()==NULL)
			return NULL;
		return this->getParent()->getParent();
	}
  
 protected:
  Color color;
};

/* -----------------------------------------------------
 * Red-Black Search Tree
 ------------------------------------------------------*/

template <class KeyType, class ValueType>
class RedBlackTree : public BinarySearchTree<KeyType, ValueType>
{
public:
  void print2 () const
  { 
    printRoot2 ((RedBlackNode<KeyType, ValueType> *)this->root);
    std::cout << "\n";
  }

  void printRoot2 (RedBlackNode<KeyType, ValueType> *r) const
  {
    if (r != NULL){
		std::cout << "[";
		printRoot2 (r->getLeft());
		std::cout << " (" << r->getKey() << ", " << r->getValue();
		if(r->getColor()==black)
			std::cout << ", B)" ;
		else
			std::cout << ", R)";
		printRoot2 (r->getRight());
		std::cout << "]";
    }
  }

  void insert (const std::pair<const KeyType, ValueType>& new_item)
  {

  	//if key already exists, overwrite with new value
  	if(this->find(new_item.first)!=this->end()){
  		(*(this->find(new_item.first))).second = new_item.second;
  	}

  	//if key DNE, make new node and add to tree
  	else{
  		//find parent
	  	RedBlackNode<KeyType, ValueType> * parent = 
	  	(RedBlackNode<KeyType, ValueType> *) this->root;

	  	while(parent!=NULL){
	  		if(new_item.first > parent->getKey()){
	  			if(parent->getRight()==NULL)
	  				break;
	  			else{
	  				parent = parent->getRight();
	  			}
	  		}

	  		else{
	  			if(parent->getLeft()==NULL)
	  				break;
	  			else{
	  				parent = parent->getLeft();
	  			}
	  		}
	  	}

	  	//create node
	  	RedBlackNode<KeyType, ValueType> * new_node = 
	  	new RedBlackNode<KeyType, ValueType>(new_item.first, new_item.second, parent);

	  	//if this is first insert, set to root and fix color
	  	if(this->root == NULL){
	  		this->root = new_node;
	  		fixTree(new_node);
	  	}

	  	else if(parent!=NULL){
	  		//connect parent to new node
		  	if(parent->getKey() > new_item.first)
		  		parent->setLeft(new_node);
		  	else
		  		parent->setRight(new_node);

		  	if(parent->getColor()!=black)
		  		fixTree(new_node);
		} 	
	}
  }

  void fixTree(RedBlackNode<KeyType, ValueType> * curr){

  	//Case 1 - Recolor Root
  	if(this->root == curr)
  	{
  		curr->setColor(black);
  	}
	
  	//Case 2/3 - Uncle = BLACK || NULL
  	else if(curr->getUncle()==NULL || curr->getUncle()->getColor()==black)
  	{
  	 	// A: 2 REDs: Left child, left parent
  	 	if(isLeftChild(curr) && isLeftChild(curr->getParent())){
  	 		leftRotate(curr);
  	 	}

	  	// B: 2 REDs: Right child, right parent
	  	else if(isRightChild(curr) && isRightChild(curr->getParent())){
	  		rightRotate(curr);
	  	}

	  	// C: Unzig Left Child, Right Parent, and then rotate
	  	else if(isLeftChild(curr) && isRightChild(curr->getParent()))
	  	{
	  		curr->getGrandParent()->setRight(curr);
	  		RedBlackNode<KeyType, ValueType> * grandparent = curr ->getGrandParent();
	  		curr->getParent()->setParent(curr);

	  		curr->getParent()->setLeft(curr->getRight());
	  		if(curr->getRight()!=NULL){
	  			curr->getRight()->setParent(curr->getParent());
	  		}

	  		curr->setRight(curr->getParent());
	  		curr->setParent(grandparent);

	  		rightRotate(curr->getRight());
	  	}
	  	// D: Unzig Right Child, Left Parent, and then rotate
	  	else if(isRightChild(curr) && isLeftChild(curr->getParent()))
	  	{
	  		curr->getGrandParent()->setLeft(curr);
	  		RedBlackNode<KeyType, ValueType> * grandparent = curr ->getGrandParent();
	  		curr->getParent()->setParent(curr);

	  		curr->getParent()->setRight(curr->getLeft());
	  		if(curr->getLeft()!=NULL){
	  			curr->getLeft()->setParent(curr->getParent());
	  		}
	  		curr->setLeft(curr->getParent());
	  		curr->setParent(grandparent);

	  		leftRotate(curr->getLeft());
	  	}
  	}

  	//Case 4 - Uncle = RED
  	else if(curr->getUncle()->getColor()==red)
  	{
  		//parent = black
  		curr->getParent()->setColor(black);
  		//uncle = black
  		curr->getUncle()->setColor(black);
  		//grandparent = red
  		curr->getGrandParent()->setColor(red);
  		//now check if grandparent is valid
  		fixTree(curr->getGrandParent());
  	}

}

private:

	bool isRightChild(RedBlackNode<KeyType, ValueType> *node)
	{
		if(node->getParent()==NULL) return false;

		if(node->getParent()->getRight() == node)
			return true;
		else
			return false;
	}

	bool isLeftChild(RedBlackNode<KeyType, ValueType> *node)
	{
		if(node->getParent()==NULL) return false;

		if(node->getParent()->getLeft() == node)
			return true;
		else
			return false;
	}

	//When child and parent are both right childs, rotate and recolor
	void rightRotate(RedBlackNode<KeyType, ValueType> * node)
	{
		RedBlackNode<KeyType, ValueType> * greatGrandParent = NULL;
		//grandparent is not root node
		if(node->getGrandParent()->getParent()!=NULL){
			//set greatGrandParent if it exists
			greatGrandParent = node->getGrandParent()->getParent();
			//if grandparent is left child, rotate
			if(isLeftChild(node->getGrandParent())){
				node->getGrandParent()->getParent()->setLeft(node->getParent());
			}
			else {//if grandparent is right child
				node->getGrandParent()->getParent()->setRight(node->getParent());
			}
		}
		else{ // if Grandparent is root node, reassign root
			this->root = node->getParent();
		}

		//if Parent was carrying a left, make it Grandparent's right
		node->getGrandParent()->setRight(node->getParent()->getLeft());
		if(node->getParent()->getLeft()!=NULL){
			node->getParent()->getLeft()->setParent(node->getGrandParent());
		}

		//set Grandparent's parent to Parent
		node->getGrandParent()->setParent(node->getParent());
		//set Parent's right to Grandparent
		node->getParent()->setLeft(node->getGrandParent());
		//Recolor
		node->getParent()->setColor(black);
		node->getGrandParent()->setColor(red);

		node->getParent()->setParent(greatGrandParent);
	}

	//When child and parent are both left childs, rotate and recolor
	void leftRotate(RedBlackNode<KeyType, ValueType> * node)
	{
		RedBlackNode<KeyType, ValueType> * greatGrandParent = NULL;
		//grandparent is not root node
		if(node->getGrandParent()->getParent()!=NULL){
			greatGrandParent = node->getGrandParent()->getParent();
			//if grandparent is left child, rotate
			if(isLeftChild(node->getGrandParent()))
				node->getGrandParent()->getParent()->setLeft(node->getParent());
			else //if grandparent is right child
				node->getGrandParent()->getParent()->setRight(node->getParent());
		}
		else{ // if Grandparent is root node, reassign root
			this->root = node->getParent();
		}

		node->getGrandParent()->setLeft(node->getParent()->getRight());
		//if Parent was carrying a right, make it Grandparent's left
		if(node->getParent()->getRight()!=NULL){
			node->getParent()->getRight()->setParent(node->getGrandParent());
		};

		//set Grandparent's parent to Parent
		node->getGrandParent()->setParent(node->getParent());
		//set Parent's right to Grandparent
		node->getParent()->setRight(node->getGrandParent());
		//Recolor
		node->getParent()->setColor(black);
		node->getGrandParent()->setColor(red);

		node->getParent()->setParent(greatGrandParent);

	}
};

