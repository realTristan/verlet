import pygame
from ..ball import VerletBall
from physics import Vector2D


class VerletBallLineCollider(object):
    def __init__(
        self, 
        position: tuple[float, float], 
        to: tuple[float, float], 
        width: int = 5,
        slope_multiplier: float = 0.06
    ) -> None:
        self.position: Vector2D = Vector2D(position[0], position[1])
        self.to: Vector2D = Vector2D(to[0], to[1])
        self.width: int = width
        self.color: tuple[int, int, int] = (255, 255, 255)
        self.slope_multiplier: float = slope_multiplier

    # Draw the Collider
    def draw(self, screen: pygame.Surface) -> None:
        pygame.draw.line(screen, self.color, self.position.get(), 
                         self.to.get(), self.width)

    # Apply the Collider
    def apply(self, vball: VerletBall) -> None:
        l_bound: float = self.position.x - vball.radius
        r_bound: float = self.to.x + vball.radius
        
        # If the circle is past the lines bounds
        if vball.current_position.x < l_bound or vball.current_position.x > r_bound:
            return
        
        # Calculate the slope of the line
        m: float = (self.position.y - self.to.y) / (self.position.x - self.to.x)

        # Calculate the y-intercept of the line
        y_int: float = self.position.y - m * self.position.x

        # Calculate the y position of the ball
        y: float = m * vball.current_position.x + y_int
        
        # If the ball is above/below the line
        y_above: float = vball.current_position.y + vball.radius + self.width
        y_below = y + self.width + vball.radius
        
        # Check to make sure the ball is within the y_above and y_below bounds
        if y_above > y and vball.current_position.y < y_below:
            vball.current_position.y = y - vball.radius - self.width
            vball.current_position.x += m * self.slope_multiplier

        