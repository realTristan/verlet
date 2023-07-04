from testing.config import SCREEN, draw_background, CLOCK, SUB_STEPS
from testing.events import close_event, on_click
from objects.verlet.ball import VerletBall
import pygame


# Initialize pygame
pygame.init()

# Window Title
pygame.display.set_caption("pyverlet")

# Verlet Balls
verlet_balls: list[VerletBall] = [
    VerletBall((500.0, 300.0)), VerletBall((300.0, 300.0))]

# Game Loop
while 1:
    draw_background()
    close_event()

    # Cap the amount of balls present
    while len(verlet_balls) > 10:
        verlet_balls.pop(0)
    
    # On click, Add another ball
    verlet_balls = on_click(verlet_balls)
    while len(verlet_balls) > 10:
        verlet_balls.pop(0)

    # Run
    for _ in range(SUB_STEPS):
        [ball.update(SCREEN) for ball in verlet_balls]

    # Frames and update the display
    CLOCK.tick(60)
    pygame.display.flip()
