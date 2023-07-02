import pygame, time
from verlet import VerletBall, VerletConstraint
from config import SCREEN, BACKGROUND_COLOR, GRAVITY, CLOCK, SUB_STEPS
from events import close_event, on_click

# Initialize pygame
pygame.init()

# Title and Icon
pygame.display.set_caption("pyverlet")

# Draw objects
verlet_constraint: VerletConstraint = VerletConstraint([400.0, 300.0], type="sphere")
verlet_balls: list[VerletBall] = [VerletBall([500.0, 300.0]), 
                         VerletBall([300.0, 300.0])]

# Loop
while 1:
    # Set the background
    SCREEN.fill(BACKGROUND_COLOR)
    
    # Draw the constraint
    verlet_constraint.draw(SCREEN)
    
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
            verlet_ball.apply_constraint(verlet_constraint)
            VerletBall.check_collision(verlet_balls)
            
            # Draw the objects
            verlet_ball.draw(SCREEN)
    
    # Check for a close event
    close_event()
    
    # Frames and update the display
    CLOCK.tick(60)
    pygame.display.flip()
