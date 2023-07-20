#ifndef CREATIONS_FIELD_OF_CIRCLES_HPP
#define CREATIONS_FIELD_OF_CIRCLES_HPP

#include <objects/verlet/ball/colliders/circle.hpp>
#include <objects/verlet/ball/ball.hpp>
#include <physics/vector2d.h>
#include <objects/limiter.hpp>
#include <testing/events.hpp>
#include <testing/config.hpp>
#include <testing/utils.hpp>
#include <SFML/Graphics.hpp>
#include <vector>

#define CIRCLE_COLLIDER_POSITION Vec2D<float>(170.0f, 400.0f)
#define CIRCLE_COLLIDER_RADIUS 100.0f
#define CIRCLE_COLLIDER_COLOR WHITE

#define VERLET_BALL_COUNT 50
#define VERLET_BALL_POSITION Vec2D<float>(150.0f, 200.0f)
#define VERLET_BALL_RADIUS 5.0f
#define VERLET_BALL_ADD_INTERVAL 100 // 100ms
#define VERLET_BALL_OFFSET Vec2D<float>(2.0f, 0.0f)
#define VERLET_BALL_RANDOM_COLOR true

typedef std::vector<VerletBall *> VerletBallVector;

class FieldOfCirclesCreation
{
public:
    static void start()
    {
        // Initialize a new window
        sf::RenderWindow *window = new sf::RenderWindow(
            sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), WINDOW_TITLE);
        window->setFramerateLimit(FPS);

        // Create a new list of colliders
        std::vector<CircleCollider *> circle_colliders = std::vector<CircleCollider *>();
        for (int i = 0; i < 4; i++)
        {
            Vec2D pos = CIRCLE_COLLIDER_POSITION;
            pos.x = pos.x + 150 * i;
            CircleCollider *circle_collider = new CircleCollider(
                pos,
                CIRCLE_COLLIDER_RADIUS);

            circle_collider->set_outline_width(0.0f);
            circle_collider->set_fill_color(CIRCLE_COLLIDER_COLOR);
            circle_collider->enable_outside_collision();
            circle_collider->disable_inside_collision();
            circle_colliders.push_back(circle_collider);
        }

        // Create a new limiter
        ObjectLimiter *limiter = new ObjectLimiter(VERLET_BALL_COUNT);

        // Create a new list of balls
        VerletBallVector balls = VerletBallVector();
        Utils::auto_add_verlet_balls(
            &balls,
            VERLET_BALL_POSITION,
            VERLET_BALL_COUNT,
            VERLET_BALL_RADIUS,
            VERLET_BALL_ADD_INTERVAL,
            VERLET_BALL_OFFSET,
            VERLET_BALL_RANDOM_COLOR);

        // Window Loop
        while (window->isOpen())
        {
            Events::check_close(window);
            Utils::draw_background(window);

            // Add a ball on button click
            Utils::add_verlet_ball_on_click(
                window,
                &balls,
                VERLET_BALL_RADIUS,
                VERLET_BALL_RANDOM_COLOR);

            // Update the limiter
            limiter->update(&balls);

            // Draw the circle collider
            for (int i = 0; i < circle_colliders.size(); i++)
            {
                circle_colliders[i]->draw(window);
            }

            // Draw and update the balls
            for (int i = 0; i < SUBSTEPS; i++)
            {
                for (int j = 0; j < balls.size(); j++)
                {
                    balls[j]->draw(window);
                    balls[j]->update(window, &balls);
                    for (int k = 0; k < circle_colliders.size(); k++)
                    {
                        circle_colliders[k]->apply(balls[j]);
                    }
                }
            }

            // Update the window
            window->display();
        }
    }
};

#endif // CREATIONS_FIELD_OF_CIRCLES_HPP