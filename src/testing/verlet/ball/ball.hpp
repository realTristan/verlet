#ifndef TESTING_VERLET_BALL_HPP
#define TESTING_VERLET_BALL_HPP

#include <objects/verlet/ball/colliders/circle_closed.hpp>
#include <objects/verlet/ball/ball.hpp>
#include <testing/events.hpp>
#include <testing/config.hpp>
#include <testing/utils.hpp>
#include <SFML/Graphics.hpp>
#include <thread>
#include <vector>

#define VERLET_BALL_COUNT 100
#define VERLET_BALL_VECTOR Vec2D(400, 100)
#define VERLET_BALL_RADIUS 10
#define VERLET_BALL_ADD_INTERVAL 100 // 100ms
#define VERLET_BALL_COLOR CYAN

typedef std::vector<VerletBall *> VerletBallVector;

// Verlet Ball Testing Class
class VerletBallTesting
{
public:
    static void start()
    {
        // Initialize a new window
        sf::RenderWindow window(
            sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), WINDOW_TITLE);
        window.setFramerateLimit(60);

        // Create a new list of balls
        VerletBallVector balls = VerletBallVector();
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

            // Update the window
            window.display();
        }
    }
};

#endif // TESTING_VERLET_BALL_HPP