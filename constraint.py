import pygame


# Contraint class
class Constraint:
    def __init__(self, position: list[float]) -> None:
        self.position: list[float] = position
        self.radius: float = 200.0
        self.width: int = 1
        self.color: tuple[int, int, int] = (255, 255, 255)


    # Draw the constraint
    def draw(self, screen: pygame.Surface) -> None:
        pygame.draw.circle(screen, self.color, self.position, 
                           self.radius, self.width)

