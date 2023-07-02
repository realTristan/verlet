import pygame
from ..ball import VerletBall
from physics import Vector2D


# Contraint class
class VerletBallCircleConstraint(object):
    def __init__(self, position: tuple[float, float], radius: float = 200.0) -> None:
        self.position: Vector2D = Vector2D(position[0], position[1])
        self.radius: float = radius
        self.width: int = 1
        self.color: tuple[int, int, int] = (255, 255, 255)

    # Draw the constraint
    def draw(self, screen: pygame.Surface) -> None:
        pygame.draw.circle(screen, self.color, self.position.get(),
                           self.radius, self.width)

    # Apply the constraint
    def apply(self, vball: VerletBall):
        # Calculate the distance between the ball and the constraint
        dist: Vector2D = self.position - vball.current_position

        # The vector magnitude of the ball
        magnitude: float = dist.magnitude()
        delta: float = self.radius - vball.radius
        if magnitude > delta:
            vball.current_position.set(
                self.position.x - dist.x / magnitude * delta,
                self.position.y - dist.y / magnitude * delta
            )

            # Update the verlet ball velocity to account for friction
            # if vball.friction is not None:
            #     vball.velocity.x -= vball.friction() * \
            #         dist.x / mag * delta
