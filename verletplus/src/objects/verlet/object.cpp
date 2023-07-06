#include <iostream>
#include "../../physics/vector2d.cpp"
#include "../../utils/colors.cpp"
#include "../../utils/time.cpp"

class VerletObject
{
public:
    Vector2D current_position;
    Vector2D prev_position;
    Vector2D acceleration;
    Vector2D velocity;
    Color color = Colors().WHITE;
    float start_time;

    VerletObject(Vector2D position, Color color) {
        this->current_position = position;
        this->prev_position = position;
        this->acceleration = Vector2D();
        this->velocity = Vector2D();
        this->color = color;
        this->start_time = Time().seconds();
    }

    // Set the object's color
    void set_color(Color color) {
        this->color = color;
    }

    // Calculate the object's velocity
    Vector2D calculate_velocity() {
        return this->current_position - this->prev_position;
    }

    // Perform the verlet integration to calculate the displacement
    Vector2D calculate_displacement(float dt) {
        return this->current_position + this->velocity + this->acceleration * dt;
    }

    // Accelerate the object
    void accelerate(Vector2D acceleration) {
        this->acceleration += acceleration;
    }

    // Update the object's position
    void update_position() {
        // Get the time difference (delta time)
        float dt = Time().seconds() - this->start_time;

        // Update the object's position
        this->velocity = this->calculate_velocity();
        this->prev_position = this->current_position.copy();
        this->current_position = this->calculate_displacement(dt);

        // Reset the acceleration and start time
        this->acceleration.zero();
        this->start_time = Time().seconds();
    }
};
