#include "eventhandler.hpp"

EventHandler::EventHandler(const sf::RenderWindow &window) : window(window) {}

void EventHandler::subscribe(const ActionKey event, const std::function<void()> callback)
{
    if (subscribers.find(event) == subscribers.end())
    {
        subscribers[event] = std::vector<std::function<void()>>(1, callback);
    }
    else
    {
        subscribers[event].push_back(callback);
    }
}

void EventHandler::handle(const sf::Keyboard::Key key) const
{
    const auto action_key = ActionKey(key);
    if (subscribers.find(action_key) == subscribers.end())
    {
        return;
    }

    for (const auto callback : subscribers.at(action_key))
    {
        callback();
    }
}
