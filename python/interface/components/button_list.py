import pygame
from .button import Button
from typing import Any


# ButtonListItem class
class ButtonListItem(object):
    def __init__(self, item: Any, button: Button) -> None:
        self.item: Any = item
        self.button: Button = button


# ButtonList class
class ButtonList:
    def __init__(self) -> None:
        self.items: list[ButtonListItem] = []

    # Draw the list
    def draw(self, screen: pygame.Surface, items: list) -> None:
        self.items = []
        for i, item in enumerate(items):
            item_obj: ButtonListItem = ButtonListItem(
                item,
                Button(
                    width=120,
                    height=30,
                    position=(10, 120 + i * 40),
                    text=item.__class__.__name__,
                    color=(255, 255, 255),
                ).draw(screen),
            )

            # Append the item
            self.items.append(item_obj)

    # Return the clicked items
    def clicked(self, event: pygame.event.Event) -> list[ButtonListItem]:
        return [i for i in self.items if i.button.clicked(event)]

    # Remove the item
    def remove(self, item: ButtonListItem) -> None:
        self.items.remove(item)
