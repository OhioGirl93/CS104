#include "llistdbl.h"
#include "stackdbl.h"
#include <iostream>
using namespace std;

//Constructor
StackDbl::StackDbl(){
	list_ = LListDbl(); //initialize list_
}

//Destructor
StackDbl::~StackDbl(){
	list_.clear();
}

//Returns true if the stack is empty, false otherwise
bool StackDbl::empty() const{
	return list_.empty();
}

//Pushes a new value, val, onto the top of the stack
void StackDbl::push(const double& val){
	list_.insert(list_.size(), val);
}

//Returns the top value on the stack
double const &  StackDbl::top() const{
	return list_.get(list_.size()-1);
}

//Removes the top element on the stack
void StackDbl::pop(){
	list_.remove(list_.size()-1);
}