#ifndef TESTING_VERLET_BALL_COLLIDERS_LINE_HPP
#define TESTING_VERLET_BALL_COLLIDERS_LINE_HPP

#include <objects/verlet/ball/colliders/line.hpp>
#include <objects/verlet/ball/ball.hpp>
#include <objects/limiter.hpp>
#include <testing/events.hpp>
#include <testing/config.hpp>
#include <testing/utils.hpp>
#include <SFML/Graphics.hpp>
#include <vector>

#define LINE_COLLIDER_VECTOR Vec2D<float>(200, 250)
#define LINE_COLLIDER_LENGTH 150
#define LINE_COLLIDER_ANGLE 15
#define LINE_COLLIDER_WIDTH 5
#define LINE_COLLIDER_COLOR WHITE

#define VERLET_BALL_COUNT 100
#define VERLET_BALL_VECTOR Vec2D<float>(200, 200)
#define VERLET_BALL_RADIUS 4
#define VERLET_BALL_ADD_INTERVAL 100 // 100ms
#define VERLET_BALL_OFFSET Vec2D<float>(0, 0)
#define VERLET_BALL_RANDOM_COLOR true

typedef std::vector<VerletBall *> VerletBallVector;

// Line Collider Testing Class
class LineColliderTesting
{
public:
    static void start()
    {
        // Initialize a new window
        sf::RenderWindow *window = new sf::RenderWindow(
            sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), WINDOW_TITLE);
        window->setFramerateLimit(FPS);

        // Create a new list of colliders
        LineCollider *line_collider = new LineCollider(
            LINE_COLLIDER_VECTOR,
            LINE_COLLIDER_LENGTH,
            LINE_COLLIDER_ANGLE,
            LINE_COLLIDER_WIDTH,
            LINE_COLLIDER_COLOR);

        // Create a new list of balls
        VerletBallVector balls = VerletBallVector();
        Utils::auto_add_verlet_balls(
            &balls,
            VERLET_BALL_VECTOR,
            VERLET_BALL_COUNT,
            VERLET_BALL_RADIUS,
            VERLET_BALL_ADD_INTERVAL,
            VERLET_BALL_OFFSET,
            VERLET_BALL_RANDOM_COLOR);

        // Create a new limiter
        ObjectLimiter *limiter = new ObjectLimiter(VERLET_BALL_COUNT);

        // Window Loop
        while (window->isOpen())
        {
            Events::check_close(window);
            Utils::draw_background(window);

            // Add a ball on button click
            Utils::add_verlet_ball_on_click(
                window,
                &balls,
                VERLET_BALL_RADIUS,
                VERLET_BALL_RANDOM_COLOR);

            // Update the limiter
            limiter->update(&balls);

            // Draw the line collider
            line_collider->draw(window);

            // Draw and update the balls
            for (int i = 0; i < SUBSTEPS; i++)
            {
                for (int j = 0; j < balls.size(); j++)
                {
                    balls[j]->draw(window);
                    balls[j]->update(window, &balls);
                    line_collider->apply(balls[j]);
                }
            }

            // Update the window
            window->display();
        }
    }
};

#endif // TESTING_VERLET_BALL_COLLIDERS_LINE_HPP