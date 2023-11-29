#include <iostream>
#include "board.hpp"

// Ask user for info about the board size, amount of games, etc.
Board ask_info();

// The main game loop, this is where the games are played.
void game_loop(Board); 

// Ask user for int input.
int ask_int();

// Ask user for x coordinate (y coordinate is an int so we use ask_int() for that).
int ask_x_coordinate();

// Main
int main()
{
    game_loop(ask_info());
    return 0;
}

// Ask user for board info and return the boar to be used.
Board ask_info()
{
    std::cout << "Choose a board height." << std::endl;
    int height = ask_int();
    std::cout << "Choose a board width." << std::endl;
    int width = ask_int();
    std::cout << "Choose the amount of games you would like to play." << std::endl;
    int game_amount = ask_int ();

    Board board(height, width, game_amount);

    std::cout << "Lol.";

    return board;
}

// Ask user for int.
int ask_int()
{
    int i;
    std::cin >> i;
    return i;
}

// Ask x coordinate as chess notation and convert back to int.
int ask_x_coordinate()
{
    char x;
    std::cin >> x;
    return int(x) - 'A';
}

// Game loop.
void game_loop(Board board)
{
    while (board.get_game_amount() > 0)
    {
        board.print();
        std::cout << "Select x coordinate (a-MAX): " << std::endl;
        int x = ask_x_coordinate();
        std::cout << "Select y coordinate (1-MAX): " << std::endl;
        int y = ask_int() - 1;
        board.get_tile(x, y)->color = 'X';
    }
}
