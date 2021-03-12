//===============================================================================================//
/*!
 *  \file      Mesh.cpp
 *  \author    Loïc Corenthy
 *  \version   1.1
 *  \date      06/09/2012
 *  \copyright (c) 2012 Loïc Corenthy. All rights reserved.
 */
//===============================================================================================//

#include "Mesh.hpp"
#include "BoundingBox.hpp"
#include "Color.hpp"
#include "Ray.hpp"
#include "Renderable.hpp"
#include "Triangle.hpp"
#include "Vector.hpp"
#include <optional>

using std::lock_guard;
using std::mutex;
using std::nullopt;
using std::optional;
using std::shared_ptr;

using LCNS::BoundingBox;
using LCNS::Color;
using LCNS::Mesh;
using LCNS::Ray;
using LCNS::Renderable;
using LCNS::Vector;

Mesh::Mesh(void)
: Renderable()
, _boundingBox()
{
}

Mesh::Mesh(unsigned int triangleCount)
: Renderable()
, _boundingBox()
{
    // Allocate memory in vector for the triangles
    _triangles.reserve(triangleCount);
}

void Mesh::addTriangle(const Triangle& triangle)
{
    _triangles.push_back(triangle);
}

void Mesh::boundingBoxLimits(const Point& min, const Point& max)
{
    _boundingBox.min(min);
    _boundingBox.max(max);
}

const BoundingBox& Mesh::boundingBox(void) const
{
    return _boundingBox;
}

bool Mesh::intersect(LCNS::Ray& ray)
{
    // Check if the ray intersect the bounding box
    if (_boundingBox.intersect(ray))
    {
        auto        closestDist    = std::numeric_limits<double>::max();
        Renderable* rClosestObject = nullptr;
        Renderable* objectFromRay  = ray.intersected();

        int i = 0;

        for (auto& triangle : _triangles)
        {
            const bool hasIntersection = triangle.intersect(ray);
            if (hasIntersection && ray.length() < closestDist && objectFromRay != ray.intersected())
            {
                closestDist          = ray.length();
                rClosestObject       = ray.intersected();
                _intersectedTriangle = i++;
            }
        }

        // return the result
        if (i > 0)
        {
            ray.length(closestDist);
            ray.intersected(rClosestObject);
            return true;
        }
        else
        {
            ray.length(std::numeric_limits<float>::max());
            ray.intersected(nullptr);
            return false;
        }
    }
    else
    {
        ray.length(std::numeric_limits<float>::max());
        ray.intersected(nullptr);
        return false;
    }
}

Color Mesh::color(const Ray& ray, unsigned int reflectionCount)
{
    const lock_guard<mutex> lock(_mutex);
    return _triangles[_intersectedTriangle].color(ray, reflectionCount);
}

Vector Mesh::normal(const Point& position) const
{
    return _triangles[_intersectedTriangle].normal(position);
}

Vector Mesh::interpolatedNormal(const Point& position) const
{
    return _triangles[_intersectedTriangle].interpolatedNormal(position);
}

void Mesh::shader(shared_ptr<Shader> shader)
{
    assert(shader != nullptr && "Shader not defined!!");

    for (auto& triangle : _triangles)
    {
        triangle.shader(shader);
    }
}

optional<Ray> Mesh::refractedRay(const Ray& incomingRay)
{
    assert(false && "Not implemented yet :)");
    return nullopt;
}
