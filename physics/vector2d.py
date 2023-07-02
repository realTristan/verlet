class Vector2D:
    def __init__(self, x: float, y: float) -> None:
        self.x: float = x
        self.y: float = y
    
    # When two Vector2D variables are substracted
    def __sub__(self, other: 'Vector2D') -> 'Vector2D':
        return Vector2D(self.x - other.x, self.y - other.y)
    
    # When two Vector2D variables are added
    def __add__(self, other: 'Vector2D') -> 'Vector2D':
        return Vector2D(self.x + other.x, self.y + other.y)
    
    # When two Vector2D variables are multiplied
    def __mul__(self, other: float) -> 'Vector2D':
        return Vector2D(self.x * other, self.y * other)
    
    # When two Vector2D variables are divided
    def __truediv__(self, other: float) -> 'Vector2D':
        return Vector2D(self.x / other, self.y / other)
    
    # Reset the position
    def zero(self) -> None:
        self.x = 0.0
        self.y = 0.0
    
    # Set the position
    def set(self, x: float = None, y: float = None) -> None: # type: ignore
        if x is not None:
            self.x = x
        if y is not None:
            self.y = y
    
    # Get the position
    def get(self) -> tuple[float, float]:
        return (self.x, self.y)

    # Create a copy
    def copy(self)-> 'Vector2D':
        return Vector2D(self.x, self.y)
    
    # Dot product
    def dot(self, other: 'Vector2D') -> float:
        return self.x * other.x + self.y * other.y
    
    # Cross product
    def cross(self, other: 'Vector2D') -> float:
        return self.x * other.y - self.y * other.x
    
    # Magnitude
    def magnitude(self) -> float:
        return (self.x * self.x + self.y * self.y) ** 0.5
    
    # Normalize
    def normalize(self) -> None:
        mag: float = self.magnitude()
        self.x /= mag
        self.y /= mag
        
    # Scale all values
    def scale(self, scalar: float) -> None:
        self.x *= scalar
        self.y *= scalar
    
    # Add to all values
    def add(self, scalar: float) -> None:
        self.x += scalar
        self.y += scalar
    