import pygame
import time
from physics import Vector2D
from verlet.object import VerletObject


# Ball class
class VerletBall(VerletObject):
    def __init__(
        self, 
        position: tuple[float, float], 
        radius: float = 10.0, 
        color: tuple[int, int, int] = (255, 255, 255)
    ) -> None:
        super(VerletBall, self).__init__(position, color)
        
        # Self variables
        self.radius: float = radius

    # Draw the object
    def draw(self, screen: pygame.Surface) -> None:
        pygame.draw.circle(screen, self.color, 
                           self.current_position.get(), self.radius)

    # Check if the ball is colliding with other balls
    @staticmethod
    def check_collisions(balls: list['VerletBall']) -> None:
        for ball_1 in balls:
            for ball_2 in balls:
                if ball_1 == ball_2:
                    continue

                # Calculate the distance between the balls
                dist: Vector2D = ball_1.current_position - ball_2.current_position
                
                # the vector magnitude of the ball
                magnitude: float = dist.magnitude() + 1.0e-9
                rad_sum: float = ball_1.radius + ball_2.radius
                if magnitude < rad_sum:
                    # Calculate the ball overlap (the amount the balls have overlapped)
                    overlap: Vector2D = dist / magnitude

                    # Update this balls position (move it to the side)
                    ball_1.current_position += overlap * 0.5 * (rad_sum - magnitude)

                    # Update the other ball's position (move it to the opposite side)
                    ball_2.current_position -= overlap * 0.5 * (rad_sum - magnitude)
