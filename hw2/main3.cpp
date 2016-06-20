#include "stackdbl.h"
#include <iostream>
using namespace std;

int main(){
	StackDbl stack = StackDbl();

	//check if empty function works
	if(stack.empty()==true)
		cout << "SUCCESS: stack's empty function works." << endl;
	else
		cout << "FAIL: stack's empty function does not work." << endl;

	//check if push function works
	stack.push(0.5);
	stack.push(1.5);
	stack.push(2.5);
	if(stack.empty()==false)
		cout << "SUCCESS: stack is no longer empty." << endl;
	else
		cout << "FAIL: stack is still empty." << endl;

	//test top function and see if push function works
	cout << stack.top() << endl;
	if(stack.top()==2.5)
		cout << "SUCCESS: top function works and push function works. returned 2.5" << endl;
	else
		cout << "FAIL: top or push function did not work. return this instead: " << stack.top() <<endl;

	//testing pop function
	stack.pop();
	cout << stack.top()<< endl;
	cout << "If above number is 1.5, then SUCCESS. Else, FAIL." << endl;
	stack.pop();
	cout <<stack.top() << endl;
	cout << "If above number is 0.5, then SUCCESS. Else, FAIL." << endl;


	return 0;
}