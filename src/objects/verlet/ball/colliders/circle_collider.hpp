#include <iostream>
#include <physics/vector2d.hpp>
#include <utils/colors.hpp>

#ifndef CIRCLE_COLLIDER_HPP
#define CIRCLE_COLLIDER_HPP

class CircleCollider
{
public:
    Vector2D position;
    float radius;
    Color color = Colors().WHITE;

    CircleCollider(Vector2D position, float radius, Color color)
    {
        this->position = position;
        this->radius = radius;
        this->color = color;
    }
};

#endif