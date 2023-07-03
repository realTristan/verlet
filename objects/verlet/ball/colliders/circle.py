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
        # Calculate the distance between the ball and the circle
        dist: Vector2D = ball.current_position - self.position
        magnitude = dist.magnitude() + 1.0e-9
        rad_sum: float = ball.radius + self.radius
        if magnitude < rad_sum and magnitude > self.radius:
            # Calculate the ball overlap (the amount the balls have overlapped)
            overlap: Vector2D = dist / magnitude

            # Update this balls position (move it to the side)
            ball.current_position += overlap * 0.5 * (rad_sum - magnitude)
            return
        
        # Check if the ball is inside the collider
        dist = self.position - ball.current_position
        magnitude = dist.magnitude() + 1.0e-9
        delta: float = self.radius - ball.radius - self.width
        if magnitude > delta and magnitude < self.radius:
            ball.current_position.set(
                self.position.x - dist.x / magnitude * delta,
                self.position.y - dist.y / magnitude * delta)
