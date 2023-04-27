#ifndef _EVENTHANDLER_HPP
#define _EVENTHANDLER_HPP

#include <functional>
#include <unordered_map>
#include <vector>

#include <SFML/Graphics.hpp>

enum ActionKey
{
    TURN_LEFT = sf::Keyboard::A,
    TURN_RIGHT = sf::Keyboard::D,
    FORWARD = sf::Keyboard::W,
    BACKWARD = sf::Keyboard::S,
};

class EventHandler
{
private:
    const sf::RenderWindow &window;
    std::unordered_map<ActionKey, std::vector<std::function<void()>>> subscribers;

public:
    EventHandler(const sf::RenderWindow &window);
    void subscribe(const ActionKey event, const std::function<void()> callback);
    void handle(const sf::Keyboard::Key key) const;
};

#endif
