#include <iostream>
#include "board.hpp"

Board::Board(){};

Board::Board
    (int height, int width, int game_amount, Player player_1, Player player_2, int in_a_row) 
    : height(height), width(width), game_amount(game_amount), player_1(player_1), player_2(player_2), in_a_row(in_a_row)
{
    // // Initiate tiles
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

            if (y == 0 && x == 0)
                top_left_tile = current;

            if (x == 0)
                first_in_row = current;

            // 0th neighbor.
            if (y > 0)
            {
                current->neighbors[0] = above;

                // Set 0th neighbors 4th neighbor to be the current tile.
                current->neighbors[0]->neighbors[4] = current;
            }

            // 1st neighbor.
            if (y > 0 && x < (width - 1))
            {
                current->neighbors[1] = above->neighbors[2];

                current->neighbors[1]->neighbors[5] = current;
            }

            // 6th neighbor.
            if (x > 0)
            {
                current->neighbors[6] = previous;

                current->neighbors[6]->neighbors[2] = current;
            }

            // 7th neighbor.
            if (x > 0 && y > 0)
            {
                current->neighbors[7] = above->neighbors[6];

                current->neighbors[7]->neighbors[3] = current;
            }

            if (y > 0)
                above = above->neighbors[2];
        }

        above = first_in_row;
    }
}

Board::~Board()
{
    // TODO
}

// Getters
int Board::get_game_amount()
{
    return game_amount;
}

Player Board::get_player_1()
{
    return player_1;
}

Player Board::get_player_2()
{
    return player_2;
}

int Board::get_width()
{
    return width;
}

int Board::get_height()
{
    return height;
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
    // Print spaces for formatting.
    std::cout << "     ";

    // Print chess notation letters.
    for(int x = 0; x < width; x++)
    {
        std::cout << char(x + 65) << "  ";
    }
    std::cout << std::endl;

    // Print second line.
    std::cout << "  + ";
    for(int x = 0; x < width; x++)
    {
        std::cout << " _ ";
    } 
    std::cout << std::endl;

    // Iterate and print the board tiles.
    for (int y = 0; y < height; y++)
    {
        for(int i = 0; i < std::to_string(height).length() - std::to_string(y+1).length(); i++)
        {
            std::cout << " ";
        }
        std::cout << y+1 << " | ";
        for (int x = 0; x < width; x++)
        {
            std::cout << ' ' << get_tile(x, y)->color << ' ';
        }
        std::cout << '\n';
    }
}
