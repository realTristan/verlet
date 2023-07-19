#ifndef VERLET_BALL_HPP
#define VERLET_BALL_HPP

#include <objects/verlet/object.hpp>
#include <objects/verlet/grid.hpp>
#include <physics/constants.h>
#include <physics/vector2d.h>
#include <SFML/Graphics.hpp>
#include <utils/colors.hpp>

class VerletBall : public VerletObject
{
public:
    float radius;
    int point_count;

    Cell<VerletBall> *grid_cell;

    // Initialize the verlet object
    VerletBall(
        Vec2D<float> position,
        float radius,
        float outline_width = 1.0f,
        Color fill_color = WHITE,
        Color outline_color = WHITE,
        int point_count = 128) : VerletObject(position, outline_width, fill_color, outline_color)
    {
        this->radius = radius;
        this->point_count = point_count;
    }

    // Set the grid cell
    void set_grid_cell(Cell<VerletBall> *grid_cell)
    {
        this->grid_cell = grid_cell;
    }

    // Draw the object
    void draw(sf::RenderWindow *window)
    {
        sf::CircleShape circle(this->radius);
        circle.setPosition(this->current_position.x, this->current_position.y);
        circle.setFillColor(Colors::to_sf(this->fill_color));
        circle.setOutlineColor(Colors::to_sf(this->outline_color));
        circle.setOutlineThickness(this->outline_width);
        circle.setPointCount(this->point_count);
        window->draw(circle);
    }

    // Handle collisions with other objects
    void handle_collision(VerletBall *other_ball)
    {
        // Calculate the distance between the balls
        Vec2D<float> dist = this->current_position - other_ball->current_position;

        // the vector magnitude of the ball
        float magnitude = dist.magnitude() + 1.0e-9f;
        float rad_sum = this->radius + other_ball->radius;
        if (magnitude < rad_sum)
        {
            // Calculate the ball overlap (the amount the balls have overlapped)
            Vec2D<float> overlap = dist / magnitude;

            // Update this balls position (move it to the side)
            this->current_position += overlap * 0.5f * (rad_sum - magnitude);

            // Update the other ball's position (move it to the opposite side)
            other_ball->current_position -= overlap * 0.5f * (rad_sum - magnitude);
        }
    }

    // Check if the ball is colliding with other balls
    void collisions(std::vector<VerletBall *> *balls)
    {
        for (VerletBall *other_ball : *balls)
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
    void update(sf::RenderWindow *window, std::vector<VerletBall *> *balls)
    {
        this->accelerate(GRAVITY);
        this->update_position();
        this->collisions(balls);
        this->draw(window);
    }

    // Update without checking for collisions
    void update_with_grid(sf::RenderWindow *window, Grid<VerletBall> *grid)
    {
        this->accelerate(GRAVITY);
        this->update_position();
        this->draw(window);
        if (this->grid_cell != nullptr)
        {
            grid->find_collisions(this->grid_cell);
        }
    }
};

#endif // VERLET_BALL_HPP