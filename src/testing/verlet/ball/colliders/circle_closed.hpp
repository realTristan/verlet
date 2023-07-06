#include <iostream>
#include <SFML/Graphics.hpp>
#include <objects/verlet/ball/ball.hpp>
#include <objects/verlet/ball/colliders/circle_closed.hpp>
#include <testing/events.hpp>
#include <thread>

#ifndef TESTING_VERLET_BALL_COLLIDERS_CIRCLE_CLOSED_HPP
#define TESTING_VERLET_BALL_COLLIDERS_CIRCLE_CLOSED_HPP

#define CIRCLE_COLLIDER_VECTOR Vector2D(400, 300)
#define CIRCLE_COLLIDER_RADIUS 300
#define CIRCLE_COLLIDER_THICKNESS 2
#define CIRCLE_COLLIDER_COLOR Colors().WHITE
#define CIRCLE_COLLIDER_OUTSIDE_COLLISIONS true

#define VERLET_BALL_VECTOR Vector2D(200, 200)
#define VERLET_BALL_RADIUS 4
#define VERLET_BALL_COLOR Colors().CYAN

class ClosedCircleColliderTesting
{
public:
    static int start()
    {
        // Initialize a new window
        sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), WINDOW_TITLE);

        // Create a new list of colliders
        ClosedCircleCollider circle_collider = ClosedCircleCollider(
            CIRCLE_COLLIDER_VECTOR,
            CIRCLE_COLLIDER_RADIUS,
            CIRCLE_COLLIDER_THICKNESS,
            CIRCLE_COLLIDER_COLOR,
            CIRCLE_COLLIDER_OUTSIDE_COLLISIONS);

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

            // Draw the circle collider
            circle_collider.draw(&window);
            for (auto &ball : balls)
            {
                circle_collider.apply(ball);
            }

            // Update the window
            window.display();
        }
        return 0;
    }
};

#endif // TESTING_VERLET_BALL_COLLIDERS_CIRCLE_CLOSED_HPP