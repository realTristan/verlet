#ifndef OBJECT_LINE_HPP
#define OBJECT_LINE_HPP

#include <physics/vector2d.h>
#include <SFML/Graphics.hpp>
#include <utils/colors.hpp>
#include <math.h>

#define M_PI 3.14159265358979323846

class Line
{
public:
    Vec2D<float> start = Vec2D<float>(0.0f, 0.0f);
    Vec2D<float> end = Vec2D<float>(0.0f, 0.0f);
    float length = 0.0f;
    float angle = 0.0f;
    int width = 1;
    Color color = WHITE;

    // Constructor
    Line(
        Vec2D<float> start,
        float length,
        float angle,
        int width = 1,
        Color color = WHITE)
    {
        // Set the variables
        this->start = start;
        this->length = length;
        this->angle = angle * M_PI / 180;
        this->width = width;
        this->color = color;
        this->end = this->calculate_end();
    }

    // Calculate the end of the line
    Vec2D<float> calculate_end()
    {
        return Vec2D<float>(this->start.x + this->length, this->start.y + this->length * sin(this->angle));
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
                line[i].color = Colors::to_sf(this->color);
            }
            window->draw(line, 2, sf::Lines);
        }
    }
};

#endif // OBJECT_LINE_HPP