from dataclasses import dataclass


# Colors class
@dataclass
class Colors:
    RED: tuple[int, int, int] = (255, 0, 0)
    GREEN: tuple[int, int, int] = (0, 255, 0)
    BLUE: tuple[int, int, int] = (0, 0, 255)
    WHITE: tuple[int, int, int] = (255, 255, 255)
    YELLOW: tuple[int, int, int] = (255, 255, 0)
    CYAN: tuple[int, int, int] = (0, 255, 255)
    MAGENTA: tuple[int, int, int] = (255, 0, 255)
    ORANGE: tuple[int, int, int] = (255, 165, 0)
    PURPLE: tuple[int, int, int] = (128, 0, 128)
    PINK: tuple[int, int, int] = (255, 192, 203)

    @staticmethod
    def to_hex(color: tuple[int, int, int]) -> str:
        return "#%02x%02x%02x" % color

    @staticmethod
    def to_rgb(color: str) -> tuple[int, int, int]:
        return tuple(int(color[i : i + 2], 16) for i in (0, 2, 4))

    @staticmethod
    def random_rgb() -> tuple[int, int, int]:
        import random

        return (random.randint(0, 255), random.randint(0, 255), random.randint(0, 255))

    @staticmethod
    def random_hex() -> str:
        return Colors.to_hex(Colors.random())

    @staticmethod
    def random() -> tuple[int, int, int]:
        import random

        return random.choice(
            [
                Colors.RED,
                Colors.GREEN,
                Colors.BLUE,
                Colors.WHITE,
                Colors.YELLOW,
                Colors.CYAN,
                Colors.MAGENTA,
                Colors.ORANGE,
                Colors.PURPLE,
                Colors.PINK,
            ]
        )
