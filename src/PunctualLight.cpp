#include "PunctualLight.hpp"
#include "Ray.hpp"
#include "Scene.hpp"
#include "Renderable.hpp"

#include <cassert>
#include <cmath>

using namespace MatouMalin;


PunctualLight::PunctualLight(void)
:Light(),
 _position(Point(0.0, 0.0, 0.0))
{
}

PunctualLight::PunctualLight(const MatouMalin::Point & pPosition,const Color & pIntensity)
:Light(pIntensity),
 _position(pPosition)
{
}

PunctualLight::PunctualLight(const PunctualLight & pPunctualLight)
:Light(pPunctualLight),
 _position(pPunctualLight._position)
{
	_position = pPunctualLight._position;
}

PunctualLight PunctualLight::operator=(const PunctualLight & pPunctualLight)
{
    if(this == & pPunctualLight)
        return *this;

    Light::operator=(pPunctualLight);

    _position = pPunctualLight._position;

    return *this;
}

PunctualLight::~PunctualLight(void)
{
}

Color PunctualLight::intensityAt(const MatouMalin::Point & pPoint,const Scene & pScene, Renderable* pCurrentObject) const
{
    // Direction between point on object and current light
    Vector lDirection(_position - pPoint);

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
        return _intensity*(1.0f/(1.0f+lDirection.length()));

}
