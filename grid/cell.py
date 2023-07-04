from typing import Any


# Cell class
class Cell(list[Any]):
    def __init__(self, values: list[Any] = []):
        super(Cell, self).__init__()
        [self.append(value) for value in values]
    
    # Update the cell objects
    def update(self, grid, other_cell: 'Cell') -> None:
        for obj_1 in self:
            self.remove(obj_1)
            grid.put(obj_1)
        
        for obj_2 in other_cell:
            other_cell.remove(obj_2)
            grid.put(obj_2)

    # Check for collisions
    def check_collisions(self, grid, other_cell: 'Cell') -> None:
        # Iterate over all the objects in the current cell and the other cell
        for obj_1 in self:
            for obj_2 in other_cell:
                if obj_1 == obj_2:
                    continue
                    
                # Handle the collision and update the cells
                obj_1.handle_collision(obj_2)
        
        # Update the cells
        self.update(grid, other_cell)
