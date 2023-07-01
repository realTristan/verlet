import pygame, time


# Ball class
class Ball:
    def __init__(self, pos_cur: list[float]) -> None:
        self.pos_cur: list[float] = pos_cur
        self.pos_old: list[float] = pos_cur
        self.accel: list[float] = [0.0, 0.0]
        self.radius: float = 10.0
        self.start_time: float = time.time()

    # Draw the object
    def draw(self, screen: pygame.Surface) -> None:
        pygame.draw.circle(screen, (255, 255, 255), self.pos_cur, self.radius)

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
    def apply_constraint(self, constraint):
        # Calculate the distance between the ball and the constraint
        to_obj: list[float] = [self.pos_cur[0] - constraint.position[0], 
                               self.pos_cur[1] - constraint.position[1]]

        dist: float = (to_obj[0] ** 2 + to_obj[1] ** 2) ** 0.5
        if dist > constraint.radius - self.radius:
            n: list[float] = [to_obj[0] / dist, to_obj[1] / dist]
            self.pos_cur[0] = constraint.position[0] + n[0] * (dist - self.radius)
            self.pos_cur[1] = constraint.position[1] + n[1] * (dist - self.radius)
    
    # Check if the ball is colliding with other balls
    def check_collision(self, balls: list['Ball']) -> None:
        for ball in balls:
            if ball == self:
                continue
            
            # Calculate the distance between the balls
            to_obj: list[float] = [self.pos_cur[0] - ball.pos_cur[0],
                                   self.pos_cur[1] - ball.pos_cur[1]]
            
            dist: float = (to_obj[0] ** 2 + to_obj[1] ** 2) ** 0.5
            if dist < self.radius + ball.radius:
                n: list[float] = [to_obj[0] / dist, to_obj[1] / dist]
                
                # Calculate the ball overlap (the amount the balls have overlapped)
                overlap: float = (dist - self.radius - ball.radius) / 2
                
                # Update this balls position (move it to the side)
                self.pos_cur[0] -= overlap * n[0]
                self.pos_cur[1] -= overlap * n[1]
                
                # Update the other ball's position (move it to the opposite side)
                ball.pos_cur[0] += overlap * n[0]
                ball.pos_cur[1] += overlap * n[1]
            
            
