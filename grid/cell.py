from typing import Any

class Cell:
    def __init__(self):
        self.objects: list[Any] = []

    # Check if the objects in the cell are colliding
    def check_collision(self, grid, other_cell: 'Cell'):
        for obj_1 in self.objects:
            for obj_2 in other_cell.objects:
                # Skip if they're the same objects
                if obj_1 == obj_2:
                    continue
                
                # Get the new positions of the objects
                p1, p2 = obj_1.handle_collision(obj_2)
                
                # Remove the objects from the cell so that they can be
                # added to their new cells
                self.objects.remove(obj_1)
                other_cell.objects.remove(obj_2)
                
                # Put the objects into their new grid cells
                grid.put(obj_1, p1)
                grid.put(obj_2, p2)
        
        # Return the updated grid
        return grid
                
                