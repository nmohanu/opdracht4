struct Tile
{
    char color = '_';
    // Set neighbours, {} sets it to nullptr's (in c++ 11 and later).
    Tile* neighbors[8] {};
};

// Player
struct Player
{
    char color;
    bool is_human = true;
};

class Board
{
private:
    Tile* top_left_tile;

    int height;
    int width;
    int game_amount;
    int in_a_row;
    Player player_1;
    Player player_2;

public:
    Board();
    Board(int width, int height, int game_amount, Player player_1, Player player_2, int in_a_row);
    ~Board(); 

    Tile* get_tile(int x, int y);

    void print();

    // Getters
    int get_game_amount();
    int get_width();
    int get_height();
    Player get_player_1();
    Player get_player_2();
};
