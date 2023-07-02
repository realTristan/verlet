import pygame, time
from verlet import VerletBall, VerletBallCircleConstraint
from testing.verlet.ball.config import SCREEN, BACKGROUND_COLOR, GRAVITY, CLOCK, SUB_STEPS
from testing.verlet.ball.events import close_event, on_click

# Initialize pygame
pygame.init()

# Window Title
pygame.display.set_caption("pyverlet")

# Objects
vballs = [VerletBall((500.0, 300.0)), VerletBall((300.0, 300.0))]

# Game Loop
while 1:
    # Set the background
    SCREEN.fill(BACKGROUND_COLOR)

    # On click
    for _ in range(SUB_STEPS):
        # Add another ball
        vballs = on_click(vballs)
        while len(vballs) > 10:
            vballs.pop(0)

        # Update the ball
        for vball in vballs:
            # Calculate the delta time
            dt: float = (time.time() - vball.start_time) / SUB_STEPS

            # Apply updates to the ball
            vball.accelerate(GRAVITY)
            vball.update_position(dt)
            VerletBall.check_collisions(vballs)

            # Draw the objects
            vball.draw(SCREEN)

    # Check for a close event
    close_event()

    # Frames and update the display
    CLOCK.tick(60)
    pygame.display.flip()
