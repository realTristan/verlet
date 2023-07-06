#include <iostream>

class Thread
{
public:
    Thread() = default;
    virtual ~Thread() = default;

    void start()
    {
        std::cout << "Thread::start()" << std::endl;
        run();
    }

    virtual void run() = 0;
};