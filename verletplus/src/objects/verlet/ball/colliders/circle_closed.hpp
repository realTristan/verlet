#include <iostream>
#include <SFML/Graphics.hpp>
#include "../../../../physics/vector2d.hpp"
#include "../../../../utils/colors.hpp"
#include "circle_collider.hpp"
#include "../ball.hpp"

#ifndef CLOSED_CIRCLE_HPP
#define CLOSED_CIRCLE_HPP

class ClosedCircle : public CircleCollider
{
public:
    int width;
    bool outside_collision = true;
    bool inside_collision = true;

    ClosedCircle(Vector2D position, float radius, int width, Color color, bool outside_collision, bool inside_collision) : CircleCollider(position, radius, color)
    {
        this->width = width;
        this->outside_collision = outside_collision;
        this->inside_collision = inside_collision;
    }

    // Draw the Collider
    void draw(sf::RenderWindow *window)
    {
        sf::CircleShape circle(this->radius);
        circle.setPosition(this->position.x, this->position.y);
        circle.setFillColor(sf::Color(this->color.r, this->color.g, this->color.b));
        window->draw(circle);
    }

    // Apply the collider
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
                ball->current_position += overlap * 0.5 * (rad_sum - magnitude);
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