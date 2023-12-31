#ifndef CREATIONS_VERLET_FLUID_HPP
#define CREATIONS_VERLET_FLUID_HPP

#include <objects/verlet/ball/colliders/circle.hpp>
#include <objects/verlet/ball/colliders/line.hpp>
#include <objects/verlet/ball/ball.hpp>
#include <testing/events.hpp>
#include <testing/config.hpp>
#include <testing/utils.hpp>
#include <SFML/Graphics.hpp>
#include <vector>

#define CIRCLE_COLLIDER_VECTOR Vec2D<float>(400.0f, 300.0f)
#define CIRCLE_COLLIDER_RADIUS 300.0f
#define CIRCLE_COLLIDER_THICKNESS 2.0f
#define CIRCLE_COLLIDER_COLOR WHITE

#define LINE_COLLIDER_VECTOR Vec2D<float>(200.0f, 250.0f)
#define LINE_COLLIDER_LENGTH 150.0f
#define LINE_COLLIDER_ANGLE 60.0f
#define LINE_COLLIDER_WIDTH 2
#define LINE_COLLIDER_COLOR WHITE

#define VERLET_BALL_COUNT 400
#define VERLET_BALL_VECTOR Vec2D<float>(200.0f, 200.0f)
#define VERLET_BALL_RADIUS 4.0f
#define VERLET_BALL_ADD_INTERVAL 10 // 10ms
#define VERLET_BALL_OFFSET Vec2D<float>(0.0f, 0.0f)
#define VERLET_BALL_RANDOM_COLOR false
#define VERLET_BALL_COLOR CYAN

typedef std::vector<VerletBall *> VerletBallVector;

class FluidCreation
{
public:
    static void start()
    {
        // Initialize a new window
        sf::RenderWindow *window = new sf::RenderWindow(
            sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), WINDOW_TITLE);
        window->setFramerateLimit(60);

        // Create a new list of colliders
        CircleCollider *circle_collider = new CircleCollider(
            CIRCLE_COLLIDER_VECTOR,
            CIRCLE_COLLIDER_RADIUS,
            CIRCLE_COLLIDER_THICKNESS);

        circle_collider->set_outline_color(CIRCLE_COLLIDER_COLOR);
        circle_collider->disable_outside_collision();

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
            VERLET_BALL_RANDOM_COLOR,
            VERLET_BALL_COLOR);

        // Window Loop
        while (window->isOpen())
        {
            Events::check_close(window);
            Utils::draw_background(window);

            // Draw the colliders
            circle_collider->draw(window);
            line_collider->draw(window);

            // Draw and update the balls
            for (int i = 0; i < SUBSTEPS; i++)
            {
                for (int j = 0; j < balls.size(); j++)
                {
                    balls[j]->draw(window);
                    balls[j]->update(window, &balls);
                    line_collider->apply(balls[j]);
                    circle_collider->apply(balls[j]);
                }
            }

            // Update the window
            window->display();
        }
    }
};

#endif // CREATIONS_VERLET_FLUID_HPP