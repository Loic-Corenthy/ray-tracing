//===============================================================================================//
/*!
 *  \file      Ray.cpp
 *  \author    Loïc Corenthy
 *  \version   1.1
 *  \date      14/10/2012
 *  \copyright (c) 2012 Loïc Corenthy. All rights reserved.
 */
//===============================================================================================//
//
#include "Ray.hpp"

#include "Renderable.hpp"

using std::shared_ptr;

using LCNS::Point;
using LCNS::Ray;
using LCNS::Renderable;
using LCNS::Vector;

Ray::Ray(const Point& origin, const Vector& direction)
: _origin(origin)
, _direction(direction)
{
}

const Point& Ray::origin(void) const
{
    return _origin;
}

void Ray::origin(const Point& point)
{
    _origin = point;
}

const Vector& Ray::direction(void) const
{
    return _direction;
}

void Ray::direction(const Vector& vector)
{
    _direction = vector;
}

double Ray::length(void) const
{
    return _length;
}

void Ray::length(double length)
{
    _length = length;
}

void Ray::intersected(Renderable* intersected)
{
    _intersected = intersected;
}

Renderable* Ray::intersected(void)
{
    return _intersected;
}

Point Ray::intersection(void) const
{
    return (_origin + _direction * _length);
}
