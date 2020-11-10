//
//  Mesh.cpp
//  RayTracing
//
//  Created by Loïc CORENTHY on 9/6/12.
//
//

#include "Mesh.hpp"

// Namespaces
using namespace MatouMalin;

Mesh::Mesh(void)
:Renderable(),
 _bB(),
 _intersectedTriangle(-1)
{

}

Mesh::Mesh(unsigned int triangleCount)
:Renderable(),
 _bB(),
 _intersectedTriangle(-1)
{
    // Allocate memory in vector for the triangles
    _triangles.reserve(triangleCount);
}

Mesh::Mesh(const Mesh & mesh)
:Renderable(mesh),
 _triangles(mesh._triangles),
 _bB(mesh._bB),
 _intersectedTriangle(mesh._intersectedTriangle)
{

}

Mesh::~Mesh(void)
{

}

Mesh Mesh::operator=(const Mesh & mesh)
{
    if (this == & mesh)
        return *this;

    Renderable::operator=(mesh);

    _triangles = mesh._triangles;
    _bB = mesh._bB;
    _intersectedTriangle = mesh._intersectedTriangle;

    return *this;
}

bool Mesh::intersect(MatouMalin::Ray & ray)
{
    // Check if the ray intersect the bounding box
    if (_bB.intersect(ray))
    {
        float lClosestDist = std::numeric_limits<float>::max();
        Renderable* rClosestObject = nullptr;
        Renderable* lObjectFromRay = ray.intersected();

        int lI = 0;
        bool lHasIntersection(false);

        // Look for the closest intersection point among the triangles
        auto lIterator = _triangles.begin();
        auto lEnd = _triangles.end();

        while( lIterator != lEnd )
        {
            lHasIntersection = lIterator->intersect(ray);
            if(lHasIntersection && ray.length()<lClosestDist && lObjectFromRay != ray.intersected())
            {
                lClosestDist = ray.length();
                rClosestObject = ray.intersected();
                _intersectedTriangle = lI++;
            }

            lIterator++;
        }

        // return the result
        if(lI > 0)
        {
            ray.setLength(lClosestDist);
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

Color Mesh::color(Ray & ray, unsigned int reflectionCount)
{
    return _triangles[_intersectedTriangle].color(ray, reflectionCount);
}

Vector Mesh::normal(const Point & position) const
{
    return _triangles[_intersectedTriangle].normal(position);
}

Vector Mesh::interpolatedNormal(const Point & position) const
{
    return _triangles[_intersectedTriangle].interpolatedNormal(position);
}

void Mesh::setShader(Shader *shader)
{
    assert(shader != nullptr && "Shader not defined!!");

    auto lIt  = _triangles.begin();
    auto lEnd = _triangles.end();

    while (lIt != lEnd)
    {
        lIt->setShader(shader);
        lIt++;
    }
}

bool Mesh::refractedRay(const Ray &incomingRay, Ray &refractedRay)
{
    assert(false && "Not implemented yet :)");
    return false;
}
