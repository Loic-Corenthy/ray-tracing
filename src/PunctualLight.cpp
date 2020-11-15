//===============================================================================================//
/*!
 *  \file      PunctualLight.cpp
 *  \author    Loïc Corenthy
 *  \version   1.0
 *  \date      14/10/2012
 *  \copyright (c) 2012 Loïc Corenthy. All rights reserved.
 */
//===============================================================================================//

#include "PunctualLight.hpp"

#include <cassert>
#include <cmath>

#include "Ray.hpp"
#include "Scene.hpp"
#include "Renderable.hpp"

using namespace LCNS;

PunctualLight::PunctualLight(void)
: Light()
, _position(Point(0.0, 0.0, 0.0))
{
}

PunctualLight::PunctualLight(const LCNS::Point& position, const Color& intensity)
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

Color PunctualLight::intensityAt(const LCNS::Point& point, const Scene& scene, Renderable* currentObject) const
{
    // Direction between point on object and current light
    Vector direction(_position - point);

    // Create the corresponding ray
    Ray myRay(point, direction);
    myRay.setIntersected(currentObject);

    // Check if there is an object between them. Ask for at least 2 intersections points with the scene as the ray will always intersect with the
    // object containing the point point.
    bool hasIntersection = false;
    hasIntersection      = scene.intersect(myRay);

    // If an object is found, or if the light is inside the object, this light does not contribute on that point. Otherwise, calculate the amount of
    // light arriving at the point
    if (hasIntersection || (direction * currentObject->normal(point) <= 0.0))
        return Color(0.0f);
    else
        return _intensity * (1.0f / (1.0f + direction.length()));
}
