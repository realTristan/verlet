#include <iostream>
#include "../../../../physics/vector2d.cpp"
#include "../../../../utils/colors.cpp"

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