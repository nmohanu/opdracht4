struct Tile
{
    char color;
    Tile* neighbors[8] {};
    Tile* next {};
};

class Board
{
private:
    Tile* top_left_tile;

    int height = 7;
    int width = 6;

public:
    Board();
    Board(int width, int height);
    ~Board(); 

    Tile* get_tile(int x, int y);

    void print();
};
