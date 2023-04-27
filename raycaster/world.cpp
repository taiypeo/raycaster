#include <array>
#include <stdexcept>
#include <vector>

#include "world.hpp"

World::World(
    const std::vector<std::vector<int>> &map,
    const std::vector<std::array<int, 3>> &colors) : map(map),
                                                     colors(colors)
{
    if (map.empty() || map[0].empty())
    {
        throw std::invalid_argument("map cannot be empty");
    }
}
