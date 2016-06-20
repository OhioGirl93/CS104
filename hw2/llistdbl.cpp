#include "llistdbl.h"
#include <cstdlib>
#include <iostream>
using namespace std;

LListDbl::LListDbl()
{
  //initialize empty list
  head_ = NULL;
  tail_ = NULL;
  size_ = 0;
}

LListDbl::~LListDbl()
{
  //deallocate items
  clear();
}

bool LListDbl::empty() const
{
  return size_ == 0;
}

int LListDbl::size() const
{
  return size_;
}

void LListDbl::insert(int loc, const double& val)
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
void LListDbl::remove(int loc)
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

void LListDbl::set(int loc, const double& val)
{
  Item *temp = getNodeAt(loc);
  temp->val = val;
}

double& LListDbl::get(int loc)
{
  Item *temp = getNodeAt(loc);
  return temp->val;
}

double const & LListDbl::get(int loc) const
{
  Item *temp = getNodeAt(loc);
  return temp->val;
}

void LListDbl::clear()
{
  while(head_ != NULL){
    Item *temp = head_->next;
    delete head_;
    head_ = temp;
  }
  tail_ = NULL;
  size_ = 0;
}

LListDbl::Item* LListDbl::getNodeAt(int loc) const
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