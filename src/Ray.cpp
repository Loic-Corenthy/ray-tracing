//===============================================================================================//
/*!
 *  \file      Ray.cpp
 *  \author    Loïc Corenthy
 *  \version   1.0
 *  \date      14/10/2012
 *  \copyright (c) 2012 Loïc Corenthy. All rights reserved.
 */
//===============================================================================================//
//
#include "Ray.hpp"

using namespace LCNS;

Ray::Ray(void)
: _origin(Point(0.0f, 0.0f, 0.0f))
, _direction(Vector(0.0f, 0.0f, 0.0f))
, _intersected(nullptr)
{
    _length = (float) MAXFLOAT;
}

Ray::Ray(const Point& origin, const Vector& direction)
: _origin(origin)
, _direction(direction)
, _intersected(nullptr)
{
    _length = (float) MAXFLOAT;
}

Ray::Ray(const Ray& ray)
: _origin(ray._origin)
, _direction(ray._direction)
, _length(ray._length)
, _intersected(ray._intersected)
{
}

Ray Ray::operator=(const Ray& ray)
{
    if (this == &ray)
        return *this;

    _origin      = ray._origin;
    _direction   = ray._direction;
    _length      = ray._length;
    _intersected = ray._intersected;

    return *this;
}

Ray::~Ray(void)
{
}

void Ray::setOrigin(const Point& point)
{
    _origin = point;
}

void Ray::setDirection(const Vector& vector)
{
    _direction = vector;
}

void Ray::setLength(double length)
{
    _length = length;
}

void Ray::setIntersected(Renderable* intersected)
{
    _intersected = intersected;
}

const Point& Ray::origin(void) const
{
    return _origin;
}

const Vector& Ray::direction(void) const
{
    return _direction;
}

double Ray::length(void) const
{
    return _length;
}

Renderable* Ray::intersected(void) const
{
    return _intersected;
}

Point Ray::intersection(void) const
{
    return (_origin + _direction * _length);
}
