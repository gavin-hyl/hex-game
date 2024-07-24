#pragma once

#include <string>
#include <vector>

using color_t = std::string;

#define RESET       color_t("\033[0m")
#define BLACK       color_t("\033[30m")
#define RED         color_t("\033[31m")
#define GREEN       color_t("\033[32m")
#define YELLOW      color_t("\033[33m")
#define BLUE        color_t("\033[34m")
#define MAGENTA     color_t("\033[35m")
#define CYAN        color_t("\033[36m")
#define WHITE       color_t("\033[37m")
#define GRAY        color_t("\033[2;37m")
#define BOLD        color_t("\033[1m")

#define COLOR(color, txt) color + txt + RESET

static const std::vector<color_t> PLAYER_COLORS = {MAGENTA, GREEN, YELLOW, RED, BLUE};