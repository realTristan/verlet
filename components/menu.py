from components.button import Button
from physics import Vector2D
import pygame

class Menu:
    def __init__(self, screen: pygame.Surface) -> None:
        # Add line collider button
        self.line_collider_button: Button = Button(
            width=105,
            height=35,
            position=Vector2D(10, 10),
            text="Add Line Collider",
            color=(255, 255, 255),
        ).draw(screen)
        
        # Add circle collider button
        self.circle_collider_button: Button = Button(
            width=105,
            height=35,
            position=Vector2D(10, 60),
            text="Add Circle Collider",
            color=(255, 255, 255),
        ).draw(screen)
    
    # Draw the buttons
    def draw_buttons(self, screen) -> None:
        self.line_collider_button.draw(screen)
        self.circle_collider_button.draw(screen)
