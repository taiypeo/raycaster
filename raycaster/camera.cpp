#include <exception>
#include <ostream>

#include "camera.hpp"
#include "eventhandler.hpp"

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
        throw std::runtime_error("dir is not orthogonal to plane");
    }

    handler.subscribe(
        ActionKey::FORWARD,
        [this, speed]()
        { this->pos += Vector(0, speed); });
    handler.subscribe(
        ActionKey::BACKWARD,
        [this, speed]()
        { this->pos += Vector(0, -speed); });
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
