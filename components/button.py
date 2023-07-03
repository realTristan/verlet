import pygame
from physics import Vector2D


class Button:
    def __init__(
        self,
        width: int = 100,
        height: int = 50,
        position: Vector2D = Vector2D(0, 0),
        text: str = "Button",
        color: tuple[int, int, int] = (255, 255, 255),
    ) -> None:
        self.width: int = width
        self.height: int = height
        self.position: Vector2D = position
        self.color: tuple[int, int, int] = color
        self.text: str = text

    # Draw the button
    def draw(self, screen: pygame.Surface) -> 'Button':
        pygame.draw.rect(screen, self.color, pygame.Rect(
            self.position.get(), (self.width, self.height)))
        font = pygame.font.SysFont("Arial", 10)
        text = font.render(self.text, True, (0, 0, 0))
        screen.blit(text, (self.position.x + 10, self.position.y + 10))
        return self
    
    # Check if the event is a valid event
    def is_valid_event(self, event: pygame.event.Event) -> bool:
        if event.type != pygame.MOUSEBUTTONDOWN:
            return False
        return event.button == 1

    # Return whether the button was clicked
    def clicked(self, event: pygame.event.Event) -> bool:
        if not self.is_valid_event(event):
            return False
        x0, x1 = self.position.x, event.pos[0]
        y0, y1 = self.position.y, event.pos[1]
        return x0 <= x1 <= x0 + self.width and y0 <= y1 <= y0 + self.height
