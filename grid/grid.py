from ..testing.config import WIDTH, HEIGHT
from ..physics import Vector2D
from typing import Any
from .cell import Cell

# Grid class
class Grid:
    def __init__(self, cell_size: int = 100):
        self.cell_size: int = cell_size
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
        for i in range(0, self.width - 1, 1):
            for j in range(0, self.height - 1, 1):
                # Get the current cell
                current_cell: Cell = self.get(i, j)
                
                # Get the cell infront
                front_cell: Cell = self.get(i, j+1)
                self = front_cell.check_collision(self, current_cell)
                
                # Check if at bottom grid row
                if j+1 > self.height:
                    continue
                
                # Iterate over the two cells below
                for k in range(0, 2, 1):
                    below_cell: Cell = self.get(i, j+k)
                    self = below_cell.check_collision(self, current_cell)
