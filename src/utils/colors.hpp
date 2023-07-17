#ifndef COLORS_HPP
#define COLORS_HPP

#include <SFML/Graphics.hpp>

#define RED Color(255, 0, 0)
#define GREEN Color(0, 255, 0)
#define BLUE Color(0, 0, 255)
#define WHITE Color(255, 255, 255)
#define BLACK Color(0, 0, 0)
#define YELLOW Color(255, 255, 0)
#define PURPLE Color(255, 0, 255)
#define CYAN Color(0, 255, 255)
#define ORANGE Color(255, 165, 0)
#define PINK Color(255, 192, 203)
#define MAGENTA Color(255, 0, 255)

// Color class
class Color
{
public:
    int r;
    int g;
    int b;

    Color() {
        this->r = 0;
        this->g = 0;
        this->b = 0;
    }
    Color(int r, int g, int b)
    {
        this->r = r;
        this->g = g;
        this->b = b;
    }
};

// Colors class
class Colors
{
public:
    // Generate a random rgb color
    static Color random_rgb()
    {
        return Color(rand() % 255, rand() % 255, rand() % 255);
    }

    // Generate a random color from the constant colors
    static Color random_color()
    {
        Color colors[10] = {RED, GREEN, BLUE, YELLOW, CYAN, MAGENTA, WHITE, ORANGE, PURPLE, PINK};
        return colors[rand() % 10];
    }

    // Convert a Color object to a sf::Color object
    static sf::Color to_sf(Color color)
    {
        return sf::Color(color.r, color.g, color.b);
    }
};

#endif // COLORS_HPP