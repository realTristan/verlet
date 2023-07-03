from typing import Any

class Cell:
    def __init__(self):
        self.objects: list[Any] = []

    # Check if the objects in the cell are colliding
    def check_collision(self, other_cell: 'Cell'):
        for obj_1 in self.objects:
            for obj_2 in other_cell.objects:
                if obj_1 == obj_2:
                    continue
                
                if obj_1.collides(obj_2):
                    pass
                    # handle the collision