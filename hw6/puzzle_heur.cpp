#include "puzzle_heur.h"
#include "board.h"
#include <cmath>
using namespace std;

int PuzzleManhattanHeuristic::compute(const Board& b)
{
	int distance = 0;
	for(int i=0; i<b.size(); i++){
		for(int j=0; j<b.size(); i++){
			if(b[i]!=0 && b[i]!=i)
				distance += (abs(i/b.dim()-j/b.dim()) + abs(i%b.dim()-j%b.dim()));
		}
	}

	return distance;
}

int PuzzleOutOfPlaceHeuristic::compute(const Board& b)
{
	//number of tiles out of place
	int numTiles = 0;
	//start at index 1 to neglect tile 0/blank tile
	for(int i=1; i<b.size(); i++){
		if(b[i]!=i)
			numTiles++;
	}
	return numTiles;
}

int PuzzleBFSHeuristic::compute(const Board& b){
	return 0;
}
