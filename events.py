import pygame, random
from ball import Ball
from config import BALL_COLORS

# Check if a close event has occurred
def close_event():
  for event in pygame.event.get():
        if event.type == pygame.QUIT:
            pygame.quit()
            quit()


# On click add a new ball at the mouse position
def on_click(balls: list[Ball]) -> list[Ball]:
    def random_color():
        return random.choice(BALL_COLORS)
    
    def add_ball(balls: list[Ball]) -> list[Ball]:
        # Get the mouse position
        mouse_pos: tuple[int, int] = pygame.mouse.get_pos()
        
        # Add a new ball
        ball = Ball([mouse_pos[0], mouse_pos[1]])
        ball.set_color(random_color())
        balls.append(ball)
        
        # Return the updated balls
        return balls
    
    # Iterate over the events
    for event in pygame.event.get():
        if event.type == pygame.MOUSEBUTTONDOWN:
            return add_ball(balls)
    
    # Return the balls
    return balls