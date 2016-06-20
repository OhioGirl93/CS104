#include "splaytree.h"
#include <iostream>
#include <string>
using namespace std;

int main() {
  SplayTree<int, char> tree;

  tree.insert(make_pair(11, 'A'));
    tree.print();

  tree.insert(make_pair(6,'B'));
    tree.print();

  tree.insert(make_pair(14,'C'));
    tree.print();

  tree.insert(make_pair(12,'D'));
    tree.print();

  tree.insert(make_pair(25, 'E'));
    tree.print();

  tree.insert(make_pair(19, 'F'));
    tree.print();

  tree.insert(make_pair(13, 'G'));
  tree.print();

  for(SplayTree<int,char>::iterator it = tree.begin(); it!=tree.end(); ++it)
    cout <<"(" <<(*it).first<< ", " << (*it).second << ")  ";

  cout << endl;
    return 0;

}