from threading import Thread
from typing import Callable
import time, threading


# Threads class
class Threads(object):
    def __init__(self, threads: int):
        self.threads: int = threads
        self.active: int = 0
        self.lock: threading.Lock = threading.Lock()

    # Run a thread
    def run(self, target: Callable, args: tuple, kwargs: dict) -> None:
        # Run the target
        self.lock.acquire()  # Acquire the lock
        target(*args, **kwargs)  # Run the target

        # Once finished...
        self.active -= 1  # Decrement the active count
        self.lock.release()  # Release the lock

    # Start a thread
    def start(
        self, target: Callable, args: tuple = (), kwargs: dict = {}, timeout: int = 60
    ) -> None:
        start_time: float = time.time()
        while self.active >= self.threads:
            if start_time + timeout > time.time():
                return None

        # Get the thread
        self.active += 1
        Thread(target=self.run, args=(target, args, kwargs)).start()
