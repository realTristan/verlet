#include <iostream>
#include <SFML/Graphics.hpp>
#include "../physics/vector2d.cpp"
#include "../utils/colors.cpp"
#include <math.h>

class Line
{
    // Line variables
    public:
        Vector2D start = Vector2D(0, 0);
        float length = 0;
        float angle = 0;
        Color color = Colors().WHITE;
        

    // Constructor
    Line(Vector2D start, float length, float angle, Color color) {
        this->start = start;
        this->length = length;
        this->angle = angle;
        this->color = color;
    }

    // Draw the line
    void draw(sf::RenderWindow *window) {
        sf::Vertex line[] = {
            sf::Vertex(sf::Vector2f(this->start.x, this->start.y)),
            sf::Vertex(sf::Vector2f(this->start.x + this->length, this->start.y + this->length * sin(this->angle)))
        };
        line[0].color = sf::Color(this->color.r, this->color.g, this->color.b);
        line[1].color = sf::Color(this->color.r, this->color.g, this->color.b);
        window->draw(line, 2, sf::Lines);
    }
};