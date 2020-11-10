//
//  Lambert.cpp
//  RayTracing
//
//  Created by Loïc CORENTHY on 9/4/12.
//
//

#include "Lambert.hpp"

// Standard includes
#include <cmath>

// Local includes
#include "Vector.hpp"
#include "Ray.hpp"

// Namespaces
using namespace MatouMalin;

Lambert::Lambert(void)
:BRDF(),
 _diffusionColor(0.0)
{
}

Lambert::Lambert(const Color & diffusionColor)
:BRDF(diffusionColor*0.1),
 _diffusionColor(diffusionColor)
{
}

Lambert::Lambert(const Lambert & lambert)
:BRDF(lambert),
 _diffusionColor(lambert._diffusionColor)
{

}

Lambert Lambert::operator=(const Lambert & lambert)
{
    if(this == & lambert)
        return *this;

    BRDF::operator=(lambert);

    _diffusionColor = lambert._diffusionColor;

    return *this;
}

Lambert::~Lambert(void)
{
}

Color Lambert::reflectance(const Vector & vecToLight, const Vector & vecToViewer,const Vector & normal,const Point & intersection)
{
    return diffuse(vecToLight, normal, intersection);
}

Color Lambert::diffuse(const Vector & vecToLight, const Vector & normal, const Point & intersection) const
{
    // Make local copy to normalize
	Vector lVecToLight(vecToLight);
    lVecToLight.normalize();

    // Calculate diffusion coefficient
	double lCosAlpha = lVecToLight*normal;

    // Set negative coefficents to zero
    lCosAlpha = (lCosAlpha < 0.0)?0.0:lCosAlpha;

    const CubeMap* lCubeMap = cubeMap();
    if (lCubeMap)
    {
        Ray lNormalRay(intersection,normal);
        Color lDiffColor = const_cast<CubeMap*>(lCubeMap)->colorAt(lNormalRay);
        return lDiffColor*lCosAlpha;

    }
    else
        return (_diffusionColor*lCosAlpha);
}

Color Lambert::specular(const MatouMalin::Vector &vecToLight, const MatouMalin::Vector &vecToViewer, const MatouMalin::Vector &normal, const MatouMalin::Point &intersection) const
{
    return Color(0.0f);
}













