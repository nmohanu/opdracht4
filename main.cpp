#include <iostream>
#include "board.hpp"
#include "input.hpp"

// The main game loop, this is where the games are played.
void game_loop(Board&); 

// Set player to pc or human.
void set_player_type(Player&);

// Main
int main()
{
    // Players.
    Player player_1;
    Player player_2;
    
    // Board info.
    std::cout << "Choose a board height.\n";
    int height = ask_int();
    std::cout << "Choose a board width.\n";
    int width = ask_int();
    std::cout
        << "Choose the amount of games you would like to play.\n";
    int game_amount = ask_int();
    std::cout << "How many in a row to win?\n";
    int in_a_row = ask_int(std::max(height, width));

    // Player 1 info.
    std::cout << "Player 1: Computer or Human? C/H\n";
    set_player_type(player_1);
    std::cout
        << "Player 1: Select a symbol to represent your tiles:\n";
    player_1.color = ask_char();

    // Player 2 info.
    std::cout << "Player 2: Computer or Human? C/H\n";
    set_player_type(player_2);
    std::cout
        << "Player 2: Select a symbol to represent your tiles:\n";
    player_2.color = ask_char();
    
    Board board
        (height, width, game_amount, player_1, player_2, in_a_row);

    game_loop(board);

    std::cout << "The games are over!" << std::endl;
    std::cout << "Player 1: " << board.get_player_1().wins << " wins." << std::endl;
    std::cout << "Player 2: " << board.get_player_2().wins << " wins." << std::endl;
    for(int i = 0; i < game_amount; i++)
    {
        std::cout << "Game " << i << " took " << board.turn_amount_of_games[i] << " turns." << std::endl;
    }

    return 0;
}

// Game loop.
void game_loop(Board& board)
{
    while (board.get_game_amount() > 0)
    {
        board.player_takes_turn(board.get_current_turn() % 2);
        if (!board.check_stalemate())
            board.check_if_won();
    }
}

// Set player to human or conmputer.
void set_player_type(Player& player)
{
    char player_type = ask_char();

    if(player_type == 'C' || player_type == 'c')
    {
        player.is_human = false;
    }
    else if(player_type != 'H' && player_type != 'h')
    {
        std::cout << "Sorry, incorrect response!" << std::endl;
        set_player_type(player);
    }
}
