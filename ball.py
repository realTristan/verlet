import pygame, time
from constraint import Constraint


# Ball class
class Ball:
    def __init__(self, pos_cur: list[float]) -> None:
        self.pos_cur: list[float] = pos_cur
        self.pos_old: list[float] = pos_cur
        self.accel: list[float] = [0.0, 0.0]
        self.radius: float = 10.0
        self.start_time: float = time.time()
        self.color: tuple[int, int, int] = (255, 255, 255)

    # Update the ball's color
    def set_color(self, color: tuple[int, int, int]):
        self.color = color
        
    # Draw the object
    def draw(self, screen: pygame.Surface) -> None:
        pygame.draw.circle(screen, self.color, self.pos_cur, self.radius)

    # Calculate the objects velocity
    def calculate_velocity(self) -> list[float]:
        return [(self.pos_cur[0] - self.pos_old[0]) / 2,
                (self.pos_cur[1] - self.pos_old[1]) / 2]

    # Calculate the verlet integration
    def calculate_verlet(self, velocity: list[float], dt: float) -> list[float]:
        return [self.pos_cur[0] + velocity[0] + self.accel[0] * dt * dt,
                self.pos_cur[1] + velocity[1] + self.accel[1] * dt * dt]

    # Update the objects position
    def update_position(self, dt: float) -> None:
        velocity: list[float] = self.calculate_velocity()
        
        # Save the current position
        self.pos_old = self.pos_cur

        # Perform the Verlet integration
        self.pos_cur = self.calculate_verlet(velocity, dt)

        # Reset the acceleration
        self.accel = [0.0, 0.0]

    # Accelerate the object
    def accelerate(self, acceleration: list[float]) -> None:
        self.accel[0] += acceleration[0]
        self.accel[1] += acceleration[1]

    # Apply the constraint
    def apply_constraint(self, c: Constraint):
        # Calculate the distance between the ball and the constraint
        dist: list[float] = [self.pos_cur[0] - c.position[0], 
                               self.pos_cur[1] - c.position[1]]

        mag: float = (dist[0] ** 2 + dist[1] ** 2) ** 0.5 # the vector magnitude of the ball
        delta: float = c.radius - self.radius
        if mag >= delta:
            self.pos_cur[0] = c.position[0] + dist[0] / mag * delta
            self.pos_cur[1] = c.position[1] + dist[1] / mag * delta
    
    # Check if the ball is colliding with other balls
    @staticmethod
    def check_collision(balls: list['Ball']) -> None:
        for ball_1 in balls:
            for ball_2 in balls:
                if ball_1 == ball_2:
                    continue
                
                # Calculate the distance between the balls
                dist: list[float] = [ball_1.pos_cur[0] - ball_2.pos_cur[0],
                                    ball_1.pos_cur[1] - ball_2.pos_cur[1]]
                
                mag: float = (dist[0] ** 2 + dist[1] ** 2) ** 0.5 # the vector magnitude of the ball
                delta: float = ball_1.radius + ball_2.radius
                if mag <= delta:
                    # Calculate the ball overlap (the amount the balls have overlapped)
                    overlap: float = (mag - delta) / 2
                    
                    # Update this balls position (move it to the side)
                    ball_1.pos_cur[0] -= overlap * dist[0] / mag
                    ball_1.pos_cur[1] -= overlap * dist[1] / mag
                    
                    # Update the other ball's position (move it to the opposite side)
                    ball_2.pos_cur[0] += overlap * dist[0] / mag
                    ball_2.pos_cur[1] += overlap * dist[1] / mag

