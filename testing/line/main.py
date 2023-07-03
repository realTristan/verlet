from objects import Line
from physics import Vector2D
from testing.config import draw_background
import pygame

# Initialize pygame
pygame.init()

# Window Title
pygame.display.set_caption("pyverlet")

# Set the screen
screen: pygame.Surface = pygame.display.set_mode((800, 600))

# Create a new line
line = Line(Vector2D(100, 100), 100, 30, 4)

# Game Loop
while 1:
    draw_background()
    line.draw(screen)
    pygame.display.flip()

