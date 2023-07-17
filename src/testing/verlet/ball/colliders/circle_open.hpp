#ifndef TESTING_VERLET_BALL_COLLIDERS_CIRCLE_OPEN_HPP
#define TESTING_VERLET_BALL_COLLIDERS_CIRCLE_OPEN_HPP

#include <objects/verlet/ball/colliders/circle_open.hpp>
#include <objects/verlet/ball/ball.hpp>
#include <testing/events.hpp>
#include <testing/utils.hpp>
#include <SFML/Graphics.hpp>
#include <vector>

#define CIRCLE_COLLIDER_POSITION Vec2D<float>(400, 300)
#define CIRCLE_COLLIDER_RADIUS 300
#define CIRCLE_COLLIDER_THICKNESS 2
#define CIRCLE_COLLIDER_COLOR WHITE
#define CIRCLE_COLLIDER_INSIDE_COLLISIONS true
#define CIRCLE_COLLIDER_OUTSIDE_COLLISIONS false

#define VERLET_BALL_COUNT 300
#define VERLET_BALL_VECTOR Vec2D<float>(200, 200)
#define VERLET_BALL_RADIUS 4
#define VERLET_BALL_ADD_INTERVAL 100 // 100ms
#define VERLET_BALL_OFFSET Vec2D<float>(0, 0)
#define VERLET_BALL_RANDOM_COLOR true

typedef std::vector<VerletBall *> VerletBallVector;

// Open Circle Collider Testing
class OpenCircleColliderTesting
{
public:
    static void start()
    {
        // Initialize a new window
        sf::RenderWindow window(
            sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), WINDOW_TITLE);
        window.setFramerateLimit(60);

        // Create a new list of colliders
        OpenCircleCollider circle_collider = OpenCircleCollider(
            CIRCLE_COLLIDER_POSITION,
            CIRCLE_COLLIDER_RADIUS,
            CIRCLE_COLLIDER_THICKNESS,
            CIRCLE_COLLIDER_COLOR,
            CIRCLE_COLLIDER_INSIDE_COLLISIONS,
            CIRCLE_COLLIDER_OUTSIDE_COLLISIONS);

        // Create a new list of balls
        VerletBallVector balls = VerletBallVector();
        Utils::auto_add_verlet_balls(
            &balls,
            VERLET_BALL_VECTOR,
            VERLET_BALL_COUNT,
            VERLET_BALL_RADIUS,
            VERLET_BALL_ADD_INTERVAL,
            VERLET_BALL_OFFSET,
            VERLET_BALL_RANDOM_COLOR);

        // Window Loop
        while (window.isOpen())
        {
            Events::check_close(&window);
            Utils::draw_background(&window);

            // Draw the circle collider
            circle_collider.draw(&window);
            
            // Draw and update the balls
            for (int i = 0; i < SUBSTEPS; i++)
            {
                for (int j = 0; j < balls.size(); j++)
                {
                    balls[j]->draw(&window);
                    balls[j]->update(&window, &balls);
                    circle_collider.apply(balls[j]);
                }
            }

            // Update the window
            window.display();
        }
    }
};

#endif // TESTING_VERLET_BALL_COLLIDERS_CIRCLE_OPEN_HPP