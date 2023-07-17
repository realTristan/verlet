#ifndef TESTING_VERLET_GRID_HPP
#define TESTING_VERLET_GRID_HPP

#include <objects/verlet/ball/colliders/circle_open.hpp>
#include <objects/verlet/ball/colliders/line.hpp>
#include <objects/verlet/ball/ball.hpp>
#include <testing/events.hpp>
#include <testing/config.hpp>
#include <testing/utils.hpp>
#include <SFML/Graphics.hpp>
#include <grid/grid.hpp>
#include <vector>

#define CIRCLE_COLLIDER_POSITION Vec2D(400, 300)
#define CIRCLE_COLLIDER_RADIUS 300
#define CIRCLE_COLLIDER_THICKNESS 2
#define CIRCLE_COLLIDER_COLOR WHITE
#define CIRCLE_COLLIDER_INSIDE_COLLISIONS true
#define CIRCLE_COLLIDER_OUTSIDE_COLLISIONS false

#define LINE_COLLIDER_VECTOR Vec2D(200, 250)
#define LINE_COLLIDER_LENGTH 150
#define LINE_COLLIDER_ANGLE 60
#define LINE_COLLIDER_WIDTH 2
#define LINE_COLLIDER_COLOR WHITE
#define LINE_COLLIDER_SLOPE_MULTIPLIER 0.1

#define VERLET_BALL_COUNT 600
#define VERLET_BALL_VECTOR Vec2D(200, 200)
#define VERLET_BALL_RADIUS 4
#define VERLET_BALL_ADD_INTERVAL 100 // 100ms
#define VERLET_BALL_OFFSET Vec2D(0, 0)
#define VERLET_BALL_RANDOM_COLOR true

typedef std::vector<VerletBall *> VerletBallVector;

class GridTesting
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

        LineCollider line_collider = LineCollider(
            LINE_COLLIDER_VECTOR,
            LINE_COLLIDER_LENGTH,
            LINE_COLLIDER_ANGLE,
            LINE_COLLIDER_WIDTH,
            LINE_COLLIDER_COLOR,
            LINE_COLLIDER_SLOPE_MULTIPLIER);

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

        // Initialize a new grid
        Grid<VerletBall> *grid = new Grid<VerletBall>(WINDOW_WIDTH, WINDOW_HEIGHT);

        // Window Loop
        while (window.isOpen())
        {
            Events::check_close(&window);
            Utils::draw_background(&window);

            // Check for collisions
            grid->find_collisions(-1);

            // Draw the colliders
            circle_collider.draw(&window);
            line_collider.draw(&window);

            // Draw and update the balls
            for (int i = 0; i < SUBSTEPS; i++)
            {
                for (int j = 0; j < balls.size(); j++)
                {
                    balls[j]->draw(&window);
                    balls[j]->update_no_collisions(&window);
                    circle_collider.apply(balls[j]);
                    line_collider.apply(balls[j]);
                }
            }

            // Update the window
            window.display();
        }
    }
};

#endif // TESTING_VERLET_GRID_HPP