from testing.config import WIDTH, HEIGHT
from physics import Vector2D
from typing import Any
from .cell import Cell
from utils import Threads


# Grid class
class Grid(object):
    def __init__(self, cell_size: int = 100):
        self.cell_size: int = cell_size
        self.width: int = WIDTH // self.cell_size
        self.height: int = HEIGHT // self.cell_size
        self.grid: list[list[Cell]] = [
            [Cell() for _ in range(self.width)] for _ in range(self.height)
        ]  # If cell index, pass (i, j)

    # Reset the grid
    def reset(self) -> None:
        self.grid = [
            [Cell() for _ in range(self.width)] for _ in range(self.height)
        ]  # If cell index, pass (i, j)

    # Get a cell from the grid
    def get(self, x: int, y: int) -> Cell | None:
        if x > self.width or y > self.height:
            return None
        return self.grid[y][x]

    # Get the cell index from a position
    def calculate_cell_index(self, position: Vector2D) -> tuple[int, int]:
        return (int(position.x // self.cell_size), int(position.y // self.cell_size))

    # Put an object into the grid
    def put(self, obj: Any) -> None:
        x, y = self.calculate_cell_index(obj.current_position)
        cell: Cell | None = self.get(x, y)
        cell.append(obj) if cell is not None else None

    # Fill the grid with objects
    def fill(self, objects: list[Any]) -> None:
        [self.put(obj) for obj in objects]

    # Find all the collisions for each cell in the grid
    def find_collisions(self, threads: int = -1) -> None:
        # Initialize the threads
        threads: Threads | None = Threads(threads) if threads != -1 else None

        # Iterate over all cells
        def run() -> None:
            for i in range(0, self.width - 1):
                for j in range(0, self.height - 1):
                    # Get the current cell
                    current_cell: Cell | None = self.get(i, j)
                    if current_cell is None:
                        return

                    # Check all the cells around the current cell
                    for x in range(i - 1, i + 2):
                        for y in range(j - 1, j + 2):
                            # Get the cell
                            other_cell: Cell | None = self.get(x, y)
                            if other_cell is None:
                                continue

                            # Check for collisions
                            current_cell.check_collisions(other_cell)

        # Start the threads if they exist, otherwise just run the function
        threads.start(target=run, timeout=1) if threads is not None else run()
