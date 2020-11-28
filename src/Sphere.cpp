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

#include "Shader.hpp"

using namespace LCNS;

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
    float b = 2
              * (ray.direction()[0] * (ray.origin()[0] - _center[0]) + ray.direction()[1] * (ray.origin()[1] - _center[1])
                 + ray.direction()[2] * (ray.origin()[2] - _center[2]));
    float c = (ray.origin()[0] - _center[0]) * (ray.origin()[0] - _center[0]) + (ray.origin()[1] - _center[1]) * (ray.origin()[1] - _center[1])
              + (ray.origin()[2] - _center[2]) * (ray.origin()[2] - _center[2]) - _radius * _radius;

    float root1(0.0f);
    float root2(0.0f);
    bool  rootOk(false);

    rootOk = _solveSecDeg(a, b, c, root1, root2);

    if (rootOk == false)
        return false;

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

const LCNS::Point& Sphere::center(void) const
{
    return _center;
}

void Sphere::setCenter(const LCNS::Point& point)
{
    _center = point;
}

float Sphere::radius(void) const
{
    return _radius;
}

void Sphere::setRadius(float radius)
{
    _radius = radius;
}

Vector Sphere::normal(const Point& position) const
{
    return ((position - _center).normalize());
}

Vector Sphere::interpolatedNormal(const Point& position) const
{
    return ((position - _center).normalize());
}

bool Sphere::_solveSecDeg(float a, float b, float c, float& root1, float& root2)
{
    float delta = 0;
    delta       = b * b - 4 * a * c;

    if (delta < 0)
    {
        root1 = 0;
        root2 = 0;
        return false;
    }
    else if (delta == 0)
    {
        root1 = -b / (2 * a);
        root2 = -b / (2 * a);
        return true;
    }
    else
    {
        root1 = (-b - sqrt(delta)) / (2 * a);
        root2 = (-b + sqrt(delta)) / (2 * a);
        return true;
    }
}
