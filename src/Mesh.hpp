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

#include <c++/10.2.0/optional>
#include <cassert>
#include <memory>
#include <optional>
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
        explicit Mesh(unsigned int triangleCount);

        /// Copy constructor
        Mesh(const Mesh& mesh) = delete;

        /// Copy operator
        Mesh operator=(const Mesh& mesh) = delete;

        /// Destructor
        ~Mesh(void) = default;

        /// Add a triangle to the mesh
        void addTriangle(const Triangle& triangle);

        /// Set min and max point in bounding box
        void boundingBoxLimits(const Point& min, const Point& max);

        /// Get bounding box (read only)
        const BoundingBox& boundingBox(void) const;

        /// Virtual function from Renderable
        bool intersect(Ray& ray) override;

        /// Virtual function from Renderable
        Color color(const Ray& ray, unsigned int reflectionCount = 0) override;

        /// Virtual function from Renderable
        Vector normal(const Point& position) const override;

        /// Virtual function from Renderable
        Vector interpolatedNormal(const Point& position) const override;

        /// Redefine function in Renderable
        void shader(std::shared_ptr<Shader> shader) override;

        /// Virtual function from Renderable
        std::optional<Ray> refractedRay(const Ray& incomingRay) override;

    private:
        std::vector<Triangle> _triangles;
        BoundingBox           _boundingBox;
        int                   _intersectedTriangle = -1;

    };  // class Mesh

}  // namespace LCNS
