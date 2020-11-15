#include "Phong.hpp"

// Standard includes
#include <cmath>

// Local includes
#include "Vector.hpp"
#include "Ray.hpp"

// Namespaces
using namespace LCNS;

Phong::Phong(void)
: _diffusionColor(Color(0.0))
, _specularColor(Color(0.0))
, _exponent(0)
{
}

Phong::Phong(const Color& diffusionColor, const Color& specularColor, int exponent)
: BRDF(diffusionColor * 0.2)
, _diffusionColor(diffusionColor)
, _specularColor(specularColor)
, _exponent(exponent)
{
}

Phong::Phong(const Phong& phong)
: BRDF(phong)
, _diffusionColor(phong._diffusionColor)
, _specularColor(phong._specularColor)
, _exponent(phong._exponent)
{
}

Phong Phong::operator=(const Phong& phong)
{
    if (this == &phong)
        return *this;

    BRDF::operator=(phong);

    _diffusionColor = phong._diffusionColor;
    _specularColor  = phong._specularColor;
    _exponent       = phong._exponent;

    return *this;
}

Phong::~Phong(void)
{
}

Color Phong::reflectance(const Vector& vecToLight, const Vector& vecToViewer, const Vector& normal, const Point& intersection)
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
    cosBeta          = reflexion * vecToViewerCopy;

    // Set negative coefficents to zero
    cosAlpha = (cosAlpha < 0.0) ? 0.0 : cosAlpha;
    cosBeta  = (cosBeta < 0.0) ? 0.0 : cosBeta;

    const CubeMap* cubeMap = BRDF::cubeMap();
    if (cubeMap)
    {
        Ray   normalRay(intersection, normal);
        Color diffColor = const_cast<CubeMap*>(cubeMap)->colorAt(normalRay);
        return diffColor * cosAlpha + _specularColor * pow(cosBeta, _exponent);
    }
    else
        return _diffusionColor * cosAlpha + _specularColor * pow(cosBeta, _exponent);
}


Color Phong::diffuse(const Vector& vecToLight, const Vector& normal, const Point& intersection) const
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


Color Phong::specular(const Vector& vecToLight, const Vector& vecToViewer, const Vector& normal, const Point& intersection) const
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
