from objects.verlet.ball import VerletBall
from .circle_collider import CircleCollider
from physics import Vector2D
import pygame

# Closed Circle Collider class
class ClosedCircleCollider(CircleCollider):
    def __init__(
        self, 
        position: tuple[float, float], 
        radius: float = 200.0,
        color: tuple[int, int, int] = (255, 255, 255),
        outside_collision: bool = True,
    ) -> None:
        super(ClosedCircleCollider, self).__init__(position, radius, color)
        self.outside_collision: bool = outside_collision

    # Draw the filled circle collider
    def draw(self, screen: pygame.Surface) -> None:
        pygame.draw.circle(screen, self.color, self.position.get(),
                           self.radius)

    # Apply the Collider
    def apply(self, ball: VerletBall) -> None:
        if not self.outside_collision:
            return
        
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
