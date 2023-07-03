import threading


# Threads class for performance improvements
class Threads:
    def __init__(self):
        self.lock: threading.Lock = threading.Lock()
    
    
    # Run the thread
    def run(self, target, args: tuple):
        def thread():
            self.lock.acquire()
            target(*args)
            self.lock.release()
        
        t = threading.Thread(target=thread, args=args, daemon=True)
        t.start()
        t.join()

