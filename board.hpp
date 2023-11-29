struct Tile
{
    char color = '#';
    // Set neighbours, {} sets it to nullptr's (in c++ 11 and later).
    Tile* neighbors[8] {};
};

class Board
{
private:
    Tile* top_left_tile;

    int height;
    int width;
    int game_amount;

public:
    Board(int width, int height, int game_amount);
    ~Board(); 

    Tile* get_tile(int x, int y);

    void print();
    int get_game_amount();
};
