#include <iostream>
#include<SFML/Graphics.hpp>

class Events
{
public:
    void check_close(sf::RenderWindow *window)
    {
        sf::Event event;
        while (window->pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
    }
};