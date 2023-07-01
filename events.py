import pygame
from circle import Circle


# Check if a close event has occurred
def close_event():
  for event in pygame.event.get():
        if event.type == pygame.QUIT:
            pygame.quit()
            quit()


# On click add a new circle at the mouse position
def on_click(circles: list[Circle]) -> list[Circle]:
    def add_circle(circles: list[Circle]) -> list[Circle]:
        # Get the mouse position
        mouse_pos: tuple[int, int] = pygame.mouse.get_pos()
        
        # Add a new circle
        circle = Circle([mouse_pos[0], mouse_pos[1]])
        circles.append(circle)
        
        # Return the updated circles
        return circles
    
    # Iterate over the events
    for event in pygame.event.get():
        if event.type == pygame.MOUSEBUTTONDOWN:
            return add_circle(circles)
    
    # Return the circles
    return circles