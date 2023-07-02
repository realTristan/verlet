class Acceleration:
    def __init__(self, acceleration: tuple[float, float] = (0.0, 0.0)) -> None:
        self.x: float = acceleration[0]
        self.y: float = acceleration[1]
    
    # Reset the acceleration
    def reset(self) -> None:
        self.x = 0.0
        self.y = 0.0
    
    # Set the acceleration
    def set(self, x: float = None, y: float = None) -> None: # type: ignore
        if x is not None:
            self.x = x
        if y is not None:
            self.y = y
    
    # Get the acceleration
    def get(self) -> tuple[float, float]:
        return (self.x, self.y)

    # Create a copy
    def copy(self)-> 'Acceleration':
        return Acceleration((self.x, self.y))

    # When two Acceleration variables are substracted
    def __sub__(self, other: 'Acceleration') -> 'Acceleration':
        return Acceleration((self.x - other.x, self.y - other.y))
    
    # When two Acceleration variables are added
    def __add__(self, other: 'Acceleration') -> 'Acceleration':
        return Acceleration((self.x + other.x, self.y + other.y))