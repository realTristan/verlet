class Vector3D:
    def __init__(self, x: float, y: float, z: float) -> None:
        self.x: float = x
        self.y: float = y
        self.z: float = z
    
    # When two Vector3D variables are substracted
    def __sub__(self, other: 'Vector3D') -> 'Vector3D':
        return Vector3D(self.x - other.x, self.y - other.y, self.z - other.z)
    
    # When two Vector3D variables are added
    def __add__(self, other: 'Vector3D') -> 'Vector3D':
        return Vector3D(self.x + other.x, self.y + other.y, self.z + other.z)
    
    # When two Vector3D variables are multiplied
    def __mul__(self, scalar: float) -> 'Vector3D':
        return Vector3D(self.x * scalar, self.y * scalar, self.z * scalar)
    
    # When two Vector3D variables are divided
    def __truediv__(self, scalar: float) -> 'Vector3D':
        return Vector3D(self.x / scalar, self.y / scalar, self.z / scalar)
    
    # When to the power
    def __pow__(self, scalar: float) -> 'Vector3D':
        return Vector3D(self.x ** scalar, self.y ** scalar, self.z ** scalar)
    
    # Reset the position
    def zero(self) -> 'Vector3D':
        self.x = 0.0
        self.y = 0.0
        self.z = 0.0
        return self
    
    # Copy the vector
    def copy(self) -> 'Vector3D':
        return Vector3D(self.x, self.y, self.z)
    
    # Set the position
    def set(self, x: float = None, y: float = None, z: float = None) -> 'Vector3D': # type: ignore
        if x is not None:
            self.x = x
        if y is not None:
            self.y = y
        if z is not None:
            self.z = z
        return self
    
    # Get the position
    def get(self) -> tuple[float, float, float]:
        return (self.x, self.y, self.z)

    # Create a copy
    def copy(self)-> 'Vector3D':
        return Vector3D(self.x, self.y, self.z)
    
    # Dot product
    def dot(self, other: 'Vector3D') -> float:
        return self.x * other.x + self.y * other.y + self.z * other.z
    
    # Magnitude
    def magnitude(self) -> float:
        return (self.x * self.x + self.y * self.y * self.z * self.z) ** 0.5
    
    # Normalize
    def normalize(self) -> 'Vector3D':
        mag: float = self.magnitude()
        self.x /= mag
        self.y /= mag
        self.z /= mag
        return self
    
    # Scale all values
    def mult(self, other: 'Vector3D') -> 'Vector3D':
        self.x *= other.x
        self.y *= other.y
        self.z *= other.z
        return self
    
    # Add to all values
    def add(self, scalar: float) -> 'Vector3D':
        self.x += scalar
        self.y += scalar
        self.z += scalar
        return self
    
    # Substract from all values
    def sub(self, scalar: float) -> 'Vector3D':
        self.x -= scalar
        self.y -= scalar
        self.z -= scalar
        return self
    
    # Divide from all values
    def div(self, other: 'Vector3D') -> 'Vector3D':
        self.x /= other.x
        self.y /= other.y
        self.z /= other.z
        return self
    