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

#include "Ray.hpp"
#include "Color.hpp"
#include "Scene.hpp"
#include "Shader.hpp"

using namespace LCNS;

Triangle::Triangle(void)
: _normal(Vector(0.0, 0.0, 0.0))
{
    _vertice[0] = Point(0.0);
    _vertice[1] = Point(0.0);
    _vertice[2] = Point(0.0);

    _vertexNormal[0] = Vector(0.0);
    _vertexNormal[1] = Vector(0.0);
    _vertexNormal[2] = Vector(0.0);
}

Triangle::Triangle(const Point& point0, const Point& point1, const Point& point2)
{
    _vertice[0] = point0;
    _vertice[1] = point1;
    _vertice[2] = point2;

    _vertexNormal[0] = Vector(0.0);
    _vertexNormal[1] = Vector(0.0);
    _vertexNormal[2] = Vector(0.0);

    updateNormal();
}

Triangle::Triangle(const Triangle& triangle)
{
    _vertice[0] = triangle._vertice[0];
    _vertice[1] = triangle._vertice[1];
    _vertice[2] = triangle._vertice[2];

    _vertexNormal[0] = triangle._vertexNormal[0];
    _vertexNormal[1] = triangle._vertexNormal[1];
    _vertexNormal[2] = triangle._vertexNormal[2];

    _normal = triangle._normal;
}

Triangle::~Triangle(void)
{
}

void Triangle::updateNormal(void)
{
    Vector aB(_vertice[1] - _vertice[0]);
    Vector aC(_vertice[2] - _vertice[0]);

    _normal = aB ^ aC;
    _normal.normalize();
}

bool Triangle::intersect(Ray& ray)
{
    double scalarProd = ray.direction() * _normal;

    // Check if ray is not parallel to triangle
    if (scalarProd != 0.0)
    {
        Vector pointInTriangle(_vertice[0][0], _vertice[0][1], _vertice[0][2]);
        Vector origin(ray.origin().x(), ray.origin().y(), ray.origin().z());

        // Calculate coeffient in the equation of the plane containing the triangle
        double d = (_normal * pointInTriangle) * (-1.0);

        // Calculate the lenght the ray when intersecting the plane
        double length = (-1.0) * (origin * _normal + d) / (scalarProd);

        // Calculate the coordinates of the intersection point
        Point p = ray.origin() + ray.direction() * length;

        // Check if the point in the plane is really inside the triangle
        Vector aB = _vertice[1] - _vertice[0];
        Vector bC = _vertice[2] - _vertice[1];
        Vector cA = _vertice[0] - _vertice[2];

        Vector aP = p - _vertice[0];
        Vector bP = p - _vertice[1];
        Vector cP = p - _vertice[2];

        if ((aB ^ aP) * _normal >= 0.0 && (bC ^ bP) * _normal >= 0.0 && (cA ^ cP) * _normal >= 0.0 && length > 0.0)
        {
            ray.setLength(length);
            ray.setIntersected(this);
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

Vector Triangle::interpolatedNormal(const LCNS::Point& position) const
{
    return _barycentricNormal(position);
}

bool Triangle::refractedRay(const Ray& incomingRay, Ray& refractedRay)
{
    assert(false && "Not implemented yet :)");
    return false;
}

Vector Triangle::_barycentricNormal(const LCNS::Point& positionInTriangle) const
{
    Vector aB(_vertice[1] - _vertice[0]);
    Vector aC(_vertice[2] - _vertice[0]);

    Vector normal             = aB ^ aC;
    double invNormalLengthSqr = 1.0 / (normal * normal);

    double alpha = normal * ((_vertice[2] - _vertice[1]) ^ (positionInTriangle - _vertice[1]));
    alpha *= invNormalLengthSqr;

    double beta = normal * ((_vertice[0] - _vertice[2]) ^ (positionInTriangle - _vertice[2]));
    beta *= invNormalLengthSqr;

    double gamma = 1.0 - alpha - beta;

    assert(alpha + beta + gamma > 0.999 && alpha + beta + gamma < 1.001);

    return (_vertexNormal[0] * alpha + _vertexNormal[1] * beta + _vertexNormal[2] * gamma);
}
