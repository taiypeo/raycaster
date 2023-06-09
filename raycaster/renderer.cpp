#include <cmath>

#include "camera.hpp"
#include "renderer.hpp"
#include "utils.hpp"
#include "vector.hpp"
#include "world.hpp"

Renderer::Renderer(
    sf::RenderWindow &window,
    const Camera &camera,
    double max_dist,
    const World &world) : window(window),
                          camera(camera),
                          max_dist(max_dist),
                          world(world)
{
    const auto window_size = window.getSize();
    window_width = window_size.x;
    window_height = window_size.y;
}

double get_closest_wall_component(double pos_component, double dir_component)
{
    const double closest = std::floor(pos_component);
    if (dir_component > 0)
    {
        return closest + 1;
    }

    if (is_close(pos_component, closest))
    {
        return closest - 1;
    }

    return closest;
}

bool move_to_wall(Vector &cur_pos, const Vector &pix_dir)
{
    const double closest_x = get_closest_wall_component(cur_pos.x, pix_dir.x),
                 closest_y = get_closest_wall_component(cur_pos.y, pix_dir.y);

    bool is_vertical;
    if (is_close(pix_dir.x, 0.))
    {
        cur_pos.y = closest_y;
        is_vertical = false;
    }
    else if (is_close(pix_dir.y, 0.))
    {
        cur_pos.x = closest_x;
        is_vertical = true;
    }
    else
    {
        Vector delta_scaled_x(pix_dir), delta_scaled_y(pix_dir);
        delta_scaled_x *= (closest_x - cur_pos.x) / pix_dir.x;
        delta_scaled_y *= (closest_y - cur_pos.y) / pix_dir.y;

        if (delta_scaled_x.norm() < delta_scaled_y.norm())
        {
            cur_pos.x = closest_x;
            cur_pos.y += delta_scaled_x.y;
            is_vertical = true;
        }
        else
        {
            cur_pos.x += delta_scaled_y.x;
            cur_pos.y = closest_y;
            is_vertical = false;
        }
    }

    return is_vertical;
}

int get_cell(const Vector &cur_pos, const Vector &pix_dir, bool is_vertical, const World &world)
{
    int world_x = static_cast<int>(cur_pos.x), world_y = static_cast<int>(cur_pos.y);

    if (is_vertical)
    {
        if (pix_dir.x < 0)
        {
            --world_x;
        }
    }
    else
    {
        if (pix_dir.y < 0)
        {
            --world_y;
        }
    }

    if (world_x < 0 || world_x >= world.map[0].size() || world_y < 0 || world_y >= world.map.size())
    {
        return 0;
    }

    return world.map[world_x][world_y];
}

void Renderer::render()
{
    window.clear();

    for (int pixel = 0; pixel < window_width; ++pixel)
    {
        const Vector pix_dir = camera.dir + (2 * static_cast<double>(pixel) / window_width - 1) * camera.plane;
        Vector cur_pos = camera.pos;
        int cell = 0;
        double dist = 0;
        bool is_vertical = false;
        while (dist < max_dist)
        {
            is_vertical = move_to_wall(cur_pos, pix_dir);
            dist = (cur_pos - camera.pos).norm();
            cell = get_cell(cur_pos, pix_dir, is_vertical, world);
            if (cell != MapValue::EMPTY)
            {
                break;
            }
        }

        if (cell == MapValue::EMPTY || dist >= max_dist)
        {
            continue;
        }

        const double cos_angle = camera.plane.cos_angle(pix_dir),
                     offset = cos_angle * dist,
                     perp_dist = std::sqrt(dist * dist - offset * offset);

        const double line_height = std::floor(window_height / perp_dist),
                     line_top = window_height / 2. - line_height / 2.,
                     line_bottom = window_height / 2. + line_height / 2.;

        const double color_scaling_factor = is_vertical ? 1 : 0.5;
        sf::Vertex line[] = {
            sf::Vertex(sf::Vector2f(pixel, line_top)),
            sf::Vertex(sf::Vector2f(pixel, line_bottom))};
        for (auto &v : line)
        {
            v.color = sf::Color(
                world.colors[cell][0] * color_scaling_factor,
                world.colors[cell][1] * color_scaling_factor,
                world.colors[cell][2] * color_scaling_factor);
        }

        window.draw(line, 2, sf::Lines);
    }

    window.display();
}
