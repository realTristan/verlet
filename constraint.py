import pygame


# Contraint class
class Constraint:
    def __init__(self, position: list[float]):
        self.position: list[float] = position
        self.radius: float = 200.0
        self.width: int = 1


    # Draw the constraint
    def draw(self, screen: pygame.Surface):
        pygame.draw.circle(screen, (255, 255, 255), 
                           self.position, self.radius, self.width)

