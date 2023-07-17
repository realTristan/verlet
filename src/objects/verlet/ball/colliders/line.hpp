#ifndef VERLET_BALL_COLLIDERS_LINE_HPP
#define VERLET_BALL_COLLIDERS_LINE_HPP

#include <objects/verlet/ball/ball.hpp>
#include <objects/line.hpp>
#include <physics/vector2d.h>

class LineCollider : public Line
{
public:
    float slope_multiplier;
    LineCollider(
        Vec2D<float> start,
        float length,
        float angle,
        int width = 1,
        Color color = WHITE,
        float slope_multiplier = 1.0f) : Line(start, length, angle, width, color)
    {
        this->slope_multiplier = slope_multiplier;
    }

    // Apply the Collider
    void apply(VerletBall *ball)
    {
        float l_bound = this->start.x - ball->radius;
        float r_bound = this->end.x + ball->radius;

        // If the circle is past the lines bounds
        if (ball->current_position.x < l_bound || ball->current_position.x > r_bound)
        {
            return;
        }

        // Calculate the slope of the line
        float slope = (this->start.y - this->end.y) / (this->start.x - this->end.x);

        // Calculate the y intercept of the line
        float y_int = this->start.y - slope * this->start.x;

        // Calculate the y position of the ball
        float y = slope * ball->current_position.x + y_int;

        // If the ball is above/below the line
        float y_above = ball->current_position.y + ball->radius + this->width + 3.0f;
        float y_below = y + this->width + ball->radius;

        // Check to make sure the ball is within the y_above and y_below bounds
        if (y_above > y && ball->current_position.y < y_below)
        {
            ball->current_position.y = y - ball->radius - this->width - 3.0f;
            ball->current_position.x += slope * this->slope_multiplier;
        }
    }
};

#endif // VERLET_BALL_COLLIDERS_LINE_HPP
