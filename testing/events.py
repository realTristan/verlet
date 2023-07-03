import pygame, random
from verlet import VerletBall
from testing.config import BALL_COLORS

# Check if a close event has occurred
def close_event() -> None:
  for event in pygame.event.get():
        if event.type == pygame.QUIT:
            pygame.quit()
            quit()


# On click add a new ball at the mouse position
def on_click(verlet_balls: list[VerletBall]) -> list[VerletBall]:
    def random_color() -> tuple[int, int, int]:
        return random.choice(BALL_COLORS)
    
    def random_radius() -> int:
        return random.randint(5, 20)
    
    def add_ball(verlet_balls: list[VerletBall], radius: float) -> list[VerletBall]:
        # Get the mouse position
        mouse_pos: tuple[int, int] = pygame.mouse.get_pos()
        
        # Add a new ball
        verlet_ball = VerletBall((mouse_pos[0], mouse_pos[1]), radius=radius)
        verlet_ball.set_color(random_color())
        verlet_balls.append(verlet_ball)
        
        # Return the updated balls
        return verlet_balls
    
    # Iterate over the events
    for event in pygame.event.get():
        if event.type == pygame.MOUSEBUTTONDOWN:
            return add_ball(verlet_balls, random_radius())
    
    # Return the balls
    return verlet_balls