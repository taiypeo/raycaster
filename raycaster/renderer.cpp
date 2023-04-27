#include "camera.hpp"
#include "renderer.hpp"
#include "utils.hpp"
#include "vector.hpp"

Renderer::Renderer(sf::RenderWindow &window, const Camera &camera, double max_dist) : window(window),
                                                                                      camera(camera),
                                                                                      max_dist(max_dist)
{
    const auto window_size = window.getSize();
    window_width = window_size.x;
    window_height = window_size.y;
}

void Renderer::render()
{
    window.clear();

    for (int pixel = 0; pixel < window_width; ++pixel)
    {
        const Vector pix_dir = camera.dir - camera.plane + static_cast<double>(pixel) / window_width * camera.plane;
        Vector cur_pos = camera.pos;
        int cell = 0;
        double dist = 0;
        while (dist < max_dist)
        {
            int closest_x = static_cast<int>(cur_pos.x);
            if (camera.dir.x > 0)
            {
                ++closest_x;
            }
            else if (camera.dir.x <= 0 && is_close(cur_pos.x, closest_x))
            {
                --closest_x;
            }
            int closest_y = static_cast<int>(cur_pos.y);
            if (camera.dir.y > 0)
            {
                ++closest_y;
            }
            else if (camera.dir.y <= 0 && is_close(cur_pos.y, closest_y))
            {
                --closest_y;
            }

            Vector dir_x_scaled(pix_dir), dir_y_scaled(pix_dir);
            dir_x_scaled *= (closest_x - cur_pos.x) / pix_dir.x;
            dir_y_scaled *= (closest_y - cur_pos.y) / pix_dir.y;
            if (dir_x_scaled.norm() < dir_y_scaled.norm())
            {
                cur_pos.x = closest_x;
                cur_pos.y += dir_x_scaled.y;
            }
            else
            {
                cur_pos.x += dir_y_scaled.x;
                cur_pos.y = closest_y;
            }

            dist = (cur_pos - camera.pos).norm();
            cell = WORLD[static_cast<int>(cur_pos.x)][static_cast<int>(cur_pos.y)];
            if (cell != 0)
            {
                break;
            }
        }

        if (cell == 0 || dist >= max_dist)
        {
            continue;
        }

        const double line_height = -window_height / max_dist * dist + window_height,
                     line_top = window_height / 2. - line_height / 2.,
                     line_bottom = window_height / 2. + line_height / 2.;

        sf::Vertex line[] = {
            sf::Vertex(sf::Vector2f(pixel, line_top)),
            sf::Vertex(sf::Vector2f(pixel, line_bottom))};
        for (auto &v : line)
        {
            v.color = sf::Color(COLORS[cell][0], COLORS[cell][1], COLORS[cell][2]);
        }

        window.draw(line, 2, sf::Lines);
    }

    window.display();
}
