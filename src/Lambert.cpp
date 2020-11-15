//===============================================================================================//
/*!
 *  \file      Lambert.cpp
 *  \author    Loïc Corenthy
 *  \version   1.0
 *  \date      04/09/2012
 *  \copyright (c) 2012 Loïc Corenthy. All rights reserved.
 */
//===============================================================================================//

#include "Lambert.hpp"

#include <cmath>

#include "Vector.hpp"
#include "Ray.hpp"

using namespace LCNS;

Lambert::Lambert(void)
: BRDF()
, _diffusionColor(0.0)
{
}

Lambert::Lambert(const Color& diffusionColor)
: BRDF(diffusionColor * 0.1)
, _diffusionColor(diffusionColor)
{
}

Lambert::Lambert(const Lambert& lambert)
: BRDF(lambert)
, _diffusionColor(lambert._diffusionColor)
{
}

Lambert Lambert::operator=(const Lambert& lambert)
{
    if (this == &lambert)
        return *this;

    BRDF::operator=(lambert);

    _diffusionColor = lambert._diffusionColor;

    return *this;
}

Lambert::~Lambert(void)
{
}

Color Lambert::reflectance(const Vector& vecToLight, const Vector& vecToViewer, const Vector& normal, const Point& intersection)
{
    return diffuse(vecToLight, normal, intersection);
}

Color Lambert::diffuse(const Vector& vecToLight, const Vector& normal, const Point& intersection) const
{
    // Make local copy to normalize
    Vector vecToLightCopy(vecToLight);
    vecToLightCopy.normalize();

    // Calculate diffusion coefficient
    double cosAlpha = vecToLightCopy * normal;

    // Set negative coefficents to zero
    cosAlpha = (cosAlpha < 0.0) ? 0.0 : cosAlpha;

    const CubeMap* cubeMap = BRDF::cubeMap();
    if (cubeMap)
    {
        Ray   normalRay(intersection, normal);
        Color diffColor = const_cast<CubeMap*>(cubeMap)->colorAt(normalRay);
        return diffColor * cosAlpha;
    }
    else
        return (_diffusionColor * cosAlpha);
}

Color Lambert::specular(const LCNS::Vector& vecToLight,
                        const LCNS::Vector& vecToViewer,
                        const LCNS::Vector& normal,
                        const LCNS::Point&  intersection) const
{
    return Color(0.0f);
}
