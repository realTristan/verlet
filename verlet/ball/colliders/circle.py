import pygame
from ..ball import VerletBall
from physics import Vector2D


# Contraint class
class VerletBallCircleCollider(object):
    def __init__(
        self, 
        position: tuple[float, float], 
        radius: float = 200.0, 
        width: int = 5,
        color: tuple[int, int, int] = (255, 255, 255)
    ) -> None:
        
        # Variables
        self.position: Vector2D = Vector2D(position[0], position[1])
        self.width: int = width
        self.color: tuple[int, int, int] = color
        self.radius: float = radius

    # Draw the Collider
    def draw(self, screen: pygame.Surface) -> None:
        pygame.draw.circle(screen, self.color, self.position.get(),
                           self.radius, self.width)

    # Apply the Collider
    def apply(self, ball: VerletBall):
        # Calculate the distance between the ball and the Collider
        dist: Vector2D = self.position - ball.current_position

        # The vector magnitude of the ball
        magnitude: float = dist.magnitude()
        
        # Check if the ball is inside the Collider
        delta: float = self.radius - ball.radius - self.width
        if magnitude > delta:
            ball.current_position.set(
                self.position.x - dist.x / magnitude * delta,
                self.position.y - dist.y / magnitude * delta)
