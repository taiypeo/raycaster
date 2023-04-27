#ifndef _WORLD_HPP
#define _WORLD_HPP

#include <array>
#include <vector>

enum MapValue
{
    EMPTY
};

struct World
{
    const std::vector<std::vector<int>> &map;
    const std::vector<std::array<int, 3>> &colors;

    World(const std::vector<std::vector<int>> &map, const std::vector<std::array<int, 3>> &colors);
};

#endif
