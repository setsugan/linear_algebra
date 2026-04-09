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
    friend Vector operator*(const double left, const Vector &right);
    friend std::ostream &operator<<(std::ostream &os, const Vector &vec);
    friend std::istream &operator>>(std::istream &is, Vector &vec);

    Vector() = default;
    Vector(double x, double y, double z) : m_x(x), m_y(y), m_z(z) {}
    ~Vector() = default;

    double &operator[](size_t index)
    {
        switch (index)
        {
        case 0:
            return m_x;
        case 1:
            return m_y;
        case 2:
            return m_z;
        default:
            throw std::out_of_range("index out of bounds");
        }
    }
    double operator[](size_t index) const
    {
        switch (index)
        {
        case 0:
            return m_x;
        case 1:
            return m_y;
        case 2:
            return m_z;
        default:
            throw std::out_of_range("index out of bounds");
        }
    }

    double length() const
    {
        return sqrt(m_x * m_x + m_y * m_y + m_z * m_z);
    }

    void print_info() const
    {
        std::cout << "Vector [ x : " << m_x << ", y : " << m_y << ", z : " << m_z << "]" << std::endl;
    }

private:
    double m_x;
    double m_y;
    double m_z;
};

inline Vector &operator+=(Vector &left, const Vector &right)
{
    left.m_x += right.m_x;
    left.m_y += right.m_y;
    left.m_z += right.m_z;
    return left;
}
inline Vector &operator-=(Vector &left, const Vector &right)
{
    left.m_x -= right.m_x;
    left.m_y -= right.m_y;
    left.m_z -= right.m_z;
    return left;
}
inline Vector operator+(const Vector &left, const Vector &right)
{
    Vector vec(left.m_x, left.m_y, left.m_z);
    return vec += right;
}
inline Vector operator-(const Vector &left, const Vector &right)
{
    Vector vec(left.m_x, left.m_y, left.m_z);
    return vec -= right;
}
inline Vector operator*(const Vector &left, const double right)
{
    return Vector(left.m_x * right,
                    left.m_y * right,
                    left.m_z * right);
}
inline Vector operator*(const double left, const Vector &right)
{
    return Vector(right.m_x * left,
                    right.m_y * left,
                    right.m_z * left);
}
inline std::ostream &operator<<(std::ostream &os, const Vector &vec)
{
    os << "Vector [ x : " << vec.m_x << ", y : " << vec.m_y << ", z : " << vec.m_z << "]";
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
    vec.m_x = x;
    vec.m_y = y;
    vec.m_z = z;

    return is;
}

} // namespace linear_algebra

#endif // LINEAR_ALGEBRA_VECTOR_HPP
