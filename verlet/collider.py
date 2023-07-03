import pygame
from physics import Vector2D


# Contraint class
class VerletCollider(object):
    def __init__(
        self, 
        position: tuple[float, float],
        width: int = 5,
        color: tuple[int, int, int] = (255, 255, 255)
    ) -> None:
        self.position: Vector2D = Vector2D(position[0], position[1])
        self.width: int = width
        self.color: tuple[int, int, int] = color
