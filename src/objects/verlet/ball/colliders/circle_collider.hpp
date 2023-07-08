#include <iostream>
#include <physics/vector2d.hpp>
#include <utils/colors.hpp>

#ifndef CIRCLE_COLLIDER_HPP
#define CIRCLE_COLLIDER_HPP

class CircleCollider
{
public:
    Vec2D position;
    Vec2D center;
    float radius;
    Color color = WHITE;

    CircleCollider(Vec2D position, float radius, Color color = WHITE)
    {
        this->position = position;
        this->radius = radius;
        this->color = color;
        this->center = Vec2D(position.x + radius, position.y + radius);
    }
};

#endif // CIRCLE_COLLIDER_HPP