#include <iostream>
#include "alistint.h"

using namespace std;

AListInt::AListInt(){
	list =new int[10]; //default size = 10
	sizeOfArray=0; //number of items in array
	capacity = 10; //total capacity of array
}

AListInt::AListInt(int cap){
	list = new int[cap];
	sizeOfArray = 0;
	capacity = cap;
}

AListInt::~AListInt(){
	delete [] list;
}

 //Returns the current number of items in the list 
int AListInt::size() const{
	return sizeOfArray;
}
  
//Returns true if the list is empty, false otherwise
bool AListInt::empty() const{
	return sizeOfArray==0;
}

//Inserts val so it appears at index, pos
void AListInt::insert (int pos, const int& val){
	//if position is greater than size, error
	if(pos>sizeOfArray || pos<0){
		cout << "Invalid position. Please enter a valid position." << endl;
		return;
	}
	//if the size of the array has reached capacity, resize
	if(capacity==sizeOfArray)
		resize();
	//if adding to the end or adding to an empty list
	if(pos==sizeOfArray){
		list[pos]=val;
		sizeOfArray++;
	}
	//if inserting something in between
	else{
		for(int i=sizeOfArray; i>pos; i--){
			list[i]=list[i-1];
		}
		list[pos] = val;
		sizeOfArray++;
	}
}

//Removes the value at index, pos
void AListInt::remove (int pos){
	//check if valid position in list
	if(pos>sizeOfArray-1 || pos<0){
		cout << "Invalid position. Please enter a valid position." << endl;
		return;
	}
	//if removing the end or only item in list
	if(pos==sizeOfArray)
		sizeOfArray--;
	//if removing somewhere in between
	else{
		for(int i=pos; i<sizeOfArray; i++){
			list[i]=list[i+1];
		}
		sizeOfArray--;
	}
}

//Overwrites the old value at index, pos, with val
void AListInt::set (int position, const int& val){
	list[position] = val;
}

//Returns the value at index, pos
int& AListInt::get (int position){
	return list[position];
}

//Returns the value at index, pos
int const & AListInt::get (int position) const{
	return list[position];
}

//Should double the size of the list maintaining its contents
void AListInt::resize(){
	int *newList = new int [capacity*2];
	for(int i=0; i<capacity; i++){
		newList[i] = list[i];
	}
	delete [] list; //delete old
	list = newList;
	capacity = capacity*2; //double capacity
}