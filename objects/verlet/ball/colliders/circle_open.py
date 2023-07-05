import pygame
from objects.verlet.ball.ball import VerletBall
from physics import Vector2D
from .circle_collider import CircleCollider


# Open Circle Collider class
class OpenCircleCollider(CircleCollider):
    def __init__(
        self,
        position: tuple[float, float],
        radius: float = 200.0,
        width: int = 5,
        color: tuple[int, int, int] = (255, 255, 255),
        outside_collision: bool = True,
        inside_collision: bool = True,
    ) -> None:
        # Variables
        super(OpenCircleCollider, self).__init__(position, radius, color)
        self.outside_collision: bool = outside_collision
        self.inside_collision: bool = inside_collision
        self.width: int = width

    # Draw the Collider
    def draw(self, screen: pygame.Surface) -> None:
        pygame.draw.circle(
            screen, self.color, self.position.get(), self.radius, self.width
        )

    # Apply the Collider
    def apply(self, ball: VerletBall) -> None:
        if not self.outside_collision and not self.inside_collision:
            return
        
        # Calculate the distance between the ball and the circle
        dist: Vector2D = ball.current_position - self.position
        magnitude = dist.magnitude() + 1.0e-9

        # Check if the ball is outside the collider
        if self.outside_collision:
            rad_sum: float = ball.radius + self.radius
            if magnitude < rad_sum and (
                not self.inside_collision or magnitude > self.radius
            ):
                # Calculate the ball overlap (the amount the balls have overlapped)
                overlap: Vector2D = dist / magnitude

                # Update this balls position (move it to the side)
                ball.current_position += overlap * 0.5 * (rad_sum - magnitude)
                return

        # Check if the ball is inside the collider
        if self.inside_collision:
            delta: float = self.radius - ball.radius - self.width
            if magnitude > delta and (
                not self.outside_collision or magnitude < self.radius
            ):
                ball.current_position.set(
                    self.position.x + dist.x / magnitude * delta,
                    self.position.y + dist.y / magnitude * delta,
                )
