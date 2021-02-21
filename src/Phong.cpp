//===============================================================================================//
/*!
 *  \file      Phong.cpp
 *  \author    Loïc Corenthy
 *  \version   1.1
 *  \date      14/10/2012
 *  \copyright (c) 2012 Loïc Corenthy. All rights reserved.
 */
//===============================================================================================//

#include "Phong.hpp"

#include <cmath>

#include "Vector.hpp"
#include "Ray.hpp"

// Namespaces
using namespace LCNS;

Phong::Phong(const Color& diffusionColor, const Color& specularColor, int exponent)
: BRDF(diffusionColor * 0.2)
, _diffusionColor(diffusionColor)
, _specularColor(specularColor)
, _exponent(exponent)
{
}

void Phong::diffusionColor(const Color& diffusionColor) noexcept
{
    _diffusionColor = diffusionColor;
}

Color Phong::diffusionColor(void) const noexcept
{
    return _diffusionColor;
}

void Phong::specularColor(const Color& specularColor) noexcept
{
    _specularColor = specularColor;
}

Color Phong::specularColor(void) const noexcept
{
    return _specularColor;
}

void Phong::exponent(int exponent) noexcept
{
    _exponent = exponent;
}

int Phong::exponent(void) const noexcept
{
    return _exponent;
}

Color Phong::reflectance([[maybe_unused]] const Vector& vecToLight,
                         [[maybe_unused]] const Vector& vecToViewer,
                         [[maybe_unused]] const Vector& normal,
                         [[maybe_unused]] const Point&  intersection)
{
    // Make local copy for modification
    Vector vecToLightCopy(vecToLight);
    Vector vecToViewerCopy(vecToViewer);
    Vector vecNormal(normal);

    // Normalize vectors
    vecToLightCopy.normalize();
    vecToViewerCopy.normalize();

    // Calculate diffusion coefficient
    double cosAlpha = vecToLightCopy * normal;

    // Calculate specular coefficient
    double cosBeta   = (vecToLightCopy * normal) * 2.0;
    Vector reflexion = vecNormal * cosBeta - vecToLightCopy;

    cosBeta = reflexion * vecToViewerCopy;

    // Set negative coefficents to zero
    cosAlpha = (cosAlpha < 0.0) ? 0.0 : cosAlpha;
    cosBeta  = (cosBeta < 0.0) ? 0.0 : cosBeta;

    const auto cubeMap = BRDF::cubeMap();
    if (cubeMap)
    {
        Ray   normalRay(intersection, normal);
        Color diffColor = cubeMap->colorAt(normalRay);
        return diffColor * cosAlpha + _specularColor * pow(cosBeta, _exponent);
    }
    else
        return _diffusionColor * cosAlpha + _specularColor * pow(cosBeta, _exponent);
}


Color Phong::diffuse([[maybe_unused]] const Vector& vecToLight,
                     [[maybe_unused]] const Vector& normal,
                     [[maybe_unused]] const Point&  intersection) const
{
    // Make local copy to normalize
    Vector vecToLightCopy(vecToLight);
    vecToLightCopy.normalize();

    // Calculate diffusion coefficient
    double cosAlpha = vecToLightCopy * normal;

    // Set negative coefficents to zero
    cosAlpha = (cosAlpha < 0.0) ? 0.0 : cosAlpha;

    const auto cubeMap = BRDF::cubeMap();
    if (cubeMap)
    {
        Ray   normalRay(intersection, normal);
        Color diffColor = cubeMap->colorAt(normalRay);
        return diffColor * cosAlpha;
    }
    else
        return (_diffusionColor * cosAlpha);
}


Color Phong::specular([[maybe_unused]] const Vector& vecToLight,
                      [[maybe_unused]] const Vector& vecToViewer,
                      [[maybe_unused]] const Vector& normal,
                      [[maybe_unused]] const Point&  intersection) const
{
    Vector vecToLightCopy(vecToLight);
    Vector vecToViewerCopy(vecToViewer);
    Vector vecNormal(normal);

    // Normalize vectors
    vecToLightCopy.normalize();
    vecToViewerCopy.normalize();

    // Calculate specular coefficient
    double cosBeta   = (vecToLightCopy * normal) * 2.0;
    Vector reflexion = vecNormal * cosBeta - vecToLightCopy;
    cosBeta          = reflexion * vecToViewerCopy;

    // Set negative coefficents to zero
    cosBeta = (cosBeta < 0.0) ? 0.0 : cosBeta;

    return (_specularColor * pow(cosBeta, _exponent));
}
