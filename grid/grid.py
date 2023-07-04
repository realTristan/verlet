from testing.config import WIDTH, HEIGHT
from physics import Vector2D
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
    def get(self, x: int, y: int) -> Cell | None:
        return self.grid[x][y] if x >= 0 and y >= 0 and \
            x < self.width and y < self.height else None

    # Put an object into the grid
    def put(self, obj: Any, position: Vector2D) -> None:
        # Get the cell
        x: int = round(position.x / self.cell_size)
        y: int = round(position.y / self.cell_size)
        cell: Cell | None = self.get(x, y)
        if cell is None:
            return

        # Add the object to the cell
        cell.objects.append(obj)

    # Find all the collisions for each cell in the grid
    def find_collisions(self) -> None:
        # Iterate over all cells
        for i in range(0, self.width - 2, 1):
            for j in range(0, self.height - 2, 1):
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
                        current_cell.check_collision(self, other_cell)
