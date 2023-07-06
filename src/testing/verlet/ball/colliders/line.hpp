#include <SFML/Graphics.hpp>
#include <objects/verlet/ball/ball.hpp>
#include <objects/verlet/ball/colliders/circle_open.hpp>
#include <objects/verlet/ball/colliders/line.hpp>
#include <testing/events.hpp>
#include <testing/config.hpp>
#include <thread>

#ifndef TESTING_VERLET_BALL_COLLIDERS_LINE_HPP
#define TESTING_VERLET_BALL_COLLIDERS_LINE_HPP

#define LINE_COLLIDER_VECTOR Vector2D(200, 250)
#define LINE_COLLIDER_LENGTH 150
#define LINE_COLLIDER_ANGLE 15
#define LINE_COLLIDER_COLOR Colors().WHITE
#define LINE_COLLIDER_SLOPE_MULTIPLIER 0.1

#define VERLET_BALL_VECTOR Vector2D(200, 200)
#define VERLET_BALL_RADIUS 4
#define VERLET_BALL_COLOR Colors().CYAN


class LineColliderTesting
{
public:
    static int start()
    {
        // Initialize a new window
        sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), WINDOW_TITLE);

        // Create a new list of colliders
        LineCollider line_collider = LineCollider(
            LINE_COLLIDER_VECTOR,
            LINE_COLLIDER_LENGTH,
            LINE_COLLIDER_ANGLE,
            LINE_COLLIDER_COLOR,
            LINE_COLLIDER_SLOPE_MULTIPLIER
        );

        // Create a new list of balls
        std::vector<VerletBall *> balls = std::vector<VerletBall *>{};
        std::thread t([&]() {
            for (int i = 0; i < 600; i++) {
                std::this_thread::sleep_for(std::chrono::milliseconds(10));
                VerletBall *ball = new VerletBall(
                    VERLET_BALL_VECTOR,
                    VERLET_BALL_RADIUS,
                    VERLET_BALL_COLOR
                );
                balls.push_back(ball);
            } 
        });

        // Window Loop
        while (window.isOpen())
        {
            Events::check_close(&window);
            window.clear();

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