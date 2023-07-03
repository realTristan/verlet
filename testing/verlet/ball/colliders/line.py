import pygame, time, threading
from verlet import VerletBall, VerletBallLineCollider
from testing.verlet.ball.config import SCREEN, BACKGROUND_COLOR, CLOCK, SUB_STEPS
from testing.verlet.ball.events import close_event, on_click

# Initialize pygame
pygame.init()

# Window Title
pygame.display.set_caption("pyverlet")

# Objects
lines: list[VerletBallLineCollider] = [
    VerletBallLineCollider((200.0, 100.0), (400.0, 200.0)),
    VerletBallLineCollider((300.0, 400.0), (500.0, 300.0)),
    VerletBallLineCollider((200.0, 500.0), (400.0, 580.0))
]
verlet_balls = [VerletBall((200.0, 100.0), radius=10.0),
          VerletBall((300.0, 100.0), radius=10.0)]

# Automatically add the balls
def auto_add_balls():
    while 1:
        time.sleep(0.5)
        verlet_balls.append(
            VerletBall((250.0, 50.0), radius=10.0))
        
# Start threading
threading.Thread(target=auto_add_balls).start()

# Game Loop
while 1:
    # Set the background
    SCREEN.fill(BACKGROUND_COLOR)

    # On click
    for _ in range(SUB_STEPS):
        # Add another ball
        verlet_balls = on_click(verlet_balls)
        while len(verlet_balls) > 10:
            verlet_balls.pop(0)

        # Update the ball
        [ball.update(SCREEN, lines, verlet_balls) for ball in verlet_balls]
        # [[line.apply(ball) for line in lines] for ball in verlet_balls]

        # Draw the Collider
        for line in lines:
            line.draw(SCREEN)

    # Check for a close event
    close_event()

    # Frames and update the display
    CLOCK.tick(60)
    pygame.display.flip()
