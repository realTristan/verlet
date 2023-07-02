import pygame, time
from testing.verlet.ball.config import SCREEN, BACKGROUND_COLOR, CLOCK, SUB_STEPS
from testing.verlet.ball.events import close_event, on_click
from verlet import VerletBallCircleCollider, VerletBall
from physics import Vector2D, GRAVITY

# Create a new Collider class to override the apply function
class NuclearCoreCircleCollider(VerletBallCircleCollider):
    def __init__(self, position: tuple[float, float]):
        super(NuclearCoreCircleCollider, self).__init__(position)

    # Overriden apply function
    def apply(self, vball: VerletBall):
        # Calculate the distance between the ball and the Collider
        dist: Vector2D = self.position - vball.current_position

        # The vector magnitude of the ball
        magnitude: float = dist.magnitude()
        delta: float = self.radius - vball.radius
        if magnitude > delta:
            vball.current_position.set(
                self.position.x - self.width - dist.x / (magnitude * delta),
                self.position.y - self.width - dist.y / (magnitude * delta)
            )

# Initialize pygame
pygame.init()

# Window Title
pygame.display.set_caption("pyverlet")

# Objects
vconst = NuclearCoreCircleCollider((400.0, 300.0))
vballs = [VerletBall((500.0, 300.0), radius=10.0, color=(255, 255, 255)),
          VerletBall((400.0, 300.0), radius=10.0, color=(255, 255, 255)),
          VerletBall((300.0, 300.0), radius=10.0, color=(0, 255, 255))]

# Game Loop
while 1:
    # Set the background
    SCREEN.fill(BACKGROUND_COLOR)

    # On click
    for _ in range(SUB_STEPS):
        # Add another ball
        vballs = on_click(vballs, ball_radius=10.0) # type: ignore
        while len(vballs) > 10:
            vballs.pop(0)

        # Update the ball
        for vball in vballs:
            # Calculate the delta time
            dt: float = (time.time() - vball.start_time) / SUB_STEPS

            # Apply updates to the ball
            vball.accelerate(GRAVITY)
            vball.update_position(dt)
            vconst.apply(vball)
            VerletBall.check_collisions(vballs)

            # Draw the objects
            vball.draw(SCREEN)

        # Draw the Collider
        vconst.draw(SCREEN)

    # Check for a close event
    close_event()

    # Frames and update the display
    CLOCK.tick(60)
    pygame.display.flip()
