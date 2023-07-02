from typing import Any

# Friction class
class Friction:
    def __init__(self, mu: float, mass: float):
        self.mu: float = mu
        self.mass: float = mass
        self.gravity: float = 9.81
    
    # Calculate the applied friction
    def __getitem__(self) -> float:
        return self.gravity * self.mass * self.mu
