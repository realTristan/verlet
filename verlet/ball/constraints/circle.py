import pygame
from ..ball import VerletBall
from physics import Position


# Contraint class
class VerletBallCircleConstraint:
    def __init__(self, position: tuple[float, float], radius: float = 200.0) -> None:
        self.position: Position = Position(position)
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
        dist: Position = self.position - vball.current_position

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
