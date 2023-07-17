#ifndef VERLET_OBJECT_HPP
#define VERLET_OBJECT_HPP

#include <physics/vector2d.h>
#include <utils/colors.hpp>
#include <utils/time.h>

class VerletObject
{
public:
    Vec2D<float> current_position;
    Vec2D<float> prev_position;
    Vec2D<float> acceleration;
    Vec2D<float> velocity;
    Color color = WHITE;
    float start_time;

    VerletObject(Vec2D<float> position, Color color)
    {
        this->current_position = position;
        this->prev_position = position;
        this->acceleration = Vec2D<float>();
        this->velocity = Vec2D<float>();
        this->color = color;
        this->start_time = Time::now();
    }

    // Set the object's color
    void set_color(Color color)
    {
        this->color = color;
    }

    // Calculate the object's velocity
    Vec2D<float> calculate_velocity()
    {
        return this->current_position - this->prev_position;
    }

    // Perform the verlet integration to calculate the displacement
    Vec2D<float> calculate_displacement(float dt)
    {
        return this->current_position + this->velocity + this->acceleration * dt;
    }

    // Accelerate the object
    void accelerate(Vec2D<float> acceleration)
    {
        this->acceleration += acceleration;
    }

    // Update the object's position
    void update_position()
    {
        // Get the time difference (delta time)
        float dt = Time::now() - this->start_time;

        // Update the object's position
        this->velocity = this->calculate_velocity();
        this->prev_position = this->current_position.copy();
        this->current_position = this->calculate_displacement(dt);

        // Reset the acceleration and start time
        this->acceleration.zero();
        this->start_time = Time::now();
    }
};

#endif // VERLET_OBJECT_HPP