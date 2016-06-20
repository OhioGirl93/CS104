#include "puzzle_solver.h"
using namespace std;

// Constructor (makes a copy of the Board and stores it in b_)
//  Also takes a PuzzleHeuristic which will score boards
PuzzleSolver::PuzzleSolver(const Board &b, PuzzleHeuristic* ph)
{
	_ph = ph;
	_b = b;
	_expansions =0;
}

// Destructor
PuzzleSolver::~PuzzleSolver()
{
}

//Default Constructor
PuzzleSolver::PuzzleSolver()
{
}

// Run the A* search and builds the solution and tracks
// the number of expansions
void PuzzleSolver::run()
{
	//Puzzle Move comparator
	PuzzleMoveBoardComp bcomp;
	PuzzleMoveScoreComp scomp;
	//create open set and add the first board to it
	Heap<PuzzleMove*, PuzzleMoveScoreComp> openSet (2, scomp);

	//starting position of the board
	PuzzleMove* parent = new PuzzleMove(&_b);

	parent->h = _ph->compute(_b);
	openSet.push(parent);

	//check parent off as visited
	PuzzleMoveSet closedSet (bcomp);
	closedSet.insert(parent);

	while(!openSet.empty()){

		PuzzleMove* s = openSet.top();
		openSet.pop();

		if(s->b->solved()){

			_solution.push_front(s->tileMove);

			//back track and add all previous tile numbers
			while(s->prev != NULL){
				_solution.push_front(s->tileMove);
				s = s->prev;
			}
			return;
		}
		//potential moves of the board from current position
		map<int, Board*> potMoves = (s->b)->potentialMoves();

		for(map<int, Board*>::iterator it = potMoves.begin(); it != potMoves.end(); ++it){
			//create potential move
			PuzzleMove* p = new PuzzleMove(it->first, it->second, s);
			//compute and set move's heuristic value 
			p->h = _ph->compute(*(it->second));
			//add to potential move to the set if it has not been visited
			if(closedSet.find(p) == closedSet.end()){
				closedSet.insert(p);
				openSet.push(p);
				_expansions++;
			}
			else{
				delete p->b;
				delete p;

			}
		}	
	}	
}

// Return the solution deque
std::deque<int> PuzzleSolver::getSolution()
{
	return _solution;
}

// Return how many expansions were performed in the search
int PuzzleSolver::getNumExpansions()
{
	return _expansions;
}
