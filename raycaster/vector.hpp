#ifndef _VECTOR_HPP
#define _VECTOR_HPP

#include <ostream>

struct Vector
{
    double x, y;

    Vector(double x, double y);

    Vector &operator+=(const Vector &other);
    Vector &operator-=(const Vector &other);
    Vector &operator*=(double constant);

    Vector rotate(double angle) const;
    double norm() const;
};

Vector operator+(const Vector &vec1, const Vector &vec2);
Vector operator-(const Vector &vec1, const Vector &vec2);
Vector operator*(const Vector &vec, double constant);
Vector operator*(double constant, const Vector &vec);

std::ostream &operator<<(std::ostream &out, const Vector &vec);

#endif
