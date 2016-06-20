#include "llistint.h"
#include <iostream>
using namespace std;

int main(){
	LListInt list1, list2, list3;

	for(int i=1; i<6; i++){
		list1.push_back(i); //integers 1 -5
		list2.push_back(i*2); //even 2-10
		list3.push_back(i*3); //multiples of 3 to 15
	}

	//checking if push back works
	cout << "List1 after push back: ";
	for(int i=0; i<5; i++){
		cout << list1.get(i) << " ";
	}
	cout << endl;

	cout << "List2 after push back: ";
	for(int i=0; i<5; i++){
		cout << list2.get(i) << " ";
	}
	cout << endl;

	cout << "List3 after push back: ";
	for(int i=0; i<5; i++){
		cout << list3.get(i) << " ";
	}
	cout << endl;

	//testing = operator
	LListInt list4 = list2;
	cout << "List4 after = operator: ";
	for(int i=0; i<5; i++){
		cout << list4.get(i) << " ";
	}
	cout << endl;
	
	//testing what happens when setting list4 to itself
	list4=list4;
	cout << "List4 after setting it to itself: ";
	for(int i=0; i<5; i++){
		cout << list4.get(i) << " ";
	}
	cout << endl;

	//testing copy constructor
	LListInt list5(list3);
	cout << "List5 after copy constructor: ";
	for(int i=0; i<5; i++){
		cout << list5.get(i) << " ";
	}
	cout << endl;

	return 0;
}