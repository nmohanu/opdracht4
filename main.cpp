#include <iostream>
#include <cstdlib>
#include "board.hpp"

// Ask user for info about the board size, amount of games, etc.
Board initialize_board();

// The main game loop, this is where the games are played.
void game_loop(Board&); 

// Ask user for int input.
int ask_int();

// Ask user for x coordinate (y coordinate is an int so we use ask_int() for that).
int ask_x_coordinate();

// Ask user for single char response.
char ask_char();

// Human player makes turn.
void human_turn(Board&, Player&);

// Computer makes turn.
void computer_turn(Board&, Player&);

// Set player to pc or human.
void set_player_type(Player&);

// Check if a turn is valid.
bool check_turn_validity(int, int, Board&);

// register turn in turn stack.
void register_turn(Board&, Player&, int, int);

// Undo a certain amount of turns.
void take_back_turn(Board&);

// Print turns memory.
void print_turns(Board&);

// Main
int main()
{
    Board board = initialize_board();
    game_loop(board);
    return 0;
}

// Ask user for board info and return the boar to be used.
Board initialize_board()
{
    // Players.
    Player player_1;
    Player player_2;
    
    // Board info.
    std::cout << "Choose a board height." << std::endl;
    int height = ask_int();
    std::cout << "Choose a board width." << std::endl;
    int width = ask_int();
    std::cout << "Choose the amount of games you would like to play." << std::endl;
    int game_amount = ask_int();
    std::cout << "How many in a row to win?" << std::endl;
    int in_a_row = ask_int();

    // Player 1 info.
    std::cout << "Player 1: Computer or Human? C/H" << std::endl;
    set_player_type(player_1);
    std::cout << "Player 1: Select a symbol to represent your tiles:" << std::endl;
    player_1.color = ask_char();

    // Player 2 info.
    std::cout << "Player 2: Computer or Human? C/H" << std::endl;
    set_player_type(player_2);
    std::cout << "Player 2: Select a symbol to represent your tiles:" << std::endl;
    player_2.color = ask_char();
    
    Board board(height, width, game_amount, player_1, player_2, in_a_row);
    return board;
}

// Ask single char input.
char ask_char()
{
    char i;
    std::cin >> i;
    return i;
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
void game_loop(Board& board)
{
    // Storing the players in an array allows us to easily set the current player.
    Player players[] = {board.get_player_1(), board.get_player_2()};
    int turn_count = 0;

    while (board.get_game_amount() > 0)
    {
        // Set current player
        Player current_player = players[turn_count % 2];

        if(current_player.is_human)
        {
            // Turn info
            std::cout << "Current turn: " << ((turn_count) / 2) + 1 << std::endl;
            std::cout << "Current player's turn: Player " << turn_count % 2 + 1 << std::endl;
            board.print();
            human_turn(board, current_player);
        }
        else
        {
            computer_turn(board, current_player);
        }

        turn_count++;

        // Print turn memory after player's turn.
        if(turn_count%2 == 0)
        {
            print_turns(board);
        }
    }
}

void print_turns(Board& board)
{
    std::cout << "Moves in memory: " << std::endl;
    Turn* turn = board.turns.first_out;
    while(turn != nullptr)
    {
        std::cout << char(turn->x + 'A') << turn->y << " by player: " << turn->player << std::endl;
        std::cout << "tile color: " << board.get_tile(turn->x, turn->y)->color << std::endl;
        turn = turn->next;
    }
}

// Human player makes turn.
void human_turn(Board& board, Player& current_player)
{
    std::cout << "Select x coordinate or type 't' to go back a turn: " << std::endl;
    int x = ask_x_coordinate();
    if(char(x + 'A') == 't')
    {
        // Player takes back turns.
        take_back_turn(board);
        // Same player's turn again.
        human_turn(board, current_player);
    }
    else {
        std::cout << "Select y coordinate: " << std::endl;
        int y = ask_int() - 1;

        if(check_turn_validity(x, y, board))
        {
            board.get_tile(x, y)->color = current_player.color;
        }
        else
        {
            std::cout << "This tile is already taken! Please try again." << std::endl;
            // Try again
            human_turn(board, current_player);
        }

        register_turn(board, current_player, x, y);
        
    }
}

// Computer makes a turn.
void computer_turn(Board& board, Player& current_player)
{
    int x = rand() % board.get_width();  
    int y = rand() % board.get_height();  
    if(check_turn_validity(x, y, board))
    {
        board.get_tile(x, y)->color = current_player.color;
        std::cout << "Computer choose: " << char(x + 65) << x << std::endl;
    }
    else
    {
        // Try again
        computer_turn(board, current_player);
    }
    register_turn(board, current_player, x, y);
}

// Set player to human or conmputer.
void set_player_type(Player& player)
{
    char player_type = ask_char();
    if(player_type == 'C')
    {
        player.is_human = false;
    }
}

// Check if a tile is already taken.
bool check_turn_validity(int x, int y, Board& board)
{
    if(board.get_tile(x, y)->color != board.get_player_1().color 
        && board.get_tile(x, y)->color != board.get_player_2().color)
    {
        return true;
    }
    else 
    {
        return false;
    }
}

// Save turn in the stack.
void register_turn(Board& board, Player& player, int x, int y)
{
    Turn* turn = new Turn(&player, x, y);
    board.turns.push(turn);
}

// Undo an amount of turns.
void take_back_turn(Board& board)
{
    std::cout << "How many turns would you like to go back?" << std::endl;
    std::cout << "Note: 1 turn takes back the previous turn of BOTH players." << std::endl;
    int turn_to_take_back = ask_int();
    int turns_left = turn_to_take_back * 2;
    while (turns_left > 0)
    {
        if(!board.turns.is_empty())
        {
            board.get_tile(board.turns.first_out->y, board.turns.first_out->x)->color = '_';
            board.turns.delete_first_out();
            turns_left--;
        }
        else 
        {
            board.print();
            std::cout << "You selected more turns than possible, but we took back the maximum amount of turns for you." << std::endl;
            return;
        }
    }
    board.print();
    std::cout << "We took back " << turn_to_take_back << " turns back for you." << std::endl;
}