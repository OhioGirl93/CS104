#include <iostream>
#include <exception>
#include <cstdlib>
#include "bst.h"
#include <iostream>

template <class KeyType, class ValueType>
class SplayNode : public Node<KeyType, ValueType>
{
public:
  SplayNode (KeyType k, ValueType v, SplayNode<KeyType, ValueType> *p)
    : Node<KeyType, ValueType> (k, v, p)
    {}
  
  virtual ~SplayNode () {}
  
  virtual SplayNode<KeyType, ValueType> *getParent () const
    { return (SplayNode<KeyType,ValueType>*) this->_parent; }
  
  virtual SplayNode<KeyType, ValueType> *getLeft () const
    { return (SplayNode<KeyType,ValueType>*) this->_left; }
  
  virtual SplayNode<KeyType, ValueType> *getRight () const
    { return (SplayNode<KeyType,ValueType>*) this->_right; }

	SplayNode<KeyType, ValueType> * getUncle()
	{
		if(this->getParent()==NULL || this->getParent()->getParent()==NULL)
			return NULL;

		if(this->getGrandParent()->getLeft() == this->getParent())
			return this->getParent()->getParent()->getRight();
		return this->getParent()->getParent()->getLeft();
	}

	SplayNode<KeyType, ValueType> * getGrandParent()
	{
		if(this->getParent()==NULL || this->getParent()->getParent()==NULL)
			return NULL;
		return this->getParent()->getParent();
	}
};

/* -----------------------------------------------------
 * Splay Tree
 ------------------------------------------------------*/

template <class KeyType, class ValueType>
class SplayTree : public BinarySearchTree<KeyType, ValueType>
{
public:

  void insert (const std::pair<const KeyType, ValueType>& new_item)
  {
	//find parent
  	SplayNode<KeyType, ValueType> * parent = 
  	(SplayNode<KeyType, ValueType> *) this->root;

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
  	SplayNode<KeyType, ValueType> * new_node = 
  	new SplayNode<KeyType, ValueType>(new_item.first, new_item.second, parent);

  	//if this is first insert, set to root
  	if(this->root == NULL){
  		this->root = new_node;
  	}
  	else if(parent!=NULL){
  		//connect parent to new node
	  	if(parent->getKey() > new_item.first)
	  		parent->setLeft(new_node);
	  	else
	  		parent->setRight(new_node);
	  	splay(new_node);
	} 	
	
  }

  void splay(SplayNode<KeyType, ValueType> * curr)
  {
  	while(curr!=this->root){
  		//ROOT ZIG - parent is root
	  	if(curr->getParent()==this->root)
	  	{
	  		this->root = curr;
	  		curr->getParent()->setParent(curr);

	  		if(isRightChild(curr)){
		  		if(curr->getLeft()!=NULL){
		  			curr->getParent()->setRight(curr->getLeft());
		  			curr->getLeft()->setParent(curr->getParent());
		  		}
		  		else
		  			curr->getParent()->setRight(NULL);

		  		curr->setLeft(curr->getParent());
		  	}
		  	else{
		  		if(curr->getRight()!=NULL){
		  			curr->getParent()->setLeft(curr->getRight());
		  			curr->getRight()->setParent(curr->getParent());
		  		}
		  		else
		  			curr->getParent()->setLeft(NULL);

		  		curr->setRight(curr->getParent());
		  	}

	  		curr->setParent(NULL);
	  	}

	  	//RIGHT ZIG ZIG - Right child, Right Parent
	  	else if(isRightChild(curr) && isRightChild(curr->getParent()))
	  	{

	  		rightRotate(curr);

	  		SplayNode<KeyType, ValueType>* gp = curr->getGrandParent();
	  		bool parentIsRight = isRightChild(curr->getParent());

	  		curr->getParent()->setParent(curr);

	  		curr->getParent()->setRight(curr->getLeft());
	  		if(curr->getLeft()!=NULL){  			
	  			curr->getLeft()->setParent(curr->getParent());
	  		}

	  		curr->setLeft(curr->getParent());

	  		if(gp==NULL){
	  			this->root = curr;
	  			curr->setParent(NULL);

	  		}
	  		else{
	  			curr->setParent(gp);
	  			if(parentIsRight){
	  				gp->setRight(curr);
	  			}
	  			else
	  				gp->setLeft(curr);	  			
	  		}
	  	}

	  	//LEFT ZIG ZIG - Left child, Left Parent
	 	else if(isLeftChild(curr) && isLeftChild(curr->getParent()))
	 	{
	 		leftRotate(curr);

	 		SplayNode<KeyType, ValueType>* gp = curr->getGrandParent();
	 		bool parentIsRight = isRightChild(curr->getParent());

	 		curr->getParent()->setParent(curr);

	  		curr->getParent()->setLeft(curr->getRight());
	 		if(curr->getRight()!=NULL){
	  			curr->getRight()->setParent(curr->getParent());
	  		}

	  		curr->setRight(curr->getParent());

	  		if(gp==NULL){
	  			this->root = curr;
	  			curr->setParent(NULL);
	  		}
	  		else{
	  			curr->setParent(gp);
	  			if(parentIsRight){
	  				gp->setRight(curr);
	  			}
	  			else
	  				gp->setLeft(curr);
	  		}
	 	}

	  	// ZIG ZAG: Left Child, Right Parent, unzig then rotate
	  	else if(isLeftChild(curr) && isRightChild(curr->getParent()))
	  	{
	  		curr->getGrandParent()->setRight(curr);
	  		SplayNode<KeyType, ValueType> * grandparent = curr ->getGrandParent();
	  		curr->getParent()->setParent(curr);

	  		curr->getParent()->setLeft(curr->getRight());
	  		if(curr->getRight()!=NULL){
	  			curr->getRight()->setParent(curr->getParent());
	  		}

	  		curr->setRight(curr->getParent());
	  		curr->setParent(grandparent);
	 
	  		rightRotate(curr->getRight());
	  	}
	  	// ZIG ZAG: Right Child, Left Parent, unzig then rotate
	  	else if(isRightChild(curr) && isLeftChild(curr->getParent()))
	  	{
	  		curr->getGrandParent()->setLeft(curr);
	  		SplayNode<KeyType, ValueType> * grandparent = curr ->getGrandParent();
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
}

  SplayNode<KeyType, ValueType>* find (const KeyType & k)  
  {
	SplayNode<KeyType, ValueType>* temp = internalFind(k);
	if(temp!=NULL)
		splay(temp);
	return temp;
  }

private:
	
  	SplayNode<KeyType, ValueType>* internalFind(const KeyType& k) 
	{
		SplayNode<KeyType, ValueType> *curr = (SplayNode<KeyType, ValueType>* )this->root;
		while (curr){
			if (curr->getKey() == k) {
				return curr;
			}
			else if (k < curr->getKey()) {
				curr = curr->getLeft();
	      	}
	      	else {
				curr = curr->getRight();
	      	}
	    }

	    return NULL;
	}

	bool isRightChild(SplayNode<KeyType, ValueType> *node)
	{
		if(node->getParent()==NULL) return false;

		if(node->getParent()->getRight() == node)
			return true;
		else
			return false;
	}

	bool isLeftChild(SplayNode<KeyType, ValueType> *node)
	{
		if(node->getParent()==NULL) return false;

		if(node->getParent()->getLeft() == node)
			return true;
		else
			return false;
	}

	//When child and parent are both right childs, rotate and recolor
	void rightRotate(SplayNode<KeyType, ValueType> * node)
	{
		SplayNode<KeyType, ValueType> * greatGrandParent = NULL;
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

		node->getParent()->setParent(greatGrandParent);
	}

	//When child and parent are both left childs, rotate and recolor
	void leftRotate(SplayNode<KeyType, ValueType> * node)
	{
		SplayNode<KeyType, ValueType> * greatGrandParent = NULL;
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

		node->getParent()->setParent(greatGrandParent);
	}
};