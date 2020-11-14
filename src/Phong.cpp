#include "Phong.hpp"

// Standard includes
#include <cmath>

// Local includes
#include "Vector.hpp"
#include "Ray.hpp"

// Namespaces
using namespace MatouMalin;

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
    Vector lVecToLight(vecToLight);
    Vector lVecToViewer(vecToViewer);
    Vector lVecNormal(normal);

    // Normalize vectors
    lVecToLight.normalize();
    lVecToViewer.normalize();

    // Calculate diffusion coefficient
    double lCosAlpha = lVecToLight * normal;

    // Calculate specular coefficient
    double lCosBeta   = (lVecToLight * normal) * 2.0;
    Vector lReflexion = lVecNormal * lCosBeta - lVecToLight;
    lCosBeta          = lReflexion * lVecToViewer;

    // Set negative coefficents to zero
    lCosAlpha = (lCosAlpha < 0.0) ? 0.0 : lCosAlpha;
    lCosBeta  = (lCosBeta < 0.0) ? 0.0 : lCosBeta;

    const CubeMap* lCubeMap = cubeMap();
    if (lCubeMap)
    {
        Ray   lNormalRay(intersection, normal);
        Color lDiffColor = const_cast<CubeMap*>(lCubeMap)->colorAt(lNormalRay);
        return lDiffColor * lCosAlpha + _specularColor * pow(lCosBeta, _exponent);
    }
    else
        return _diffusionColor * lCosAlpha + _specularColor * pow(lCosBeta, _exponent);
}


Color Phong::diffuse(const Vector& vecToLight, const Vector& normal, const Point& intersection) const
{
    // Make local copy to normalize
    Vector lVecToLight(vecToLight);
    lVecToLight.normalize();

    // Calculate diffusion coefficient
    double lCosAlpha = lVecToLight * normal;

    // Set negative coefficents to zero
    lCosAlpha = (lCosAlpha < 0.0) ? 0.0 : lCosAlpha;

    const CubeMap* lCubeMap = cubeMap();
    if (lCubeMap)
    {
        Ray   lNormalRay(intersection, normal);
        Color lDiffColor = const_cast<CubeMap*>(lCubeMap)->colorAt(lNormalRay);
        return lDiffColor * lCosAlpha;
    }
    else
        return (_diffusionColor * lCosAlpha);
}


Color Phong::specular(const Vector& vecToLight, const Vector& vecToViewer, const Vector& normal, const Point& intersection) const
{
    Vector lVecToLight(vecToLight);
    Vector lVecToViewer(vecToViewer);
    Vector lVecNormal(normal);

    // Normalize vectors
    lVecToLight.normalize();
    lVecToViewer.normalize();

    // Calculate specular coefficient
    double lCosBeta   = (lVecToLight * normal) * 2.0;
    Vector lReflexion = lVecNormal * lCosBeta - lVecToLight;
    lCosBeta          = lReflexion * lVecToViewer;

    // Set negative coefficents to zero
    lCosBeta = (lCosBeta < 0.0) ? 0.0 : lCosBeta;

    return (_specularColor * pow(lCosBeta, _exponent));
}
