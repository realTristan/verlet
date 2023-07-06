#include <SFML/Graphics.hpp>
#include "objects/verlet/ball/ball.hpp"
#include "objects/verlet/ball/colliders/circle_closed.hpp"

int main()
{
    // Initialize a new window
    sf::RenderWindow window(sf::VideoMode(800, 600), "verlet");

    // Create a new list of colliders
    std::vector<ClosedCircle> colliders = std::vector<ClosedCircle> {
        ClosedCircle(Vector2D(200, 300), 100, 10, Colors().WHITE, true, true)
    };

    // Create a new list of balls
    std::vector<VerletBall*> balls = std::vector<VerletBall*> {
        new VerletBall(Vector2D(275, 50), 10, Colors().WHITE)
    };

    // Window Loop
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        window.clear();

        // Draw and update the balls
        for (auto &ball : balls) {
            ball->draw(&window);
            ball->update(&window, balls);
        }

        // Draw the colliders
        for (auto &collider : colliders) {
            collider.draw(&window);
            for (auto &ball : balls) {
                collider.apply(ball);
            }
        }

        // Update the window
        window.display();
    }

    return 0;
}
