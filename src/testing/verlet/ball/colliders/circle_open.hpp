#ifndef TESTING_VERLET_BALL_COLLIDERS_CIRCLE_OPEN_HPP
#define TESTING_VERLET_BALL_COLLIDERS_CIRCLE_OPEN_HPP

#include <objects/verlet/ball/colliders/circle_open.hpp>
#include <objects/verlet/ball/ball.hpp>
#include <testing/events.hpp>
#include <testing/utils.hpp>
#include <utils/window.hpp>
#include <thread>
#include <vector>

#define CIRCLE_COLLIDER_VECTOR Vec2D(400, 300)
#define CIRCLE_COLLIDER_RADIUS 300
#define CIRCLE_COLLIDER_THICKNESS 2
#define CIRCLE_COLLIDER_COLOR WHITE
#define CIRCLE_COLLIDER_INSIDE_COLLISIONS false
#define CIRCLE_COLLIDER_OUTSIDE_COLLISIONS true

#define VERLET_BALL_COUNT 100
#define VERLET_BALL_VECTOR Vec2D(200, 200)
#define VERLET_BALL_RADIUS 4
#define VERLET_BALL_ADD_INTERVAL 10 // 10ms
#define VERLET_BALL_COLOR CYAN

typedef std::vector<VerletBall *> VerletBallVector;

// Open Circle Collider Testing
class OpenCircleColliderTesting
{
public:
    static void start()
    {
        // Initialize a new window
        Window window = Window();

        // Create a new list of colliders
        OpenCircleCollider circle_collider = OpenCircleCollider(
            CIRCLE_COLLIDER_VECTOR,
            CIRCLE_COLLIDER_RADIUS,
            CIRCLE_COLLIDER_THICKNESS,
            CIRCLE_COLLIDER_COLOR,
            CIRCLE_COLLIDER_INSIDE_COLLISIONS,
            CIRCLE_COLLIDER_OUTSIDE_COLLISIONS);

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
                ball->update(&window, &balls);
            }

            // Draw the circle collider
            circle_collider.draw(&window);
            for (auto &ball : balls)
            {
                circle_collider.apply(ball);
            }

            // Update the window
            window.display();
        }
    }
};

#endif // TESTING_VERLET_BALL_COLLIDERS_CIRCLE_OPEN_HPP