#include <iostream>
#include <SFML/Graphics.hpp>
#include <utils/colors.hpp>
#include <vector>
#include <interface/components/button.hpp>
#include <physics/vector2d.hpp>

#ifndef INTERFACE_COMPONENTS_BUTTONS_LIST_HPP
#define INTERFACE_COMPONENTS_BUTTONS_LIST_HPP

template <typename T>
class ButtonList
{
private:
    Vec2D position;
    int button_width;
    int button_height;
    std::vector<Button *> buttons;
    Color button_color = WHITE;

public:
    ButtonList(
        Vec2D position,
        int button_width,
        int button_height,
        Color button_color = WHITE)
    {
        this->position = position;
        this->button_width = button_width;
        this->button_height = button_height;
        this->button_color = button_color;
    }

    // Draw the list of buttons
    void draw(sf::RenderWindow *window, std::vector<T> items)
    {
        int i = 0;
        for (T item : items)
        {
            // Get the button position
            Vec2D position = Vec2D(
                this->position.x, this->position.y + i * this->button_height);

            // Create the button
            Button button(
                std::to_string(item),
                position,
                this->button_width,
                this->button_height,
                this->button_color);

            // Draw the button
            button.draw(window);

            // Add the button to the list of buttons
            buttons.push_back(&button);

            // Increment the index
            i++;
        }
    }

    // Get the items of the buttons that are clicked
    /*
        Example: List of colliders (items) that you can add/remove to the scene

        // Variables
        vector<T> items = ...
        ButtonList<T> bl = ...

        // Clicked indices
        vector<int> indices = bl.get_clicked_indices(window);

        // Iterate over them
        for (int index : indices)
        {
            items.erase(items.begin() + index); // Remove the item from the list
        }
    */
    std::vector<int> get_clicked_indices(sf::RenderWindow &window)
    {
        std::vector<int> clicked_indices;
        int i = 0;
        for (Button *button : this->buttons)
        {
            if (button->is_clicked(window))
            {
                clicked_indices.push_back(i);
            }
            i++;
        }
        return clicked_indices;
    }
};

#endif // INTERFACE_COMPONENTS_BUTTONS_LIST_HPP