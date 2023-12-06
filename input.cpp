#include "input.hpp"
#include <iostream>

int ask_int()
{
    int i;
    std::cin >> i;
    return i;
}

int ask_x_coordinate()
{
    char x;
    std::cin >> x;

    if (x >= 'A' && x <= 'Z') return x - 'A';
    else if (x >= 'a' && x <= 'z') return x - 'a';
    else return -1;
}

char ask_char()
{
    char i;
    std::cin >> i;
    return i;
}
