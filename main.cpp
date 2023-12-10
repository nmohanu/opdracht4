#include <iostream>
#include "board.hpp"
#include "input.hpp"

#include <fstream>

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

    player_1.color = 'a';
    player_2.color = 'b';

    player_1.is_human = false;
    player_2.is_human = false;

    player_1.wins = 0;
    player_2.wins = 0;

    for (int i = 2; i < 100; i++)
    {
        Board board(i, i, 20, player_1, player_2, i);

        game_loop(board);

        player_1.wins = 0;
        player_2.wins = 0;
    }

    return 0;
}

// Game loop.
void game_loop(Board& board)
{
    int start_game_amount = board.get_game_amount();
    int total_turns = 0;

    while (board.get_game_amount() > 0)
    {
        board.player_takes_turn(board.get_current_turn() % 2);
        if (!board.check_stalemate())
        {
            if (board.check_if_won())
            {
                total_turns += board.get_current_turn();

                board.process_win();
            }
        }
    }

    // Append result to file.
    float average_turns = ((float) total_turns) / ((float) start_game_amount);

    std::ofstream f("plot.p", std::ios_base::app);

    f << board.get_width() << "\t\t" << average_turns << '\n';
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
