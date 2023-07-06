from testing.config import WIDTH, HEIGHT
from physics import Vector2D
from typing import Any
from .cell import Cell
from utils import Threads
import numpy as np


# Grid class
class Grid():
    def __init__(self, cell_size: int = 100):
        self.cell_size: int = cell_size
        self.width: int = WIDTH // self.cell_size
        self.height: int = HEIGHT // self.cell_size
        self.grid: np.ndarray = np.array(
            [np.array([Cell([]) for _ in range(0, self.width)]) for _ in range(0, self.height)])

    # Reset the grid
    def reset(self) -> None:
        self.grid = np.array(
            [np.array([Cell([]) for _ in range(0, self.width)]) for _ in range(0, self.height)])

    # Deprecate an object from the grid
    def deprecate(self, obj: Any) -> None:
        x, y = self.calculate_cell_index(obj.current_position)
        cell: Cell | None = self.get(x, y)
        if cell is None:
            return
        cell.objects = np.delete(cell.objects, np.where(cell.objects == obj))

    # Get a cell from the grid
    def get(self, x: int, y: int) -> Cell | None:
        if x >= self.width or x < 0 or y >= self.height or y < 0:
            return None
        return self.grid[y][x]

    # Get the cell index from a position
    def calculate_cell_index(self, position: Vector2D) -> tuple[int, int]:
        return (int(position.x // self.cell_size), int(position.y // self.cell_size))

    # Put an object into the grid
    def put(self, obj: Any) -> None:
        x, y = self.calculate_cell_index(obj.current_position)
        cell: Cell | None = self.get(x, y)
        if cell is None:
            return
        cell.objects = np.append(cell.objects, obj)

    # Fill the grid with objects
    def fill(self, objects: list[Any]) -> None:
        [self.put(obj) for obj in objects]

    # Find all the collisions for each cell in the grid
    def find_collisions(self, threads: int = -1) -> None:  # type: ignore
        # Initialize the threads
        threads: Threads | None = Threads(threads) if threads != -1 else None

        # Iterate over all cells
        def run() -> None:
            for x in range(0, self.width):
                for y in range(0, self.height):
                    # Get the current cell
                    current_cell: Cell | None = self.get(x, y)
                    if current_cell is None:
                        continue

                    # Check all the cells around the current cell
                    for dx in range(x - 1, x + 2):
                        for dy in range(y - 1, y + 2):
                            # Get the cell
                            other_cell: Cell | None = self.get(dx, dy)
                            if other_cell is None:
                                continue

                            # Check for collisions
                            if len(current_cell.objects) > 0 or len(other_cell.objects) > 0:
                                current_cell.check_collisions(self, other_cell)

        # Start the threads if they exist, otherwise just run the function
        threads.start(target=run, timeout=1) if threads is not None else run()
