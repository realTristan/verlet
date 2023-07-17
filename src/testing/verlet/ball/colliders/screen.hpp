#ifndef TESTING_VERLET_BALL_COLLIDERS_SCREEN_HPP
#define TESTING_VERLET_BALL_COLLIDERS_SCREEN_HPP

#include <objects/verlet/ball/colliders/screen.hpp>
#include <objects/verlet/ball/ball.hpp>
#include <testing/events.hpp>
#include <testing/config.hpp>
#include <testing/utils.hpp>
#include <SFML/Graphics.hpp>
#include <thread>
#include <vector>

#define VERLET_BALL_COUNT 1
#define VERLET_BALL_VECTOR Vec2D(200, 200)
#define VERLET_BALL_RADIUS 10
#define VERLET_BALL_ADD_INTERVAL 100 // 100ms
#define VERLET_BALL_OFFSET Vec2D(0, 0)
#define VERLET_BALL_COLOR CYAN

typedef std::vector<VerletBall *> VerletBallVector;

// Screen Collider Testing Class
class ScreenColliderTesting
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
            VERLET_BALL_OFFSET,
            VERLET_BALL_COLOR);

        // Create a screen collider
        ScreenCollider screen_collider = ScreenCollider(WINDOW_WIDTH, WINDOW_HEIGHT);

        // Window Loop
        while (window.isOpen())
        {
            Events::check_close(&window);
            Utils::draw_background(&window);

            // Draw and update the balls
            for (int i = 0; i < SUBSTEPS; i++)
            {
                for (int j = 0; j < balls.size(); j++)
                {
                    balls[j]->draw(&window);
                    balls[j]->update(&window, &balls);
                    screen_collider.apply(balls[j]);
                }
            }

            // Update the window
            window.display();
        }
    }
};

#endif // TESTING_VERLET_BALL_COLLIDERS_SCREEN_HPP