#ifndef TESTING_EVENTS_HPP
#define TESTING_EVENTS_HPP

#include <SFML/Graphics.hpp>

class Events
{
public:
    static void check_close(sf::RenderWindow *window)
    {
        sf::Event event;
        while (window->pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window->close();
        }
    }
};

#endif