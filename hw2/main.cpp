#include "llistdbl.h"
#include <iostream>

using namespace std;

int main() {
    //create list
	LListDbl *list = new LListDbl();
	
	//check if empty() works
	if(list->empty())
		cout << "SUCCESS: List is empty initially." << endl;
	else 
		cout << "FAIL: List is not empty initially when it should be." << endl;

    //list: 0.5, 1.5, 2.5
	list->insert(0, 0.5);
	list->insert(1, 1.5);
	list->insert(2, 2.5); 

	//check if items were added/if insert() works
	if(!list->empty())
		cout << "SUCCESS: Items added successfully" << endl;
	else
		cout << "FAIL: Items did not add" << endl;

	//check is size() works
	if (list->size()==3)
		cout << "SUCCESS: List has size 3 after insertions." << endl;
	else
    	cout << "FAIL: List has size " << list->size() << " after insertions." << endl;

    //check if get() works
    if(list->get(1)==1.5)
    	cout << "SUCCESS: the value at index 1 is 1.5" << endl;
    else
    	cout << "FAIL: the value returned was not 1.5, but rather: " << list->get(0) << endl;

    list->remove(1); //List: 0.5, 2.5

    //check if remove() reduced the size
    if(list->size()==2)
    	cout << "SUCCESS: Size is now 2 after removal." << endl;
    else
    	cout << "FAIL: Size is not 2 after removal, but rather: " << list->size() << endl;

    //check if remove() linked the lists correctly
	 if(list->get(1)==2.5)
	   	cout << "SUCCESS: previous index 1 was deleted and is now 2.5." << endl;
	 else
	    cout << "FAIL: current index is not 2.5, but rather: " << list->get(1) << endl;

    list->set(0, 3.5); //List: 3.5, 2.5

    //check if set() works
	if(list->get(0)==3.5)
    	cout << "SUCCESS: previous index 0 was replaced and is now 3.5." << endl;
    else
    	cout << "FAIL: index is not 3.5, but rather: " << list->get(1) << endl;

    //test inserting in non-empty list at head
    list->insert(0, 4.5); //list should be: 4.5, 3.5, 2.5
    if(list->size()==3 && list->get(0)==4.5)
    	cout << "SUCCESS: inserted at head in non-empty list and size = 2." << endl;
    else
    	cout << "FAIL: failed to either insert or increment size. Size: " << list->size() 
    	<< " List value at head: " << list->get(0) << endl;

    //test inserting in non-empty list at tail
    list->insert(list->size(), 5.5); //list should be: 4.5, 3.5, 2.5, 5.5
    if(list->size()==4 && list->get(list->size()-1)==5.5)
    	cout << "SUCCESS: inserted at tail in non-empty list and size = 3." << endl;
    else
    	cout << "FAIL: failed to either insert or increment size. Size: " << list->size() 
    	<< " List value at tail: " << list->get(list->size()-1) << endl;

    //test inserting in non-empty list in middle
    list->insert(1, 6.5); //list should be 4.5, 6.5, 3.5, 2.5, 5.5
    if(list->size()==5 && list->get(1)==6.5)
    	cout << "SUCCESS: inserted at head in non-empty list and size = 4." << endl;
    else
    	cout << "FAIL: failed to either insert or increment size. Size: " << list->size() 
    	<< " List value at index 1: " << list->get(1) << endl;

    //test inserting at invalid locations
    list->insert(-1, 7.5);
    list->insert(10, 8.5);
    cout << "SUCCESS if two statements above state invalid location." << endl;

    //test removing from head
    list->remove(0); //list: 6.5, 3.5, 2.5, 5.5
    if(list->size()==4 && list->get(0)==6.5)
    	cout << "SUCCESS: removed head in non-empty list and size = 4." << endl;
    else
    	cout << "FAIL: failed to remove head or decrement size. Size: " << list->size() 
    	<< " List value at head: " << list->get(0) << endl;

    //test removing from middle
    list->remove(2); //list: 6.5, 3.5, 5.5
    if(list->size()==3 && list->get(2)==5.5)
    	cout << "SUCCESS: removed in middle in non-empty list and size = 3." << endl;
    else
    	cout << "FAIL: failed to remove head or decrement size. Size: " << list->size() 
    	<< " List value at index 2: " << list->get(2) << endl;

    //test removing from tail
    list->remove(list->size()-1); //list: 6.5, 3.5
    if(list->size()==2 && list->get(list->size()-1)==3.5)
    	cout << "SUCCESS: removed head in non-empty list and size = 2." << endl;
    else
    	cout << "FAIL: failed to remove head or decrement size. Size: " << list->size() 
    	<< " List value at tail: " << list->get(list->size()-1) << endl;

    //test removing from invalid locations
    list->remove(10);
    list->remove(-1);
    cout << "SUCCESS if two statements above state invalid location." << endl;


    list->clear();
    //check if clear() works
	if (list->size()==0)
		cout << "SUCCESS: List has size 0 after clearing." << endl;
	else
    	cout << "FAIL: List has size " << list->size() << " after clearing." << endl;

    //deallocate
	delete list;
	return 0;
}