import pygame
from testing.verlet.ball.config import SCREEN, BACKGROUND_COLOR, CLOCK, SUB_STEPS
from testing.verlet.ball.events import close_event, on_click
from verlet import VerletBall, VerletBallCircleCollider

# Initialize pygame
pygame.init()

# Window Title
pygame.display.set_caption("pyverlet")

# Objects
verlet_collider = VerletBallCircleCollider((400.0, 300.0))
verlet_balls = [VerletBall((500.0, 300.0), radius=10.0),
          VerletBall((300.0, 300.0), radius=10.0)]

# Game Loop
while 1:
    # Set the background
    SCREEN.fill(BACKGROUND_COLOR)

    # Steps
    for _ in range(SUB_STEPS):
        # On click, Add another ball
        verlet_balls = on_click(verlet_balls, ball_radius=10.0)
        while len(verlet_balls) > 10:
            verlet_balls.pop(0)
    
        # Update the ball
        [ball.update(SCREEN, [verlet_collider], verlet_balls) for ball in verlet_balls]
        # [verlet_collider.apply(ball) for ball in verlet_balls]
    
        # Draw the Collider
        verlet_collider.draw(SCREEN)
    
    # Check for a close event
    close_event()

    # Frames and update the display
    CLOCK.tick(60)
    pygame.display.flip()
