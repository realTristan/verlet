import pygame

class Text:
    def __init__(self, text: str, position: tuple[int, int], size: int, color: tuple[int, int, int], font: str = "Arial"):
        self.text = text
        self.position = position
        self.size = size
        self.color = color
        self.font = font
    
    def draw(self, screen: pygame.Surface) -> None:
        pygame.font.init()
        font = pygame.font.SysFont(self.font, self.size)
        text = font.render(self.text, True, self.color)
        screen.blit(text, self.position)