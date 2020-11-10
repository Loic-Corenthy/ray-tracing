#include "Ray.hpp"

using namespace MatouMalin;

Ray::Ray(void)
:_origin(Point(0.0f,0.0f,0.0f)),
 _direction(Vector(0.0f,0.0f,0.0f)),
 _intersected(nullptr)
{
    _length = (float)MAXFLOAT;
}

Ray::Ray(const Point & pOrigin, const Vector & pDirection)
:_origin(pOrigin),
 _direction(pDirection),
 _intersected(nullptr)
{
	_length = (float)MAXFLOAT;
}

Ray::Ray(const Ray & pRay)
:_origin(pRay._origin),
 _direction(pRay._direction),
 _length(pRay._length),
 _intersected(pRay._intersected)
{
}

Ray Ray::operator=(const Ray & pRay)
{
    if(this == & pRay)
        return *this;

    _origin = pRay._origin;
	_direction = pRay._direction;
	_length = pRay._length;
	_intersected = pRay._intersected;

    return *this;
}

Ray::~Ray(void)
{
}


