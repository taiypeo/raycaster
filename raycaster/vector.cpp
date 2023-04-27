#include <cmath>
#include <ostream>

#include "vector.hpp"

Vector::Vector(double x, double y) : x(x), y(y) {}

Vector &Vector::operator+=(const Vector &other)
{
    x += other.x;
    y += other.y;
    return *this;
}

Vector &Vector::operator-=(const Vector &other)
{
    x -= other.x;
    y -= other.y;
    return *this;
}

Vector &Vector::operator*=(double constant)
{
    x *= constant;
    y *= constant;
    return *this;
}

Vector Vector::rotate(double angle) const
{
    double new_x = cos(angle) * x - sin(angle) * y;
    double new_y = sin(angle) * x + cos(angle) * y;
    return Vector(new_x, new_y);
}

double Vector::norm() const
{
    return sqrt(x * x + y * y);
}

Vector operator+(const Vector &vec1, const Vector &vec2)
{
    Vector result(vec1);
    result += vec2;
    return result;
}

Vector operator-(const Vector &vec1, const Vector &vec2)
{
    Vector result(vec1);
    result -= vec2;
    return result;
}

Vector operator*(const Vector &vec, double constant)
{
    Vector result(vec);
    result *= constant;
    return result;
}

Vector operator*(double constant, const Vector &vec)
{
    return vec * constant;
}

std::ostream &operator<<(std::ostream &out, const Vector &vec)
{
    out << "Vec(" << vec.x << ", " << vec.y << ")";
    return out;
}
