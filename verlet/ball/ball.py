import pygame
import time
from physics import Vector2D


# Ball class
class VerletBall(object):
    def __init__(
        self, 
        position: tuple[float, float], 
        radius: float = 10.0, 
        color: tuple[int, int, int] = (255, 255, 255)
    ) -> None:
        
        # Physics variables
        self.current_position: Vector2D = Vector2D(position[0], position[1])
        self.prev_position: Vector2D = Vector2D(position[0], position[1])
        self.acceleration: Vector2D = Vector2D(0.0, 0.0)
        self.velocity: Vector2D = Vector2D(0.0, 0.0)
        
        # Self variables
        self.radius: float = radius
        self.start_time: float = time.time()
        self.color: tuple[int, int, int] = color
        self.friction: Friction = None  # type: ignore

    # Update the ball's color
    def set_color(self, color: tuple[int, int, int]) -> None:
        self.color = color

    # Draw the object
    def draw(self, screen: pygame.Surface) -> None:
        pygame.draw.circle(screen, self.color, 
                           self.current_position.get(), self.radius)

    # Calculate the objects velocity
    def calculate_velocity(self) -> Vector2D:
        return (self.current_position - self.prev_position) * 0.96

    # Perform the verlet integration to calcualte the displacement
    def calculate_displacement(self, dt: float):
        return self.current_position + self.velocity + self.acceleration * dt * dt

    # Update the objects position
    def update_position(self, dt: float) -> None:
        self.velocity = self.calculate_velocity()

        # Save the current position (use a copy)
        self.prev_position = self.current_position.copy()

        # Perform the Verlet integration
        self.current_position = self.calculate_displacement(dt)

        # Reset the acceleration
        self.acceleration.zero()

    # Accelerate the object
    def accelerate(self, acceleration: Vector2D) -> None:
        self.acceleration += acceleration

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
                magnitude: float = dist.magnitude()
                rad_sum: float = ball_1.radius + ball_2.radius
                if magnitude < rad_sum:
                    # Calculate the ball overlap (the amount the balls have overlapped)
                    overlap: Vector2D = dist / magnitude

                    # Update this balls position (move it to the side)
                    ball_1.current_position += overlap * 0.5 * (rad_sum - magnitude)

                    # Update the other ball's position (move it to the opposite side)
                    ball_2.current_position -= overlap * 0.5 * (rad_sum - magnitude)
