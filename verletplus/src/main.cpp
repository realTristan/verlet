#include <SFML/Graphics.hpp>
#include "objects/verlet/ball/ball.hpp"
#include "objects/verlet/ball/colliders/circle_open.hpp"
#include "objects/verlet/ball/colliders/line.hpp"
#include <thread>

int main()
{
    // Initialize a new window
    sf::RenderWindow window(sf::VideoMode(800, 600), "verlet");

    // Create a new list of colliders
    OpenCircleCollider circle_collider = OpenCircleCollider(Vector2D(400, 300), 300, 2, Colors().WHITE, false, true);
    LineCollider line_collider = LineCollider(Vector2D(200, 250), 150, 15, Colors().WHITE, 0.1);

    // Create a new list of balls
    std::vector<VerletBall*> balls = std::vector<VerletBall*> {};
    std::thread t([&](){
        for (int i = 0; i < 600; i++) {
            std::this_thread::sleep_for(std::chrono::milliseconds(10));
            balls.push_back(new VerletBall(Vector2D(200, 200), 4, Colors().CYAN));
        }
    });

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

        // Draw the circle collider
        circle_collider.draw(&window);
        for (auto &ball : balls) {
            circle_collider.apply(ball);
        }

        // Draw the line collider
        line_collider.draw(&window);
        for (auto &ball : balls) {
            line_collider.apply(ball);
        }

        // Update the window
        window.display();
    }

    return 0;
}
