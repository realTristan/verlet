import pygame
from typing import Callable


class Button:
    def __init__(
        self,
        on_click: Callable,
        width: int = 100, 
        height: int = 50, 
        position: tuple[int, int] = (0, 0),
        text: str = "Button",
        color: tuple[int, int, int] = (255, 255, 255),
    ) -> None:
        self.width: int = width
        self.height: int = height
        self.position: tuple[int, int] = position
        self.color: tuple[int, int, int] = color
        self.on_click: Callable = on_click
        self.text: str = text
    
    def draw(self, screen: pygame.Surface) -> 'Button':
        pygame.draw.rect(screen, self.color, pygame.Rect(self.position, (self.width, self.height)))
        font = pygame.font.SysFont("Arial", 10)
        text = font.render(self.text, True, (0, 0, 0))
        screen.blit(text, (self.position[0] + 10, self.position[1] + 10))
        return self
        
    def clicked(self, position: tuple[int, int]) -> bool:
        x0, x1 = self.position[1], position[0]
        y0, y1 = self.position[1], position[1]
        return x0 <= x1 <= x0 + self.width and y0 <= y1 <= y0 + self.height
            
    