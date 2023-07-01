import pygame, time
from circle import Circle
from constraint import Constraint

pygame.init()

# Create the screen
SCREEN: pygame.Surface = pygame.display.set_mode((800, 600))
BACKGROUND_COLOR: tuple[int, int, int] = (0, 0, 0)

# Constants
GRAVITY: list[float] = [0.0, 9.81]

# Title and Icon
pygame.display.set_caption("Physics Engine")

# Draw an object
circle: Circle = Circle([500.0, 300.0])
constraint: Constraint = Constraint([400.0, 300.0])

# Start time in nanoseconds
start_time: float = time.time()
    
# Loop
clock: pygame.time.Clock = pygame.time.Clock()
while 1:
    # set the background
    SCREEN.fill(BACKGROUND_COLOR)
    
    # Update the circle
    circle.accelerate(GRAVITY)
    circle.update_position(time.time() - start_time)
    circle.apply_constraint(constraint)
    
    # Draw the objects
    circle.draw(SCREEN)
    constraint.draw(SCREEN)
    
    # Check for events
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            pygame.quit()
            quit()
    
    # Frames and update the display
    clock.tick(60)
    pygame.display.flip()