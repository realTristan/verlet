#ifndef CREATIONS_ROTATING_BALL_HPP
#define CREATIONS_ROTATING_BALL_HPP

#include <objects/verlet/ball/colliders/circle.hpp>
#include <objects/verlet/ball/colliders/line.hpp>
#include <objects/verlet/ball/ball.hpp>
#include <physics/vector2d.h>
#include <testing/events.hpp>
#include <testing/config.hpp>
#include <SFML/Graphics.hpp>
#include <utils/colors.hpp>
#include <interface/components/text.hpp>
#include <vector>

#define CIRCLE_COLLIDER_POSITION Vec2D<float>(400.0f, 300.0f)
#define CIRCLE_COLLIDER_RADIUS 300.0f
#define CIRCLE_COLLIDER_COLOR WHITE

#define VERLET_BALL_COUNT 50
#define VERLET_BALL_POSITION Vec2D<float>(200.0f, 100.0f)
#define VERLET_BALL_RADIUS 5.0f
#define VERLET_BALL_ADD_INTERVAL 100 // 100ms
#define VERLET_BALL_OFFSET Vec2D<float>(2.0f, 0.0f)
#define VERLET_BALL_RANDOM_COLOR true

#define LINE_COLLIDER_POSITION Vec2D<float>(200.0f, 100.0f)
#define LINE_COLLIDER_LENGTH 1.0f
#define LINE_COLLIDER_ANGLE 35.0f
#define LINE_COLLIDER_WIDTH 2

#define TEXT_POSITION Vec2D<float>(250.0f, 265.0f)
#define TEXT_SIZE 50

typedef std::vector<VerletBall *> VerletBallVector;

class RotatingBallCreation
{
public:
    static void start()
    {
        // Create the window
        sf::RenderWindow *window = new sf::RenderWindow(
            sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), WINDOW_TITLE);
        window->setFramerateLimit(60);

        // Create the ball
        VerletBallVector balls = VerletBallVector{
            new VerletBall(
                VERLET_BALL_POSITION,
                VERLET_BALL_RADIUS)};

        // Create the line collider
        LineCollider *line = new LineCollider(
            LINE_COLLIDER_POSITION,
            LINE_COLLIDER_LENGTH,
            LINE_COLLIDER_ANGLE,
            LINE_COLLIDER_WIDTH,
            BLACK);

        // Create the open circle collider
        CircleCollider *circle = new CircleCollider(
            CIRCLE_COLLIDER_POSITION,
            CIRCLE_COLLIDER_RADIUS);

        circle->set_outline_color(CIRCLE_COLLIDER_COLOR);
        circle->disable_outside_collision();

        // Create the text
        Text *text = new Text("Rotating Ball", TEXT_POSITION, TEXT_SIZE, WHITE);

        // Game Loop
        while (window->isOpen())
        {
            window->clear(Colors::to_sf(BLACK));
            Events::check_close(window);

            // Draw the text
            text->draw(window);

            // Draw the colliders
            line->draw(window);
            circle->draw(window);

            // Update the ball
            for (int i = 0; i < SUBSTEPS; i++)
            {
                for (int j = 0; j < balls.size(); j++)
                {
                    line->apply(balls[j]);
                    circle->apply(balls[j]);
                }
            }

            // Update the display
            window->display();
        }
    }
};

#endif // CREATIONS_ROTATING_BALL_HPP
