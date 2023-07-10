#ifndef THREAD_HPP
#define THREAD_HPP

// Thread class
class Thread
{
public:
    Thread() = default;
    virtual ~Thread() = default;

    void start()
    {
        run();
    }

    virtual void run() = 0;
};

#endif