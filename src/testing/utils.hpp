#ifndef TESTING_UTILS_HPP
#define TESTING_UTILS_HPP

#include <objects/verlet/ball/ball.hpp>
#include <physics/vector2d.h>
#include <testing/config.hpp>
#include <SFML/Graphics.hpp>
#include <utils/colors.hpp>
#include <thread>
#include <vector>

// Utils Class
class Utils
{
public:
    // Automatically add balls to the array
    static void auto_add_verlet_balls(
        std::vector<VerletBall *> *balls,
        Vec2D<float> ball_vector,
        int ball_count,
        int ball_radius,
        int interval = 100,
        Vec2D<float> offset = Vec2D<float>(0, 0),
        bool random_color = false,
        Color ball_color = CYAN)
    {
        std::thread t([balls, ball_vector, ball_count, ball_radius, interval, offset, random_color, ball_color]() {
            for (int i = 0; i < ball_count; i++) 
            {
                std::this_thread::sleep_for(std::chrono::milliseconds(interval));
                Color color = ball_color;
                if (random_color) 
                {
                    color = Colors::random_color();
                }
                VerletBall *ball = new VerletBall(
                    ball_vector + Vec2D<float>(i * offset.x, i * offset.y),
                    ball_radius);
                ball->set_fill_color(color);
                balls->push_back(ball);
            }
        });
        t.detach();
    }

    // Add a ball on click
    static void add_verlet_ball_on_click(
        sf::RenderWindow *window,
        std::vector<VerletBall *> *balls,
        int ball_radius,
        bool random_color = false,
        Color ball_color = CYAN)
    {
        // Check if mouse button clicked
        if (!sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            return;
        }

        // Add a ball
        sf::Vector2i mouse_position = sf::Mouse::getPosition(*window);
        Vec2D<float> ball_pos = Vec2D<float>(mouse_position.x, mouse_position.y);
        Color color = ball_color;
        if (random_color)
        {
            color = Colors::random_color();
        }
        VerletBall *ball = new VerletBall(
            ball_pos,
            ball_radius);
        ball->set_fill_color(color);
        balls->push_back(ball);
    }

    // Draw the background
    static void draw_background(sf::RenderWindow *window)
    {
        window->clear();
        for (int x = 0; x < WINDOW_WIDTH; x += 50)
        {
            for (int y = 0; y < WINDOW_HEIGHT; y += 50)
            {
                sf::RectangleShape *rectangle = new sf::RectangleShape(sf::Vector2f(50, 50));
                rectangle->setPosition(sf::Vector2f(x, y));
                rectangle->setFillColor(Colors::to_sf(BACKGROUND_COLOR));
                rectangle->setOutlineThickness(1);
                rectangle->setOutlineColor(sf::Color(50, 50, 50));
                window->draw(*rectangle);
            }
        }
    }
};

#endif // TESTING_UTILS_HPP