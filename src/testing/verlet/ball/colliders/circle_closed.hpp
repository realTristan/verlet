#include <iostream>
#include <SFML/Graphics.hpp>
#include <objects/verlet/ball/ball.hpp>
#include <objects/verlet/ball/colliders/circle_closed.hpp>
#include <testing/events.hpp>
#include <thread>

#ifndef TESTING_VERLET_BALL_COLLIDERS_CIRCLE_CLOSED_HPP
#define TESTING_VERLET_BALL_COLLIDERS_CIRCLE_CLOSED_HPP

class ClosedCircleColliderTesting
{
public:
    static int start()
    {
        // Initialize a new window
        sf::RenderWindow window(sf::VideoMode(800, 600), "verlet");

        // Create a new list of colliders
        ClosedCircleCollider circle_collider = ClosedCircleCollider(Vector2D(400, 300), 100, 2, Colors().WHITE, true);

        // Create a new list of balls
        std::vector<VerletBall *> balls = std::vector<VerletBall *>{};
        std::thread t([&]() {
        for (int i = 0; i < 600; i++) {
            std::this_thread::sleep_for(std::chrono::milliseconds(10));
            balls.push_back(new VerletBall(Vector2D(200, 200), 4, Colors().CYAN));
        } });

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