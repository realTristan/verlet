#include <iostream>
#include <SFML/Graphics.hpp>
#include <physics/vector2d.hpp>
#include <utils/colors.hpp>
#include <math.h>

#ifndef LINE_HPP
#define LINE_HPP

class Line
{
public:
    Vector2D start = Vector2D(0, 0);
    Vector2D end = Vector2D(0, 0);
    float length = 0;
    float angle = 0;
    int width = 1;
    Color color = WHITE;

    // Constructor
    Line(
        Vector2D start,
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
    Vector2D calculate_end()
    {
        return Vector2D(this->start.x + this->length, this->start.y + this->length * sin(this->angle));
    }

    // Draw the line
    void draw(sf::RenderWindow *window)
    {
        for (int i = 0; i < this->width; i++)
        {
            sf::Vertex line[] = {
                sf::Vertex(sf::Vector2f(this->start.x, this->start.y - i)),
                sf::Vertex(sf::Vector2f(this->end.x, this->end.y - i))};
            for (int i = 0; i < 2; i++)
            {
                line[i].color = sf::Color(this->color.r, this->color.g, this->color.b);
            }
            window->draw(line, 2, sf::Lines);
        }
    }
};

#endif