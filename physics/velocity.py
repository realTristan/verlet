# Velocity class
class Velocity:
    def __init__(self, velocity: tuple[float, float] = (0.0, 0.0)) -> None:
        self.x: float = velocity[0]
        self.y: float = velocity[1]
    
    # Reset the velocity
    def reset(self) -> None:
        self.x = 0.0
        self.y = 0.0
    
    # Set the velocity
    def set(self, x: float = None, y: float = None) -> None: # type: ignore
        if x is not None:
            self.x = x
        if y is not None:
            self.y = y
    
    # Get the velocity
    def get(self) -> tuple[float, float]:
        return (self.x, self.y)
    
    # Create a copy
    def copy(self):
        return Velocity((self.x, self.y))
    
    # When two Velocity variables are substracted
    def __sub__(self, other: 'Velocity') -> 'Velocity':
        return Velocity((self.x - other.x, self.y - other.y))
    
    # When two Velocity variables are added
    def __add__(self, other: 'Velocity') -> 'Velocity':
        return Velocity((self.x + other.x, self.y + other.y))