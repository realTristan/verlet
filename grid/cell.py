from typing import Any

class Cell(list[Any]):
    def __init__(self):
        super(Cell, self).__init__()
    
    # Check for collisions
    def check_collisions(self, other_cell: 'Cell') -> None:
        # Iterate over all the objects in the current cell
        for obj in self:
            # Iterate over all the objects in the other cell
            for other_obj in other_cell:
                # Check if the objects are the same
                if obj == other_obj:
                    continue
                
                # Check if the objects are colliding
                obj.handle_collision(other_obj)
                
                