import pygame


# Pygame Constants
WIDTH: int = 800
HEIGHT: int = 600
SCREEN: pygame.Surface = pygame.display.set_mode((WIDTH, HEIGHT))
BACKGROUND_COLOR: tuple[int, int, int] = (0, 0, 0)
CLOCK: pygame.time.Clock = pygame.time.Clock()

# Other Constants
SUB_STEPS: int = 8
BALL_COLORS: list[tuple[int, int, int]] = [
    (255, 0, 0), (0, 255, 0), (0, 0, 255),
    (255, 255, 0), (255, 0, 255), (0, 255, 255),
]