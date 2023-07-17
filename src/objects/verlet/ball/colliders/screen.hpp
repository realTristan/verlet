#ifndef VERLET_BALL_SCREEN_COLLIDER_HPP
#define VERLET_BALL_SCREEN_COLLIDER_HPP

#include <objects/verlet/ball/ball.hpp>
#include <physics/vector2d.hpp>

class ScreenCollider
{
private:
    int width_min = 0;
    int width_max = 0;
    int height_min = 0;
    int height_max = 0;

    // Handle the right collision
    void handle_right_collision(VerletBall *ball) {
        // If the ball is outside the screen to the right
        if (ball->current_position.x + ball->radius > this->width_max) {
            // Move the ball to the right edge
            ball->current_position.x = this->width_max - ball->radius * 2;
        }
    }

    // Handle the left collision
    void handle_left_collision(VerletBall *ball) {
        // If the ball is outside the screen to the left
        if (ball->current_position.x - ball->radius < this->width_min) {
            // Move the ball to the left edge
            ball->current_position.x = this->width_min + ball->radius * 2;
        }
    }

    // Handle the top collision
    void handle_top_collision(VerletBall *ball) {
        // If the ball is outside the screen to the top
        if (ball->current_position.y - ball->radius < this->height_min) {
            // Move the ball to the top edge
            ball->current_position.y = this->height_min + ball->radius * 2;
        }
    }

    // Handle the bottom collision
    void handle_bottom_collision(VerletBall *ball) {
        // If the ball is outside the screen to the bottom
        if (ball->current_position.y + ball->radius > this->height_max) {
            // Move the ball to the bottom edge
            ball->current_position.y = this->height_max - ball->radius * 2;
        }
    }

public:
    ScreenCollider(int width, int height) {
        this->width_max = width;
        this->height_max = height;
    }

    void apply(VerletBall *ball) {
        this->handle_right_collision(ball);
        this->handle_left_collision(ball);
        this->handle_top_collision(ball);
        this->handle_bottom_collision(ball);
    }
};

#endif // SCREEN_COLLIDER_HPP