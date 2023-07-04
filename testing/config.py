import pygame


# Pygame Constants
WIDTH: int = 800
HEIGHT: int = 600
SCREEN: pygame.Surface = pygame.display.set_mode((WIDTH, HEIGHT))
CLOCK: pygame.time.Clock = pygame.time.Clock()

# Other Constants
SUB_STEPS: int = 8

# Background
BACKGROUND_COLOR: tuple[int, int, int] = (0, 0, 0)

# Draw the background
def draw_background():
    SCREEN.fill(BACKGROUND_COLOR)
    for x in range(0, WIDTH, 50):
        for y in range(0, HEIGHT, 50):
            pygame.draw.rect(SCREEN, (50, 50, 50), (x, y, 50, 50), 1)
