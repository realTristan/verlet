#include <iostream>
#include <SFML/Graphics.hpp>
#include <objects/verlet/ball/ball.hpp>
#include <objects/verlet/ball/colliders/circle_open.hpp>
#include <objects/verlet/ball/colliders/line.hpp>
#include <testing/events.hpp>
#include <testing/config.hpp>
#include <grid/grid.hpp>
#include <thread>
#include <testing/utils.hpp>
#include <interface/menu.hpp>

#ifndef TESTING_VERLET_MENU_HPP
#define TESTING_VERLET_MENU_HPP

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

class MenuTesting
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
        Utils::auto_add_verlet_balls(
            &window,
            &balls,
            VERLET_BALL_COUNT,
            VERLET_BALL_VECTOR,
            VERLET_BALL_RADIUS,
            VERLET_BALL_COLOR,
        );

        // Menu variables
        Menu menu = Menu();
        bool show_circle_collider = false;
        bool show_line_collider = false;
        
        // Window Loop
        while (window.isOpen())
        {
            Events::check_close(&window);
            window.clear();

            // Draw the menu
            menu.draw(&window);

            // Check if the menu buttons have been clicked
            if (menu.circle_collider_button.is_clicked(&window)) {
                show_circle_collider = !show_circle_collider;
            }
            if (menu.line_collider_button.is_clicked(&window)) {
                show_line_collider = !show_line_collider;
            }

            // Draw and update the balls
            for (auto &ball : balls)
            {
                ball->draw(&window);
                ball->update(&window);
            }

            // Draw the circle collider
            if (show_circle_collider) {
                circle_collider.draw(&window);
                for (auto &ball : balls)
                {
                    circle_collider.apply(ball);
                }
            }

            // Draw the line collider
            if (show_line_collider) {
                line_collider.draw(&window);
                for (auto &ball : balls)
                {
                    line_collider.apply(ball);
                }
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

#endif

/*


# Initialize pygame
pygame.init()

# Window Title
pygame.display.set_caption("verlet")

# Colliders and Verlet Balls
colliders: list[OpenCircleCollider | LineCollider] = []
verlet_balls: list[VerletBall] = []

# Create a list of colliders
items: ButtonList = ButtonList()

# Create a menu
menu: Menu = Menu(SCREEN)

# Automatically add the balls
def auto_add_balls():
    while 1:
        time.sleep(0.1)
        ball: VerletBall = VerletBall(
            (270.0, 60.0), random.randint(5, 10), Colors.random()
        )
        verlet_balls.append(ball)


# Start threading
threading.Thread(target=auto_add_balls).start()

# Game Loop
while 1:
    # Draw the background
    draw_background()

    # Draw the menu and items
    menu.draw_buttons(SCREEN)
    items.draw(SCREEN, colliders)

    # Cap the amount of balls present
    while len(verlet_balls) > 200:
        verlet_balls.pop(0)

    # Check for a close event
    for event in pygame.event.get():
        # Check if the event is a close event
        if event.type == pygame.QUIT:
            pygame.quit()
            exit()

        # Check if the event is a click event
        for item in items.clicked(event):
            colliders.remove(item.item)
            items.remove(item)

        # Check if the event is a click event
        if menu.line_collider_button.clicked(event):
            colliders.append(LineCollider((200.0, 100.0), 150.0, 35.0, 2))

        # Check if the event is a click event
        elif menu.circle_collider_button.clicked(event):
            colliders.append(
                OpenCircleCollider(
                    position=(400.0, 300.0),
                    radius=300,
                    width=5,
                    outside_collision=False,
                )
            )

    # Update the verlet_balls
    [ball.update(SCREEN, verlet_balls) for ball in verlet_balls]
    [[collider.apply(ball) for collider in colliders] for ball in verlet_balls]
    [collider.draw(SCREEN) for collider in colliders]

    # Frames and update the display
    # CLOCK.tick(60)
    pygame.display.flip()
*/