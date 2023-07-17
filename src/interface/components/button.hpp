#ifndef INTERFACE_COMPONENTS_BUTTON_HPP
#define INTERFACE_COMPONENTS_BUTTON_HPP

#include <interface/components/text.hpp>
#include <physics/vector2d.h>
#include <SFML/Graphics.hpp>
#include <utils/colors.hpp>

class Button
{
private:
    std::string text;
    Vec2D<float> position;
    int width;
    int height;
    Color color = WHITE;

public:
    Button() {
        this->text = "";
        this->position = Vec2D<float>(0.0f, 0.0f);
        this->width = 0;
        this->height = 0;
    }
    Button(
        std::string text,
        Vec2D<float> position,
        int width,
        int height,
        Color color = WHITE)
    {
        this->text = text;
        this->position = position;
        this->width = width;
        this->height = height;
        this->color = color;
    }

    // Draw the button
    void draw(sf::RenderWindow *window)
    {
        // Create the button shape
        sf::RectangleShape button(sf::Vector2f(this->width, this->height));
        button.setPosition(sf::Vector2f(this->position.x, this->position.y));
        button.setFillColor(Colors::to_sf(this->color));

        // Create the button text
        Vec2D<float> text_position = Vec2D<float>(
            this->position.x + this->width / 2.0f - text.length() - 15.0f,
            this->position.y + this->height / 2.0f - 5.0f);

        // Draw the text
        Text *text = new Text(this->text, text_position, 10, BLACK);

        // Draw the text and button shape
        window->draw(button);
        text->draw(window);
    }

    // Check if the button is clicked
    bool is_clicked(sf::RenderWindow *window)
    {
        sf::Vector2i mouse_position = sf::Mouse::getPosition(*window);
        sf::Vector2f button_position = sf::Vector2f(this->position.x, this->position.y);
        sf::Vector2f button_size = sf::Vector2f(this->width, this->height);
        sf::FloatRect button_rect = sf::FloatRect(button_position, button_size);
        return button_rect.contains(mouse_position.x, mouse_position.y) && sf::Mouse::isButtonPressed(sf::Mouse::Left);
    }
};

#endif // INTERFACE_COMPONENTS_BUTTON_HPP