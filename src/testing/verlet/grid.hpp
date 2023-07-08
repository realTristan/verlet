#include <iostream>
#include <SFML/Graphics.hpp>
#include <objects/verlet/ball/ball.hpp>
#include <objects/verlet/ball/colliders/circle_open.hpp>
#include <objects/verlet/ball/colliders/line.hpp>
#include <testing/events.hpp>
#include <testing/config.hpp>
#include <grid/grid.hpp>
#include <thread>

#define CIRCLE_COLLIDER_VECTOR Vec2D(400, 300)
#define CIRCLE_COLLIDER_RADIUS 300
#define CIRCLE_COLLIDER_THICKNESS 2
#define CIRCLE_COLLIDER_COLOR WHITE
#define CIRCLE_COLLIDER_INSIDE_COLLISIONS false
#define CIRCLE_COLLIDER_OUTSIDE_COLLISIONS true

#define LINE_COLLIDER_VECTOR Vec2D(200, 250)
#define LINE_COLLIDER_LENGTH 150
#define LINE_COLLIDER_ANGLE 60
#define LINE_COLLIDER_WIDTH 2
#define LINE_COLLIDER_COLOR WHITE
#define LINE_COLLIDER_SLOPE_MULTIPLIER 0.1

#define VERLET_BALL_COUNT 600
#define VERLET_BALL_VECTOR Vec2D(200, 200)
#define VERLET_BALL_RADIUS 4
#define VERLET_BALL_COLOR CYAN

#ifndef TESTING_VERLET_GRID_HPP
#define TESTING_VERLET_GRID_HPP

class GridTesting
{
public:
    static int start()
    {
        // Initialize a new window
        sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), WINDOW_TITLE);

        // Create a new list of colliders
        OpenCircleCollider circle_collider = OpenCircleCollider(
            CIRCLE_COLLIDER_VECTOR,
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
        std::vector<VerletBall *> balls = std::vector<VerletBall *>{};
        std::thread t([&]() {
            for (int i = 0; i < VERLET_BALL_COUNT; i++) {
                std::this_thread::sleep_for(std::chrono::milliseconds(10));
                VerletBall *ball = new VerletBall(
                    VERLET_BALL_VECTOR,
                    VERLET_BALL_RADIUS,
                    VERLET_BALL_COLOR
                );
                balls.push_back(ball);
            }
        });

        // Initialize a new grid
        Grid<VerletBall>* grid = new Grid<VerletBall>(WINDOW_WIDTH, WINDOW_HEIGHT);

        // Window Loop
        while (window.isOpen())
        {
            Events::check_close(&window);
            window.clear();

            // Check for collisions
            grid->find_collisions(-1);

            // Draw and update the balls
            for (auto &ball : balls)
            {
                ball->draw(&window);
                ball->update_no_collisions(&window);
            }

            // Draw the circle collider
            circle_collider.draw(&window);
            for (auto &ball : balls)
            {
                circle_collider.apply(ball);
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

#endif

/*
# Initialize pygame
pygame.init()

# Window Title
pygame.display.set_caption("verlet")

# Create a new grid
grid: Grid = Grid(WIDTH, HEIGHT)

# Colliders and Verlet Balls
colliders: list[OpenCircleCollider | LineCollider] = [
    LineCollider((200.0, 100.0), 150.0, 35.0, 2),
    OpenCircleCollider((400.0, 300.0), 300, 5, outside_collision=False),
]
verlet_balls: list[VerletBall] = [
    VerletBall((270.0, 60.0), 10, Colors.random()) for _ in range(10)
]
grid.fill(verlet_balls)


# Automatically add the balls
def auto_add_balls():
    while 1:
        time.sleep(0.1)
        ball: VerletBall = VerletBall(
            (270.0, 60.0), random.randint(5, 10), Colors.random()
        )
        verlet_balls.append(ball)
        grid.put(ball)


# Start threading
threading.Thread(target=auto_add_balls).start()

# Game Loop
while 1:
    draw_background()
    close_event()
    on_click(verlet_balls)
    
    # Cap the amount of balls present
    while len(verlet_balls) > 300:
        ball: VerletBall = verlet_balls.pop(0)
        grid.deprecate(ball)

    # Update the verlet_balls
    grid.find_collisions(-1)
    [ball.update_no_collisions(SCREEN) for ball in verlet_balls]
    [[collider.apply(ball) for collider in colliders] for ball in verlet_balls]
    [collider.draw(SCREEN) for collider in colliders]

    # Frames and update the display
    CLOCK.tick(60)
    pygame.display.flip()

*/