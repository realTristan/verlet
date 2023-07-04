import pygame
from objects.verlet.ball.ball import VerletBall
from physics import Vector2D
from .collider import CircleCollider


# Closed Circle Collider class
class ClosedCircleCollider(CircleCollider):
    def __init__(
        self, 
        position: tuple[float, float], 
        radius: float = 200.0,
        color: tuple[int, int, int] = (255, 255, 255),
    ) -> None:
        super(ClosedCircleCollider, self).__init__(position, radius, color)

    # Draw the filled circle collider
    def draw(self, screen: pygame.Surface) -> None:
        pygame.draw.circle(screen, self.color, self.position.get(),
                           self.radius)

    # Apply the Collider
    def apply(self, ball: VerletBall) -> None:
        # Calculate the distance between the ball and the circle
        dist: Vector2D = ball.current_position - self.position
        magnitude = dist.magnitude() + 1.0e-9
        
        # Check if the ball is outside the collider
        rad_sum: float = ball.radius + self.radius
        if magnitude < rad_sum and magnitude > self.radius:
            # Calculate the ball overlap (the amount the balls have overlapped)
            overlap: Vector2D = dist / magnitude

            # Update this balls position (move it to the side)
            ball.current_position += overlap * 0.5 * (rad_sum - magnitude)