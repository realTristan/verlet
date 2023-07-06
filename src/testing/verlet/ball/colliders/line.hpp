#include <SFML/Graphics.hpp>
#include <objects/verlet/ball/ball.hpp>
#include <objects/verlet/ball/colliders/circle_open.hpp>
#include <objects/verlet/ball/colliders/line.hpp>
#include <testing/events.hpp>
#include <thread>

class LineColliderTesting
{
public:
    static int start()
    {
        // Initialize a new window
        sf::RenderWindow window(sf::VideoMode(800, 600), "verlet");

        // Create a new list of colliders
        LineCollider line_collider = LineCollider(Vector2D(200, 250), 150, 15, Colors().WHITE, 0.1);

        // Create a new list of balls
        std::vector<VerletBall *> balls = std::vector<VerletBall *>{};
        std::thread t([&]() {
        for (int i = 0; i < 600; i++) {
            std::this_thread::sleep_for(std::chrono::milliseconds(10));
            balls.push_back(new VerletBall(Vector2D(200, 200), 4, Colors().CYAN));
        } });

        // Window Loop
        while (window.isOpen())
        {
            Events::check_close(&window);
            window.clear();

            // Draw and update the balls
            for (auto &ball : balls)
            {
                ball->draw(&window);
                ball->update(&window, balls);
            }

            // Draw the line collider
            line_collider.draw(&window);
            for (auto &ball : balls)
            {
                line_collider.apply(ball);
            }

            // Update the window
            window.display();
        }

        return 0;
    }
};