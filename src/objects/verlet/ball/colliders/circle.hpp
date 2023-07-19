#ifndef VERLET_BALL_COLLIDERS_CIRCLE_HPP
#define VERLET_BALL_COLLIDERS_CIRCLE_HPP

#include <objects/verlet/ball/ball.hpp>
#include <SFML/Graphics.hpp>
#include <utils/colors.hpp>

class CircleCollider
{
public:
    Vec2D<float> position;
    float outline_width;
    int point_count;
    float radius;

    Color fill_color;
    Color outline_color;

    bool outside_collision;
    bool inside_collision;

    CircleCollider(
        Vec2D<float> position,
        float radius,
        float outline_width = 1.0f,
        Color fill_color = TRANSPARENT,
        Color outline_color = WHITE,
        bool outside_collision = true,
        bool inside_collision = true,
        int point_count = 128)
    {
        this->position = position;

        this->radius = radius;
        this->outline_width = outline_width;
        this->point_count = point_count;

        this->fill_color = fill_color;
        this->outline_color = outline_color;

        this->outside_collision = outside_collision;
        this->inside_collision = inside_collision;
        this->outline_width = outline_width;
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
    void set_outline_color(Color color)
    {
        this->outline_color = color;
    }

    // Set the fill color
    void set_fill_color(Color color)
    {
        this->fill_color = color;
    }

    // Set the width
    void set_outline_width(float outline_width)
    {
        this->outline_width = outline_width;
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
        circle.setOrigin(this->radius, this->radius);
        circle.setPosition(this->position.x + 4.0f, this->position.y + 3.0f);
        circle.setFillColor(Colors::to_sf(this->fill_color));
        circle.setOutlineColor(Colors::to_sf(this->outline_color));
        circle.setOutlineThickness(this->outline_width);
        circle.setPointCount(this->point_count);
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
            float delta = this->radius - ball->radius - this->outline_width;
            bool ball_colliding_with_circle = magnitude >= delta;
            bool ball_inside_circle = magnitude < this->radius;

            if (ball_colliding_with_circle && (!this->outside_collision || ball_inside_circle))
            {
                ball->current_position += dist / magnitude * (delta - magnitude);
                return;
            }
        }

        // Check if the ball is outside the collider
        if (this->outside_collision)
        {
            float rad_sum = ball->radius + this->radius + this->outline_width;
            bool ball_colliding_with_circle = magnitude <= rad_sum;
            bool ball_outside_circle = magnitude > this->radius;

            if (ball_colliding_with_circle && (!this->inside_collision || ball_outside_circle))
            {
                // Calculate the ball overlap (the amount the balls have overlapped)
                Vec2D<float> overlap = dist / magnitude;
                float offset = ((ball->radius * 2.0f) + this->radius + this->outline_width);

                // Update this balls position (move it to the side)
                ball->current_position += (overlap * 0.5f * (offset - magnitude));
            }
        }
    }
};

#endif // VERLET_BALL_COLLIDERS_CIRCLE_HPP
