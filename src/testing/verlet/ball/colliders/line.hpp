#ifndef TESTING_VERLET_BALL_COLLIDERS_LINE_HPP
#define TESTING_VERLET_BALL_COLLIDERS_LINE_HPP

#include <objects/verlet/ball/colliders/circle_open.hpp>
#include <objects/verlet/ball/colliders/line.hpp>
#include <objects/verlet/ball/ball.hpp>
#include <testing/events.hpp>
#include <testing/config.hpp>
#include <testing/utils.hpp>
#include <utils/window.hpp>
#include <utils/types.hpp>
#include <thread>

#define LINE_COLLIDER_VECTOR Vec2D(200, 250)
#define LINE_COLLIDER_LENGTH 150
#define LINE_COLLIDER_ANGLE 15
#define LINE_COLLIDER_WIDTH 5
#define LINE_COLLIDER_COLOR WHITE
#define LINE_COLLIDER_SLOPE_MULTIPLIER 0.1

#define VERLET_BALL_COUNT 100
#define VERLET_BALL_VECTOR Vec2D(200, 200)
#define VERLET_BALL_RADIUS 4
#define VERLET_BALL_ADD_INTERVAL 10 // 10ms
#define VERLET_BALL_COLOR CYAN

// Line Collider Testing Class
class LineColliderTesting
{
public:
    static int start()
    {
        // Initialize a new window
        Window window = Window();

        // Create a new list of colliders
        LineCollider line_collider = LineCollider(
            LINE_COLLIDER_VECTOR,
            LINE_COLLIDER_LENGTH,
            LINE_COLLIDER_ANGLE,
            LINE_COLLIDER_WIDTH,
            LINE_COLLIDER_COLOR,
            LINE_COLLIDER_SLOPE_MULTIPLIER);

        // Create a new list of balls
        VerletBallVector balls = VerletBallVector{};
        Utils::auto_add_verlet_balls(
            &balls,
            VERLET_BALL_VECTOR,
            VERLET_BALL_COUNT,
            VERLET_BALL_RADIUS,
            VERLET_BALL_ADD_INTERVAL,
            VERLET_BALL_COLOR);

        // Window Loop
        while (window.isOpen())
        {
            Events::check_close(&window);
            Utils::draw_background(&window);

            // Draw and update the balls
            for (auto &ball : balls)
            {
                ball->draw(&window);
                ball->update(&window, balls);
            }

            // Draw the line collider
            line_collider.draw(&window);
            for (auto &ball : balls)
            {
                line_collider.apply(ball);
            }

            // Update the window
            window.display();
        }

        return 0;
    }
};

#endif // TESTING_VERLET_BALL_COLLIDERS_LINE_HPP