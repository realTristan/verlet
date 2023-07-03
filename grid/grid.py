from ..testing.verlet.ball.config import WIDTH, HEIGHT
from ..physics import Vector2D
from typing import Any
from .cell import Cell

# Grid class
class Grid:
    def __init__(self):
        self.cell_size: int = 100
        self.width: int = round(WIDTH / self.cell_size)
        self.height: int = round(HEIGHT / self.cell_size)
        self.grid: list[list[Cell]] = [
            [Cell() for _ in range(self.height)] for _ in range(self.width)]
    
    
    # Get a cell from the grid
    def get(self, x: int, y: int) -> Cell:
        return self.grid[x][y]


    # Put an object into the grid
    def put(self, obj: Any, position: Vector2D):
        # Get the cell
        x: int = round(position.x / self.cell_size)
        y: int = round(position.y / self.cell_size)
        cell: Cell = self.get(x, y)
        
        # Add the object to the cell
        cell.objects.append(obj)
        
        # Update the grid
        self.grid[x][y] = cell
    
    
    # Find all the collisions for each cell in the grid
    def find_collisions(self):
        # Iterate over all cells
        for i in range(self.width):
            for j in range(self.height):
                # Get the current cell
                current_cell: Cell = self.get(i, j)
                
                # Iterate over all surrounding cells, including the current one
                for x in range(-1, 2):
                    for y in range(-1, 2):
                        # Skip the current cell
                        if x == 0 and y == 0:
                            continue
                        
                        # Get the other cell
                        other_cell: Cell = self.get(i + x, j + y)
                        
                        # Check if the surrounding cell is different
                        if other_cell != current_cell:
                            current_cell.check_collision(other_cell)
