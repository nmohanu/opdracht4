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

// Turns
struct Turn
{
    int x;
    int y;
    Player* player;
    Turn* next;

    Turn(Player* player, int x, int y) : player(player), x(x), y(y)
    {
        next = nullptr;
    }
};

class Turn_Queue
{
    public:
        Turn_Queue()
        {
            first_out = nullptr;
        }

        Turn* first_out;

        void push(Turn* turn)
        {
            turn->next = first_out;
            first_out = turn;
        }

        void delete_first_out()
        {
            if(!this->is_empty())
            {
                Turn* temp = first_out;
                first_out = first_out->next;
                delete temp;
            }
        }

        bool is_empty()
        {
            return (first_out == nullptr);
        }
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
    Turn_Queue turns;

    // Getters
    int get_game_amount();
    int get_width();
    int get_height();
    Player get_player_1();
    Player get_player_2();
};
