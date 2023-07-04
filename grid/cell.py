from typing import Any


class Cell(list[Any]):
    def __init__(self): # , index: tuple[int, int]
        super(Cell, self).__init__()
        # self.index: tuple[int, int] = index

    # Update the cell based on the new positions
    # def update(self, grid, obj: Any, other_obj: Any) -> None:
    #    if obj in self and self.index != grid.calculate_cell_index(
    #        obj.current_position
    #    ):
    #        self.remove(obj)
    #        grid.put(obj)
    #
    #    if other_obj in self and self.index != grid.calculate_cell_index(
    #        other_obj.current_position
    #    ):
    #        self.remove(other_obj)
    #        grid.put(other_obj)

    # Check for collisions
    def check_collisions(self, other_cell: "Cell") -> None:
        # Iterate over all the objects in the current cell and the other cell
        for obj_1 in self:
            for obj_2 in other_cell:
                if obj_1 == obj_2:
                    continue

                # Handle the collision and update the cells
                obj_1.handle_collision(obj_2)
                # self.update(grid, obj_1, obj_2)
