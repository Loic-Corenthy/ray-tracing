//===============================================================================================//
/*!
 *  \file      Mesh.cpp
 *  \author    Loïc Corenthy
 *  \version   1.0
 *  \date      06/09/2012
 *  \copyright (c) 2012 Loïc Corenthy. All rights reserved.
 */
//===============================================================================================//

#include "Mesh.hpp"

using namespace LCNS;

Mesh::Mesh(void)
: Renderable()
, _bB()
, _intersectedTriangle(-1)
{
}

Mesh::Mesh(unsigned int triangleCount)
: Renderable()
, _bB()
, _intersectedTriangle(-1)
{
    // Allocate memory in vector for the triangles
    _triangles.reserve(triangleCount);
}

Mesh::Mesh(const Mesh& mesh)
: Renderable(mesh)
, _triangles(mesh._triangles)
, _bB(mesh._bB)
, _intersectedTriangle(mesh._intersectedTriangle)
{
}

Mesh::~Mesh(void)
{
}

Mesh Mesh::operator=(const Mesh& mesh)
{
    if (this == &mesh)
        return *this;

    Renderable::operator=(mesh);

    _triangles           = mesh._triangles;
    _bB                  = mesh._bB;
    _intersectedTriangle = mesh._intersectedTriangle;

    return *this;
}

bool Mesh::intersect(LCNS::Ray& ray)
{
    // Check if the ray intersect the bounding box
    if (_bB.intersect(ray))
    {
        float       closestDist    = std::numeric_limits<float>::max();
        Renderable* rClosestObject = nullptr;
        Renderable* objectFromRay  = ray.intersected();

        int  i = 0;
        bool hasIntersection(false);

        // Look for the closest intersection point among the triangles
        auto iterator = _triangles.begin();
        auto end      = _triangles.end();

        while (iterator != end)
        {
            hasIntersection = iterator->intersect(ray);
            if (hasIntersection && ray.length() < closestDist && objectFromRay != ray.intersected())
            {
                closestDist          = ray.length();
                rClosestObject       = ray.intersected();
                _intersectedTriangle = i++;
            }

            iterator++;
        }

        // return the result
        if (i > 0)
        {
            ray.setLength(closestDist);
            ray.setIntersected(rClosestObject);
            return true;
        }
        else
        {
            ray.setLength(std::numeric_limits<float>::max());
            ray.setIntersected(nullptr);
            return false;
        }
    }
    else
    {
        ray.setLength(std::numeric_limits<float>::max());
        ray.setIntersected(nullptr);
        return false;
    }
}

Color Mesh::color(const Ray& ray, unsigned int reflectionCount)
{
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

void Mesh::setShader(Shader* shader)
{
    assert(shader != nullptr && "Shader not defined!!");

    auto it  = _triangles.begin();
    auto end = _triangles.end();

    while (it != end)
    {
        it->setShader(shader);
        it++;
    }
}

bool Mesh::refractedRay(const Ray& incomingRay, Ray& refractedRay)
{
    assert(false && "Not implemented yet :)");
    return false;
}
