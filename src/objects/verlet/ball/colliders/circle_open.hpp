#ifndef VERLET_BALL_COLLIDERS_CIRCLE_CLOSED_HPP
#define VERLET_BALL_COLLIDERS_CIRCLE_CLOSED_HPP

#include <objects/verlet/ball/colliders/circle_collider.hpp>
#include <objects/verlet/ball/ball.hpp>
#include <SFML/Graphics.hpp>
#include <utils/window.hpp>

class OpenCircleCollider : public CircleCollider
{
public:
    bool outside_collision;
    bool inside_collision;
    int width;

    OpenCircleCollider(
        Vec2D position,
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
    void draw(Window *window)
    {
        sf::CircleShape circle(this->radius);
        circle.setOrigin(this->radius, this->radius);
        circle.setPosition(this->position.x, this->position.y);
        circle.setOutlineThickness(this->width);
        circle.setFillColor(sf::Color::Transparent);
        circle.setPointCount(128);
        window->draw(circle);
    }

    // Apply the Collider
    void apply(VerletBall *ball)
    {
        if (!this->outside_collision && !this->inside_collision)
        {
            return;
        }

        // Calculate the distance between the ball and the circle
        Vec2D dist = ball->current_position - this->center;
        float magnitude = dist.magnitude() + 1.0e-9;

        // Check if the ball is outside the collider
        if (this->outside_collision)
        {
            float rad_sum = ball->radius + this->radius;
            if (magnitude < rad_sum && (!this->inside_collision || magnitude > this->radius))
            {
                // Calculate the ball overlap (the amount the balls have overlapped)
                Vec2D overlap = dist / magnitude;

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
                    this->center.x + dist.x / magnitude * delta,
                    this->center.y + dist.y / magnitude * delta);
            }
        }
    }
};

#endif // VERLET_BALL_COLLIDERS_CIRCLE_OPEN_HPP
