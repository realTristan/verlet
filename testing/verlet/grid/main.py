from objects import LineCollider, VerletBall, OpenCircleCollider
import pygame, time, threading, random
from testing.config import BALL_COLORS, draw_background, CLOCK
from grid import Grid
from physics import Vector2D
from testing.events import on_click, close_event

# Initialize pygame
pygame.init()

# Window Title
pygame.display.set_caption("pyverlet")

# Set the screen
screen: pygame.Surface = pygame.display.set_mode((800, 600))

# Create a new grid
grid: Grid = Grid()

# Colliders and Verlet Balls
colliders: list[OpenCircleCollider | LineCollider] = [
    LineCollider(Vector2D(200.0, 100.0), 150.0, 35.0, 2),
    OpenCircleCollider((400.0, 300.0), 300, 5, allow_outside_collision=False)
]
verlet_balls: list[VerletBall] = [
    VerletBall((270.0, 60.0), 10, random.choice(BALL_COLORS)) for _ in range(10)]
grid.fill(verlet_balls)

# Automatically add the balls
def auto_add_balls():
    while 1:
        time.sleep(0.1)
        ball: VerletBall = VerletBall(
            (270.0, 60.0), random.randint(5, 10), random.choice(BALL_COLORS))
        verlet_balls.append(ball)
        grid.put(ball)

# Start threading
# threading.Thread(target=auto_add_balls).start()

# Game Loop
while 1:
    draw_background()
    close_event()
    on_click(verlet_balls)

    # Cap the amount of balls present
    while len(verlet_balls) > 10:
        ball: VerletBall = verlet_balls.pop(0)
        
    # Update the verlet_balls
    [ball.update_grid(screen, grid, threads=-1) for ball in verlet_balls]
    [[collider.apply(ball) for collider in colliders] for ball in verlet_balls]
    [collider.draw(screen) for collider in colliders]
    
    # Frames and update the display
    CLOCK.tick(60)
    pygame.display.flip()

