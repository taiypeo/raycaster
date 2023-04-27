#include <iostream>

#include <SFML/Graphics.hpp>

#include "camera.hpp"
#include "eventhandler.hpp"
#include "renderer.hpp"
#include "vector.hpp"

int main()
{
    sf::RenderWindow window(sf::VideoMode(200, 200), "SFML works!");
    EventHandler event_handler(window);

    Camera camera(event_handler, Vector(1.5, 3.5), Vector(1, 0), Vector(0, 1), 0.1, 0.1);
    std::cout << camera << std::endl;

    Renderer renderer(window, camera, 100);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
        }

        event_handler.handle();
        renderer.render();
    }

    return 0;
}
