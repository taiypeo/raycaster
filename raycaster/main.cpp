#include <iostream>

#include <SFML/Graphics.hpp>

#include "eventhandler.hpp"

void sample_w_subscriber()
{
    std::cout << "W pressed!" << std::endl;
}

void sample_d_subscriber()
{
    std::cout << "D pressed!" << std::endl;
}

int main()
{
    sf::RenderWindow window(sf::VideoMode(200, 200), "SFML works!");
    EventHandler event_handler(window);
    event_handler.subscribe(ActionKey::FORWARD, sample_w_subscriber);
    event_handler.subscribe(ActionKey::TURN_RIGHT, sample_d_subscriber);

    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
            else if (event.type == sf::Event::KeyPressed)
            {
                event_handler.handle(event.key.code);
            }
        }

        window.clear();
        window.draw(shape);
        window.display();
    }

    return 0;
}
