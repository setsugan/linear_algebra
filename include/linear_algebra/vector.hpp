/**
 * @file vector.hpp
 * @author riku yukimaru (setsugan.robocon@gmail.com)
 * @brief
 * @version 0.1
 * @date 2026-04-09
 *
 * @copyright Copyright (c) 2026
 *
 */
#ifndef LINEAR_ALGEBRA_VECTOR_HPP
#define LINEAR_ALGEBRA_VECTOR_HPP

#include <iostream>
#include <cmath>
#include <assert.h>

namespace linear_algebra {
class Vector
{
public:
    friend Vector &operator+=(Vector &left, const Vector &right);
    friend Vector &operator-=(Vector &left, const Vector &right);
    friend Vector operator+(const Vector &left, const Vector &right);
    friend Vector operator-(const Vector &left, const Vector &right);
    friend Vector operator*(const Vector &left, const double right);
    friend Vector &operator*=(Vector &left, const double right);
    friend Vector operator*(const double left, const Vector &right);
    friend Vector &operator/=(Vector &left, const double right);
    friend Vector operator/(const Vector &left, const double right);
    friend std::ostream &operator<<(std::ostream &os, const Vector &vec);
    friend std::istream &operator>>(std::istream &is, Vector &vec);

    Vector() = default;
    Vector(double x, double y, double z) : x_(x), y_(y), z_(z) {}
    ~Vector() = default;

    double &operator[](size_t index)
    {
        switch (index)
        {
        case 0:
            return x_;
        case 1:
            return y_;
        case 2:
            return z_;
        default:
            throw std::out_of_range("index out of bounds");
        }
    }
    double operator[](size_t index) const
    {
        switch (index)
        {
        case 0:
            return x_;
        case 1:
            return y_;
        case 2:
            return z_;
        default:
            throw std::out_of_range("index out of bounds");
        }
    }

    double length() const
    {
        return sqrt(x_ * x_ + y_ * y_ + z_ * z_);
    }

    void print_info() const
    {
        std::cout << "Vector [ x : " << x_ << ", y : " << y_ << ", z : " << z_ << "]" << std::endl;
    }

private:
    double x_;
    double y_;
    double z_;
};

inline Vector &operator+=(Vector &left, const Vector &right)
{
    left.x_ += right.x_;
    left.y_ += right.y_;
    left.z_ += right.z_;
    return left;
}
inline Vector &operator-=(Vector &left, const Vector &right)
{
    left.x_ -= right.x_;
    left.y_ -= right.y_;
    left.z_ -= right.z_;
    return left;
}
inline Vector operator+(const Vector &left, const Vector &right)
{
    Vector vec(left.x_, left.y_, left.z_);
    return vec += right;
}
inline Vector operator-(const Vector &left, const Vector &right)
{
    Vector vec(left.x_, left.y_, left.z_);
    return vec -= right;
}
inline Vector &operator*=(Vector &left, const double right)
{
    left.x_ *= right;
    left.y_ *= right;
    left.z_ *= right;
    return left;
}
inline Vector operator*(const Vector &left, const double right)
{
    Vector vec(left.x_, left.y_, left.z_);
    return vec *= right;
}
inline Vector operator*(const double left, const Vector &right)
{
    Vector vec(right.x_, right.y_, right.z_);
    return vec *= left;
}
inline Vector &operator/=(Vector &left, const double right)
{
    left.x_ /= right;
    left.y_ /= right;
    left.z_ /= right;
    return left;
}
Vector operator/(const Vector &left, const double right)
{
    Vector vec(left.x_, left.y_, left.z_);
    vec /= right;
    return;
}
inline std::ostream &operator<<(std::ostream &os, const Vector &vec)
{
    os << "Vector [ x : " << vec.x_ << ", y : " << vec.y_ << ", z : " << vec.z_ << "]";
    return os;
}
inline std::istream &operator>>(std::istream &is, Vector &vec)
{
    double x;
    double y;
    double z;

    std::cout << "Please type in the coordinates for the vector" << std::endl;
    std::cout << "order [x,y,z], separated by spaces : ";

    is >> x >> y >> z;
    vec.x_ = x;
    vec.y_ = y;
    vec.z_ = z;

    return is;
}

} // namespace linear_algebra

#endif // LINEAR_ALGEBRA_VECTOR_HPP
