#pragma once

#include "player.hpp"
#include "turn.hpp"

struct Tile
{
    char color = '_';
    // Set neighbours, {} sets it to nullptr's (in c++ 11 and later).
    Tile* neighbors[8] {};
};

class Board
{
    Tile* top_left_tile;

    int height;
    int width;
    int game_amount;
    int in_a_row;
    Player players[2];

    int calculate_possible_matches(Board& board);
    bool is_full(Board& new_board);

    int current_turn = 0;

    void set_tile(Player& player, int x, int y);

    void human_takes_turn(Player& player, Board& board);
    void computer_takes_turn(Player& player);


    bool check_turn_validity(int x, int y);

public:
    int *turn_amount_of_games = {};
    void undo_turn(Board& board, bool clear_all);

    Board();

    Board(int width, int height, int game_amount, Player player_1,
        Player player_2, int in_a_row);

    ~Board(); 

    Tile* get_tile(int x, int y);

    void player_takes_turn(int player_idx, Board& board);

    bool check_if_won(Board&);
    int amount_in_a_row(Tile*, int);
    void process_win(Board&);
    void clear_board(Board& board);

    void print();
    void print_turn_queue();

    TurnStack turn_stack;

    // Getters
    int get_game_amount();
    int get_width();
    int get_height();
    int get_current_turn();
    Player& get_player_1();
    Player& get_player_2();
};
