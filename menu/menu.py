from menu.button import Button
from verlet.ball.colliders.line import VerletBallLineCollider
from verlet.ball.colliders.circle import VerletBallCircleCollider
import pygame

class Menu:
    def __init__(self, screen: pygame.Surface) -> None:
        # Add line collider button
        self.line_collider_button: Button = Button(
            on_click=self.add_line_collider,
            width=105,
            height=35,
            position=(10, 10),
            text="Add Line Collider",
            color=(255, 255, 255),
        ).draw(screen)
            
        # Add circle collider button
        self.circle_collider_button: Button = Button(
            on_click=self.add_circle_collider,
            width=105,
            height=35,
            position=(10, 60),
            text="Add Circle Collider",
            color=(255, 255, 255),
        ).draw(screen)
    
    # Draw the buttons
    def draw_buttons(self, screen) -> None:
        self.line_collider_button.draw(screen)
        self.circle_collider_button.draw(screen)
    
    # Check if the event is a valid event
    def is_valid_event(self, event: pygame.event.Event) -> bool:
        if event.type != pygame.MOUSEBUTTONDOWN:
            return False
        return event.button == 1
    
    # Add a line collider
    def add_line_collider(
        self, 
        colliders: list[VerletBallLineCollider],
        **kwargs: dict,
    ) -> list[VerletBallLineCollider]:
        # Add the collider to the list of colliders
        colliders.append(VerletBallLineCollider(**kwargs)) # type: ignore
        
        # Return the list of colliders
        return colliders
    
    
    # Add a circle collider
    def add_circle_collider(
        self, 
        colliders: list[VerletBallCircleCollider],
        **kwargs: dict,
    ) -> list[VerletBallCircleCollider]:
        # Create a new collider
        collider: VerletBallCircleCollider = VerletBallCircleCollider(**kwargs) # type: ignore
        
        # Add the collider to the list of colliders
        colliders.append(collider)
        
        # Return the list of colliders
        return colliders
        