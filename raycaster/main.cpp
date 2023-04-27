#include <SFML/Graphics.hpp>

#include "camera.hpp"
#include "eventhandler.hpp"
#include "renderer.hpp"
#include "vector.hpp"

int main()
{
    sf::RenderWindow window(sf::VideoMode(640, 480), "Raycaster");

    EventHandler event_handler(window);
    Camera camera(event_handler, Vector(22, 12), Vector(-1, 0), Vector(0, 0.66), 0.015, 0.003);
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
