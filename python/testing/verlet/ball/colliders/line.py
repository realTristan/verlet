from testing.config import SCREEN, draw_background, CLOCK, SUB_STEPS
from objects.verlet.ball.colliders import LineCollider
from testing.events import close_event, on_click
from objects.verlet.ball import VerletBall
from utils import Colors
import pygame, time, threading, random


# Initialize pygame
pygame.init()

# Window Title
pygame.display.set_caption("verlet")

# Objects
lines: list[LineCollider] = [
    LineCollider((200.0, 50.0), 120.0, 40.0, 2),
    LineCollider((400.0, 300.0), 120.0, -60.0, 2),
    LineCollider((200.0, 400.0), 150.0, 30.0, 2),
]
verlet_balls = [
    VerletBall((200.0, 100.0), radius=10.0),
    VerletBall((300.0, 100.0), radius=10.0),
]


# Automatically add the balls
def auto_add_balls():
    while 1:
        time.sleep(0.5)
        verlet_balls.append(
            VerletBall((250.0, 50.0), random.randint(5, 10), Colors.random())
        )


# Start threading
threading.Thread(target=auto_add_balls).start()

# Game Loop
while 1:
    draw_background()
    close_event()

    # Cap the amount of balls present
    while len(verlet_balls) > 200:
        verlet_balls.pop(0)

    # On click
    for _ in range(SUB_STEPS):
        # Add another ball
        verlet_balls = on_click(verlet_balls)
        while len(verlet_balls) > 10:
            verlet_balls.pop(0)

        # Update the ball
        [ball.update(SCREEN, verlet_balls) for ball in verlet_balls]
        [[line.apply(ball) for line in lines] for ball in verlet_balls]
        [line.draw(SCREEN) for line in lines]

    # Frames and update the display
    CLOCK.tick(60)
    pygame.display.flip()
