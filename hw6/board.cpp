#include <iostream>
#include <iomanip>
#include <map>
#include <cmath>
#include <cstdlib>
#include <stdexcept>
#include "board.h"
#include <ostream>
using namespace std;

Board::Board(int dim, int numInitMoves, int seed )
{
  _size = dim*dim;
  _tiles = new int[_size];

  //set time to seed
  srand(seed);

  //fill tiles from 0 to size-1
  for(int i=0; i < _size; i++){
    _tiles[i] = i;
  }

  int blankLoc = 0;
  while(numInitMoves > 0){
    int r = rand()%4;
    int randNeighbor = -1;
    if(r == 0){
      int n = blankLoc - dim;
      if(n >= 0){
	randNeighbor = n;
      }
    }
    else if(r == 1){
      int w = blankLoc - 1;
      if(blankLoc % dim != 0){
	randNeighbor = w;
      }
    }
    else if(r == 2){
      int s = blankLoc + dim;
      if(s  < _size){
	randNeighbor = s;
      }
    }
    else {
      int e = blankLoc + 1;
      if(blankLoc % dim != dim-1){
	randNeighbor = e;
      }
    }
    if(randNeighbor > -1){
      _tiles[blankLoc] = _tiles[randNeighbor];
      _tiles[randNeighbor] = 0;
      blankLoc = randNeighbor;
      numInitMoves--;
    }
  }
}

Board::Board(){

}

//destructor
Board::~Board()
{
  delete [] _tiles;
}

//copy constructor
Board::Board(const Board& other)
{
  _size = other._size;
  _tiles = new int[_size];

  for(int i=0; i<_size; i++){
    _tiles[i] = other._tiles[i];
  }
}


void Board::move(int tile)
{
  int side_dim = dim();
  int tr, tc, br, bc;

  // find tile row and column
  int i=-1;
  while(_tiles[++i] != tile);

  tr = i / side_dim; 
  tc = i % side_dim;

  // find blank row and column
  int j=-1;
  while(_tiles[++j] != 0);

  br = j / side_dim;
  bc = j % side_dim;

  if( abs(static_cast<double>(tr-br)) + abs(static_cast<double>(tc-bc)) != 1){
    cout << "Invalid move of tile " << tile << " at ";
    cout << tr << "," << tc << " and blank spot at ";
    cout << br << "," << bc << endl;
    return;
  }
  // Swap tile and blank spot
  _tiles[j] = tile;
  _tiles[i] = 0;
}

map<int, Board*> Board::potentialMoves() const
{ 
  map<int, Board*> map;
  int index0 = -1;
  for(int i=0; i<_size; i++){
    if(_tiles[i]==0)
      index0 = i;
  }

  if(index0 == -1){
    cout << "Error: no possible moves" << endl;
    return map;
  }

  int row = index0/dim();
  int col = index0%dim();
  //check right
  if(col<dim()-1){
    Board* r = new Board(*this);
    r->move(_tiles[index0+1]);
    map[_tiles[index0+1]] = r;
  }
  //check left
  if(col>0){
    Board* l = new Board(*this);
    l->move(_tiles[index0-1]);
    map[_tiles[index0-1]] = l;
  }

  //check if tile above is inbounds and same col
  if(row>0) {
    Board* u = new Board(*this);
    u->move(_tiles[index0-dim()]);
    map[_tiles[index0-dim()]] = u;
  }

  //check if tile below is inbounds and same col
  if(row<dim()-1){
    Board* d = new Board(*this);
    d->move(_tiles[index0+dim()]);
    map[_tiles[index0+dim()]] = d;
  }

  return map;
  
}

bool Board::operator<(const Board& rhs) const
{
  for(int i=0; i<_size; i++){
    if(_tiles[i]<rhs._tiles[i])
      return true;
  }
  return false;
}

bool Board::solved() const
{
  for(int i=0; i<_size; i++){
    if(_tiles[i] != i) return false;
  }
  return true;
}

std::ostream& operator<<(std::ostream &os, const Board &b)
{
  int counter=0;
  int index=0;
  int endIndex = b.dim();
  while(counter<2*b.dim()+1){
    if(counter%2==0){
      b.printRowBanner(os);
    }
    else{
      os <<"|";
      for(;index < endIndex; index++){
        if(b._tiles[index]==0)
          os << "  |";
        else if(b._tiles[index]/10!=0)
          os << b._tiles[index] << "|";
        else
          os <<" " << b._tiles[index] << "|";
      }
      os << "\n";
      endIndex+=b.dim();
    }
    counter++;
  }
  return os;
}

const int& Board::operator[](int loc) const 
{ 
  return _tiles[loc]; 
}

int Board::size() const 
{ 
  return _size; 
}

int Board::dim() const
{
  return static_cast<int>(sqrt(_size));
}

void Board::printRowBanner(ostream& os) const
{
  int side_dim = dim();
  if(side_dim == 0) return;
  os << '+';
  for(int i=0; i < side_dim; i++){
    os << "--+";
  }
  os << endl;
}
