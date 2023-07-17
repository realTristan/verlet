#ifndef VERLET_BALL_COLLIDERS_CIRCLE_CLOSED_HPP
#define VERLET_BALL_COLLIDERS_CIRCLE_CLOSED_HPP

#include <objects/verlet/ball/colliders/circle_collider.hpp>
#include <objects/verlet/ball/ball.hpp>
#include <SFML/Graphics.hpp>

class OpenCircleCollider : public CircleCollider
{
public:
    bool outside_collision;
    bool inside_collision;
    int width;

    OpenCircleCollider(
        Vec2D<float> position,
        float radius,
        int width = 1,
        Color color = WHITE,
        bool inside_collision = true,
        bool outside_collision = true) : CircleCollider(position, radius, color)
    {
        this->outside_collision = outside_collision;
        this->inside_collision = inside_collision;
        this->width = width;
    }

    // Draw the Collider
    void draw(sf::RenderWindow *window)
    {
        sf::CircleShape circle(this->radius);
        circle.setScale(1.0f, 1.0f);
        circle.setOutlineColor(Colors::to_sf(this->color));
        circle.setOrigin(this->radius, this->radius);
        circle.setPosition(this->position.x + 4.0f, this->position.y + 2.0f);
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
        Vec2D<float> dist = ball->current_position - this->position;
        float magnitude = dist.magnitude() + 1.0e-9f;

        // Check if the ball is inside the collider
        if (this->inside_collision)
        {
            float delta = this->radius - ball->radius - this->width;
            bool ball_inside_circle = magnitude < this->radius;
            if (magnitude > delta && (!this->outside_collision || ball_inside_circle))
            {
                ball->current_position += dist / magnitude * (delta - magnitude);
                return;
            }
        }

        // Check if the ball is outside the collider
        if (this->outside_collision)
        {
            float rad_sum = ball->radius + this->radius;
            bool ball_colliding_with_circle = magnitude < rad_sum;
            bool ball_outside_circle = magnitude > this->radius;
            if (ball_colliding_with_circle && (!this->inside_collision || ball_outside_circle))
            {
                // Calculate the ball overlap (the amount the balls have overlapped)
                Vec2D<float> overlap = dist / magnitude;

                // Update this balls position (move it to the side)
                ball->current_position += overlap * 0.5f * (rad_sum - magnitude);
            }
        }
    }
};

#endif // VERLET_BALL_COLLIDERS_CIRCLE_OPEN_HPP
