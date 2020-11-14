//
//  Plane.cpp
//  RayTracing
//
//  Created by Loïc CORENTHY on 10/12/12.
//
//

#include "Plane.hpp"

using namespace MatouMalin;

Plane::Plane(void)
: _equationCoeffs{ 0.0, 0.0, 0.0, 0.0 }
,  // (c++11)
_position(0.0, 0.0, 0.0)
, _normal(0.0, 0.0, 0.0)
{
}

Plane::Plane(double a, double b, double c, double d)
: _equationCoeffs{ a, b, c, d }
, _normal(a, b, c)
{
    _updatePosition();
}

Plane::Plane(const Vector& normal, const Point& position)
: _normal(normal)
, _position(position)
{
    _updateEquation();
}

Plane::Plane(const Plane& plane)
: _normal(plane._normal)
, _position(plane._position)
{
    _equationCoeffs[0] = plane._equationCoeffs[0];
    _equationCoeffs[1] = plane._equationCoeffs[1];
    _equationCoeffs[2] = plane._equationCoeffs[2];
    _equationCoeffs[3] = plane._equationCoeffs[3];
}

Plane Plane::operator=(const Plane& plane)
{
    if (this == &plane)
        return *this;

    _normal   = plane._normal;
    _position = plane._position;

    _equationCoeffs[0] = plane._equationCoeffs[0];
    _equationCoeffs[1] = plane._equationCoeffs[1];
    _equationCoeffs[2] = plane._equationCoeffs[2];
    _equationCoeffs[3] = plane._equationCoeffs[3];

    return *this;
}

Plane::~Plane(void)
{
}

bool Plane::intersect(Ray& ray)
{
    double lScalarProd = ray.direction() * _normal;

    // Check if ray is not parallel to triangle
    if (lScalarProd != 0.0)
    {
        Vector lOrigin(ray.origin().x(), ray.origin().y(), ray.origin().z());

        // Calculate the lenght the ray when intersecting the plane
        double lLength = (-1.0) * (lOrigin * _normal + _equationCoeffs[3]) / (lScalarProd);

        ray.setLength(lLength);
        ray.setIntersected(nullptr);  // (c++11)
        return true;
    }
    else
        return false;
}

void Plane::setCoefficient(unsigned int index, double value)
{
    assert(0 <= index && index < 4 && "index out of boundaries for the coefficients");
    _equationCoeffs[index] = value;

    _updatePosition();
    _updateNormal();
}

void Plane::setNormal(const Vector& normal)
{
    _normal = normal;
    _updateEquation();
}

void Plane::setPosition(const Point& position)
{
    _position = position;
    _updateEquation();
}

void Plane::_updateEquation(void)
{
    _equationCoeffs[0] = _normal.x();
    _equationCoeffs[1] = _normal.y();
    _equationCoeffs[2] = _normal.z();

    Vector lPosition(_position.x(), _position.y(), _position.z());
    _equationCoeffs[3] = (_normal * lPosition) * (-1.0);
}

void Plane::_updateNormal(void)
{
    _normal.setVector(_equationCoeffs[0], _equationCoeffs[1], _equationCoeffs[2]);
}

void Plane::_updatePosition(void)
{
    assert(_equationCoeffs[2] != 0.0 && "Problem in updating position in plane");
    _position.setPoint(_equationCoeffs[1] * (-1.0), _equationCoeffs[0], _equationCoeffs[3] / _equationCoeffs[2] * (-1));
}
