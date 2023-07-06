from testing.config import SCREEN, draw_background, CLOCK, SUB_STEPS
from objects.verlet.ball.colliders import ClosedCircleCollider
from testing.events import close_event, on_click
from objects.verlet.ball import VerletBall
from utils import Colors
import pygame


# Initialize pygame
pygame.init()

# Window Title
pygame.display.set_caption("verlet")

# Objects
verlet_collider = ClosedCircleCollider((400.0, 300.0))
verlet_balls = [
    VerletBall((500.0, 50.0), radius=10.0, color=Colors.random()),
    VerletBall((400.0, 50.0), radius=10.0, color=Colors.random()),
]

# Game Loop
while 1:
    # Draw the background
    draw_background()

    # Cap the amount of balls present
    while len(verlet_balls) > 200:
        verlet_balls.pop(0)

    # Steps
    for _ in range(SUB_STEPS):
        # On click, Add another ball
        verlet_balls = on_click(verlet_balls)
        while len(verlet_balls) > 10:
            verlet_balls.pop(0)

        # Update the ball
        [ball.update(SCREEN, verlet_balls) for ball in verlet_balls]
        [verlet_collider.apply(ball) for ball in verlet_balls]

        # Draw the Collider
        verlet_collider.draw(SCREEN)

    # Check for a close event
    close_event()

    # Frames and update the display
    CLOCK.tick(60)
    pygame.display.flip()
