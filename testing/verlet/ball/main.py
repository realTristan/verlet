import pygame
from verlet import VerletBall
from testing.verlet.ball.config import SCREEN, BACKGROUND_COLOR, CLOCK, SUB_STEPS
from testing.verlet.ball.events import close_event, on_click
# Initialize pygame
pygame.init()

# Window Title
pygame.display.set_caption("pyverlet")

# Verlet Balls
verlet_balls: list[VerletBall] = [
    VerletBall((500.0, 300.0)), VerletBall((300.0, 300.0))]

# Game Loop
while 1:
    # Set the background
    SCREEN.fill(BACKGROUND_COLOR)
    
    # On click, Add another ball
    verlet_balls = on_click(verlet_balls)
    while len(verlet_balls) > 10:
        verlet_balls.pop(0)

    # Run
    for _ in range(SUB_STEPS):
        [ball.update(SCREEN) for ball in verlet_balls]
    
    # Check for a close event
    close_event()

    # Frames and update the display
    CLOCK.tick(60)
    pygame.display.flip()
