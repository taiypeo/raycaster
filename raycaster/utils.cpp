#include <cmath>

#include "utils.hpp"

bool is_close(double a, double b)
{
    return std::fabs(a - b) <= std::numeric_limits<double>::epsilon();
}
