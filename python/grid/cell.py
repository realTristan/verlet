from typing import Any
import numpy as np
import time

# Cell class
class Cell():
    def __init__(self, objects: list[Any] = []):
        super(Cell, self).__init__()
        self.objects = np.array(objects, dtype=object)
        
        
    # Update the cell objects
    def update(self, grid, other_cell: 'Cell') -> None:
        # Iterate over all the objects in the current cell
        tot_popped: int = 0
        for i in range(len(self.objects)):
            index: int = i + tot_popped
            if index >= len(self.objects):
                break
            
            # Get the object
            obj: Any = self.objects[index]
            
            # Update the cell and grid
            prev_len: int = len(self.objects)
            self.objects = np.delete(self.objects, index)
            if len(self.objects) != prev_len:
                tot_popped += 1
                grid.put(obj)
        
        # Iterate over all the objects in the other cell
        tot_popped = 0     
        for i in range(len(other_cell.objects)):
            index: int = i + tot_popped
            if index >= len(other_cell.objects):
                break
            
            # Get the object
            obj: Any = other_cell.objects[index]
            
            # Update the cell and grid
            prev_len: int = len(other_cell.objects)
            other_cell.objects = np.delete(other_cell.objects, index)
            if len(other_cell.objects) != prev_len:
                tot_popped += 1
                grid.put(obj)
                
    
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
