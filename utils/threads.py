from threading import Thread
from typing import Callable
import time, threading

# Threads class
class Threads(object):
    def __init__(self, thread_count: int, target: Callable):
        self.thread_count: int = thread_count
        self.target: Callable = target
        self.threads: list[Thread] = [Thread(target=self.run) for _ in range(self.thread_count)]
        self.inactive: list[Thread] = []
        self.lock: threading.Lock = threading.Lock()

    # Run threads
    def run(self) -> None:
        # Acquire the lock
        self.lock.acquire()

        # Run the target
        self.target()

        # Get the working thread
        thread: Thread = threading.current_thread()

        # Remove from inactive and append to threads
        self.threads.append(thread)
        self.inactive.remove(thread)

        # Release the lock
        self.lock.release()
    
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
        
        # Get the thread
        return self.threads.pop()
