//===============================================================================================//
/*!
 *  \file      Point.hpp
 *  \author    Loïc Corenthy
 *  \version   1.0
 *  \date      14/10/2012
 *  \copyright (c) 2012 Loïc Corenthy. All rights reserved.
 */
//===============================================================================================//

#include "Point.hpp"

using LCNS::Point;
using LCNS::Vector;

Point::Point(double x, double y, double z)
: _coords{ x, y, z }
{
}

Point::Point(double commonValue)
: _coords{ commonValue, commonValue, commonValue }
{
}

Point::Point(const Point& point)
{
    _coords[0] = point._coords[0];
    _coords[1] = point._coords[1];
    _coords[2] = point._coords[2];
}

Point& Point::operator=(const Point& point)
{
    if (this == &point)
        return *this;

    _coords[0] = point._coords[0];
    _coords[1] = point._coords[1];
    _coords[2] = point._coords[2];

    return *this;
}

double Point::operator[](unsigned int index) const
{
    assert(index < 3 && "Point: index out of bounds");
    return _coords[index];
}

double& Point::operator[](unsigned int index)
{
    assert(index < 3 && "Point: index out of bounds");
    return _coords[index];
}

Vector Point::operator-(const Point& point) const noexcept
{
    return Vector(_coords[0] - point._coords[0], _coords[1] - point._coords[1], _coords[2] - point._coords[2]);
}

Point Point::operator+(const Vector& vector) const noexcept
{
    return Point(_coords[0] + vector[0], _coords[1] + vector[1], _coords[2] + vector[2]);
}

void Point::set(double x, double y, double z) noexcept
{
    _coords[0] = x;
    _coords[1] = y;
    _coords[2] = z;
}

void Point::x(double x) noexcept
{
    _coords[0] = x;
}

void Point::y(double y) noexcept
{
    _coords[1] = y;
}

void Point::z(double z) noexcept
{
    _coords[2] = z;
}

double Point::x(void) const noexcept
{
    return _coords[0];
}

double Point::y(void) const noexcept
{
    return _coords[1];
}

double Point::z(void) const noexcept
{
    return _coords[2];
}

double& Point::x(void) noexcept
{
    return _coords[0];
}

double& Point::y(void) noexcept
{
    return _coords[1];
}

double& Point::z(void) noexcept
{
    return _coords[2];
}
