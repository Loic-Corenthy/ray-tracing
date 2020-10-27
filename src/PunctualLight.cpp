#include "PunctualLight.hpp"
#include "Ray.hpp"
#include "Scene.hpp"
#include "Renderable.hpp"

#include <cassert>
#include <math.hpp>

using namespace MatouMalin;


PunctualLight::PunctualLight(void)
:Light(),
 mPosition(Point(0.0, 0.0, 0.0))
{
}

PunctualLight::PunctualLight(const MatouMalin::Point & pPosition,const Color & pIntensity)
:Light(pIntensity),
 mPosition(pPosition)
{
}

PunctualLight::PunctualLight(const PunctualLight & pPunctualLight)
:Light(pPunctualLight),
 mPosition(pPunctualLight.mPosition)
{
	mPosition = pPunctualLight.mPosition;
}

PunctualLight PunctualLight::operator=(const PunctualLight & pPunctualLight)
{
    if(this == & pPunctualLight)
        return *this;
    
    Light::operator=(pPunctualLight);
    
    mPosition = pPunctualLight.mPosition;
    
    return *this;
}

PunctualLight::~PunctualLight(void)
{
}

Color PunctualLight::intensityAt(const MatouMalin::Point & pPoint,const Scene & pScene, Renderable* pCurrentObject) const
{
    // Direction between point on object and current light
    Vector lDirection(mPosition - pPoint);
    
    // Create the corresponding ray
	Ray lMyRay(pPoint,lDirection);
    lMyRay.setIntersected(pCurrentObject);
    
    // Check if there is an object between them. Ask for at least 2 intersections points with the scene as the ray will always intersect with the object containing the point pPoint.
	bool lHasIntersection = false;
	lHasIntersection = pScene.intersect(lMyRay);
    
    // If an object is found, or if the light is inside the object, this light does not contribute on that point. Otherwise, calculate the amount of light arriving at the point
	if(lHasIntersection || (lDirection*pCurrentObject->normal(pPoint) <= 0.0))
        return Color(0.0f);
	else
        return mIntensity*(1.0f/(1.0f+lDirection.length()));
    
}