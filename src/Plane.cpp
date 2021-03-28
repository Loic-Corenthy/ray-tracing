//===============================================================================================//
/*!
 *  \file      Plane.cpp
 *  \author    Loïc Corenthy
 *  \version   1.2
 *  \date      12/10/2012
 *  \copyright (c) 2012 Loïc Corenthy. All rights reserved.
 */
//===============================================================================================//

#include "Plane.hpp"

using namespace LCNS;

Plane::Plane(double a, double b, double c, double d)
: _equationCoeffs{ a, b, c, d }
, _normal(a, b, c)
{
    _updatePosition();
}

Plane::Plane(const Vector& normal, const Point& position)
: _position(position)
, _normal(normal)
{
    _updateEquation();
}

Plane::Plane(const Plane& plane)
: _position(plane._position)
, _normal(plane._normal)
{
    _equationCoeffs[0] = plane._equationCoeffs[0];
    _equationCoeffs[1] = plane._equationCoeffs[1];
    _equationCoeffs[2] = plane._equationCoeffs[2];
    _equationCoeffs[3] = plane._equationCoeffs[3];
}

Plane& Plane::operator=(const Plane& plane)
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

bool Plane::intersect(Ray& ray)
{
    const double scalarProd = ray.direction() * _normal;

    // Check if ray is not parallel to triangle
    if (scalarProd != 0.0)
    {
        const Vector origin(ray.origin().x(), ray.origin().y(), ray.origin().z());

        // Calculate the lenght the ray when intersecting the plane
        const double length = (-1.0) * (origin * _normal + _equationCoeffs[3]) / (scalarProd);

        ray.length(length);
        ray.intersected(nullptr);

        return true;
    }
    else
        return false;
}

void Plane::coefficient(unsigned int index, double value)
{
    assert(index < 4 && "index out of boundaries for the coefficients");
    _equationCoeffs[index] = value;

    _updatePosition();
    _updateNormal();
}

void Plane::normal(const Vector& normal)
{
    _normal = normal;
    _updateEquation();
}

void Plane::position(const Point& position)
{
    _position = position;
    _updateEquation();
}

double Plane::coefficient(unsigned int index) const
{
    assert(index < 4 && "index out of boundaries for the coefficients");
    return _equationCoeffs[index];
}

Vector Plane::normal(void) const
{
    return _normal;
}

Point Plane::position(void) const
{
    return _position;
}

void Plane::_updateEquation(void)
{
    _equationCoeffs[0] = _normal.x();
    _equationCoeffs[1] = _normal.y();
    _equationCoeffs[2] = _normal.z();

    const Vector position(_position.x(), _position.y(), _position.z());
    _equationCoeffs[3] = (_normal * position) * (-1.0);
}

void Plane::_updateNormal(void)
{
    _normal.setVector(_equationCoeffs[0], _equationCoeffs[1], _equationCoeffs[2]);
}

void Plane::_updatePosition(void)
{
    assert(_equationCoeffs[2] != 0.0 && "Problem in updating position in plane");
    _position.set(_equationCoeffs[1] * (-1.0), _equationCoeffs[0], _equationCoeffs[3] / _equationCoeffs[2] * (-1.0));
}
