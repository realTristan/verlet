#include <iostream>
#include <interface/components/button.hpp>
#include <interface/components/button_list.hpp>
#include <physics/vector2d.hpp>

#ifndef INTERFACE_MENU_HPP
#define INTERFACE_MENU_HPP

class Menu
{
public:
    Button line_collider_button;
    Button circle_collider_button;

    Menu() {
        this->line_collider_button = Button(
            "Line Collider",
            Vec2D(10, 10),
            105,
            35,
            WHITE
        );
        this->circle_collider_button = Button(
            "Circle Collider",
            Vec2D(10, 60),
            105,
            35,
            WHITE
        );
    }

    // Draw the menu
    void draw(sf::RenderWindow *window) {
        this->circle_collider_button.draw(window);
        this->line_collider_button.draw(window);
    }
};

#endif // INTERFACE_MENU_HPP