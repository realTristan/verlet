#ifndef VERLET_BALL_COLLIDERS_CIRCLE_CLOSED_HPP
#define VERLET_BALL_COLLIDERS_CIRCLE_CLOSED_HPP

#include <objects/verlet/ball/colliders/circle_collider.hpp>
#include <objects/verlet/ball/ball.hpp>
#include <SFML/Graphics.hpp>

class OpenCircleCollider : public CircleCollider
{
public:
    sf::Color fill_color = sf::Color::Transparent;
    bool outside_collision = false;
    bool inside_collision = true;
    int width;

    OpenCircleCollider(
        Vec2D<float> position,
        float radius,
        int width = 1,
        Color color = WHITE) : CircleCollider(position, radius, color)
    {
        this->outside_collision = outside_collision;
        this->inside_collision = inside_collision;
        this->width = width;
    }

    // Set the width
    void set_width(int width)
    {
        this->width = width;
    }

    // Set the fill color
    void set_fill_color(Color color)
    {
        this->fill_color = Colors::to_sf(color);
    }

    // Enable inside collision
    void enable_inside_collision()
    {
        this->inside_collision = true;
    }

    // Disable inside collision
    void disable_inside_collision()
    {
        this->inside_collision = false;
    }

    // Enable outside collision
    void enable_outside_collision()
    {
        this->outside_collision = true;
    }

    // Disable outside collision
    void disable_outside_collision()
    {
        this->outside_collision = false;
    }

    // Draw the Collider
    void draw(sf::RenderWindow *window)
    {
        sf::CircleShape circle(this->radius);
        circle.setScale(1.0f, 1.0f);
        circle.setOutlineColor(Colors::to_sf(this->color));
        circle.setOrigin(this->radius, this->radius);
        circle.setPosition(this->position.x + 4.0f, this->position.y + 3.0f);
        circle.setOutlineThickness(this->width);
        circle.setFillColor(this->fill_color);
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
            float rad_sum = ball->radius + this->radius + this->width;
            bool ball_colliding_with_circle = magnitude < rad_sum;
            bool ball_outside_circle = magnitude > this->radius;
            if (ball_colliding_with_circle && (!this->inside_collision || ball_outside_circle))
            {
                // Calculate the ball overlap (the amount the balls have overlapped)
                Vec2D<float> overlap = dist / magnitude;
                float offset = ((ball->radius * 2.0f) + this->radius);

                // Update this balls position (move it to the side)
                ball->current_position += (overlap * 0.5f * (offset - magnitude));
            }
        }
    }
};

#endif // VERLET_BALL_COLLIDERS_CIRCLE_OPEN_HPP
