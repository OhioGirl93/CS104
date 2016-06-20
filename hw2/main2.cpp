#include "alistint.h"
#include <iostream>
using namespace std;

int main(){
	//check if both constructors work
	AListInt list1;
	AListInt list2(15);

	//check if empty function works
	if(list1.empty() && list2.empty())
		cout << "SUCCESS: Lists are both empty initially." << endl;
	else
		cout << "FAIL: Lists are not both empty initially." << endl;

	//check if insert function works
	list1.insert(0,10);
	for(int i=0; i<15; i++) //set list 2 to multiples of 5 from 0 to 70
		list2.insert(i, i*5);

	//check if size function works and if insert function correctly inserted
	if(list1.size()==1)
		cout << "SUCCESS: List 1 successfully inserted and has size 1." << endl;
	else
		cout << "FAIL: List 1 does not have size 1. Instead, size = " << list1.size() << endl;
	if(list2.size()==15)
		cout << "SUCCESS: List 2 successfully inserted and has size 15." << endl;
	else
		cout << "FAIL: List 2 does not have size 15. Instead, size = " << list2.size() << endl;
	
	//check if get function works and if insert function correctly inserted
	if(list1.get(0)==10)
		cout << "SUCCESS: List 1 inserted 10 for the first element." << endl;
	else
		cout << "FAIL: List 1 did not insert 10 for the first element, but rather: " << list1.get(0) << endl;
	
	//check if resize function works
	list2.insert(15, 2);
	if(list2.size()==16){
		cout << "SUCCESS: List 2 resize works and size = 16. The new elements in the list: ";
		for(int i=0; i<list2.size(); i++){
			cout << list2.get(i) << " ";
		}
		cout << endl;
	}
	else{
		cout << "FAIL: List 2 resize does not work. The size is: " << list2.size() << " and the list consists of: ";
		for(int i=0; i<list2.size(); i++){
			cout << list2.get(i) << " ";
		}
		cout << endl;
	}

	//check if set function works
	list1.set(0, 99);
	if(list1.get(0)==99)
		cout << "SUCCESS: The value of List 1 at index 0 was set to 99." << endl;
	else
		cout << "FAIL: The value of List 1 at index 0 was not set to 99, but rather: " << list1.get(0) << endl;

	//check if insert function works from head/tail/middle
	list1.insert(0, 100); //List: 100, 99
	if(list1.size()==2 && list1.get(0)==100)
		cout << "SUCCESS: inserted at head and size = 2." << endl;
	else
		cout << "FAIL: failed to insert at head or increment size. Size: " << list1.size() 
		<< " List value at index 0: " << list1.get(0) << endl;

	list1.insert(2, 97);  //List: 100, 99, 97
	if(list1.size()==3 && list1.get(2)==97)
		cout << "SUCCESS: inserted at tail and size = 3." << endl;
	else
		cout << "FAIL: failed to insert at tail or increment size. Size: " << list1.size() 
		<< " List value at index 0: " << list1.get(2) << endl;

	list1.insert(2, 98);   //List: 100, 99, 98, 97
	if(list1.size()==4 && list1.get(2)==98)
		cout << "SUCCESS: inserted at head and size = 2." << endl;
	else
		cout << "FAIL: failed to insert in middle or increment size. Size: " << list1.size() 
		<< " List value at index 0: " << list1.get(2) << endl;

	//test if inserting at invalid positions
	list1.insert(10, 96);
	list1.insert(-1, 95);
	cout << "SUCCESS if two statements above state invalid positions." << endl;


	//check if remove function works from tail/head
	list2.remove(15);
	list2.remove(0);
	if(list2.size()==14){
		cout << "SUCCESS: 2 items where removed from List 2." << endl;
		if(list2.get(0)==5 && list2.get(13)==70){
			cout << "SUCCESS: List 2 now consists of: ";
			for(int i=0; i<list2.size(); i++){
				cout << list2.get(i) << " ";
			}
			cout << endl;
		}
		else{
			cout << "FAIL: List 2 now consists of: ";
			for(int i=0; i<list2.size(); i++){
				cout << list2.get(i) << " ";
			}
			cout << endl;
		}
	}
	else
		cout << "FAIL: 2 items were not removed from the list." << "The size is: " << list2.size() << endl;

	//check if remove function works in middle
	list2.remove(2);
	if(list2.size()==13 && list2.get(2)==20)
		cout << "SUCCESS: removed from middle and size = 13." << endl;
	else
		cout << "FAIL: failed to remove from middle. Size: " << list2.size() << " List value at index 2: "
		<< list2.get(2) << endl;

	//test if removing at invalid positions
	list2.remove(100);
	list2.remove(-1);
	cout << "SUCCESS if two statements above state invalid positions." << endl;

	return 0;
}