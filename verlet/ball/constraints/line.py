import pygame
from ..ball import VerletBall


class VerletBallLineConstraint:
    def __init__(self, position: list[float], to: list[float], width: int = 1) -> None:
        self.position: list[float] = position
        self.width: int = width
        self.to: list[float] = to
        self.color: tuple[int, int, int] = (255, 255, 255)

    # Draw the constraint
    def draw(self, screen: pygame.Surface) -> None:
        pygame.draw.line(screen, self.color, self.position, 
                         self.to, self.width)

    # Apply the constraint
    def apply(self, vball: VerletBall) -> None:
        l_bound: float = self.position[0] - vball.radius
        r_bound: float = self.to[0] + vball.radius
        
        # If the circle is past the lines bounds
        if vball.pos_cur[0] < l_bound or vball.pos_cur[0] > r_bound:
            return
        
        # Calculate the slope of the line
        m: float = (self.position[1] - self.to[1]) / (self.position[0] - self.to[0])

        # Calculate the y-intercept of the line
        y_int: float = self.position[1] - m * self.position[0]

        # Calculate the y position of the ball
        y: float = m * vball.pos_cur[0] + y_int
        
        # If the ball is below the line
        y_above: float = vball.pos_cur[1] + vball.radius
        y_below = y + self.width + vball.radius
        
        # Check to make sure the ball is within the y_above and y_below bounds
        if y_above > y and vball.pos_cur[1] < y_below:
            vball.pos_cur[1] = y - vball.radius

        