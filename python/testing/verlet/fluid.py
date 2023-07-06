from objects.verlet.ball.colliders import OpenCircleCollider, LineCollider
from testing.config import draw_background, CLOCK, SCREEN
from objects.verlet.ball import VerletBall
from testing.events import close_event
from utils import Colors
import pygame, time, threading


# Initialize pygame
pygame.init()

# Window Title
pygame.display.set_caption("verlet")

# Colliders and Verlet Balls
colliders: list[OpenCircleCollider | LineCollider] = [
    LineCollider((200.0, 100.0), 150.0, 35.0, 4),
    LineCollider((400.0, 400.0), 150.0, -90.0, 4),
    OpenCircleCollider((400.0, 300.0), 300, 5, outside_collision=False),
]
verlet_balls: list[VerletBall] = []


# Automatically add the balls
def auto_add_balls():
    while 1:
        time.sleep(0.05)
        ball: VerletBall = VerletBall(
            (300.0, 60.0), 5.0, Colors.CYAN
        )
        verlet_balls.append(ball)


# Start threading
t: threading.Thread = threading.Thread(target=auto_add_balls)
t.start()

# Game Loop
while 1:
    draw_background()
    close_event()

    # Cap the amount of balls present
    while len(verlet_balls) > 200:
        ball: VerletBall = verlet_balls.pop(0)

    # Update the verlet_balls
    [ball.update(SCREEN, verlet_balls) for ball in verlet_balls]
    [[collider.apply(ball) for collider in colliders] for ball in verlet_balls]
    [collider.draw(SCREEN) for collider in colliders]

    # Frames and update the display
    CLOCK.tick(60)
    pygame.display.flip()
