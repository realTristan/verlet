#ifndef TIME_H
#define TIME_H

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

#endif // TIME_H