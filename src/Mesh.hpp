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
        Mesh(unsigned int triangleCount);

        /// Copy constructor
        Mesh(const Mesh& mesh);

        /// Copy operator
        Mesh operator=(const Mesh& mesh);

        /// Destructor
        ~Mesh(void);

        /// Add a triangle to the mesh
        void addTriangle(const Triangle& triangle);

        /// Set min and max point in bounding box
        void setBBLimits(const Point& min, const Point& max);

        /// Get bounding box (read only)
        const BoundingBox& boundingBox(void) const;

        /// Virtual function from Renderable
        bool intersect(Ray& ray);

        /// Virtual function from Renderable
        Color color(Ray& ray, unsigned int reflectionCount = 0);

        /// Virtual function from Renderable
        Vector normal(const Point& position) const;

        /// Virtual function from Renderable
        Vector interpolatedNormal(const Point& position) const;

        /// Redefine function in Renderable
        void setShader(Shader* shader);

        /// Virtual function from Renderable
        bool refractedRay(const Ray& incomingRay, Ray& refractedRay);

    private:
        std::vector<Triangle> _triangles;
        BoundingBox           _bB;
        int                   _intersectedTriangle;

    };  // class Mesh

    inline void Mesh::addTriangle(const Triangle& triangle)
    {
        _triangles.push_back(triangle);
    }

    inline void Mesh::setBBLimits(const Point& min, const Point& max)
    {
        _bB.setMin(min);
        _bB.setMax(max);
    }

    inline const BoundingBox& Mesh::boundingBox(void) const
    {
        return _bB;
    }
}  // namespace MatouMalin

#endif
