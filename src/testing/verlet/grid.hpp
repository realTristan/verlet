#ifndef TESTING_VERLET_GRID_HPP
#define TESTING_VERLET_GRID_HPP

#include <objects/verlet/ball/colliders/circle.hpp>
#include <objects/verlet/ball/colliders/line.hpp>
#include <objects/verlet/ball/ball.hpp>
#include <objects/verlet/grid.hpp>
#include <testing/events.hpp>
#include <testing/config.hpp>
#include <testing/utils.hpp>
#include <SFML/Graphics.hpp>
#include <vector>

#define CIRCLE_COLLIDER_POSITION Vec2D<float>(400, 300)
#define CIRCLE_COLLIDER_RADIUS 300
#define CIRCLE_COLLIDER_THICKNESS 2
#define CIRCLE_COLLIDER_COLOR WHITE

#define LINE_COLLIDER_POSITION Vec2D<float>(200, 250)
#define LINE_COLLIDER_LENGTH 150
#define LINE_COLLIDER_ANGLE 60
#define LINE_COLLIDER_WIDTH 2
#define LINE_COLLIDER_COLOR WHITE

#define VERLET_BALL_COUNT 100
#define VERLET_BALL_POSITION Vec2D<float>(200, 200)
#define VERLET_BALL_RADIUS 4
#define VERLET_BALL_ADD_INTERVAL 100 // 100ms
#define VERLET_BALL_OFFSET Vec2D<float>(0, 0)
#define VERLET_BALL_RANDOM_COLOR true

typedef std::vector<VerletBall *> VerletBallVector;

class GridTesting
{
public:
    static void start()
    {
        // Initialize a new window
        sf::RenderWindow *window = new sf::RenderWindow(
            sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), WINDOW_TITLE);
        window->setFramerateLimit(FPS);

        // Create a new list of colliders
        CircleCollider *circle_collider = new CircleCollider(
            CIRCLE_COLLIDER_POSITION,
            CIRCLE_COLLIDER_RADIUS,
            CIRCLE_COLLIDER_THICKNESS);

        circle_collider->set_outline_color(CIRCLE_COLLIDER_COLOR);
        circle_collider->disable_outside_collision();

        LineCollider *line_collider = new LineCollider(
            LINE_COLLIDER_POSITION,
            LINE_COLLIDER_LENGTH,
            LINE_COLLIDER_ANGLE,
            LINE_COLLIDER_WIDTH,
            LINE_COLLIDER_COLOR);

        // Create a new list of balls
        VerletBallVector balls = VerletBallVector{
            new VerletBall(
                VERLET_BALL_POSITION,
                VERLET_BALL_RADIUS),
            new VerletBall(
                VERLET_BALL_POSITION,
                VERLET_BALL_RADIUS),
        };

        // Initialize a new grid
        Grid<VerletBall> *grid = new Grid<VerletBall>(WINDOW_WIDTH, WINDOW_HEIGHT);
        grid->fill(balls);

        // Create a new limiter
        ObjectLimiter *limiter = new ObjectLimiter(VERLET_BALL_COUNT);

        // Window Loop
        while (window->isOpen())
        {
            Events::check_close(window);
            Utils::draw_background(window);

            // Add balls on click
            // Check if mouse button clicked
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
            {
                sf::Vector2i mouse_position = sf::Mouse::getPosition(*window);
                Vec2D<float> ball_pos = Vec2D<float>(mouse_position.x, mouse_position.y);
                VerletBall *ball = new VerletBall(
                    ball_pos,
                    VERLET_BALL_RADIUS);
                ball->set_fill_color(Colors::random_color());
                balls.push_back(ball);
                grid->put(ball);
            }

            // Update the limiter
            limiter->update(&balls, grid);

            // Draw the colliders
            circle_collider->draw(window);
            line_collider->draw(window);

            // Draw and update the balls
            for (int i = 0; i < SUBSTEPS; i++)
            {
                for (int j = 0; j < balls.size(); j++)
                {
                    // Draw and update the ball
                    balls[j]->draw(window);
                    balls[j]->update_with_grid(window, grid);

                    // Apply collisions
                    circle_collider->apply(balls[j]);
                    line_collider->apply(balls[j]);
                }
            }

            // Update the window
            window->display();
        }
    }
};

#endif // TESTING_VERLET_GRID_HPP