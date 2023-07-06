from interface.components.button import Button
from physics import Vector2D
import pygame

class Menu:
    def __init__(self, screen: pygame.Surface) -> None:
        # Add line collider button
        self.line_collider_button: Button = Button(
            text="Add Line Collider",
            position=(10, 10),
            width=105,
            height=35,
            color=(255, 255, 255),
        ).draw(screen)
        
        # Add circle collider button
        self.circle_collider_button: Button = Button(
            text="Add Circle Collider",
            position=(10, 60),
            width=105,
            height=35,
            color=(255, 255, 255),
        ).draw(screen)
    
    # Draw the buttons
    def draw_buttons(self, screen) -> None:
        self.line_collider_button.draw(screen)
        self.circle_collider_button.draw(screen)
