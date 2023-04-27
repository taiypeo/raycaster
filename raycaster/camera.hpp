#ifndef _CAMERA_HPP
#define _CAMERA_HPP

#include <ostream>

#include "vector.hpp"

struct Camera
{
    Vector pos, dir, plane;

    Camera(const Vector &pos, const Vector &dir, const Vector &plane);
};

std::ostream &operator<<(std::ostream &out, const Camera &cam);

#endif
