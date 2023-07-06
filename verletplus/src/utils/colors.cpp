#include <iostream>

class Color
{
public:
    int r;
    int g;
    int b;

    Color(int r, int g, int b)
    {
        this->r = r;
        this->g = g;
        this->b = b;
    }
};

class Colors
{
public:
    // Constant colors
    Color RED = Color(255, 0, 0);
    Color GREEN = Color(0, 255, 0);
    Color BLUE = Color(0, 0, 255);
    Color YELLOW = Color(255, 255, 0);
    Color CYAN = Color(0, 255, 255);
    Color MAGENTA = Color(255, 0, 255);
    Color WHITE = Color(255, 255, 255);
    Color BLACK = Color(0, 0, 0);
    Color ORANGE = Color(255, 165, 0);
    Color PURPLE = Color(128, 0, 128);
    Color PINK = Color(255, 192, 203);

    // Generate a random rgb color
    std::tuple<int, int, int> random_rgb()
    {
        return std::make_tuple(rand() % 255, rand() % 255, rand() % 255);
    }

    // Generate a random color from the constant colors
    Color random_color()
    {
        Color colors[11] = {RED, GREEN, BLUE, YELLOW, CYAN, MAGENTA, WHITE, BLACK, ORANGE, PURPLE, PINK};
        return colors[rand() % 11];
    }
};