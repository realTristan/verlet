#include <iostream>
#include <thread>
#include <SFML/Graphics.hpp>
#include <objects/verlet/ball/ball.hpp>
#include <vector>
#include <utils/colors.hpp>
#include <physics/vector2d.hpp>
#include <testing/config.hpp>

#ifndef TESTING_UTILS
#define TESTING_UTILS

class Utils
{
public:
    // Automatically add balls to the array
    static void auto_add_verlet_balls(
        std::vector<VerletBall *> *balls,
        Vec2D ball_vector,
        int ball_count,
        int ball_radius,
        Color ball_color = WHITE
    ) {
        std::thread t([&]() {
            for (int i = 0; i < ball_count; i++) {
                std::this_thread::sleep_for(std::chrono::milliseconds(10));
                VerletBall *ball = new VerletBall(
                    ball_vector,
                    ball_radius,
                    ball_color
                );
                balls->push_back(ball);
            }
        });
    }

    // Draw the background
    static void draw_background(sf::RenderWindow *window)
    {
        window->clear(Colors::to_sf(BACKGROUND_COLOR));
        for (int x = 0; x < WINDOW_WIDTH; x += 50)
        {
            for (int y = 0; y < WINDOW_HEIGHT; y += 50)
            {
                sf::RectangleShape rectangle(sf::Vector2f(50, 50));
                rectangle.setPosition(sf::Vector2f(x, y));
                rectangle.setFillColor(sf::Color(50, 50, 50));
                rectangle.setOutlineThickness(1);
                rectangle.setOutlineColor(sf::Color(50, 50, 50));
                window->draw(rectangle);
            }
        }
    }
};

#endif // TESTING_UTILS