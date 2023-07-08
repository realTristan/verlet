#include <iostream>
#include <physics/vector2d.hpp>
#include <utils/colors.hpp>
#include <utils/time.hpp>

#ifndef VERLET_OBJECT_HPP
#define VERLET_OBJECT_HPP

class VerletObject
{
public:
    Vec2D current_position;
    Vec2D prev_position;
    Vec2D acceleration;
    Vec2D velocity;
    Color color = WHITE;
    float start_time;

    VerletObject(Vec2D position, Color color)
    {
        this->current_position = position;
        this->prev_position = position;
        this->acceleration = Vec2D();
        this->velocity = Vec2D();
        this->color = color;
        this->start_time = Time().now();
    }

    // Set the object's color
    void set_color(Color color)
    {
        this->color = color;
    }

    // Calculate the object's velocity
    Vec2D calculate_velocity()
    {
        return this->current_position - this->prev_position;
    }

    // Perform the verlet integration to calculate the displacement
    Vec2D calculate_displacement(float dt)
    {
        return this->current_position + this->velocity + this->acceleration * dt * dt;
    }

    // Accelerate the object
    void accelerate(Vec2D acceleration)
    {
        this->acceleration += acceleration;
    }

    // Update the object's position
    void update_position()
    {
        // Get the time difference (delta time)
        float dt = Time().now() - this->start_time;

        // Update the object's position
        this->velocity = this->calculate_velocity();
        this->prev_position = this->current_position.copy();
        this->current_position = this->calculate_displacement(dt);

        // Reset the acceleration and start time
        this->acceleration.zero();
        this->start_time = Time().now();
    }
};

#endif // VERLET_OBJECT_HPP