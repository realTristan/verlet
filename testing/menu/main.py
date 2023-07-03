from menu import Menu
from verlet.ball.colliders.line import VerletBallLineCollider
from verlet.ball.colliders.circle import VerletBallCircleCollider
from verlet.ball.ball import VerletBall
from physics import GRAVITY
import pygame, time, threading

# Initialize pygame
pygame.init()

# Window Title
pygame.display.set_caption("pyverlet")

# Set the screen
screen: pygame.Surface = pygame.display.set_mode((800, 600))

# Set the background
screen.fill((0, 0, 0))

# Create a menu
menu: Menu = Menu(screen)

# Colliders and Verlet Balls
colliders: list[VerletBallCircleCollider | VerletBallLineCollider] = []
vballs: list[VerletBall] = []

# Automatically add the balls
def auto_add_balls():
    while 1:
        time.sleep(0.5)
        vballs.append(
            VerletBall((250.0, 50.0), radius=10.0))
        
# Start threading
threading.Thread(target=auto_add_balls).start()

# Game Loop
while 1:
    screen.fill((0, 0, 0))
    menu.draw_buttons(screen)
    
    while len(vballs) > 10:
        vballs.pop(0)
    
    # Check for a close event
    for event in pygame.event.get():
        # Check if the event is a close event
        if event.type == pygame.QUIT:
            pygame.quit()
            exit()
            
        # Check if the event is a valid event
        if not menu.is_valid_event(event):
            continue
        
        # Check if the event is a click event
        if menu.line_collider_button.clicked(event.pos):
            colliders = menu.line_collider_button.on_click(colliders)

        # Check if the event is a click event
        elif menu.circle_collider_button.clicked(event.pos):
            colliders = menu.circle_collider_button.on_click(colliders)
    
    # Draw the colliders
    for vball in vballs:
        # Calculate the delta time
        dt: float = (time.time() - vball.start_time)

        # Apply updates to the ball
        vball.accelerate(GRAVITY)
        vball.update_position(dt)
        [collider.apply(vball) for collider in colliders]
        VerletBall.check_collisions(vballs)

        # Draw the objects
        vball.draw(screen)
            
    # Draw the Collider
    for collider in colliders:
        collider.draw(screen)
    
    # Frames and update the display
    pygame.display.flip()

