//===============================================================================================//
/*!
 *  \file      Mesh.hpp
 *  \author    Loïc Corenthy
 *  \version   1.0
 *  \date      06/09/2012
 *  \copyright (c) 2012 Loïc Corenthy. All rights reserved.
 */
//===============================================================================================//

#pragma once

#include <cassert>
#include <vector>

#include "Renderable.hpp"
#include "Point.hpp"
#include "Vector.hpp"
#include "Shader.hpp"
#include "Triangle.hpp"
#include "BoundingBox.hpp"

namespace LCNS
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
        Color color(const Ray& ray, unsigned int reflectionCount = 0);

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
        _bB.min(min);
        _bB.max(max);
    }

    inline const BoundingBox& Mesh::boundingBox(void) const
    {
        return _bB;
    }
}  // namespace LCNS
