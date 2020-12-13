//===============================================================================================//
/*!
 *  \file      Triangle.cpp
 *  \author    Loïc Corenthy
 *  \version   1.0
 *  \date      14/10/2012
 *  \copyright (c) 2012 Loïc Corenthy. All rights reserved.
 */
//===============================================================================================//

#include "Triangle.hpp"

#include "Point.hpp"
#include "Ray.hpp"
#include "Color.hpp"
#include "Scene.hpp"
#include "Shader.hpp"
#include "Vector.hpp"
#include <memory>
#include <optional>

using std::array;
using std::make_shared;
using std::nullopt;
using std::optional;

using LCNS::Color;
using LCNS::Point;
using LCNS::Ray;
using LCNS::Triangle;
using LCNS::Vector;

Triangle::Triangle(const Point& point0, const Point& point1, const Point& point2)
{
    _vertexPosition[0] = point0;
    _vertexPosition[1] = point1;
    _vertexPosition[2] = point2;

    updateNormal();
}

Triangle::Triangle(const Triangle& triangle)
: _vertexPosition(triangle._vertexPosition)
, _vertexNormal(triangle._vertexNormal)
, _normal(triangle._normal)
{
}

Triangle& Triangle::operator=(const Triangle& triangle)
{
    if (this == &triangle)
    {
        return *this;
    }

    _vertexPosition[0] = triangle._vertexPosition[0];
    _vertexPosition[1] = triangle._vertexPosition[1];
    _vertexPosition[2] = triangle._vertexPosition[2];

    _vertexNormal[0] = triangle._vertexNormal[0];
    _vertexNormal[1] = triangle._vertexNormal[1];
    _vertexNormal[2] = triangle._vertexNormal[2];

    _normal = triangle._normal;

    return *this;
}

const std::array<Point, 3>& Triangle::vertexPositions(void) const
{
    return _vertexPosition;
}
std::array<Point, 3>& Triangle::vertexPositions(void)
{
    return _vertexPosition;
}
const std::array<Vector, 3>& Triangle::vertexNormals(void) const
{
    return _vertexNormal;
}
std::array<Vector, 3>& Triangle::vertexNormals(void)
{
    return _vertexNormal;
}

float Triangle::_det(float a1, float a2, float b1, float b2)
{
    return (a1 * b2 - a2 * b1);
}

void Triangle::normal(const Vector& normal)
{
    _normal = normal;
}

void Triangle::updateNormal(void)
{
    const auto AB = _vertexPosition[1] - _vertexPosition[0];
    const auto AC = _vertexPosition[2] - _vertexPosition[0];

    _normal = AB ^ AC;
    _normal.normalize();
}

bool Triangle::intersect(Ray& ray)
{
    double scalarProd = ray.direction() * _normal;

    // Check if ray is not parallel to triangle
    if (scalarProd != 0.0)
    {
        Vector pointInTriangle(_vertexPosition[0][0], _vertexPosition[0][1], _vertexPosition[0][2]);
        Vector origin(ray.origin().x(), ray.origin().y(), ray.origin().z());

        // Calculate coeffient in the equation of the plane containing the triangle
        double d = (_normal * pointInTriangle) * (-1.0);

        // Calculate the lenght the ray when intersecting the plane
        double length = (-1.0) * (origin * _normal + d) / (scalarProd);

        // Calculate the coordinates of the intersection point
        Point p = ray.origin() + ray.direction() * length;

        // Check if the point in the plane is really inside the triangle
        Vector aB = _vertexPosition[1] - _vertexPosition[0];
        Vector bC = _vertexPosition[2] - _vertexPosition[1];
        Vector cA = _vertexPosition[0] - _vertexPosition[2];

        Vector aP = p - _vertexPosition[0];
        Vector bP = p - _vertexPosition[1];
        Vector cP = p - _vertexPosition[2];

        if ((aB ^ aP) * _normal >= 0.0 && (bC ^ bP) * _normal >= 0.0 && (cA ^ cP) * _normal >= 0.0 && length > 0.0)
        {
            ray.length(length);
            ray.intersected(this);
            return true;
        }
        else
            return false;
    }
    else
        return false;
}

Color Triangle::color(const Ray& ray, unsigned int reflectionCount)
{
    // Calculate normal from vertex normals
    Vector normalAtPt = _barycentricNormal(ray.intersection());

    return (_shader->color(ray.direction() * (-1), normalAtPt, ray.intersection(), this, reflectionCount));
}

Vector Triangle::normal(const Point& position) const
{
    return _barycentricNormal(position);
}

Vector Triangle::interpolatedNormal(const LCNS::Point& position) const
{
    return _barycentricNormal(position);
}

optional<Ray> Triangle::refractedRay(const Ray& incomingRay)
{
    assert(false && "Not implemented yet :)");
    return nullopt;
}

Vector Triangle::_barycentricNormal(const LCNS::Point& positionInTriangle) const
{
    const Vector AB = _vertexPosition[1] - _vertexPosition[0];
    const Vector AC = _vertexPosition[2] - _vertexPosition[0];

    const Vector normal          = AB ^ AC;
    const double normalLengthSqr = normal * normal;

    const double alpha = (normal * ((_vertexPosition[2] - _vertexPosition[1]) ^ (positionInTriangle - _vertexPosition[1]))) / normalLengthSqr;
    const double beta  = (normal * ((_vertexPosition[0] - _vertexPosition[2]) ^ (positionInTriangle - _vertexPosition[2]))) / normalLengthSqr;

    const double gamma = 1.0 - alpha - beta;

    assert(alpha + beta + gamma > 0.999 && alpha + beta + gamma < 1.001);

    return (_vertexNormal[0] * alpha + _vertexNormal[1] * beta + _vertexNormal[2] * gamma);
}
