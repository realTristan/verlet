#ifndef TIME_HPP
#define TIME_HPP

#include <ctime>

class Time
{
public:
    // Get the current time
    static float now()
    {
        return (float)clock() / CLOCKS_PER_SEC;
    }
};

#endif