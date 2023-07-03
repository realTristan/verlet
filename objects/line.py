from physics import Vector2D
import math, pygame

# Custom Line Class
class Line:
    def __init__(
        self, 
        position: Vector2D, 
        length: float, 
        angle: float,
        width: int,
        color: tuple[int, int, int] = (255, 255, 255)
    ) -> None:
        self.start: Vector2D = position
        self.length: float = length
        self.angle: float = angle
        self.width: int = width
        self.color: tuple[int, int, int] = color
    
    # Set the line angle
    def set_angle(self, angle: float) -> None:
        self.angle = angle
    
    # Set the width of the line
    def set_length(self, length: float) -> None:
        self.length = length
    
    # Draw the line
    def draw(self, screen: pygame.Surface) -> None:
        # Determine the end position of the line
        end_x: float = self.start.x + self.length * math.sin(self.angle)
        end_y: float = self.start.y + self.length * math.sin(self.angle)
        
        # Draw the line
        pygame.draw.line(screen, self.color, 
                         self.start.get(), (end_x, end_y), self.width)