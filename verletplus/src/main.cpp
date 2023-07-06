#include <SFML/Graphics.hpp>
#include "objects/line.cpp"

int main()
{
    // Initialize a new window
    sf::RenderWindow window(sf::VideoMode(800, 600), "verlet");

    // Create a new line
    Line line = Line(Vector2D(50, 50), 100, 90, Colors().WHITE);
    
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        line.draw(&window);
        window.display();
    }

    return 0;
}
