import pygame
from ..ball import VerletBall
from physics import Vector2D


# Contraint class
class VerletBallCircleConstraint:
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
        mag: float = (dist.x ** 2 + dist.y ** 2) ** 0.5
        delta: float = self.radius - vball.radius
        if mag > delta:
            vball.current_position.x = self.position.x - dist.x / mag * delta
            vball.current_position.y = self.position.y - dist.y / mag * delta

            # Update the verlet ball velocity to account for friction
            # if vball.friction is not None:
            #     vball.velocity.x -= vball.friction() * \
            #         dist.x / mag * delta
