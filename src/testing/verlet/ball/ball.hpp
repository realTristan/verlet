#include<iostream>
#include <SFML/Graphics.hpp>
#include <objects/verlet/ball/ball.hpp>
#include <objects/verlet/ball/colliders/circle_closed.hpp>
#include <testing/events.hpp>
#include <testing/config.hpp>
#include <thread>

#ifndef TESTING_VERLET_BALL_HPP
#define TESTING_VERLET_BALL_HPP

#define VERLET_BALL_COUNT 100
#define VERLET_BALL_VECTOR Vector2D(400, 100)
#define VERLET_BALL_RADIUS 10
#define VERLET_BALL_COLOR Colors().CYAN

class VerletBallTesting
{
  public:
    static int start()
    {
        // Initialize a new window
        sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), WINDOW_TITLE);

        // Create a new list of balls
        std::vector<VerletBall *> balls = std::vector<VerletBall *>{};
        std::thread t([&]() {
        for (int i = 0; i < VERLET_BALL_COUNT; i++) {
            std::this_thread::sleep_for(std::chrono::milliseconds(500));
            VerletBall *ball = new VerletBall(
                VERLET_BALL_VECTOR, 
                VERLET_BALL_RADIUS, 
                VERLET_BALL_COLOR
            );
            balls.push_back(ball);
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

            // Update the window
            window.display();
        }
        return 0;
    }
};

#endif // TESTING_VERLET_BALL_HPP