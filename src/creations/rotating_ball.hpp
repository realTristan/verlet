#ifndef CREATIONS_ROTATING_BALL_HPP
#define CREATIONS_ROTATING_BALL_HPP

#include <objects/verlet/ball/colliders/circle_open.hpp>
#include <objects/verlet/ball/colliders/line.hpp>
#include <objects/verlet/ball/ball.hpp>
#include <physics/vector2d.h>
#include <testing/events.hpp>
#include <testing/config.hpp>
#include <SFML/Graphics.hpp>
#include <utils/colors.hpp>
#include <interface/components/text.hpp>
#include <vector>

typedef std::vector<VerletBall *> VerletBallVector;

class RotatingBall
{
public:
    static void start()
    {
        // Create the window
        sf::RenderWindow *window = new sf::RenderWindow(
            sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), WINDOW_TITLE);
        window->setFramerateLimit(60);

        // Create the ball
        VerletBallVector balls = VerletBallVector {
            new VerletBall(Vec2D(200.0f, 100.0f), 15.0f, CYAN)
        };

        // Create the line collider
        LineCollider *line = new LineCollider(Vec2D(200.0f, 100.0f), 0.001f, 35.0f, 2);

        // Create the open circle collider
        OpenCircleCollider *circle = new OpenCircleCollider(Vec2D(400.0f, 300.0f), 300.0f, 5, WHITE, false);

        // Create the text
        Text *text = new Text("Rotating Ball", Vec2D(250.0f, 265.0f), 50, WHITE);

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
