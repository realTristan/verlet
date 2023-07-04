import pygame


class Text:
    def __init__(
        self,
        text: str,
        position: tuple[float, float],
        size: int,
        color: tuple[int, int, int],
        font: str = "Arial",
    ):
        self.text: str = text
        self.position: tuple[float, float] = position
        self.size: int = size
        self.color: tuple[int, int, int] = color
        self.font: str = font

    def draw(self, screen: pygame.Surface) -> None:
        pygame.font.init()
        font = pygame.font.SysFont(self.font, self.size)
        text = font.render(self.text, True, self.color)
        screen.blit(text, self.position)
