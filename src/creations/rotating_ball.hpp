#include <iostream>
#include <SFML/Graphics.hpp>
#include <objects/verlet/ball/colliders/circle_open.hpp>
#include <objects/verlet/ball/colliders/line.hpp>
#include <objects/verlet/ball/ball.hpp>
#include <physics/vector2d.hpp>
#include <utils/colors.hpp>
#include <interface/components/text.hpp>
#include <testing/events.hpp>

#ifndef CREATIONS_ROTATING_BALL_HPP
#define CREATIONS_ROTATING_BALL_HPP

class RotatingBall
{
public:
    static void start()
    {
        // Create the window
        sf::RenderWindow window(sf::VideoMode(800, 600), "Rotating Ball");

        // Create the ball
        VerletBall ball(Vec2D(200.0f, 100.0f), 15.0f, CYAN);

        // Create the line collider
        LineCollider line(Vec2D(200.0f, 100.0f), 0.001f, 35.0f, 2);

        // Create the open circle collider
        OpenCircleCollider circle(Vec2D(400.0f, 300.0f), 300.0f, 5, WHITE, false);

        // Create the text
        Text text("Rotating Ball", Vec2D(250.0f, 265.0f), 50, WHITE);

        // Game Loop
        while (window.isOpen())
        {
            // Draw the background
            window.clear(Colors::to_sf(BLACK));

            // Check for a close event
            Events::check_close(&window);

            // Draw the text
            text.draw(&window);

            // Update the ball
            ball.update(&window);
            line.apply(&ball);
            line.draw(&window);
            circle.apply(&ball);
            circle.draw(&window);

            // Update the display
            window.display();
        }
    }
};

#endif // CREATIONS_ROTATING_BALL_HPP
