from components import Menu
from verlet.ball.colliders.line import VerletBallLineCollider
from verlet.ball.colliders.circle import VerletBallCircleCollider
from verlet.ball.ball import VerletBall
from components.list import ButtonList
from physics import GRAVITY
import pygame, time, threading, random
from testing.verlet.ball.config import BALL_COLORS

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
verlet_balls: list[VerletBall] = []

# Create a list of colliders
items: ButtonList = ButtonList()

# Automatically add the balls
def auto_add_balls():
    while 1:
        time.sleep(0.5)
        verlet_balls.append(VerletBall(
            (250.0, 50.0), 10.0, random.choice(BALL_COLORS)))

# Start threading
threading.Thread(target=auto_add_balls).start()

# Game Loop
while 1:
    screen.fill((0, 0, 0))
    menu.draw_buttons(screen)
    items.draw(screen, colliders)
    
    while len(verlet_balls) > 10:
        verlet_balls.pop(0)
    
    # Check for a close event
    for event in pygame.event.get():
        # Check if the event is a close event
        if event.type == pygame.QUIT:
            pygame.quit()
            exit()
        
        # Check if the event is a click event
        for item in items.clicked(event):
            colliders.remove(item.item)
            items.remove(item)
        
        # Check if the event is a click event
        if menu.line_collider_button.clicked(event):
            colliders.append(VerletBallLineCollider(
                start=(200.0, 100.0), 
                end=(400.0, 200.0),
                width=5,
            ))

        # Check if the event is a click event
        elif menu.circle_collider_button.clicked(event):
            colliders.append(VerletBallCircleCollider(
                position=(400.0, 300.0),
                radius=300,
                width=5,
            ))
    
    # Update the verlet_balls
    [ball.update(screen, colliders, verlet_balls) for ball in verlet_balls]
    # [[collider.apply(ball) for collider in colliders] for ball in verlet_balls]
    
    # Draw the Collider
    for collider in colliders:
        collider.draw(screen)
    
    # Frames and update the display
    pygame.display.flip()

