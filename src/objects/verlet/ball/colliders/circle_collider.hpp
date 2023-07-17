#ifndef VERLET_BALL_COLLIDERS_CIRCLE_HPP
#define VERLET_BALL_COLLIDERS_CIRCLE_HPP

#include <physics/vector2d.h>
#include <utils/colors.hpp>

class CircleCollider
{
public:
    Vec2D<float> position;
    Vec2D<float> center;
    float radius;
    Color color = WHITE;

    CircleCollider(Vec2D<float> position, float radius, Color color = WHITE)
    {
        this->position = position;
        this->radius = radius;
        this->color = color;
    }

    // Set the radius
    void set_radius(float radius)
    {
        this->radius = radius;
    }

    // Set the position
    void set_position(Vec2D<float> position)
    {
        this->position = position;
    }

    // Set the color
    void set_color(Color color)
    {
        this->color = color;
    }
};

#endif // CIRCLE_COLLIDER_HPP