#include "llistint.h"
#include <cstdlib>
#include <iostream>
using namespace std;

LListInt::LListInt()
{
  //initialize empty list
  head_ = NULL;
  tail_ = NULL;
  size_ = 0;
}

LListInt::~LListInt()
{
  //deallocate items
  clear();
}

bool LListInt::empty() const
{
  return size_ == 0;
}

int LListInt::size() const
{
  return size_;
}

void LListInt::insert(int loc, const int& val)
{
  //checks if loc is a valid index
  if(loc < 0 || loc > size_){
    cout << "Invalid location. Please enter a valid location" << endl;
    return;
  }

  //destination Item
  Item *dest = new Item();
  dest->val = val;

  //adding to empty list
  if(loc==0 && size_==0){
    dest->prev = NULL; dest->next = NULL;
    head_ = dest; tail_ = dest; size_++;
  }

  //adding to the head
  else if(loc==0){
    Item *temp = getNodeAt(0); //old head
    dest->prev = NULL; dest->next = temp;
    temp->prev = dest;
    size_++;
    head_ = dest;
  }

  //adding to the tail
  else if(loc==size_){
    Item *temp = getNodeAt(size_-1);
    dest->prev = temp; dest->next = NULL;
    temp->next = dest;
    size_++;
    tail_ = dest;
  }

  //adding somewhere in between
  else{
    //front = before dest and back = after dest
    Item *front = getNodeAt(loc-1); Item *back = getNodeAt(loc);
    //connect front/back to dest
    dest->val = val; dest->prev = front; dest->next = back; 
    front->next = dest; back->prev = dest;
    size_++;
  }

}

/**
 * Complete the following function
 */
void LListInt::remove(int loc)
{
  //checks if loc is a valid index
  if(loc < 0 || loc > size_-1){
    cout << "Invalid location. Please enter a valid location" << endl;
    return;
  }

  //removing only item
  if(loc==0 && size_==1){
    delete getNodeAt(0);
    size_--; head_ = NULL; tail_ = NULL;
  }

  //removing head
  else if(loc==0){
    delete getNodeAt(0);
    head_ = getNodeAt(1); head_->prev=NULL;
    size_--;
  }

  //removing tail
  else if(loc==size_-1){
    delete getNodeAt(size_-1);
    tail_ = getNodeAt(size_-2); tail_->next=NULL;
    size_--;
  }
  
  //removing somewhere in between
  else{
    //Items before and after loc
    Item *front = getNodeAt(loc-1); Item *back = getNodeAt(loc+1);
    delete getNodeAt(loc);   
    front->next = back; back->prev = front;
    size_--;
  }

}

void LListInt::set(int loc, const int& val)
{
  Item *temp = getNodeAt(loc);
  temp->val = val;
}

int& LListInt::get(int loc)
{
  Item *temp = getNodeAt(loc);
  return temp->val;
}

int const & LListInt::get(int loc) const
{
  Item *temp = getNodeAt(loc);
  return temp->val;
}

void LListInt::clear()
{
  while(head_ != NULL){
    Item *temp = head_->next;
    delete head_;
    head_ = temp;
  }
  tail_ = NULL;
  size_ = 0;
}

//Adds an item to the back of the list in O(1) time
void LListInt::push_back(const int& val)
{
	Item *newTail = new Item();
	newTail->val = val;
  if(size_==0){ //if list is empty
    tail_= newTail; head_= newTail;
    tail_->next = NULL; tail_-> prev = NULL;
    head_->next = NULL; head_->prev = NULL;
    size_++;
  }

  else{ //if list is not empty
    newTail->prev = tail_;
    newTail->next = NULL;
    tail_->next = newTail;
    if(size_==1) //if list is size 1, link head->next
      head_->next = newTail;
    tail_=newTail;
    size_++;
    
  }
}

//Copy constructor
LListInt::LListInt(const LListInt& other){
  head_ = NULL;
  tail_ = NULL;
  size_ = 0;
  //loop through values in other and push to this list
  for(Item* curr = other.head_; curr!=NULL; curr= curr->next){
    push_back(curr->val); 
  }
}

//Assignment Operator
LListInt& LListInt::operator=(const LListInt& other){
	if(this==&other){ //checking if same pointer
		cout << "Setting the list to itself does nothing." << endl;
		return *this;
	}
	if(head_){ //checking if head is NULL, deleting elements otherwise
		this->clear();
  }

  //loop through values in other and push to this list
  for(Item* curr = other.head_; curr!=NULL; curr= curr->next){
    push_back(curr->val);
  }
	return *this;
}

LListInt::Item* LListInt::getNodeAt(int loc) const
{
  Item *temp = head_;
  if(loc >= 0 && loc < size_){
    while(temp != NULL && loc > 0){
      temp = temp->next;
      loc--;
    }
    return temp;
  }
  else {
    //throw std::invalid_argument("bad location");
    return NULL;
  }
}