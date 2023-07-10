#ifndef WINDOW_HPP
#define WINDOW_HPP

#include <testing/config.hpp>
#include <SFML/Graphics.hpp>

class Window : public sf::RenderWindow
{
public:
    int width;
    int height;
    std::string title;
    int fps;

    Window(
        int width = WINDOW_WIDTH,
        int height = WINDOW_HEIGHT,
        std::string title = WINDOW_TITLE,
        int fps = FRAMERATE_LIMIT
    ) : sf::RenderWindow(sf::VideoMode(width, height), title)
    {
        this->setFramerateLimit(fps);
        this->width = width;
        this->height = height;
        this->title = title;
        this->fps = fps;
    }
};

#endif // WINDOW_HPP