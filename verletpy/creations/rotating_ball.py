from objects.verlet.ball.colliders import LineCollider, OpenCircleCollider
from testing.config import draw_background, CLOCK, SCREEN
from objects.verlet.ball import VerletBall
from testing.events import close_event
from interface.components import Text
from utils import Colors
import pygame


# Initialize pygame
pygame.init()

# Window Title
pygame.display.set_caption("pyverlet")

# Colliders and Verlet Balls
colliders: list[OpenCircleCollider | LineCollider] = [
    LineCollider((200.0, 100.0), 0.001, 35.0, 2),
    OpenCircleCollider(
        position=(400.0, 300.0),
        radius=300,
        width=5,
        outside_collision=False,
    ),
]
verlet_balls: list[VerletBall] = [VerletBall((200.0, 100.0), 15, Colors.CYAN)]

# Text
text = Text("Spinning Ball", (250, 265), 50, Colors.WHITE)

# Game Loop
while 1:
    draw_background()
    close_event()

    # Draw text that says "Spinning Ball" in the middle of the circle
    text.draw(SCREEN)


    # Update the verlet_balls
    [ball.update(SCREEN, verlet_balls) for ball in verlet_balls]
    [[collider.apply(ball) for collider in colliders] for ball in verlet_balls]
    [collider.draw(SCREEN) for collider in colliders]

    # Frames and update the display
    CLOCK.tick(60)
    pygame.display.flip()
