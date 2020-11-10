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

Lambert::Lambert(const Color & pDiffusionColor)
:BRDF(pDiffusionColor*0.1),
 _diffusionColor(pDiffusionColor)
{
}

Lambert::Lambert(const Lambert & pLambert)
:BRDF(pLambert),
 _diffusionColor(pLambert._diffusionColor)
{

}

Lambert Lambert::operator=(const Lambert & pLambert)
{
    if(this == & pLambert)
        return *this;

    BRDF::operator=(pLambert);

    _diffusionColor = pLambert._diffusionColor;

    return *this;
}

Lambert::~Lambert(void)
{
}

Color Lambert::reflectance(const Vector & pVecToLight, const Vector & pVecToViewer,const Vector & pNormal,const Point & pIntersection)
{
    return diffuse(pVecToLight, pNormal, pIntersection);
}

Color Lambert::diffuse(const Vector & pVecToLight, const Vector & pNormal, const Point & pIntersection) const
{
    // Make local copy to normalize
	Vector lVecToLight(pVecToLight);
    lVecToLight.normalize();

    // Calculate diffusion coefficient
	double lCosAlpha = lVecToLight*pNormal;

    // Set negative coefficents to zero
    lCosAlpha = (lCosAlpha < 0.0)?0.0:lCosAlpha;

    const CubeMap* lCubeMap = cubeMap();
    if (lCubeMap)
    {
        Ray lNormalRay(pIntersection,pNormal);
        Color lDiffColor = const_cast<CubeMap*>(lCubeMap)->colorAt(lNormalRay);
        return lDiffColor*lCosAlpha;

    }
    else
        return (_diffusionColor*lCosAlpha);
}

Color Lambert::specular(const MatouMalin::Vector &pVecToLight, const MatouMalin::Vector &pVecToViewer, const MatouMalin::Vector &pNormal, const MatouMalin::Point &pIntersection) const
{
    return Color(0.0f);
}













