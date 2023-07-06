from physics import Vector2D, GRAVITY
from objects.verlet.object import VerletObject
#from grid import Grid, Cell
import pygame


# Ball class
class VerletBall(VerletObject):
    def __init__(
        self,
        #grid: Grid,
        position: tuple[float, float],
        radius: float = 10.0, 
        color: tuple[int, int, int] = (255, 255, 255),
    ) -> None:
        super(VerletBall, self).__init__(position, color)
        
        # Self variables
        self.radius: float = radius
    #    cell_index: tuple[int, int] = grid.calculate_cell_index(self.current_position)
    #    self.cell: Cell = grid.get(*cell_index)
        
    #def check_collisions_grid(self, grid: Grid) -> None:
    #    for ball in self.cell.objects:
    #        if ball == self:
    #            continue
    #        self.handle_collision(ball)
    #        self.cell.update(grid, ball.cell)
    #        
    #        cell_index: tuple[int, int] = grid.calculate_cell_index(self.current_position)
    #        self.cell = grid.get(*cell_index)
    
    # Draw the object
    def draw(self, screen: pygame.Surface) -> None:
        pygame.draw.circle(screen, self.color, 
                           self.current_position.get(), self.radius)
    
    # Check if the ball is colliding with another ball
    def handle_collision(self, other_ball: 'VerletBall') -> None:
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

    # Check if the ball is colliding with other balls
    def collisions(self, balls: list['VerletBall']) -> None:
        for other_ball in balls:
            if self == other_ball:
                continue
            
            # Handle the collision with the other ball
            self.handle_collision(other_ball)

    # Update the ball
    def update(self, screen: pygame.Surface, balls: list['VerletBall'] = []):
        self.accelerate(GRAVITY)
        self.update_position()
        self.collisions(balls)
        self.draw(screen)
    
    # Update the ball using a grid
    def update_no_collisions(self, screen: pygame.Surface):
        self.accelerate(GRAVITY)
        self.update_position()
        self.draw(screen)