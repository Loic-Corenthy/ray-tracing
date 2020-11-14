#include "Ray.hpp"

using namespace MatouMalin;

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
