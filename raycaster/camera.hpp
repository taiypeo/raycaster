#ifndef _CAMERA_HPP
#define _CAMERA_HPP

#include <ostream>

#include "eventhandler.hpp"
#include "vector.hpp"

struct Camera
{
    Vector pos, dir, plane;

    Camera(
        EventHandler &handler,
        const Vector &pos,
        const Vector &dir,
        const Vector &plane,
        double speed,
        double rot_speed);
};

std::ostream &operator<<(std::ostream &out, const Camera &cam);

#endif
