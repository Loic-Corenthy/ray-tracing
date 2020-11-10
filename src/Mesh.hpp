//
//  Mesh.h
//  RayTracing
//
//  Created by Loïc CORENTHY on 9/6/12.
//
//

#ifndef RAYTRACING_MESH_H
#define RAYTRACING_MESH_H

// Standard includes
#include <cassert>
#include <vector>

// Local includes
#include "Renderable.hpp"
#include "Point.hpp"
#include "Vector.hpp"
#include "Shader.hpp"
#include "Triangle.hpp"
#include "BoundingBox.hpp"

namespace MatouMalin
{
    class Mesh : public Renderable
    {
    public:
        /// Default constructor
        Mesh(void);

        /// Constructor with parameters
        Mesh(unsigned int pTriangleCount);

        /// Copy constructor
        Mesh(const Mesh & pMesh);

        /// Copy operator
        Mesh operator=(const Mesh & pMesh);

        /// Destructor
        ~Mesh(void);

        /// Add a triangle to the mesh
        void addTriangle(const Triangle & pTriangle);

        /// Set min and max point in bounding box
        void setBBLimits(const Point & pMin, const Point & pMax);

        /// Get bounding box (read only)
        const BoundingBox & boundingBox(void) const;

        /// Virtual function from Renderable
        bool intersect(Ray & pRay);

        /// Virtual function from Renderable
        Color color(Ray & pRay, unsigned int pReflectionCount = 0);

        /// Virtual function from Renderable
        Vector normal(const Point & pPosition) const;

        /// Virtual function from Renderable
        Vector interpolatedNormal(const Point & pPosition) const;

        /// Redefine function in Renderable
        void setShader(Shader* pShader);

        /// Virtual function from Renderable
        bool refractedRay(const Ray & pIncomingRay, Ray & pRefractedRay);

    private:
        std::vector<Triangle> _triangles;
        BoundingBox _bB;
        int _intersectedTriangle;

    }; // class Mesh

    inline void Mesh::addTriangle(const Triangle & pTriangle)
    {
        _triangles.push_back(pTriangle);
    }

    inline void Mesh::setBBLimits(const Point &pMin, const Point &pMax)
    {
        _bB.setMin(pMin);
        _bB.setMax(pMax);
    }

    inline const BoundingBox & Mesh::boundingBox(void) const
    {
        return _bB;
    }
} // namespace MatouMalin

#endif
