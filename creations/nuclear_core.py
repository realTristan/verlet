import pygame
from testing.config import SCREEN, BACKGROUND_COLOR, CLOCK, SUB_STEPS
from testing.events import close_event, on_click
from objects.verlet.ball.colliders import OpenCircleCollider
from objects.verlet.ball.ball import VerletBall
from physics import Vector2D

# Create a new Collider class to override the apply function
class NuclearCoreCircleCollider(OpenCircleCollider):
    def __init__(self, position: tuple[float, float]):
        super(NuclearCoreCircleCollider, self).__init__(position)

    # Overriden apply function
    def apply(self, verlet_ball: VerletBall):
        # Calculate the distance between the ball and the Collider
        dist: Vector2D = self.position - verlet_ball.current_position

        # The vector magnitude of the ball
        magnitude: float = dist.magnitude()
        delta: float = self.radius - verlet_ball.radius
        if magnitude > delta:
            verlet_ball.current_position.set(
                self.position.x - self.width - dist.x / (magnitude * delta),
                self.position.y - self.width - dist.y / (magnitude * delta)
            )

# Initialize pygame
pygame.init()

# Window Title
pygame.display.set_caption("pyverlet")

# Objects
verlet_collider = NuclearCoreCircleCollider((400.0, 300.0))
verlet_balls = [VerletBall((500.0, 300.0), radius=10.0, color=(255, 255, 255)),
          VerletBall((400.0, 300.0), radius=10.0, color=(255, 255, 255)),
          VerletBall((300.0, 300.0), radius=10.0, color=(0, 255, 255))]

# Game Loop
while 1:
    # Set the background
    SCREEN.fill(BACKGROUND_COLOR)

    # On click
    for _ in range(SUB_STEPS):
        # Add another ball
        verlet_balls = on_click(verlet_balls, ball_radius=10.0) # type: ignore
        while len(verlet_balls) > 10:
            verlet_balls.pop(0)

        # Update the ball
        [ball.update(SCREEN, verlet_balls) for ball in verlet_balls]
        [verlet_collider.apply(ball) for ball in verlet_balls]

        # Draw the Collider
        verlet_collider.draw(SCREEN)

    # Check for a close event
    close_event()

    # Frames and update the display
    CLOCK.tick(60)
    pygame.display.flip()
