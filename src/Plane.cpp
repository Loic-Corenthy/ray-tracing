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
:mEquationCoeffs{0.0,0.0,0.0,0.0}, // (c++11)
 mPosition(0.0,0.0,0.0),
 mNormal(0.0,0.0,0.0)
{

}

Plane::Plane(double pA, double pB, double pC, double pD)
:mEquationCoeffs{pA,pB,pC,pD},
 mNormal(pA,pB,pC)
{
    _updatePosition();
}

Plane::Plane(const Vector & pNormal, const Point & pPosition)
:mNormal(pNormal),
 mPosition(pPosition)
{
    _updateEquation();
}

Plane::Plane(const Plane & pPlane)
:mNormal(pPlane.mNormal),
 mPosition(pPlane.mPosition)
{
    mEquationCoeffs[0] = pPlane.mEquationCoeffs[0];
    mEquationCoeffs[1] = pPlane.mEquationCoeffs[1];
    mEquationCoeffs[2] = pPlane.mEquationCoeffs[2];
    mEquationCoeffs[3] = pPlane.mEquationCoeffs[3];
}

Plane Plane::operator=(const Plane & pPlane)
{
    if (this == &pPlane)
        return *this;

    mNormal = pPlane.mNormal;
    mPosition = pPlane.mPosition;

    mEquationCoeffs[0] = pPlane.mEquationCoeffs[0];
    mEquationCoeffs[1] = pPlane.mEquationCoeffs[1];
    mEquationCoeffs[2] = pPlane.mEquationCoeffs[2];
    mEquationCoeffs[3] = pPlane.mEquationCoeffs[3];

    return *this;

}

Plane::~Plane(void)
{

}

bool Plane::intersect(Ray & pRay)
{
    double lScalarProd = pRay.direction()*mNormal;

    // Check if ray is not parallel to triangle
    if (lScalarProd != 0.0)
    {
        Vector lOrigin(pRay.origin().x(),pRay.origin().y(),pRay.origin().z());

        // Calculate the lenght the ray when intersecting the plane
        double lLength = (-1.0)*(lOrigin*mNormal + mEquationCoeffs[3])/(lScalarProd);

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
    mEquationCoeffs[pIndex] = pValue;

    _updatePosition();
    _updateNormal();
}

void Plane::setNormal(const Vector & pNormal)
{
    mNormal = pNormal;
    _updateEquation();
}

void Plane::setPosition(const Point & pPosition)
{
    mPosition = pPosition;
    _updateEquation();
}

void Plane::_updateEquation(void)
{
    mEquationCoeffs[0] = mNormal.x();
    mEquationCoeffs[1] = mNormal.y();
    mEquationCoeffs[2] = mNormal.z();

    Vector lPosition(mPosition.x(),mPosition.y(),mPosition.z());
    mEquationCoeffs[3] = (mNormal*lPosition)*(-1.0);
}

void Plane::_updateNormal(void)
{
    mNormal.setVector(mEquationCoeffs[0], mEquationCoeffs[1], mEquationCoeffs[2]);
}

void Plane::_updatePosition(void)
{
    assert(mEquationCoeffs[2] != 0.0 && "Problem in updating position in plane");
    mPosition.setPoint(mEquationCoeffs[1]*(-1.0), mEquationCoeffs[0], mEquationCoeffs[3]/mEquationCoeffs[2]*(-1));
}


