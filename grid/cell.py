from typing import Any
import numpy as np


# Cell class
class Cell():
    def __init__(self, objects: list[Any] = []):
        super(Cell, self).__init__()
        self.objects = np.array(objects, dtype=object)

    # Update the cell objects
    def update(self, grid, other_cell: 'Cell') -> None:
        for obj_1 in self.objects:
            i = np.where(self.objects == obj_1)
            self.objects = np.delete(self.objects, i)
            grid.put(obj_1)

        for obj_2 in other_cell.objects:
            i = np.where(other_cell.objects == obj_2)
            other_cell.objects = np.delete(other_cell.objects, i)
            grid.put(obj_2)

    # Check for collisions
    def check_collisions(self, grid, other_cell: 'Cell') -> None:
        # Iterate over all the objects in the current cell and the other cell
        for obj_1 in self.objects:
            for obj_2 in other_cell.objects:
                if obj_1 == obj_2:
                    continue

                # Handle the collision and update the cells
                obj_1.handle_collision(obj_2)

        # Update the cells
        self.update(grid, other_cell)
