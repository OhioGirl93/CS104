#include "rbbst.h"
#include <iostream>
#include <sstream>
#include <fstream>
#include <utility>
#include <vector>

using namespace std;

struct Rectangle {
    int ID;
    int length;
    int height;
};

//global variables
int boardLength, boardHeight, numTiles;
RedBlackTree<int, Rectangle*> rbtree;
RedBlackTree<int, pair<int, int> > solutions;
int **board;

bool isValid(){
	return false;
}

bool solverHelper(RedBlackTree<int, Rectangle*>::iterator& it){
	//base case
	if(it==rbtree.end()){
		return true;
	}
	//if not at the end, check if piece fits
	else{
		//pass in iterator and check if piece works
		//if not does not, work, back track and try again
		if(!isValid()){
			//back track
			//return false if back tracked to end and no solution exists
			return false;
		}
		else{ //if it does work, add and move on to next piece
			//add to solutions
			return solverHelper(++it);
		}
	}
}

bool solvePuzzle (RedBlackTree<int, Rectangle*>::iterator& it){
	return solverHelper(it);
}

int main(int argc, char* argv[]){

	if(argc<3){
		cout << "Missing filename. Takes inputfile outputfile." << endl;
		return -1;
	}

	ifstream infile (argv[1]);
	fstream outfile (argv[2]);

	string boardInfo;
	getline(infile, boardInfo);
	stringstream ss(boardInfo);

	ss >> boardLength;
	if(ss.fail()){
		cout << "Invalid length" << endl;
		return -1;
	}

	ss >> boardHeight;
	if(ss.fail()){
		cout << "Invalid height" << endl;
		return -1;
	}

	ss >> numTiles;
	if(ss.fail()){
		cout << "Invalid number of tiles" << endl;
		return -1;
	}

	string tileInfo;

	vector<int> tileIDs;
	vector<Rectangle*> rectangles;

	while(getline(infile, tileInfo)){
		int id, length, height;
		stringstream ss1(tileInfo);
		ss1 >> id;
		if(!ss1.fail()){
			ss1 >> length;
			if(!ss1.fail()){
				ss1 >> height;
				if(!ss1.fail()){
					Rectangle* r = new Rectangle();
					r->ID = id;
					r->length = length;
					r->height = height;
					cout << "Created tile: "<< id <<" " << length << "x"<<height << endl;
					tileIDs.push_back(id);
					rectangles.push_back(r);
				}
			}
		}
	}

	for(unsigned int i=0; i<tileIDs.size(); i++){
		pair<int, Rectangle*> p (tileIDs[i], rectangles[i]);
		rbtree.insert(p);
	}

	RedBlackTree<int, Rectangle*>::iterator it = rbtree.begin();

	board = new int*[boardHeight];
	for(int i=0; i<boardHeight; i++){
		board[i]=new int[boardLength];
	}

	if(solvePuzzle(it)){ //output board
		outfile << "Solutions" << endl;
	}
	else
		outfile << "no solution found" << endl;

	return 0;
}


