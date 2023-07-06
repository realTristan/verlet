#include <iostream>
#include <SFML/Graphics.hpp>
#include <physics/vector2d.hpp>
#include <utils/colors.hpp>
#include <math.h>

#ifndef LINE_HPP
#define LINE_HPP

class Line
{
    // Line variables
public:
    Vector2D start = Vector2D(0, 0);
    Vector2D end = Vector2D(0, 0);
    float length = 0;
    float angle = 0;
    int width = 1;
    Color color = Colors().WHITE;

    // Constructor
    Line(Vector2D start, float length, float angle, Color color)
    {
        // PI Constant
        const float M_PI = 3.14159265358979323846;

        // Set the variables
        this->start = start;
        this->length = length;
        this->angle = angle * M_PI / 180;
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
        sf::Vertex line[] = {
            sf::Vertex(sf::Vector2f(this->start.x, this->start.y)),
            sf::Vertex(sf::Vector2f(this->end.x, this->end.y))};
        for (int i = 0; i < 2; i++)
        {
            line[i].color = sf::Color(this->color.r, this->color.g, this->color.b);
        }
        window->draw(line, 2, sf::Lines);
    }
};

#endif