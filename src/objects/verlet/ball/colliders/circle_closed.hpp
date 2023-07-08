#include <iostream>
#include <SFML/Graphics.hpp>
#include <physics/vector2d.hpp>
#include <utils/colors.hpp>
#include <objects/verlet/ball/colliders/circle_collider.hpp>
#include <objects/verlet/ball/ball.hpp>

#ifndef CLOSED_CIRCLE_COLLIDER_HPP
#define CLOSED_CIRCLE_COLLIDER_HPP

class ClosedCircleCollider : public CircleCollider
{
public:
    int width;
    bool outside_collision = true;

    ClosedCircleCollider(
        Vec2D position,
        float radius,
        int width = 1,
        Color color = WHITE,
        bool outside_collision = true) : CircleCollider(position, radius, color)
    {
        this->width = width;
        this->outside_collision = outside_collision;
    }

    // Draw the Collider
    void draw(sf::RenderWindow *window)
    {
        sf::CircleShape circle(this->radius);
        circle.setOrigin(this->radius, this->radius);
        circle.setPosition(this->position.x, this->position.y);
        circle.setFillColor(Colors::to_sf(this->color));
        circle.setPointCount(128);
        window->draw(circle);
    }

    // Apply the collider
    void apply(VerletBall *ball)
    {
        if (!this->outside_collision)
        {
            return;
        }

        // Calculate the distance between the ball and the circle
        Vec2D dist = ball->current_position - this->center;
        float magnitude = dist.magnitude() + 1.0e-9;

        // Check if the ball is outside the collider
        float rad_sum = ball->radius + this->radius;
        if (magnitude < rad_sum && magnitude > this->radius)
        {
            // Calculate the ball overlap (the amount the balls have overlapped)
            Vec2D overlap = dist / magnitude;

            // Update this balls position (move it to the side)
            ball->current_position += overlap * 0.5 * (rad_sum - magnitude);
        }
    }
};

#endif // CLOSED_CIRCLE_COLLIDER_HPP