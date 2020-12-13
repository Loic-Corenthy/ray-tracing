//===============================================================================================//
/*!
 *  \file      Vector.cpp
 *  \author    Loïc Corenthy
 *  \version   1.0
 *  \date      14/10/2012
 *  \copyright (c) 2012 Loïc Corenthy. All rights reserved.
 */
//===============================================================================================//

#include "Vector.hpp"

using namespace LCNS;

Vector::Vector(double commonValue)
{
    _coords[0] = commonValue;
    _coords[1] = commonValue;
    _coords[2] = commonValue;
}

Vector::Vector(double x, double y, double z)
{
    _coords[0] = x;
    _coords[1] = y;
    _coords[2] = z;
}

double Vector::operator[](unsigned int index) const
{
    assert(index <= 2 && "Vector: index out of bounds");
    return _coords[index];
}

double& Vector::operator[](unsigned int index)
{
    assert(index <= 2 && "Vector: index out of bounds");
    return _coords[index];
}

void Vector::setVector(double x, double y, double z) noexcept
{
    _coords[0] = x;
    _coords[1] = y;
    _coords[2] = z;
}

void Vector::setX(double x) noexcept
{
    _coords[0] = x;
}

void Vector::setY(double y) noexcept
{
    _coords[1] = y;
}

void Vector::setZ(double z) noexcept
{
    _coords[2] = z;
}

double Vector::x(void) const noexcept
{
    return _coords[0];
}

double Vector::y(void) const noexcept
{
    return _coords[1];
}

double Vector::z(void) const noexcept
{
    return _coords[2];
}

double Vector::operator*(const Vector& vector) const
{
    return (_coords[0] * vector._coords[0] + _coords[1] * vector._coords[1] + _coords[2] * vector._coords[2]);
}

double Vector::length(void) const
{
    return sqrt(_coords[0] * _coords[0] + _coords[1] * _coords[1] + _coords[2] * _coords[2]);
}

double Vector::lengthSqr(void) const
{
    return (_coords[0] * _coords[0] + _coords[1] * _coords[1] + _coords[2] * _coords[2]);
}

Vector Vector::operator+(const Vector& vector) const
{
    return Vector{ _coords[0] + vector._coords[0], _coords[1] + vector._coords[1], _coords[2] + vector._coords[2] };
}

Vector Vector::operator-(const Vector& vector) const
{
    return Vector{ _coords[0] - vector._coords[0], _coords[1] - vector._coords[1], _coords[2] - vector._coords[2] };
}

Vector Vector::operator+=(const Vector& vector)
{
    _coords[0] = _coords[0] + vector._coords[0];
    _coords[1] = _coords[1] + vector._coords[1];
    _coords[2] = _coords[2] + vector._coords[2];

    return *this;
}

Vector Vector::operator-=(const Vector& vector)
{
    _coords[0] = _coords[0] - vector._coords[0];
    _coords[1] = _coords[1] - vector._coords[1];
    _coords[2] = _coords[2] - vector._coords[2];

    return *this;
}

Vector Vector::operator*(double scalar) const
{
    return Vector{ scalar * _coords[0], scalar * _coords[1], scalar * _coords[2] };
}

Vector Vector::operator^(const Vector& vector) const
{
    return Vector{ _coords[1] * vector._coords[2] - _coords[2] * vector._coords[1],
                   _coords[2] * vector._coords[0] - _coords[0] * vector._coords[2],
                   _coords[0] * vector._coords[1] - _coords[1] * vector._coords[0] };
}


Vector Vector::normalize(void)
{
    const auto lengthVector = length();

    _coords[0] /= lengthVector;
    _coords[1] /= lengthVector;
    _coords[2] /= lengthVector;

    return *this;
}
