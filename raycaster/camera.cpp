#include <stdexcept>
#include <ostream>

#include "camera.hpp"
#include "eventhandler.hpp"
#include "utils.hpp"

Camera::Camera(
    EventHandler &handler,
    const Vector &pos,
    const Vector &dir,
    const Vector &plane,
    double speed,
    double rot_speed) : pos(pos),
                        dir(dir),
                        plane(plane)
{
    if (!dir.is_orthogonal(plane))
    {
        throw std::invalid_argument("dir is not orthogonal to plane");
    }

    if (is_close(dir.x, 0.) && is_close(dir.y, 0.))
    {
        throw std::invalid_argument("dir cannot be a zero vector");
    }

    handler.subscribe(
        ActionKey::FORWARD,
        [this, speed]()
        { this->pos += speed / this->dir.norm() * this->dir; });
    handler.subscribe(
        ActionKey::BACKWARD,
        [this, speed]()
        { this->pos -= speed / this->dir.norm() * this->dir; });
    handler.subscribe(
        ActionKey::TURN_LEFT,
        [this, rot_speed]()
        { this->dir.inplace_rotate(rot_speed); this->plane.inplace_rotate(rot_speed); });
    handler.subscribe(
        ActionKey::TURN_RIGHT,
        [this, rot_speed]()
        { this->dir.inplace_rotate(-rot_speed); this->plane.inplace_rotate(-rot_speed); });
}

std::ostream &operator<<(std::ostream &out, const Camera &cam)
{
    out << "Camera(pos=" << cam.pos << ", dir=" << cam.dir << ", plane=" << cam.plane << ")";
    return out;
}
