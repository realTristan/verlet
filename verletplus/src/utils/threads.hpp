#include <iostream>

#ifndef THREAD_HPP
#define THREAD_HPP

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

#endif