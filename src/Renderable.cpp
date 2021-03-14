//===============================================================================================//
/*!
 *  \file      Renderable.cpp
 *  \author    Loïc Corenthy
 *  \version   1.1
 *  \date      14/10/2012
 *  \copyright (c) 2012 Loïc Corenthy. All rights reserved.
 */
//===============================================================================================//

#include "Renderable.hpp"

#include "Ray.hpp"
#include "Shader.hpp"

using std::shared_ptr;

using LCNS::Renderable;
using LCNS::Shader;

void Renderable::shader(shared_ptr<Shader> shader)
{
    _shader = shader;
}

shared_ptr<Shader> Renderable::shader(void)
{
    return _shader;
}

void Renderable::name(const std::string& name)
{
    _name = name;
}

std::string Renderable::name(void) const
{
    return _name;
}

bool Renderable::_refraction(const Vector& incomingDirection, const Vector& normal, double n1, double n2, Vector& refractedDirection) const
{
    if (n2 == 0.0)
    {
        return false;
    }

    const double minusCosTheta1 = incomingDirection * normal;
    const double n              = n1 / n2;

    // Test for total reflection
    const double sqrSinTheta2 = n * n * (1.0 - minusCosTheta1 * minusCosTheta1);

    if (sqrSinTheta2 > 1.0)
    {
        return false;
    }
    else
    {
        const double cosTheta2 = sqrt(1.0 - sqrSinTheta2);
        refractedDirection     = (incomingDirection - normal * minusCosTheta1) * n - normal * cosTheta2;
        return true;
    }
}
