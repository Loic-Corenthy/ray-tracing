#include "Phong.hpp"

// Standard includes
#include <math.hpp>

// Local includes
#include "Vector.hpp"
#include "Ray.hpp"

// Namespaces
using namespace MatouMalin;

Phong::Phong(void)
:mDiffusionColor(Color(0.0)),
 mSpecularColor(Color(0.0)),
 mExponent(0)
{
}

Phong::Phong(const Color & pDiffusionColor, const Color &  pSpecularColor, int pExponent)
:BRDF(pDiffusionColor*0.2),
 mDiffusionColor(pDiffusionColor),
 mSpecularColor(pSpecularColor),
 mExponent(pExponent)
{
}

Phong::Phong(const Phong & pPhong)
:BRDF(pPhong),
 mDiffusionColor(pPhong.mDiffusionColor),
 mSpecularColor(pPhong.mSpecularColor),
 mExponent(pPhong.mExponent)
{

}

Phong Phong::operator=(const Phong & pPhong)
{
    if(this == & pPhong)
        return *this;
    
    BRDF::operator=(pPhong);
    
    mDiffusionColor = pPhong.mDiffusionColor;
	mSpecularColor = pPhong.mSpecularColor;
	mExponent = pPhong.mExponent;
    
    return *this;
}

Phong::~Phong(void)
{
}

Color Phong::reflectance(const Vector & pVecToLight, const Vector & pVecToViewer,const Vector & pNormal,const Point & pIntersection)
{
    // Make local copy for modification
	Vector lVecToLight(pVecToLight);
	Vector lVecToViewer(pVecToViewer);
    Vector lVecNormal(pNormal);
    
    // Normalize vectors
    lVecToLight.normalize();
    lVecToViewer.normalize();

    // Calculate diffusion coefficient
	double lCosAlpha = lVecToLight*pNormal;
    
    // Calculate specular coefficient
    double lCosBeta = (lVecToLight*pNormal)*2.0;
    Vector lReflexion = lVecNormal*lCosBeta - lVecToLight;
	lCosBeta = lReflexion*lVecToViewer;
    
    // Set negative coefficents to zero
    lCosAlpha = (lCosAlpha < 0.0)?0.0:lCosAlpha;
    lCosBeta = (lCosBeta < 0.0)?0.0:lCosBeta;

    const CubeMap* lCubeMap = cubeMap();
    if (lCubeMap)
    {
        Ray lNormalRay(pIntersection,pNormal);
        Color lDiffColor = const_cast<CubeMap*>(lCubeMap)->colorAt(lNormalRay);
        return lDiffColor*lCosAlpha + mSpecularColor*pow(lCosBeta,mExponent);
        
    }
    else
     return mDiffusionColor*lCosAlpha + mSpecularColor*pow(lCosBeta,mExponent);

}


Color Phong::diffuse(const Vector & pVecToLight, const Vector & pNormal,const Point & pIntersection) const
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
        return (mDiffusionColor*lCosAlpha);
}


Color Phong::specular(const Vector & pVecToLight, const Vector & pVecToViewer,const Vector & pNormal,const Point & pIntersection) const
{
	Vector lVecToLight(pVecToLight);
	Vector lVecToViewer(pVecToViewer);
    Vector lVecNormal(pNormal);
    
    // Normalize vectors
    lVecToLight.normalize();
    lVecToViewer.normalize();
    
    // Calculate specular coefficient
    double lCosBeta = (lVecToLight*pNormal)*2.0;
    Vector lReflexion = lVecNormal*lCosBeta - lVecToLight;
	lCosBeta = lReflexion*lVecToViewer;
    
    // Set negative coefficents to zero
    lCosBeta = (lCosBeta < 0.0)?0.0:lCosBeta;
	
	return (mSpecularColor*pow(lCosBeta, mExponent));
}









