#include <iostream>
#include "board.hpp"

Board::Board() : Board(3, 3) { }

Board::Board(int width, int height) : width(width), height(height)
{
    Tile* first_in_row;
    Tile* previous;
    Tile* current;
    
    for (int y = 0; y < height; y++)
    {
        Tile* above;

        for (int x = 0; x < width; x++)
        {
            previous = current;
            current = new Tile();

            // Set tile color.
            if (x % 2 != y % 2)
            {
                current->color = '#';
            }
            else
            {
                current->color = ' ';
            }

            if (y == 0 && x == 0)
                top_left_tile = current;

            if (x == 0)
                first_in_row = current;

            // 0th neighbor.
            std::cout << "0\n";
            if (y > 0)
            {
                current->neighbors[0] = above;

                // Set 0th neighbors 4th neighbor to be the current tile.
                current->neighbors[0]->neighbors[4] = current;
            }

            // 1st neighbor.
            std::cout << "1\n";
            if (y > 0 && x < (width - 1))
            {
                current->neighbors[1] = above->neighbors[2];

                current->neighbors[1]->neighbors[5] = current;
            }

            // 6th neighbor.
            std::cout << "6\n";
            if (x > 0)
            {
                current->neighbors[6] = previous;

                current->neighbors[6]->neighbors[2] = current;
            }

            // 7th neighbor.
            std::cout << "7\n";
            if (x > 0 && y > 0)
            {
                current->neighbors[7] = above->neighbors[6];

                current->neighbors[7]->neighbors[3] = current;
            }

            above = above->neighbors[2];
        }

        above = first_in_row;
    }
}

Board::~Board()
{
    // TODO
}

Tile* Board::get_tile(int x, int y)
{
    Tile* current = top_left_tile;

    for (int i = 0; i < x; i++)
    {
        current = current->neighbors[2];
    }

    for (int j = 0; j < y; j++)
    {
        current = current->neighbors[4];
    }

    return current;
}

void Board::print()
{
    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            std::cout << get_tile(x, y)->color;
        }

        std::cout << '\n';
    }
}
