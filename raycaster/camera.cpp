#include <exception>
#include <ostream>

#include "camera.hpp"

Camera::Camera(const Vector &pos, const Vector &dir, const Vector &plane) : pos(pos), dir(dir), plane(plane)
{
    if (!dir.is_orthogonal(plane))
    {
        throw std::runtime_error("dir is not orthogonal to plane");
    }
}

std::ostream &operator<<(std::ostream &out, const Camera &cam)
{
    out << "Camera(pos=" << cam.pos << ", dir=" << cam.dir << ", plane=" << cam.plane << ")";
    return out;
}
