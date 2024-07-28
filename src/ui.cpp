#include <iostream>

#include "ui.hpp"

std::string get_input(std::string prompt) {
    std::string action;
    std::cout << prompt;
    std::cin >> action;
    return action;
}
void wait() {
    std::string dummy;
    std::cout << "Press enter to continue...";
    std::getline(std::cin, dummy);
    std::getline(std::cin, dummy);
};

void clear_terminal()
{
#if defined _WIN32
    system("cls");
    //clrscr(); // including header file : conio.h
#elif defined (__LINUX__) || defined(__gnu_linux__) || defined(__linux__)
    system("clear");
    //std::cout<< u8"\033[2J\033[1;1H"; //Using ANSI Escape Sequences 
#elif defined (__APPLE__)
    system("clear");
#endif
}