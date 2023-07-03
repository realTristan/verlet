import pygame
from ..ball import VerletBall
from physics import Vector2D


class VerletBallLineCollider(object):
    def __init__(
        self, 
        start: tuple[float, float], 
        end: tuple[float, float], 
        width: int = 5,
        slope_multiplier: float = 1.0
    ) -> None:
        self.start: Vector2D = Vector2D(start[0], start[1])
        self.end: Vector2D = Vector2D(end[0], end[1])
        self.width: int = width
        self.color: tuple[int, int, int] = (255, 255, 255)
        self.slope_multiplier: float = slope_multiplier

    # Draw the Collider
    def draw(self, screen: pygame.Surface) -> None:
        pygame.draw.line(screen, self.color, self.start.get(), 
                         self.end.get(), self.width)

    # Apply the Collider
    def apply(self, ball: VerletBall) -> None:
        l_bound: float = self.start.x - ball.radius
        r_bound: float = self.end.x + ball.radius
        
        # If the circle is past the lines bounds
        if ball.current_position.x < l_bound or ball.current_position.x > r_bound:
            return
        
        # Calculate the slope of the line
        m: float = (self.start.y - self.end.y) / (self.start.x - self.end.x)

        # Calculate the y-intercept of the line
        y_int: float = self.start.y - m * self.start.x

        # Calculate the y position of the ball
        y: float = m * ball.current_position.x + y_int
        
        # If the ball is above/below the line
        y_above: float = ball.current_position.y + ball.radius + self.width
        y_below = y + self.width + ball.radius
        
        # Check to make sure the ball is within the y_above and y_below bounds
        if y_above > y and ball.current_position.y < y_below:
            ball.current_position.y = y - ball.radius - self.width
            ball.current_position.x += m * self.slope_multiplier

        