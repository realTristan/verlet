import pygame, time
from physics import Vector2D, GRAVITY
from objects.verlet.object import VerletObject
from typing import Any


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
    
    # Check if the ball is colliding with another ball
    def handle_collision(self, other_ball: 'VerletBall') -> tuple[Vector2D, Vector2D]:
        # Calculate the distance between the balls
        dist: Vector2D = self.current_position - other_ball.current_position
        
        # the vector magnitude of the ball
        magnitude: float = dist.magnitude() + 1.0e-9
        rad_sum: float = self.radius + other_ball.radius
        if magnitude < rad_sum:
            # Calculate the ball overlap (the amount the balls have overlapped)
            overlap: Vector2D = dist / magnitude

            # Update this balls position (move it to the side)
            self.current_position += overlap * 0.5 * (rad_sum - magnitude)

            # Update the other ball's position (move it to the opposite side)
            other_ball.current_position -= overlap * 0.5 * (rad_sum - magnitude)
        
        # Return the new positions
        return self.current_position, other_ball.current_position

    # Check if the ball is colliding with other balls
    def collisions(self, balls: list['VerletBall']) -> None:
        for other_ball in balls:
            if self == other_ball:
                continue
            
            # Handle the collision with the other ball
            self.handle_collision(other_ball)

    # Update the ball
    def update(
        self,
        screen: pygame.Surface,
        balls: list['VerletBall'] = []
    ):
        # Apply updates to the ball
        self.accelerate(GRAVITY)
        self.update_position()
        self.collisions(balls)

        # Draw the objects
        self.draw(screen)