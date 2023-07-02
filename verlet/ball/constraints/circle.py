import pygame
from ..ball import VerletBall


# Contraint class
class VerletBallCircleConstraint:
    def __init__(self, position: list[float], radius: float = 200.0) -> None:
        self.position: list[float] = position
        self.radius: float = radius
        self.width: int = 1
        self.color: tuple[int, int, int] = (255, 255, 255)

    # Draw the constraint
    def draw(self, screen: pygame.Surface) -> None:
        pygame.draw.circle(screen, self.color, self.position,
                           self.radius, self.width)

    # Apply the constraint
    def apply(self, vball: VerletBall):
        # Calculate the distance between the ball and the constraint
        dist: list[float] = [self.position[0] - vball.pos_cur[0],
                             self.position[1] - vball.pos_cur[1]]

        # The vector magnitude of the ball
        mag: float = (dist[0] ** 2 + dist[1] ** 2) ** 0.5
        delta: float = self.radius - vball.radius
        if mag > delta:
            vball.pos_cur[0] = self.position[0] - dist[0] / mag * delta
            vball.pos_cur[1] = self.position[1] - dist[1] / mag * delta

            # Update the verlet ball velocity to account for friction
            # if vball.friction is not None:
            #     vball.velocity[0] -= vball.friction.__getitem__() * \
            #         dist[0] / mag * delta
