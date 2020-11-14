#include "PunctualLight.hpp"
#include "Ray.hpp"
#include "Scene.hpp"
#include "Renderable.hpp"

#include <cassert>
#include <cmath>

using namespace MatouMalin;


PunctualLight::PunctualLight(void)
: Light()
, _position(Point(0.0, 0.0, 0.0))
{
}

PunctualLight::PunctualLight(const MatouMalin::Point& position, const Color& intensity)
: Light(intensity)
, _position(position)
{
}

PunctualLight::PunctualLight(const PunctualLight& punctualLight)
: Light(punctualLight)
, _position(punctualLight._position)
{
    _position = punctualLight._position;
}

PunctualLight PunctualLight::operator=(const PunctualLight& punctualLight)
{
    if (this == &punctualLight)
        return *this;

    Light::operator=(punctualLight);

    _position = punctualLight._position;

    return *this;
}

PunctualLight::~PunctualLight(void)
{
}

Color PunctualLight::intensityAt(const MatouMalin::Point& point, const Scene& scene, Renderable* currentObject) const
{
    // Direction between point on object and current light
    Vector lDirection(_position - point);

    // Create the corresponding ray
    Ray lMyRay(point, lDirection);
    lMyRay.setIntersected(currentObject);

    // Check if there is an object between them. Ask for at least 2 intersections points with the scene as the ray will always intersect with the
    // object containing the point point.
    bool lHasIntersection = false;
    lHasIntersection      = scene.intersect(lMyRay);

    // If an object is found, or if the light is inside the object, this light does not contribute on that point. Otherwise, calculate the amount of
    // light arriving at the point
    if (lHasIntersection || (lDirection * currentObject->normal(point) <= 0.0))
        return Color(0.0f);
    else
        return _intensity * (1.0f / (1.0f + lDirection.length()));
}
