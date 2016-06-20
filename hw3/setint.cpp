#include "setint.h"
#include <iostream>

using namespace std;

//Default constructor - default to a list of capacity = 10
SetInt::SetInt()
{
	list_ = LListInt();
	size_ = 0;
}

//Destructor
SetInt::~SetInt()
{
	list_.clear();
}

//Returns the current number of items in the list 
int SetInt::size() const
{
	return size_;
}

//Returns true if the list is empty, false otherwise
bool SetInt::empty() const
{
	return size_==0;
}

//Inserts val into the set, do nothing if val already exists
void SetInt::insert(const int& val)
{
	if(exists(val))
		return;
	else{
		list_.insert(size_, val);
		size_++;
	}
}

//Removes the value at index, pos
void SetInt::remove(const int& val)
{
	if(!exists(val)) //checks if exists
		return;
	else{
		for(int i=0; i<size_; i++){
			if(list_.get(i)==val){
				list_.remove(i);
				size_--;
			}

		}
	}

}

//Returns true if the item is in the set
bool SetInt::exists(const int& val) const
{
	for(int i=0; i<size_; i++){
		if(list_.get(i)==val)
			return true;
	}
	return false;
}

/*
Return a pointer to the first item
and support future calls to next()
*/
int const* SetInt::first()
{
	if(!empty()){
		position = 0; //keeps track of next position
		return &(list_.get(0));
	}
	return NULL;
}

/*
Return a pointer to the next item
after the previous call to next
and NULL if you reach the end
*/
int const* SetInt::next()
{
	if(position<size_){
		position++;
		return &list_.get(position);
	}
	return NULL;
}

/*
Returns another (new) set that contains
the union of this set and "other"
*/
SetInt SetInt::setUnion(const SetInt& other) const
{
	if(this==&other) //check if trying to union itself
		return *this;

	SetInt uset;
	//add all values of current set's list to uset's list
	for(int i=0; i<size_; i++){
		uset.insert(list_.get(i));
	}

	//loop through other set, adding non-existing values
	for(int i=0; i<other.size_; i++){
		if(!uset.exists(other.list_.get(i))){
			uset.insert(other.list_.get(i));
		}
	}

	return uset; //return unioned set
}

/*
Returns another (new) set that contains
the intersection of this set and "other"
*/
SetInt SetInt::setIntersection(const SetInt& other) const
{
	if(this==&other) //check if tryin to intersect with itself
		return *this;

	SetInt iset;

	for(int i=0; i<size_; i++){ //loop through current set's list
		for(int j=0; j<other.size_; j++){ //loop through other's list
			if(this->list_.get(i)==other.list_.get(j)) //if values are equal, insert to iset
				iset.insert(other.list_.get(j));
		}
	}

	return iset;
}

SetInt SetInt::operator|(const SetInt& other) const
{
	if(this==&other)
		return *this;

	SetInt uset;
	//add all values of current set's list to uset's list
	for(int i=0; i<size_; i++){
		uset.insert(list_.get(i));
	}

	//loop through other set, adding non-existing values
	for(int i=0; i<other.size_; i++){
		if(!uset.exists(other.list_.get(i))){
			uset.insert(other.list_.get(i));
		}
	}
	return uset;

}

SetInt SetInt::operator&(const SetInt& other) const
{
	if(this==&other)
		return *this;

	SetInt iset;

	for(int i=0; i<size_; i++){ //loop through current set's list
		for(int j=0; j<other.size_; j++){ //loop through other's list
			if(this->list_.get(i)==other.list_.get(j)) //if values are equal, insert to iset
				iset.insert(other.list_.get(j));
		}
	}

	return iset;

}