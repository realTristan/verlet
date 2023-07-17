#ifndef TESTING_UTILS_HPP
#define TESTING_UTILS_HPP

#include <objects/verlet/ball/ball.hpp>
#include <physics/vector2d.hpp>
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
        Vec2D ball_vector,
        int ball_count,
        int ball_radius,
        int interval = 100,
        Vec2D offset = Vec2D(0, 0),
        Color ball_color = WHITE)
    {
        std::thread t([balls, ball_vector, ball_count, ball_radius, interval, offset, ball_color]()
                      {
            for (int i = 0; i < ball_count; i++) {
                std::this_thread::sleep_for(std::chrono::milliseconds(interval));
                VerletBall *ball = new VerletBall(
                    ball_vector + Vec2D(i * offset.x, i * offset.y),
                    ball_radius,
                    ball_color
                );
                balls->push_back(ball);
            } });
        t.detach();
    }

    // Draw the background
    static void draw_background(sf::RenderWindow *window)
    {
        window->clear();
        for (int x = 0; x < WINDOW_WIDTH; x += 50)
        {
            for (int y = 0; y < WINDOW_HEIGHT; y += 50)
            {
                sf::RectangleShape rectangle(sf::Vector2f(50, 50));
                rectangle.setPosition(sf::Vector2f(x, y));
                rectangle.setFillColor(Colors::to_sf(BACKGROUND_COLOR));
                rectangle.setOutlineThickness(1);
                rectangle.setOutlineColor(sf::Color(50, 50, 50));
                window->draw(rectangle);
            }
        }
    }
};

#endif // TESTING_UTILS_HPP