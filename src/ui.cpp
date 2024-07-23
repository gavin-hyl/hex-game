#include <iostream>

#include "ui.hpp"

std::string get_input(std::string prompt) {
    std::string action;
    std::cout << prompt;
    std::cin >> action;
    return action;
};