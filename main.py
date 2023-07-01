import pygame, time
from ball import Ball
from constraint import Constraint
from config import SCREEN, BACKGROUND_COLOR, GRAVITY, CLOCK
from events import close_event, on_click

# Initialize pygame
pygame.init()

# Title and Icon
pygame.display.set_caption("pyverlet")

# Draw objects
constraint: Constraint = Constraint([400.0, 300.0])
circles: list[Ball] = [Ball([500.0, 300.0]), 
                         Ball([300.0, 300.0])]

# Loop
while 1:
    # Set the background
    SCREEN.fill(BACKGROUND_COLOR)
    
    # On click
    circles = on_click(circles)
    
    # Update the circle
    for circle in circles:
        circle.accelerate(GRAVITY)
        circle.update_position(time.time() - circle.start_time)
        circle.apply_constraint(constraint)
        circle.check_collision(circles)
        
        # Draw the objects
        circle.draw(SCREEN)
    
    # Draw the constraint
    constraint.draw(SCREEN)
    
    # Check for a close event
    close_event()
    
    # Frames and update the display
    CLOCK.tick(60)
    pygame.display.flip()
