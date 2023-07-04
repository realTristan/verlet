from objects import VerletBallLineCollider, VerletBall, VerletBallCircleCollider
import pygame, time, threading, random
from testing.config import BALL_COLORS, draw_background, CLOCK
from grid import Grid
from physics import Vector2D

# Initialize pygame
pygame.init()

# Window Title
pygame.display.set_caption("pyverlet")

# Set the screen
screen: pygame.Surface = pygame.display.set_mode((800, 600))

# Colliders and Verlet Balls
colliders: list[VerletBallCircleCollider | VerletBallLineCollider] = [
    VerletBallLineCollider(Vector2D(200.0, 100.0), 150.0, 35.0, 2),
    VerletBallCircleCollider((400.0, 300.0), 300, 5)
]
verlet_balls: list[VerletBall] = []

# Create a new grid
grid: Grid = Grid()

# Automatically add the balls
def auto_add_balls():
    while 1:
        time.sleep(0.1)
        ball: VerletBall = VerletBall(
            (270.0, 60.0), random.randint(5, 10), random.choice(BALL_COLORS))
        verlet_balls.append(ball)
        grid.put(ball, ball.current_position)

# Start threading
threading.Thread(target=auto_add_balls).start()

# Game Loop
while 1:
    # Draw the background
    draw_background()

    # Cap the amount of balls present
    while len(verlet_balls) > 200:
        verlet_balls.pop(0)
    
    # Check for a close event
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            pygame.quit()
            exit()
        
    # Update the verlet_balls
    [ball.update_grid(screen, grid, verlet_balls) for ball in verlet_balls]
    [[collider.apply(ball) for collider in colliders] for ball in verlet_balls]
    
    # Draw the Collider
    for collider in colliders:
        collider.draw(screen)
    
    # Frames and update the display
    # CLOCK.tick(60)
    pygame.display.flip()

