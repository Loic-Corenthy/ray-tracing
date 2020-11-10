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

Mesh::Mesh(unsigned int pTriangleCount)
:Renderable(),
 _bB(),
 _intersectedTriangle(-1)
{
    // Allocate memory in vector for the triangles
    _triangles.reserve(pTriangleCount);
}

Mesh::Mesh(const Mesh & pMesh)
:Renderable(pMesh),
 _triangles(pMesh._triangles),
 _bB(pMesh._bB),
 _intersectedTriangle(pMesh._intersectedTriangle)
{

}

Mesh::~Mesh(void)
{

}

Mesh Mesh::operator=(const Mesh &pMesh)
{
    if (this == &pMesh)
        return *this;

    Renderable::operator=(pMesh);

    _triangles = pMesh._triangles;
    _bB = pMesh._bB;
    _intersectedTriangle = pMesh._intersectedTriangle;

    return *this;
}

bool Mesh::intersect(MatouMalin::Ray & pRay)
{
    // Check if the ray intersect the bounding box
    if (_bB.intersect(pRay))
    {
        float lClosestDist = std::numeric_limits<float>::max();
        Renderable* rClosestObject = nullptr;
        Renderable* lObjectFromRay = pRay.intersected();

        int lI = 0;
        bool lHasIntersection(false);

        // Look for the closest intersection point among the triangles
        auto lIterator = _triangles.begin();
        auto lEnd = _triangles.end();

        while( lIterator != lEnd )
        {
            lHasIntersection = lIterator->intersect(pRay);
            if(lHasIntersection && pRay.length()<lClosestDist && lObjectFromRay != pRay.intersected())
            {
                lClosestDist = pRay.length();
                rClosestObject = pRay.intersected();
                _intersectedTriangle = lI++;
            }

            lIterator++;
        }

        // return the result
        if(lI > 0)
        {
            pRay.setLength(lClosestDist);
            pRay.setIntersected(rClosestObject);
            return true;
        }
        else
        {
            pRay.setLength(std::numeric_limits<float>::max());
            pRay.setIntersected(nullptr);
            return false;
        }
    }
    else
    {
        pRay.setLength(std::numeric_limits<float>::max());
        pRay.setIntersected(nullptr);
        return false;
    }

}

Color Mesh::color(Ray & pRay, unsigned int pReflectionCount)
{
    return _triangles[_intersectedTriangle].color(pRay, pReflectionCount);
}

Vector Mesh::normal(const Point &pPosition) const
{
    return _triangles[_intersectedTriangle].normal(pPosition);
}

Vector Mesh::interpolatedNormal(const Point &pPosition) const
{
    return _triangles[_intersectedTriangle].interpolatedNormal(pPosition);
}

void Mesh::setShader(Shader *pShader)
{
    assert(pShader != nullptr && "Shader not defined!!");

    auto lIt  = _triangles.begin();
    auto lEnd = _triangles.end();

    while (lIt != lEnd)
    {
        lIt->setShader(pShader);
        lIt++;
    }
}

bool Mesh::refractedRay(const Ray &pIncomingRay, Ray &pRefractedRay)
{
    assert(false && "Not implemented yet :)");
    return false;
}
