// DERIVED FROM EXAMPLE FILE PROVIDED BY TEACHER
// file board.cc
#include <iostream>
#include "board.h"
using namespace std;

Board::Board ( ) {
  // Iteration square
  Square* current = entrance;

  // Loop to last square
  for(int i = 0; i < width * height; i++)
  {
    current = current->neighbours[2];
  }
  // Set exit square
  exit = current;

  setNeighbours(entrance);
}

Board::~Board ( ) {
  // TODO
}

void Board::print ( ) {
  for(int i = 0; i < height; i++)
  {
    for(int j = 0; j < width; j++)
    {
      cout << " _ ";
    }
    cout << endl;
  }
}

// Iterate to the board to give back the square that is n steps next to it.
Square* moveSquares(int steps, Square* current)
{
  if(steps < 0)
  {
    for(int i = 0; i > steps; i--)
  {
    current = current->neighbours[6];
  }
  } else{
      for(int i = 0; i < steps; i++)
    {
      current = current->neighbours[2];
    }
  }
  
  return current;
}

void Board::setNeighbours(Square* current)
{
  for(int i = 0; i < height*width; i++)
  {
    current->neighbours[0] = moveSquares(-6, current);
    current->neighbours[1] = moveSquares(-5, current);
    current->neighbours[2] = moveSquares(1, current);
    current->neighbours[3] = moveSquares(7, current);
    current->neighbours[4] = moveSquares(6, current);
    current->neighbours[5] = moveSquares(5, current);
    current->neighbours[6] = moveSquares(-1, current);
    current->neighbours[7] = moveSquares(-7, current);

    current = moveSquares(i+1, entrance);
  }
}