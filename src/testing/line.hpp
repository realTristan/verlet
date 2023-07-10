#ifndef TESTING_LINE_HPP
#define TESTING_LINE_HPP

#include <objects/verlet/ball/ball.hpp>
#include <physics/vector2d.hpp>
#include <testing/config.hpp>
#include <testing/events.hpp>
#include <testing/utils.hpp>
#include <objects/line.hpp>
#include <utils/window.hpp>
#include <thread>

#define LINE_START_VECTOR Vec2D(200, 250)
#define LINE_LENGTH 150.0f
#define LINE_ANGLE 15.0f
#define LINE_WIDTH 5
#define LINE_COLOR WHITE

class LineTesting
{
public:
    static int start()
    {
        // Initialize a new window
        Window window = Window();

        // Create a new line
        Line line = Line(
            LINE_START_VECTOR,
            LINE_LENGTH,
            LINE_ANGLE,
            LINE_WIDTH,
            LINE_COLOR);

        // Window Loop
        while (window.isOpen())
        {
            Events::check_close(&window);
            Utils::draw_background(&window);

            // Draw the line collider
            line.draw(&window);

            // Update the window
            window.display();
        }

        return 0;
    }
};

#endif