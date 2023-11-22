struct Tile
{
    char color = '#';
    Tile* neighbors[8] {};
    Tile* next {};
};

class Board
{
private:
    Tile* top_left_tile;

    int height = 7;
    int width = 6;
    int cursor_y = 0;
    int cursor_x = 0;

public:
    Board();
    Board(int width, int height);
    ~Board(); 

    Tile* get_tile(int x, int y);

    void initialize_board();
    void print();
    void set_neighbours();
};
