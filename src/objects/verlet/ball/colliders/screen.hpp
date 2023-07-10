#ifndef VERLET_BALL_SCREEN_COLLIDER_HPP
#define VERLET_BALL_SCREEN_COLLIDER_HPP

#include <physics/vector2d.hpp>
#include <objects/verlet/ball/ball.hpp>
#include <testing/config.hpp>

class ScreenCollider
{
private:
    int width_min = 0;
    int width_max = WINDOW_WIDTH;
    int height_min = 0;
    int height_max = WINDOW_HEIGHT;

    void handle_right_collision(VerletBall *ball) {
        float dist = ball->current_position.x + ball->radius - this->width_max;
        if (dist < 0) {
            ball->current_position.x = this->width_max + ball->radius;
        }
    }

    void handle_left_collision(VerletBall *ball) {
        float dist = ball->current_position.x - ball->radius + this->width_min;
        if (dist < 0) {
            ball->current_position.x = this->width_min + ball->radius;
        }
    }

    void handle_top_collision(VerletBall *ball) {
        float dist = ball->current_position.y - ball->radius + this->height_min;
        if (dist < 0) {
            ball->current_position.y = this->height_min + ball->radius;
        }
    }

    void handle_bottom_collision(VerletBall *ball) {
        float dist = ball->current_position.y + ball->radius - this->height_max;
        if (dist < 0) {
            ball->current_position.y = this->height_max - ball->radius;
        }
    }

public:
    void apply(VerletBall *ball) {
        this->handle_right_collision(ball);
        this->handle_left_collision(ball);
        this->handle_top_collision(ball);
        this->handle_bottom_collision(ball);
    }
};

#endif // SCREEN_COLLIDER_HPP