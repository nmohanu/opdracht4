#pragma once

#include "player.hpp"

// Turns
struct Turn
{
    int x;
    int y;

    Player* player;
    Turn* below = nullptr;

    Turn(Player* player, int x, int y);
};

struct TurnStack
{
    Turn* top = nullptr;

    // Push a turn on top.
    void push(Turn*);

    // Pop the top turn.
    // Don't forget to free the turn.
    Turn* pop();

    // Check if stack is empty.
    bool is_empty();
};
