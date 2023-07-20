#ifndef TESTING_LINE_HPP
#define TESTING_LINE_HPP

#include <objects/verlet/ball/ball.hpp>
#include <physics/vector2d.h>
#include <testing/config.hpp>
#include <testing/events.hpp>
#include <testing/utils.hpp>
#include <SFML/Graphics.hpp>
#include <objects/line.hpp>

#define LINE_START_VECTOR Vec2D<float>(200.0f, 250.0f)
#define LINE_LENGTH 150.0f
#define LINE_ANGLE 15.0f
#define LINE_WIDTH 5
#define LINE_COLOR WHITE

class LineTesting
{
public:
    static void start()
    {
        // Initialize a new window
        sf::RenderWindow *window = new sf::RenderWindow(
            sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), WINDOW_TITLE);
        window->setFramerateLimit(FPS);

        // Create a new line
        Line *line = new Line(
            LINE_START_VECTOR,
            LINE_LENGTH,
            LINE_ANGLE,
            LINE_WIDTH,
            LINE_COLOR);

        // Window Loop
        while (window->isOpen())
        {
            Events::check_close(window);
            Utils::draw_background(window);

            // Draw the line collider
            line->draw(window);

            // Update the window
            window->display();
        }
    }
};

#endif