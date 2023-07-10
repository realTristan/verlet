#ifndef LINE_HPP
#define LINE_HPP

#include <physics/vector2d.hpp>
#include <SFML/Graphics.hpp>
#include <utils/colors.hpp>
#include <utils/window.hpp>
#include <math.h>

class Line
{
public:
    Vec2D start = Vec2D(0, 0);
    Vec2D end = Vec2D(0, 0);
    float length = 0;
    float angle = 0;
    int width = 1;
    Color color = WHITE;

    // Constructor
    Line(
        Vec2D start,
        float length,
        float angle,
        int width = 1,
        Color color = WHITE)
    {
        // PI Constant
        const float PI = 3.14159265358979323846;

        // Set the variables
        this->start = start;
        this->length = length;
        this->angle = angle * PI / 180;
        this->width = width;
        this->color = color;
        this->end = this->calculate_end();
    }

    // Calculate the end of the line
    Vec2D calculate_end()
    {
        return Vec2D(this->start.x + this->length, this->start.y + this->length * sin(this->angle));
    }

    // Draw the line
    void draw(Window *window)
    {
        for (int i = 0; i < this->width; i++)
        {
            sf::Vertex line[] = {
                sf::Vertex(sf::Vector2f(this->start.x, this->start.y - i)),
                sf::Vertex(sf::Vector2f(this->end.x, this->end.y - i))};
            for (int i = 0; i < 2; i++)
            {
                line[i].color = Colors::to_sf(this->color);
            }
            window->draw(line, 2, sf::Lines);
        }
    }
};

#endif // LINE_HPP