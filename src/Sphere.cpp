//===============================================================================================//
/*!
 *  \file      Sphere.cpp
 *  \author    Loïc Corenthy
 *  \version   1.0
 *  \date      14/10/2012
 *  \copyright (c) 2012 Loïc Corenthy. All rights reserved.
 */
//===============================================================================================//

#include "Sphere.hpp"

#include <cmath>
#include <tuple>

#include "Color.hpp"
#include "Shader.hpp"

using std::get;
using std::make_tuple;
using std::nullopt;
using std::optional;
using std::tuple;

using LCNS::Color;
using LCNS::Sphere;
using LCNS::Vector;

Sphere::Sphere(const Point& point, float radius)
: _center(point)
, _radius(radius)
{
}

Sphere::Sphere(const Sphere& sphere)
: Renderable(sphere)
, _center(sphere._center)
, _radius(sphere._radius)
{
}

Sphere Sphere::operator=(const Sphere& sphere)
{
    if (this == &sphere)
        return *this;

    Renderable::operator=(sphere);

    _center = sphere._center;
    _radius = sphere._radius;

    return *this;
}

bool Sphere::intersect(Ray& ray)
{
    float a = ray.direction()[0] * ray.direction()[0] + ray.direction()[1] * ray.direction()[1] + ray.direction()[2] * ray.direction()[2];
    float b = 2.0f
              * (ray.direction()[0] * (ray.origin()[0] - _center[0]) + ray.direction()[1] * (ray.origin()[1] - _center[1])
                 + ray.direction()[2] * (ray.origin()[2] - _center[2]));
    float c = (ray.origin()[0] - _center[0]) * (ray.origin()[0] - _center[0]) + (ray.origin()[1] - _center[1]) * (ray.origin()[1] - _center[1])
              + (ray.origin()[2] - _center[2]) * (ray.origin()[2] - _center[2]) - _radius * _radius;

    auto roots = _solveSecDeg(a, b, c);

    if (!roots)
        return false;

    auto [root1, root2] = roots.value();

    if (root1 > 0.0 && root2 > 0.0)
    {
        ray.setLength((root1 < root2) ? root1 : root2);
        ray.setIntersected(this);
        return true;
    }
    else if ((root1 > 0.0 && root2 <= 0.0) || (root2 > 0.0 && root1 <= 0.0))
    {
        ray.setLength((root1 > root2) ? root1 : root2);
        ray.setIntersected(this);
        return true;
    }
    else
        return false;
}

Color Sphere::color(const Ray& ray, unsigned int reflectionCount)
{
    // Calculate normal from vertex normals
    Vector normalAtPt = (ray.intersection() - _center);
    normalAtPt.normalize();

    return (_shader->color(ray.direction() * (-1), normalAtPt, ray.intersection(), this, reflectionCount));
}

bool Sphere::refractedRay(const Ray& incomingRay, Ray& refractedRay)
{
    Vector incomingDirection = incomingRay.direction();
    incomingDirection.normalize();
    Vector normalToIncomingRay = normal(incomingRay.intersection());
    double airIndex            = 1.0;
    double currentObjectIndex  = _shader->refractionCoeff();

    Vector refractedDirection;

    bool firstRefraction = _refraction(incomingDirection, normalToIncomingRay, airIndex, currentObjectIndex, refractedDirection);

    if (firstRefraction)
    {
        Ray insideSphere(incomingRay.intersection() + refractedDirection * 0.1, refractedDirection);

        bool getOut = this->intersect(insideSphere);
        assert(getOut && "Intersection not found inside the sphere");

        Vector outRefractionDirection;
        incomingDirection = insideSphere.direction();
        incomingDirection.normalize();
        bool secondRefraction
        = _refraction(insideSphere.direction(), normal(insideSphere.intersection()) * (-1.0), currentObjectIndex, airIndex, outRefractionDirection);

        if (!secondRefraction)
            return false;

        assert(secondRefraction && "Ray cannot get find its way out of the sphere :p ");

        refractedRay.setOrigin(insideSphere.intersection());
        refractedRay.setDirection(outRefractionDirection);
        refractedRay.setIntersected(this);

        return true;
    }
    else
    {
        return false;
    }
}

Vector Sphere::normal(const Point& position) const
{
    return ((position - _center).normalize());
}

Vector Sphere::interpolatedNormal(const Point& position) const
{
    return ((position - _center).normalize());
}

optional<tuple<float, float>> Sphere::_solveSecDeg(float a, float b, float c)
{
    if (a == 0.0f)
        return nullopt;

    auto delta = b * b - 4.0f * a * c;

    if (delta < 0.0f)
    {
        return nullopt;
    }
    else if (delta == 0)
    {
        return make_tuple(-b / (2.0f * a), -b / (2.0f * a));
    }
    else
    {
        return make_tuple((-b - sqrt(delta)) / (2.0f * a), (-b + sqrt(delta)) / (2.0f * a));
    }
}

const LCNS::Point& Sphere::center(void) const noexcept
{
    return _center;
}

void Sphere::center(const LCNS::Point& point) noexcept
{
    _center = point;
}

float Sphere::radius(void) const noexcept
{
    return _radius;
}

void Sphere::radius(float value) noexcept
{
    _radius = value;
}
