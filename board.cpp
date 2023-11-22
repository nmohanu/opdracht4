#include <iostream>
#include "board.hpp"

Board::Board()
{
    // Initiate tiles
    initialize_board();
}

Board::~Board()
{
    // TODO
}

// Return a tile that is x steps to the right of top left tile 
// and y steps below top left tile.
Tile* Board::get_tile(int x, int y)
{
    // Select top left tile.
    Tile* current = top_left_tile;

    // Move down.
    for (int j = 0; j < y; j++)
    {
        current = current->neighbors[4];
    }

    // Move to the right.
    for (int i = 0; i < x; i++)
    {
        current = current->neighbors[2];
    }

    return current;
}

// Print the board
void Board::print()
{
    // Print letters (chess board format)
    std::cout << "     a  b  c  d  e  f" << std::endl;
    std::cout << "   + _  _  _  _  _  _  " << std::endl;

    // Iterate and print the board tiles.
    for (int y = 0; y < height; y++)
    {
        std::cout << y+1 << " | ";
        for (int x = 0; x < width; x++)
        {
            std::cout << ' ' << get_tile(x, y)->color << ' ';
        }
        std::cout << '\n';
    }
}

void Board::initialize_board()
{
    top_left_tile = new Tile;
    Tile* current = nullptr;
    Tile* previous = top_left_tile;
    Tile* first_of_row = top_left_tile;
    for(int y = 0; y < height; y++)
    {
        for(int x = 0; x < width; x++)
        {
            // Skip first iteration since we need current tile to be the second tile.
            if(x == 0 && y == 0)
            {
                continue;
            }
            // Current becomes a new tile
            current = new Tile;

            // Set neighbour tiles if it's not the edge of the board.
            if(x > 0)
            {
                // Set previous tile's right neighbour to current tile.
                previous->neighbors[2] = current;

                // Set current tile's left neighbour to the previous tile.
                current->neighbors[6] = previous;
            } 
            else
            {
                // Keep track of first tile in a row se we can connect the rows.
                first_of_row == current;
            }
            
            previous = current;
        }
        // Set the pointer of the previous row's left most tile's below neighbour to the first tile of current row.
        if(y > 0)
        {
            get_tile(0, y-1)->neighbors[4] = first_of_row;
        }
    }
    // Set the rest of the neighbours.
    set_neighbours();
}

// initialize_board connected the first tile of each row,
// based on that, we set the rest of the neighbours for each tile.
void Board::set_neighbours()
{
    for(int y = 0; y < height; y++)
    {
        for(int x = 0; x < width; x++)
        {
            // Set left neighbour.
            if(x != 0)
            {
                get_tile(x, y)->neighbors[6] = get_tile(x-1, y);

                // Set left below neighbour.
                if(y != height-1)
                {
                    get_tile(x, y)->neighbors[5] = get_tile(x-1, y+1);
                }
            }
            // Set right neighbour.
            if(x != width-1)
            {
                get_tile(x, y)->neighbors[2] = get_tile(x+1, y);

                // Set right below neighbour.
                if(y != height-1)
                {
                    get_tile(x, y)->neighbors[5] = get_tile(x+1, y+1);
                }
            }
            // Set above neighbour.
            if(y != 0)
            {
                get_tile(x, y)->neighbors[0] = get_tile(x, y-1);

                // Set above left neighbour.
                if(x != 0)
                {
                    get_tile(x, y)->neighbors[8] = get_tile(x-1, y-1);
                }

                // Set above right neighbour.
                if(x != width-1)
                {
                    get_tile(x, y)->neighbors[1] = get_tile(x+1, y-1);
                }
            }
            // Set below neighbour.
            if(y != height-1)
            {
                get_tile(x, y)->neighbors[4] = get_tile(x, y+1);
            }
        }
    }
}
