#include "board.hpp"

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
        Turn_Queue();

        Turn* first_out;

        void push(Turn*);

        void delete_first_out();

        bool is_empty();
};