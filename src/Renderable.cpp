//===============================================================================================//
/*!
 *  \file      Renderable.cpp
 *  \author    Loïc Corenthy
 *  \version   1.0
 *  \date      14/10/2012
 *  \copyright (c) 2012 Loïc Corenthy. All rights reserved.
 */
//===============================================================================================//

#include "Renderable.hpp"

#include "Ray.hpp"

using namespace LCNS;
using namespace std;

Renderable::Renderable(void)
: _shader(nullptr)
, _name(" ")
{
}

Renderable::Renderable(const Renderable& renderable)
: _shader(renderable._shader)
, _name(renderable._name)
{
}

void Renderable::operator=(const Renderable& renderable)
{
    if (this == &renderable)
        return;

    _shader = renderable._shader;
    _name   = renderable._name;
}

Renderable::~Renderable(void)
{
}

bool Renderable::_refraction(const Vector& incomingDirection, const Vector& normal, double n1, double n2, Vector& refractedDirection) const
{
    double minusCosTheta1 = incomingDirection * normal;
    double n              = n1 / n2;

    // Test for total reflection
    double sqrSinTheta2 = n * n * (1.0 - minusCosTheta1 * minusCosTheta1);

    if (sqrSinTheta2 > 1.0)
    {
        return false;
    }
    else
    {
        double cosTheta2  = sqrt(1.0 - sqrSinTheta2);
        refractedDirection = (incomingDirection - normal * minusCosTheta1) * n - normal * cosTheta2;
        return true;
    }
}
