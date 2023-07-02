import pygame, random
from verlet import VerletBall
from testing.verlet.ball.config import BALL_COLORS

# Check if a close event has occurred
def close_event() -> None:
  for event in pygame.event.get():
        if event.type == pygame.QUIT:
            pygame.quit()
            quit()


# On click add a new ball at the mouse position
def on_click(vballs: list[VerletBall], ball_radius: float = 20.0) -> list[VerletBall]:
    def random_color() -> tuple[int, int, int]:
        return random.choice(BALL_COLORS)
    
    def add_ball(vballs: list[VerletBall], radius: float) -> list[VerletBall]:
        # Get the mouse position
        mouse_pos: tuple[int, int] = pygame.mouse.get_pos()
        
        # Add a new ball
        vball = VerletBall((mouse_pos[0], mouse_pos[1]), radius=radius)
        vball.set_color(random_color())
        vballs.append(vball)
        
        # Return the updated balls
        return vballs
    
    # Iterate over the events
    for event in pygame.event.get():
        if event.type == pygame.MOUSEBUTTONDOWN:
            return add_ball(vballs, ball_radius)
    
    # Return the balls
    return vballs