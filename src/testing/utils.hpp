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
};

#endif // TESTING_UTILS