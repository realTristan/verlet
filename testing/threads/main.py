from utils import Threads
from threading import Thread


# Main function
def main():
    # Create threads
    threads: Threads = Threads(10, lambda: print("Hello, world!"))
    threads.start_all()

    # Get a thread
    thread: Thread | None = threads.get(10)
    if thread is not None:
        print("Got thread!")
    else:
        print("No thread here..")


# Run the program
main()