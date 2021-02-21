//===============================================================================================//
/*!
 *  \file      DirectionalLight.cpp
 *  \author    Loïc Corenthy
 *  \version   1.1
 *  \date      14/10/2012
 *  \copyright (c) 2012 Loïc Corenthy. All rights reserved.
 */
//===============================================================================================//

#include "DirectionalLight.hpp"

#include "Color.hpp"
#include "Renderable.hpp"
#include "Ray.hpp"
#include "Scene.hpp"
#include "Vector.hpp"
#include <memory>

using std::shared_ptr;

using LCNS::Color;
using LCNS::DirectionalLight;
using LCNS::Vector;

DirectionalLight::DirectionalLight(const Vector& direction, const Color& intensity)
: Light(intensity)
, _direction(direction)
{
}

DirectionalLight::DirectionalLight(const DirectionalLight& directionalLight)
: Light(directionalLight)
, _direction(directionalLight._direction)
{
}

DirectionalLight DirectionalLight::operator=(const LCNS::DirectionalLight& directionalLight)
{
    if (this == &directionalLight)
        return *this;

    Light::operator=(directionalLight);

    _direction = directionalLight._direction;

    return *this;
}

void DirectionalLight::direction(const Vector& direction) noexcept
{
    _direction = direction;
}

const Vector& DirectionalLight::direction(void) const noexcept
{
    return _direction;
}

Vector DirectionalLight::directionFrom([[maybe_unused]] const Point& point) const
{
    return _direction * -1.0;
}

Color DirectionalLight::intensityAt(const Point& point, const Scene& scene, Renderable* currentObject) const
{
    Ray myRay;

    myRay.origin(point);
    myRay.direction(_direction * (-1.0));
    myRay.intersected(currentObject);

    bool hasIntersection = scene.intersect(myRay);

    if (hasIntersection)
        return Color(0.0f);
    else
    {
        const double cos = currentObject->normal(point) * (_direction * (-1.0));
        return _intensity * cos;
    }
}
