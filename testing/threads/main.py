from utils import Threads
from threading import Thread


# Main function
def main():
    # Create threads
    threads: Threads = Threads(10)
    for _ in range(20):
        threads.start(target=print, args=("Hello", "World"), timeout=1)


# Run the program
main()