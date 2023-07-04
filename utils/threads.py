from threading import Thread
from typing import Callable
import time


# Threads class
class Threads(object):
    def __init__(self, thread_count: int, target: Callable):
        self.thread_count: int = thread_count
        self.target: Callable = target
        self.threads: list[Thread] = [Thread(target=self.target) for _ in range(self.thread_count)]
        self.inactive: list[Thread] = []
    
    # Start threads
    def start(self):
        for _ in range(self.threads):
            # Pop thread
            t: Thread = self.threads.pop()

            # Start thread
            t.start()
            t.join()

            # Append to inactive
            self.inactive.append(t)
    
    # Get inactive threads
    def get_inactives(self) -> list[Thread]:
        return [t for t in self.threads if not t.is_alive()]

    # Get thread
    def get(self, timeout: int) -> Thread | None:
        start_time: float = time.time()
        while len(self.threads) == 0:
            if start_time + timeout > time.time():
                return None
        return self.threads.pop()