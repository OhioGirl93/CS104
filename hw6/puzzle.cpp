#include <iostream>
#include <cstdlib>
#include <stdlib.h>
#include <deque>
#include "board.h"
#include "puzzle_heur.h"
#include "puzzle_solver.h"
#include "puzzle_move.h"
using namespace std;

int main(int argc, char *argv[])
{
  if(argc < 5){
    cerr << "Usage: ./puzzle size initMoves seed heur" << endl;
    return 1;
  }

  int dim = atoi(argv[1]);
  int initMoves = atoi(argv[2]);
  int seed = atoi(argv[3]);
  int heur = atoi(argv[4]);

  Board* b = new Board(dim, initMoves, seed);

  PuzzleHeuristic* ph;
  if(heur == 0)
  	ph = new PuzzleBFSHeuristic;
  else if(heur == 1)
  	ph = new PuzzleOutOfPlaceHeuristic;
  else if(heur == 2)
  	ph = new PuzzleManhattanHeuristic;
  else{
  	cout << "Incorrect PH type. Please try again." << endl;
  	delete b; 
  	return 0;
  }

  bool isSolved = false;
  int tileMove;
  PuzzleSolver ps (*b, ph);
  while(!isSolved && tileMove!=0){
  	cout << *b << endl;
  	cout << "Enter tile number to move or -1 for a cheat:";
  	cin >> tileMove;
  	if(tileMove == -1){
  		ps.run();
  		cout << "Try this sequence: ";
  		for(unsigned int i=0; i<ps.getSolution().size(); i++){
  			cout << ps.getSolution()[i] << " ";
  		}
  		cout << endl;
  		cout << "(Expansions = " << ps.getNumExpansions() << ")" << endl;
  	}
  	else if(tileMove>=dim*dim){

  	}
  	else{
  		b->move(tileMove);
  		if(b->solved()) 
  			isSolved=true;
  	}
  }

  cout << "You win!" << endl;

  delete b;
  delete ph;

  return 0;
}
