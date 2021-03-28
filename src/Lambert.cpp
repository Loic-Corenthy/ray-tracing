//===============================================================================================//
/*!
 *  \file      Lambert.cpp
 *  \author    Loïc Corenthy
 *  \version   1.2
 *  \date      04/09/2012
 *  \copyright (c) 2012 Loïc Corenthy. All rights reserved.
 */
//===============================================================================================//

#include "Lambert.hpp"

#include <cassert>
#include <cmath>
#include <memory>

#include "Color.hpp"
#include "Vector.hpp"
#include "Ray.hpp"

using std::shared_ptr;

using LCNS::Color;
using LCNS::Lambert;
using LCNS::Vector;

Lambert::Lambert(const Color& diffusionColor)
: _diffusionColor(diffusionColor)
{
}

void Lambert::diffusionColor(const Color& kd) noexcept
{
    _diffusionColor = kd;
}

Color Lambert::diffusionColor(void) const noexcept
{
    return _diffusionColor;
}

Color Lambert::reflectance([[maybe_unused]] const Vector& vecToLight,
                           [[maybe_unused]] const Vector& vecToViewer,
                           [[maybe_unused]] const Vector& normal,
                           [[maybe_unused]] const Point&  intersection)
{
    return diffuse(vecToLight, normal, intersection);
}

Color Lambert::diffuse([[maybe_unused]] const Vector& vecToLight,
                       [[maybe_unused]] const Vector& normal,
                       [[maybe_unused]] const Point&  intersection) const
{
    // Make local copy to normalize
    auto vecToLightCopy = Vector(vecToLight);
    vecToLightCopy.normalize();

    // Calculate diffusion coefficient
    double cosAlpha = vecToLightCopy * normal;

    // Set negative coefficents to zero
    cosAlpha = (cosAlpha < 0.0) ? 0.0 : cosAlpha;

    const auto cubeMap = BRDF::cubeMap();
    if (cubeMap)
    {
        const auto normalRay = Ray(intersection, normal);
        const auto diffColor = cubeMap->colorAt(normalRay);
        return diffColor * cosAlpha;
    }
    else
        return (_diffusionColor * cosAlpha);
}

Color Lambert::specular([[maybe_unused]] const LCNS::Vector& vecToLight,
                        [[maybe_unused]] const LCNS::Vector& vecToViewer,
                        [[maybe_unused]] const LCNS::Vector& normal,
                        [[maybe_unused]] const LCNS::Point&  intersection) const
{
    assert(false && "Not implemented yet");
    return Color(0.0f);
}
