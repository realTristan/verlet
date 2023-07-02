import pygame


# Pygame Constants
WIDTH: int = 800
HEIGHT: int = 600
SCREEN: pygame.Surface = pygame.display.set_mode((WIDTH, HEIGHT))
BACKGROUND_COLOR: tuple[int, int, int] = (0, 0, 0)
CLOCK: pygame.time.Clock = pygame.time.Clock()

# Physics Constants
GRAVITY: tuple[float, float] = (0.0, 9.81)
SUB_STEPS: int = 8

