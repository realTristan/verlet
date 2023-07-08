#include <iostream>
#include <SFML/Graphics.hpp>
#include <objects/verlet/ball/colliders/circle_collider.hpp>
#include <objects/verlet/ball/ball.hpp>

#ifndef OPEN_CIRCLE_HPP
#define OPEN_CIRCLE_HPP

class OpenCircleCollider : public CircleCollider
{
public:
    bool outside_collision;
    bool inside_collision;
    int width;

    OpenCircleCollider(
        Vector2D position,
        float radius,
        int width = 1,
        Color color = WHITE,
        bool outside_collision = true,
        bool inside_collision = true) : CircleCollider(position, radius, color)
    {
        this->outside_collision = outside_collision;
        this->inside_collision = inside_collision;
        this->width = width;
    }

    // Draw the Collider
    void draw(sf::RenderWindow *window)
    {
        sf::CircleShape circle(this->radius);
        circle.setOrigin(this->radius, this->radius);
        circle.setPosition(calculate_x(), calculate_y());
        circle.setOutlineThickness(this->width);
        circle.setFillColor(sf::Color::Transparent);
        circle.setPointCount(128);
        window->draw(circle);
    }

    // Calculate circle position x
    float calculate_x()
    {
        return this->position.x - this->radius + this->width;
    }

    // Calculate circle position y
    float calculate_y()
    {
        return this->position.y - this->radius + this->width;
    }

    // Apply the Collider
    void apply(VerletBall *ball)
    {
        if (!this->outside_collision && !this->inside_collision)
        {
            return;
        }

        // Calculate the distance between the ball and the circle
        Vector2D dist = ball->current_position - this->position;
        float magnitude = dist.magnitude() + 1.0e-9;

        // Check if the ball is outside the collider
        if (this->outside_collision)
        {
            float rad_sum = ball->radius + this->radius;
            if (magnitude < rad_sum && (!this->inside_collision || magnitude > this->radius))
            {
                // Calculate the ball overlap (the amount the balls have overlapped)
                Vector2D overlap = dist / magnitude;

                // Update this balls position (move it to the side)
                ball->current_position += overlap * 0.5 * (rad_sum + magnitude);
                return;
            }
        }

        // Check if the ball is inside the collider
        if (this->inside_collision)
        {
            float delta = this->radius - ball->radius - this->width;
            if (magnitude > delta && (!this->outside_collision || magnitude < this->radius))
            {
                ball->current_position.set(
                    this->position.x + dist.x / magnitude * delta,
                    this->position.y + dist.y / magnitude * delta);
            }
        }
    }
};

#endif
