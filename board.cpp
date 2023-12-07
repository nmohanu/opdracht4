#include <iostream>
#include "board.hpp"
#include "input.hpp"

Board::Board(){};

Board::Board(int height, int width, int game_amount, Player player_1,
    Player player_2, int in_a_row) 
: height(height), width(width), game_amount(game_amount),
    players { player_1, player_2 }, in_a_row(in_a_row)
{
    turn_amount_of_games = new int[game_amount];
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

void Board::set_tile(Player& player, int x, int y)
{
    // Toggle tile.
    get_tile(x, y)->color = player.color;

    // Append to queue.
    turn_stack.push(new Turn(&player, x, y));
}

void Board::player_takes_turn(int player_idx, Board& board)
{
    Player& player = players[player_idx];

    if (player.is_human) human_takes_turn(player, board);
    else computer_takes_turn(player);

    // Print turn memory after player's turn.
    if (player.is_human) print_turn_queue();

    current_turn++;
}

void Board::human_takes_turn(Player& player, Board& board)
{
    // Turn info
    std::cout << "Current turn: " << current_turn + 1 << '\n';
    std::cout << "Current player's turn: Player "
        << current_turn % 2 + 1 << '\n';

    print();

    std::cout
        << "Select x coordinate or type 't' to go back a turn:\n";

    int x = ask_x_coordinate();

    if(x + 'a' == 't')
    {
        if (current_turn < 2)
        {
            std::cout
                << "You may only undo your turn after the second turn.\n";
            
            // Ask again.
            human_takes_turn(player, board);
            return;
        }

        // Player takes back turns.
        undo_turn(board, false);

        // Same player's turn again.
        human_takes_turn(player, board);
        return;
    }
    else
    {
        std::cout << "Select y coordinate:\n";

        int y = ask_int(height) - 1;

        if(check_turn_validity(x, y))
        {
            set_tile(player, x, y);
        }
        else
        {
            std::cout
                << "This tile is already taken! Please try again.\n";

            // Try again
            human_takes_turn(player, board);
            return;
        }
    }
}

void Board::computer_takes_turn(Player& player)
{
    int x = rand() % get_width();  
    int y = rand() % get_height();  

    if(check_turn_validity(x, y))
    {
        set_tile(player, x, y);

        std::cout << "Computer choose: " << char(x + 'A') << x <<'\n';
    }
    else
    {
        computer_takes_turn(player);
        return;
    }
}

void Board::undo_turn(Board& board, bool clear_all)
{
    int turns_left;

    if(!clear_all)
    {
        std::cout << "How many turns would you like to go back?\n";
        std::cout << "Note: 1 turn takes back the previous turn of BOTH "
        "players.\n";
        turns_left = 2 * ask_int();
    } 
    else
    {
        turns_left = board.current_turn;
    }

    while (turns_left > 0)
    {
        if(!turn_stack.is_empty())
        {
            Turn* turn = turn_stack.pop();

            get_tile(turn->x, turn->y)->color = '_';

            delete turn;

            turns_left--;
            board.current_turn--;
        }
        else 
        {
            print();

            std::cout << "You selected more turns than possible, but "
                "we took back the maximum amount of turns for you.\n";

            return;
        }
    }

    print();

    std::cout << "We took back " << turns_left
        << " turns back for you.\n";
}

// Check if a tile is already taken.
bool Board::check_turn_validity(int x, int y)
{
    return get_tile(x, y)->color != get_player_1().color 
        && get_tile(x, y)->color != get_player_2().color;
}

// Getters
int Board::get_game_amount()
{
    return game_amount;
}

Player& Board::get_player_1()
{
    return players[0];
}

Player& Board::get_player_2()
{
    return players[1];
}

int Board::get_width()
{
    return width;
}

int Board::get_height()
{
    return height;
}

int Board::get_current_turn()
{
    return current_turn;
}

// Print the board
void Board::print()
{
    // Print letters (chess board format)
    // Print spaces for formatting.
    for(int i = 0; i < std::to_string(height).length() + 4; i++)
    {
        std::cout << " ";
    }

    // Print chess notation letters.
    for(int x = 0; x < width; x++)
    {
        std::cout << char(x + 65) << "  ";
    }
    std::cout << std::endl;

    // Print second line.
    for(int i = 0; i < std::to_string(height).length() + 1; i++)
    {
        std::cout << " ";
    }
    std::cout << "+ ";
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

void Board::print_turn_queue()
{
    std::cout << "Moves in memory:\n";

    Turn* turn = turn_stack.top;

    while(turn != nullptr)
    {
        std::cout
            << char(turn->x + 'A') << turn->y << " by player: "
            << turn->player << '\n';

        std::cout
            << "tile color: " << get_tile(turn->x, turn->y)->color
            << '\n';

        turn = turn->below;
    }
}

void Board::check_if_won(Board& board)
{
    int max_in_a_row = 0;
    Tile* tile = board.get_tile(board.turn_stack.top->x, board.turn_stack.top->y);

    for(int i = 0; i < 8; i++)
    {
        max_in_a_row = std::max(max_in_a_row, amount_in_a_row(tile, i));
    }
    if(max_in_a_row == board.in_a_row)
    {
        process_win(board);
    }
}

int Board::amount_in_a_row(Tile* tile, int direction)
{
    int in_a_row = 0;
    while (tile->neighbors[direction] != nullptr)
    {
        in_a_row++;
        tile = tile->neighbors[direction];
    }
    return in_a_row;
}

void Board::process_win(Board& board)
{
    Player* winner = board.turn_stack.top->player;
    winner->wins++;
    std::cout << "Congratulations player " << board.get_current_turn() %2 << " you won!";
    board.game_amount--;
    clear_board(board);
}

void Board::clear_board(Board& board)
{
    board.undo_turn(board, true);
}
