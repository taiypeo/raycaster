#include <cmath>
#include <ostream>

#include "vector.hpp"

constexpr double EPS = 1e-6;

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
    Vector result(*this);
    result.inplace_rotate(angle);
    return result;
}

Vector &Vector::inplace_rotate(double angle)
{
    double new_x = std::cos(angle) * x - std::sin(angle) * y;
    double new_y = std::sin(angle) * x + std::cos(angle) * y;
    x = new_x;
    y = new_y;
    return *this;
}

double Vector::norm() const
{
    return std::sqrt(x * x + y * y);
}

bool Vector::is_orthogonal(const Vector &other) const
{
    return std::abs(x * other.x + y * other.y) < EPS;
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
