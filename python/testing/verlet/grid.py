from objects.verlet.ball.colliders import OpenCircleCollider, LineCollider
from testing.config import draw_background, CLOCK, SCREEN
from testing.events import on_click, close_event
from objects.verlet.ball import VerletBall
from utils import Colors
from grid import Grid
import pygame, time, threading, random


# Initialize pygame
pygame.init()

# Window Title
pygame.display.set_caption("verlet")

# Create a new grid
grid: Grid = Grid()

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
