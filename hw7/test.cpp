#include "rbbst.h"
#include <iostream>
#include <utility>

using namespace std;

int main(){
	RedBlackTree<int, char>* tree = new RedBlackTree<int,char>();

	cout << "Constructed Tree" << endl;

	cout << "Insert 10, A" << endl;
	pair<int, char> p1(10,'a');
	tree->insert(p1);
	tree->print2();
	cout << endl;

	cout << "Insert Duplicate 10, X" << endl;
	pair<int, char> p123(10,'x');
	tree->insert(p123);
	tree->print2();
	cout << endl;

	cout << "Insert 20, B" << endl;
	pair<int, char> p2(20,'b');
	tree->insert(p2);
	tree->print2();
	cout << endl;

	cout << "Insert 30, C" << endl;
	pair<int, char> p3(30,'c');
	tree->insert(p3);
	tree->print2();
	cout << endl;


	cout << "Insert 15, D" << endl;
	pair<int, char> p4(15,'d');
	tree->insert(p4);
	tree->print2();
	cout << endl;

	cout << "Insert 25, E" << endl;
	pair<int, char> p5(25,'e');
	tree->insert(p5);
	tree->print2();
	cout << endl;

	cout << "Insert 12, F" << endl;
	pair<int, char> p6(12,'f');
	tree->insert(p6);
	tree->print2();
	cout << endl;

	cout << "Insert 5, G" << endl;
	pair<int, char> p7(5,'g');
	tree->insert(p7);
	tree->print2();
	cout << endl;
	
	cout << "Insert 3, H" << endl;
	pair<int, char> p8(3,'h');
	tree->insert(p8);
	tree->print2();
	cout << endl;

	cout << "Insert 8, I" << endl;
	pair<int, char> p9(8,'i');
	tree->insert(p9);
	tree->print2();
	cout << endl;

	cout << "Insert 27, j" << endl;
	pair<int, char> p10(27,'j');
	tree->insert(p10);
	tree->print2();
	cout << endl;

	cout << "Insert 40, k" << endl;
	pair<int, char> p11(40,'k');
	tree->insert(p11);
	tree->print2();
	cout << endl;

	cout << "Insert 50, z" << endl;
	pair<int, char> p14(50,'z');
	tree->insert(p14);
	tree->print2();
	cout << endl;

	cout << "Insert 45, l" << endl;
	pair<int, char> p12(45,'l');
	tree->insert(p12);
	tree->print2();
	cout << endl;

	cout << "Insert 9, m" << endl;
	pair<int, char> p13(9,'m');
	tree->insert(p13);
	tree->print2();
	cout << endl;
	
	
	cout << "Testing Iteration:" << endl;
	for(RedBlackTree<int,char>::iterator it = tree->begin(); it!=tree->end(); ++it){
		cout << (*it).first << " ";
	}
	cout << endl;

	return 0;
}