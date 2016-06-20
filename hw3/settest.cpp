#include <iostream>
#include "setint.h"
using namespace std;

int main(){

	SetInt s1, s2, s3;

	//insert values into s1 and s2
	for (int i=1; i<6; i++){
		s1.insert(i);
		s2.insert(i*5);
	}

	//check if first function works
	if(*s1.first()==1 && *s2.first()==5)
		cout << "SUCCESS: first function works!" << endl;
	else
		cout << "FAIL: first item in s1 is: " << *s1.first() << 
		"and first item in s2 is: " << *s2.first() << endl;

	//check if next function works
	if(*s1.next()==2 && *s2.next()==10)
		cout << "SUCCESS: next function works!" << endl;
	else
		cout << "FAIL: next item in s1 is: " << *s1.next() << 
		"and next item in s2 is: " << *s2.next() << endl;

	//check S1 values (should cout: 1, 2, 3, 4, 5)
	cout << "S1 has values: " << *s1.first() << " ";
	for(int i=1; i<5; i++){
		cout << *s1.next() << " ";
	}	
	cout << endl;

	//check S2 values (should cout: 5, 10, 15, 20, 25)
	cout << "S2 has values: " << *s2.first() << " ";
	for(int i=1; i<5; i++){
		cout << *s2.next() << " ";
	}	
	cout << endl;

	//check if size function works
	if(s1.size()==5 && s2.size()==5 && s3.size()==0)	
		cout << "SUCCESS: insert and size functions both work." << endl;
	else
		cout << "FAIL: size of s1: " << s1.size() << " size of s2: " << s2.size()
		<< " size of s3: " << s3.size() << endl;

	//check if empty works
	if(!s1.empty() && !s2.empty() && s3.empty())
		cout << "SUCCESS: empty function works." << endl;
	else
		cout << "FAIL: empty function does not work" << endl;

	//check if exists function works
	if(s2.exists(25) && !s3.exists(0))
		cout << "SUCCESS: exists function works" << endl;
	else{
		cout << "FAIL: exists function does not work.";
		if(s2.exists(25)==false)
			cout << "Gives false for 25 in s2, which should be true. ";
		if(!s3.exists(0)==false)
			cout << "Also gives true for 0 in s3, which should be false";
		cout << endl;
	}

	cout << "Testing remove function:" << endl;

	s1.remove(4); //removes 4 from list
	s2.remove(15); //removes 15 from list

	//check S1 values and size (should cout: 1, 2, 3, 5)
	cout << "S1 has values: " << *s1.first() << " ";
	for(int i=1; i<4; i++){
		cout << *s1.next() << " ";
	}	
	cout << "and size: " << s1.size() << endl;


	//check S2 values and size (should cout: 5, 10, 20, 25)
	cout << "S2 has values: " << *s2.first() << " ";
	for(int i=1; i<4; i++){
		cout << *s2.next() << " ";
	}	
	cout << "and size: " << s2.size() << endl;

	s1.insert(10);
	s1.insert(25);

	SetInt s4, s5;
	for(int i=1; i<6; i++) //Set with values: 10, 20, 30, 40, 50
		s4.insert(i*10);

	/*
	 * testing Union function/operator
	 */
	s3 = s1.setUnion(s4); //s3 should be 1 2 3 5 10 20 30 40 50
	//cout s3 values
	cout << "S3 after union with S1 and S4 has values: " << *s3.first() << " ";
	for(int i=1; i<s3.size(); i++){
		cout << *s3.next() << " ";
	}	
	cout << endl;

	//cout s1 values
	s1 = s2 | s3; //s1 should be 5 10 20 25 1 2 3  30 40 50
	cout << "S1 after union with S2 and S3 has values: " << *s1.first() << " ";
	for(int i=1; i<s1.size(); i++){
		cout << *s1.next() << " ";
	}	
	cout << endl;

	/*
	 * testing Intersection function/operator
	 */
	s5 = s1.setIntersection(s2); //s5 should be 5 10 20 25
	//cout s5 values
	cout << "S5 after intersection with S1 and S2 has values: " << *s5.first() << " ";
	for(int i=1; i<s5.size(); i++){
		cout << *s5.next() << " ";
	}	
	cout << endl;

	s3 = s1 & s4; //s3 should be 10 20 30 40 50
	// cout s3 values
	cout << "S3 after intersection with S1 and S4 has values: " << *s3.first() << " ";
	for(int i=1; i<s3.size(); i++){
		cout << *s3.next() << " ";
	}	
	cout << endl;

	return 0;
}