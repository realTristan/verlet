#ifndef VERLET_BALL_COLLIDERS_CIRCLE_OPEN_HPP
#define VERLET_BALL_COLLIDERS_CIRCLE_OPEN_HPP

#include <objects/verlet/ball/colliders/circle_collider.hpp>
#include <objects/verlet/ball/ball.hpp>
#include <physics/vector2d.hpp>
#include <SFML/Graphics.hpp>
#include <utils/colors.hpp>
#include <iostream>

class ClosedCircleCollider : public CircleCollider
{
public:
    bool outside_collision = true;

    ClosedCircleCollider(
        Vec2D position,
        float radius,
        Color color = WHITE,
        bool outside_collision = true) : CircleCollider(position, radius, color)
    {
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
        Vec2D dist = ball->current_position - this->position;
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

#endif // VERLET_BALL_COLLIDERS_CIRCLE_CLOSDED_HPP