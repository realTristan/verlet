import pygame
from physics import Vector2D
from .text import Text


class Button:
    def __init__(
        self,
        text: str,
        position: tuple[float, float] = (0, 0),
        width: int = 100,
        height: int = 50,
        color: tuple[int, int, int] = (255, 255, 255),
    ) -> None:
        self.width: int = width
        self.height: int = height
        self.position: Vector2D = Vector2D(position[0], position[1])
        self.color: tuple[int, int, int] = color
        self.text: str = text

    # Draw the button
    def draw(self, screen: pygame.Surface) -> 'Button':
        pygame.draw.rect(
            screen,
            self.color,
            pygame.Rect(self.position.get(), (self.width, self.height)),
        )
        text: Text = Text(
            self.text, (self.position.x + 10.0, self.position.y + 10.0), 10, (0, 0, 0)
        )
        text.draw(screen)
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
