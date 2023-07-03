import threading


# Threads class for performance improvements
class Threads:
    def __init__(self):
        self.lock: threading.Lock = threading.Lock()
    
    
    # Run the thread
    def run(self, target, args: tuple):
        self.lock.acquire()
        t = threading.Thread(target=target, args=args, daemon=True)
        t.start()
        t.join()
        self.lock.release()

