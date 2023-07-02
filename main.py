import pygame, time
from verlet import VerletBall, VerletCircleConstraint
from config import SCREEN, BACKGROUND_COLOR, GRAVITY, CLOCK, SUB_STEPS
from events import close_event, on_click

# Initialize pygame
pygame.init()

# Window Title
pygame.display.set_caption("pyverlet")

# Objects
verlet_constraint: VerletCircleConstraint = VerletCircleConstraint([400.0, 300.0])
verlet_balls: list[VerletBall] = [VerletBall([500.0, 300.0]),
                                  VerletBall([300.0, 300.0])]

# Game Loop
while 1:
    # Set the background
    SCREEN.fill(BACKGROUND_COLOR)

    # On click
    for _ in range(SUB_STEPS):
        # Add another ball
        verlet_balls = on_click(verlet_balls)
        while len(verlet_balls) > 10:
            verlet_balls.pop(0)

        # Update the ball
        for verlet_ball in verlet_balls:
            # Calculate the delta time
            dt: float = (time.time() - verlet_ball.start_time) / SUB_STEPS

            # Apply updates to the ball
            verlet_ball.accelerate(GRAVITY)
            verlet_ball.update_position(dt)
            verlet_constraint.apply(verlet_ball)
            VerletBall.check_collision(verlet_balls)

            # Draw the objects
            verlet_ball.draw(SCREEN)
        
        # Draw the constraint
        verlet_constraint.draw(SCREEN)

    # Check for a close event
    close_event()

    # Frames and update the display
    CLOCK.tick(60)
    pygame.display.flip()
