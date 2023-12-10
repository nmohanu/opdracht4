#include "turn.hpp"

Turn::Turn(Player* player, int x, int y) : player(player), x(x), y(y)
{}

void TurnStack::push(Turn* turn)
{
    if (top == nullptr)
    {
        top = turn;
        return;
    }

    turn->below = top;
    top = turn;
}

// Delete the first out entry.
Turn* TurnStack::pop()
{
    if(!is_empty())
    {
        Turn* temp = top;

        top = top->below;

        return temp;
    }

    return nullptr;
}

// Check if stack is empty.
bool TurnStack::is_empty()
{
    return top == nullptr;
}
