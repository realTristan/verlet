import pygame, time
from ball import Ball
from constraint import Constraint
from config import SCREEN, BACKGROUND_COLOR, GRAVITY, CLOCK, SUB_STEPS
from events import close_event, on_click

# Initialize pygame
pygame.init()

# Title and Icon
pygame.display.set_caption("pyverlet")

# Draw objects
constraint: Constraint = Constraint([400.0, 300.0])
balls: list[Ball] = [Ball([500.0, 300.0]), 
                         Ball([300.0, 300.0])]


# Loop
while 1:
    # Set the background
    SCREEN.fill(BACKGROUND_COLOR)
    
    # On click
    for _ in range(SUB_STEPS):
        balls = on_click(balls)
        while len(balls) > 10:
            balls.pop(0)
        
        # Update the ball
        for ball in balls:
            dt: float = (time.time() - ball.start_time) / SUB_STEPS
            
            # Apply updates to the ball
            ball.accelerate(GRAVITY)
            ball.update_position(dt)
            ball.apply_constraint(constraint)
            Ball.check_collision(balls)
            
            # Draw the objects
            ball.draw(SCREEN)
        
        # Draw the constraint
        constraint.draw(SCREEN)
    
    # Check for a close event
    close_event()
    
    # Frames and update the display
    CLOCK.tick(60)
    pygame.display.flip()
