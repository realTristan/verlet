from physics import Vector2D
import time


class VerletObject(object):
    def __init__(
        self, 
        position: tuple[float, float], 
        color: tuple[int, int, int] = (255, 255, 255)
    ) -> None:
        
        # Physics variables
        self.current_position: Vector2D = Vector2D(position[0], position[1])
        self.prev_position: Vector2D = Vector2D(position[0], position[1])
        self.acceleration: Vector2D = Vector2D(0.0, 0.0)
        self.velocity: Vector2D = Vector2D(0.0, 0.0)
        
        # Self variables
        self.color: tuple[int, int, int] = color
        self.start_time: float = time.time()

    # Update the ball's color
    def set_color(self, color: tuple[int, int, int]) -> None:
        self.color = color

    # Calculate the objects velocity
    def calculate_velocity(self) -> Vector2D:
        return (self.current_position - self.prev_position)

    # Perform the verlet integration to calcualte the displacement
    def calculate_displacement(self, dt: float):
        return self.current_position + self.velocity + self.acceleration * dt

    # Accelerate the object
    def accelerate(self, acceleration: Vector2D) -> None:
        self.acceleration += acceleration
        
    # Update the objects position
    def update_position(self) -> None:
        # Calculate the delta time
        dt: float = (time.time() - self.start_time)
        
        # Calculate the velocity
        self.velocity = self.calculate_velocity()

        # Save the current position (use a copy)
        self.prev_position = self.current_position.copy()

        # Perform the Verlet integration
        self.current_position = self.calculate_displacement(dt)

        # Reset the acceleration
        self.acceleration.zero()
        
        # Reset the start time
        self.start_time = time.time()
