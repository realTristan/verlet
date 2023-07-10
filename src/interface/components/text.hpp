#ifndef INTERFACE_COMPONENTS_TEXT_HPP
#define INTERFACE_COMPONENTS_TEXT_HPP

#include <physics/vector2d.hpp>
#include <SFML/Graphics.hpp>
#include <utils/window.hpp>
#include <utils/colors.hpp>

class Text
{
private:
    std::string text;
    Vec2D position;
    int size;
    Color color = WHITE;

public:
    Text(std::string text, Vec2D position, int size, Color color = WHITE)
    {
        this->text = text;
        this->position = position;
        this->size = size;
        this->color = color;
    }

    // Draw the text
    void draw(Window *window)
    {
        sf::Font font;
        font.loadFromFile("assets/fonts/arial.ttf");
        sf::Text text(this->text, font);
        text.setCharacterSize(this->size);
        text.setFillColor(Colors::to_sf(this->color));
        text.setPosition(sf::Vector2f(this->position.x, this->position.y));
        window->draw(text);
    }

    // Set the text
    void set_text(std::string text) {
        this->text = text;
    }
};

#endif // INTERFACE_COMPONENTS_TEXT_HPP