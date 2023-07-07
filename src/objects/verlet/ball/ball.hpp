#include <iostream>
#include <SFML/Graphics.hpp>
#include <physics/vector2d.hpp>
#include <physics/constants.hpp>
#include <utils/colors.hpp>
#include <objects/verlet/object.hpp>

#ifndef VERLET_BALL_HPP
#define VERLET_BALL_HPP

class VerletBall : public VerletObject
{
public:
    float radius;

    // Initialize the verlet object
    VerletBall(Vector2D position, float radius, Color color = WHITE) : VerletObject(position, color)
    {
        this->radius = radius;
    }

    // Draw the object
    void draw(sf::RenderWindow *window)
    {
        sf::CircleShape circle(this->radius);
        circle.setPosition(this->current_position.x, this->current_position.y);
        circle.setFillColor(sf::Color(this->color.r, this->color.g, this->color.b));
        window->draw(circle);
    }

    // Handle collisions with other objects
    void handle_collision(VerletBall *other_ball)
    {
        // Calculate the distance between the balls
        Vector2D dist = this->current_position - other_ball->current_position;

        // the vector magnitude of the ball
        float magnitude = dist.magnitude() + 1.0e-9;
        float rad_sum = this->radius + other_ball->radius;
        if (magnitude < rad_sum)
        {
            // Calculate the ball overlap (the amount the balls have overlapped)
            Vector2D overlap = dist / magnitude;

            // Update this balls position (move it to the side)
            this->current_position += overlap * 0.5 * (rad_sum - magnitude);

            // Update the other ball's position (move it to the opposite side)
            other_ball->current_position -= overlap * 0.5 * (rad_sum - magnitude);
        }
    }

    // Check if the ball is colliding with other balls
    void collisions(std::vector<VerletBall *> balls)
    {
        for (VerletBall *other_ball : balls)
        {
            if (this == other_ball)
            {
                continue;
            }

            // Handle the collision with the other ball
            this->handle_collision(other_ball);
        }
    }

    // Update the ball
    void update(sf::RenderWindow *window, std::vector<VerletBall *> balls = {})
    {
        this->accelerate(GRAVITY);
        this->update_position();
        this->collisions(balls);
        this->draw(window);
    }

    // Update without checking for collisions
    void update_no_collisions(sf::RenderWindow *window)
    {
        this->accelerate(GRAVITY);
        this->update_position();
        this->draw(window);
    }
};

#endif