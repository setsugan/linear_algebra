#ifndef LINEAR_ALGEBRA_VECTOR_HPP
#define LINEAR_ALGEBRA_VECTOR_HPP

#include <iostream>
#include <cmath>
#include <assert.h>

namespace linear_algebra {
class Vector {
private:
    double x_;
    double y_;
    double z_;
public:
    Vector() = default;
    Vector(double x, double y, double z) : x_(x), y_(y), z_(z) {};
    ~Vector() = default;
};

} // namespace linear_algebra

#endif // LINEAR_ALGEBRA_VECTOR_HPP
