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
:_equationCoeffs{0.0,0.0,0.0,0.0}, // (c++11)
 _position(0.0,0.0,0.0),
 _normal(0.0,0.0,0.0)
{

}

Plane::Plane(double pA, double pB, double pC, double pD)
:_equationCoeffs{pA,pB,pC,pD},
 _normal(pA,pB,pC)
{
    _updatePosition();
}

Plane::Plane(const Vector & pNormal, const Point & pPosition)
:_normal(pNormal),
 _position(pPosition)
{
    _updateEquation();
}

Plane::Plane(const Plane & pPlane)
:_normal(pPlane._normal),
 _position(pPlane._position)
{
    _equationCoeffs[0] = pPlane._equationCoeffs[0];
    _equationCoeffs[1] = pPlane._equationCoeffs[1];
    _equationCoeffs[2] = pPlane._equationCoeffs[2];
    _equationCoeffs[3] = pPlane._equationCoeffs[3];
}

Plane Plane::operator=(const Plane & pPlane)
{
    if (this == &pPlane)
        return *this;

    _normal = pPlane._normal;
    _position = pPlane._position;

    _equationCoeffs[0] = pPlane._equationCoeffs[0];
    _equationCoeffs[1] = pPlane._equationCoeffs[1];
    _equationCoeffs[2] = pPlane._equationCoeffs[2];
    _equationCoeffs[3] = pPlane._equationCoeffs[3];

    return *this;

}

Plane::~Plane(void)
{

}

bool Plane::intersect(Ray & pRay)
{
    double lScalarProd = pRay.direction()*_normal;

    // Check if ray is not parallel to triangle
    if (lScalarProd != 0.0)
    {
        Vector lOrigin(pRay.origin().x(),pRay.origin().y(),pRay.origin().z());

        // Calculate the lenght the ray when intersecting the plane
        double lLength = (-1.0)*(lOrigin*_normal + _equationCoeffs[3])/(lScalarProd);

        pRay.setLength(lLength);
        pRay.setIntersected(nullptr); // (c++11)
        return true;
    }
    else
        return false;
}

void Plane::setCoefficient(unsigned int pIndex, double pValue)
{
    assert(0 <= pIndex && pIndex <4 && "index out of boundaries for the coefficients");
    _equationCoeffs[pIndex] = pValue;

    _updatePosition();
    _updateNormal();
}

void Plane::setNormal(const Vector & pNormal)
{
    _normal = pNormal;
    _updateEquation();
}

void Plane::setPosition(const Point & pPosition)
{
    _position = pPosition;
    _updateEquation();
}

void Plane::_updateEquation(void)
{
    _equationCoeffs[0] = _normal.x();
    _equationCoeffs[1] = _normal.y();
    _equationCoeffs[2] = _normal.z();

    Vector lPosition(_position.x(),_position.y(),_position.z());
    _equationCoeffs[3] = (_normal*lPosition)*(-1.0);
}

void Plane::_updateNormal(void)
{
    _normal.setVector(_equationCoeffs[0], _equationCoeffs[1], _equationCoeffs[2]);
}

void Plane::_updatePosition(void)
{
    assert(_equationCoeffs[2] != 0.0 && "Problem in updating position in plane");
    _position.setPoint(_equationCoeffs[1]*(-1.0), _equationCoeffs[0], _equationCoeffs[3]/_equationCoeffs[2]*(-1));
}


