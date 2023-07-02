import pygame


# Pygame Variables
SCREEN: pygame.Surface = pygame.display.set_mode((800, 600))
BACKGROUND_COLOR: tuple[int, int, int] = (0, 0, 0)
CLOCK: pygame.time.Clock = pygame.time.Clock()

# Physics Constants
GRAVITY: list[float] = [0.0, 9.81]
SUB_STEPS: int = 8

