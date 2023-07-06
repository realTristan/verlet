from physics import Vector2D
import time


class VerletObject(object):
    def __init__(
        self,
        position: tuple[float, float],
        color: tuple[int, int, int] = (255, 255, 255),
    ) -> None:
        self.current_position: Vector2D = Vector2D(position[0], position[1])
        self.prev_position: Vector2D = Vector2D(position[0], position[1])
        self.acceleration: Vector2D = Vector2D(0.0, 0.0)
        self.velocity: Vector2D = Vector2D(0.0, 0.0)
        self.color: tuple[int, int, int] = color
        self.start_time: float = time.time()

    # Update the ball's color
    def set_color(self, color: tuple[int, int, int]) -> None:
        self.color = color

    # Calculate the objects velocity
    def calculate_velocity(self) -> Vector2D:
        return self.current_position - self.prev_position

    # Perform the verlet integration to calcualte the displacement
    def calculate_displacement(self, dt: float):
        return self.current_position + self.velocity + self.acceleration * dt

    # Accelerate the object
    def accelerate(self, acceleration: Vector2D) -> None:
        self.acceleration += acceleration

    # Update the objects position
    def update_position(self) -> None:
        dt: float = time.time() - self.start_time
        self.velocity = self.calculate_velocity()
        self.prev_position = self.current_position.copy()
        self.current_position = self.calculate_displacement(dt)
        self.acceleration.zero()
        self.start_time = time.time()
