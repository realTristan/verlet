from testing.config import WIDTH, HEIGHT
from physics import Vector2D
from typing import Any
from .cell import Cell
import math

# Grid class
class Grid:
    def __init__(self, cell_size: int = 50):
        self.cell_size: int = cell_size
        self.width: int = WIDTH // self.cell_size
        self.height: int = HEIGHT // self.cell_size
        self.grid: list[list[Cell]] = [
            [Cell() for _ in range(self.height)] for _ in range(self.width)]

    # Get a cell from the grid
    def get(self, x: int, y: int) -> Cell | None:
        return self.grid[x][y] if x >= 0 and y >= 0 and \
            x < WIDTH and y < HEIGHT else None

    # Put an object into the grid
    def put(self, obj: Any, position: Vector2D) -> None:
        # Get the cell
        x: int = int((math.floor(position.x / self.cell_size) + 
                      math.floor(position.y / self.cell_size)) * self.cell_size)
        y: int = int((math.floor(position.x / self.cell_size) -
                      math.floor(position.y / self.cell_size)) * self.cell_size)

        # Get the cell
        cell: Cell | None = self.get(x, y)
        
        # Add the object to the cell
        cell.append(obj) if cell is not None else None

    # Find all the collisions for each cell in the grid
    def find_collisions(self) -> None:
        # Iterate over all cells
        for i in range(1, self.width - 2, 1):
            for j in range(1, self.height - 2, 1):
                # Get the current cell
                current_cell: Cell | None = self.get(i, j)
                if current_cell is None:
                    continue

                # Check all the cells around the current cell
                for x in range(i - 1, i + 2, 1):
                    for y in range(j - 1, j + 2, 1):
                        # Get the cell
                        other_cell: Cell | None = self.get(x, y)
                        if other_cell is None:
                            continue

                        # Check the collision
                        current_cell.check_collisions(other_cell)
