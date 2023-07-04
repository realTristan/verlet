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
                
                # Remove the objects from the cell then readd them to their
                # new appropriate cells
                if obj_1 in self.objects:
                    grid.put(obj_1, p1)
                    self.objects.remove(obj_1)
                    
                if obj_2 in other_cell.objects:
                    grid.put(obj_2, p2)
                    other_cell.objects.remove(obj_2)
        
        # Return the updated grid
        return grid
                
                