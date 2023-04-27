#ifndef _RENDERER_HPP
#define _RENDERER_HPP

#include <SFML/Graphics.hpp>

#include "camera.hpp"
#include "world.hpp"

class Renderer
{
private:
    sf::RenderWindow &window;
    const Camera &camera;
    const World &world;
    int window_width, window_height;
    const double max_dist;

public:
    Renderer(
        sf::RenderWindow &window,
        const Camera &camera,
        double max_dist,
        const World &world);
    void render();
};

#endif
