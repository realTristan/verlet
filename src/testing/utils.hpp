#include <iostream>
#include <thread>
#include <SFML/Graphics.hpp>
#include <objects/verlet/ball/ball.hpp>
#include <vector>
#include <utils/colors.hpp>
#include <physics/vector2d.hpp>

#ifndef TESTING_UTILS
#define TESTING_UTILS

class Utils
{
public:
    static void auto_add_verlet_balls(
        sf::RenderWindow *window, 
        std::vector<VerletBall *> *balls,
        int VERLET_BALL_COUNT,
        Vec2D VERLET_BALL_VECTOR,
        float VERLET_BALL_RADIUS,
        Color VERLET_BALL_COLOR,
    ) {
        std::thread t([&]() {
            for (int i = 0; i < VERLET_BALL_COUNT; i++) {
                std::this_thread::sleep_for(std::chrono::milliseconds(10));
                VerletBall *ball = new VerletBall(
                    VERLET_BALL_VECTOR,
                    VERLET_BALL_RADIUS,
                    VERLET_BALL_COLOR
                );
                balls->push_back(ball);
            }
        });
    }
}

#endif // TESTING_UTILS