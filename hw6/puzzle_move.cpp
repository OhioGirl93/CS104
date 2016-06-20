#include "puzzle_move.h"
using namespace std;

PuzzleMove::PuzzleMove(Board* board)
{
	b = board;
	g = 0;
	h = 0;
	prev = NULL;
	tileMove = -1;
}

// Constructor for subsequent search boards 
// (i.e. those returned by Board::potentialMoves() )
PuzzleMove::PuzzleMove(int tile, Board* board, PuzzleMove *parent)
{
	tileMove = tile;
	b = board;
	prev = parent;
	g = parent->g+1;
	h = 0;
}

// Destructor
PuzzleMove::~PuzzleMove()
{

}