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
#include <memory>
#include <tuple>

#include "Color.hpp"
#include "Ray.hpp"
#include "Renderable.hpp"
#include "Shader.hpp"

using std::get;
using std::make_shared;
using std::make_tuple;
using std::nullopt;
using std::optional;
using std::tuple;

using LCNS::Color;
using LCNS::Ray;
using LCNS::Renderable;
using LCNS::Sphere;
using LCNS::Vector;

Sphere::Sphere(const Point& point, double radius)
: _center(point)
, _radius(radius)
{
}

Sphere::Sphere(const Sphere& sphere)
: _center(sphere._center)
, _radius(sphere._radius)
{
}

bool Sphere::intersect(Ray& ray)
{
    double a = ray.direction()[0] * ray.direction()[0] + ray.direction()[1] * ray.direction()[1] + ray.direction()[2] * ray.direction()[2];
    double b = 2.0
               * (ray.direction()[0] * (ray.origin()[0] - _center[0]) + ray.direction()[1] * (ray.origin()[1] - _center[1])
                  + ray.direction()[2] * (ray.origin()[2] - _center[2]));
    double c = (ray.origin()[0] - _center[0]) * (ray.origin()[0] - _center[0]) + (ray.origin()[1] - _center[1]) * (ray.origin()[1] - _center[1])
               + (ray.origin()[2] - _center[2]) * (ray.origin()[2] - _center[2]) - _radius * _radius;

    auto roots = _solveSecDeg(a, b, c);

    if (!roots)
        return false;

    auto [root1, root2] = roots.value();

    if (root1 > 0.0 && root2 > 0.0)
    {
        ray.length((root1 < root2) ? root1 : root2);
        ray.intersected(shared_from_this());
        return true;
    }
    else if ((root1 > 0.0 && root2 <= 0.0) || (root2 > 0.0 && root1 <= 0.0))
    {
        ray.length((root1 > root2) ? root1 : root2);
        ray.intersected(shared_from_this());
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

    return (_shader->color(ray.direction() * (-1), normalAtPt, ray.intersection(), shared_from_this(), reflectionCount));
}

optional<Ray> Sphere::refractedRay(const Ray& incomingRay)
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
            return nullopt;

        assert(secondRefraction && "Ray cannot get find its way out of the sphere :p ");

        auto refractedRay = Ray(insideSphere.intersection(), outRefractionDirection);
        refractedRay.intersected(make_shared<Sphere>(*this));

        return refractedRay;
    }
    else
    {
        return nullopt;
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

optional<tuple<double, double>> Sphere::_solveSecDeg(double a, double b, double c)
{
    if (a == 0.0)
        return nullopt;

    auto delta = b * b - 4.0 * a * c;

    if (delta < 0.0)
    {
        return nullopt;
    }
    else if (delta == 0.0)
    {
        return make_tuple(-b / (2.0 * a), -b / (2.0 * a));
    }
    else
    {
        return make_tuple((-b - sqrt(delta)) / (2.0 * a), (-b + sqrt(delta)) / (2.0 * a));
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

double Sphere::radius(void) const noexcept
{
    return _radius;
}

void Sphere::radius(double value) noexcept
{
    _radius = value;
}
