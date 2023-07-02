import pygame
from ..ball import VerletBall


# Contraint class
class VerletBallCircleConstraint:
    def __init__(self, position: list[float], type: str = "circle", radius: float = 200.0) -> None:
        self.position: list[float] = position
        self.radius: float = radius
        self.width: int = 1
        self.color: tuple[int, int, int] = (255, 255, 255)
        self.type: str = type

    # Draw the constraint
    def draw(self, screen: pygame.Surface) -> None:
        pygame.draw.circle(screen, self.color, self.position, 
                           self.radius, self.width)
    
    # Apply the constraint
    def apply(self, verlet_ball: VerletBall):
        # Calculate the distance between the ball and the constraint
        dist: list[float] = [self.position[0] - verlet_ball.pos_cur[0], 
                             self.position[1] - verlet_ball.pos_cur[1]]

        mag: float = (dist[0] ** 2 + dist[1] ** 2) ** 0.5 # the vector magnitude of the ball
        delta: float = self.radius - verlet_ball.radius # if the constraint is a circle
        if mag > delta:
            verlet_ball.pos_cur[0] = self.position[0] - dist[0] / mag * delta
            verlet_ball.pos_cur[1] = self.position[1] - dist[1] / mag * delta
    

