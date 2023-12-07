#include "input.hpp"
#include <iostream>

// Function to ask an integer above zero.
int ask_int()
{
    int i;
    std::cin >> i;
    while(i <= 0)
    {
        std::cout << "Sorry, you need to choose a number above 0." << std::endl;
        std::cin >> i;
        
    }
    return i;
}

// Function if a maximum number is relevant.
int ask_int(int max)
{
    int i;
    std::cin >> i;
    while(i > max || i <= 0)
    {
        std::cout << "Sorry, you need to choose a number between 0 and " << max << std::endl;
        std::cin >> i;
        
    }
    
    return i;
}

// This will convert chess notation to y coordinate.
int ask_x_coordinate()
{
    char x;
    std::cin >> x;

    if (x >= 'A' && x <= 'Z') return x - 'A';
    else if (x >= 'a' && x <= 'z') return x - 'a';
    else return -1;
}

// Ask for a single character input.
char ask_char()
{
    std::string i;
    std::cin >> i;
    char j = i[0];
    return j;
}
