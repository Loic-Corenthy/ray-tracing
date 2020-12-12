//===============================================================================================//
/*!
 *  \file      Triangle.hpp
 *  \author    Loïc Corenthy
 *  \version   1.0
 *  \date      14/10/2012
 *  \copyright (c) 2012 Loïc Corenthy. All rights reserved.
 */
//===============================================================================================//

#pragma once

#include <cassert>
#include <array>
#include <type_traits>
#include <optional>

#include "Renderable.hpp"
#include "Point.hpp"
#include "Vector.hpp"
#include "Shader.hpp"

namespace LCNS
{
    // Forward declaration
    class Ray;

    class Triangle : public Renderable
    {
    public:
        /// Default constructor
        Triangle(void) = default;

        /// Constructor with vertices parameters
        Triangle(const Point& point0, const Point& point1, const Point& point2);

        /// Copy constructor
        Triangle(const Triangle& triangle);

        /// Copy operator
        Triangle& operator=(const Triangle& triangle);

        /// Destructor
        ~Triangle(void) = default;

        /// Get the position of the vertices (read only)
        const std::array<Point, 3>& vertexPositions(void) const;

        /// Get the position of the vertices (read / write)
        std::array<Point, 3>& vertexPositions(void);

        /// Get the normal of the vertices (read only)
        const std::array<Vector, 3>& vertexNormals(void) const;

        /// Get the normal of the vertices (read / write)
        std::array<Vector, 3>& vertexNormals(void);

        /// Set the normal of the triangle
        void normal(const Vector& normal);

        /// Calculate the normal vector of the triangle
        void updateNormal(void);

        /// Virtual function from Renderable
        bool intersect(Ray& ray) override;

        /// Virtual function from Renderable
        Color color(const Ray& ray, unsigned int reflectionCount = 0) override;

        /// Virtual function, get the normal at the intersection point
        Vector normal(const Point& position) const override;

        /// Virtual function, get the normal at the intersection point (interpolating from other vectors)
        Vector interpolatedNormal(const Point& position) const override;

        /// Virtual function from Renderable
        std::optional<Ray> refractedRay(const Ray& incomingRay) override;

    private:
        /// Calculate determinant of a 2x2 matrix
        float _det(float a1, float a2, float b1, float b2);

        /// Calculate barycentric interpolation of normal from vertex normals
        Vector _barycentricNormal(const Point& positionInTriangle) const;

    private:
        std::array<Point, 3>  _vertexPosition;
        std::array<Vector, 3> _vertexNormal;
        Vector                _normal;

    };  // class Triangle

}  // namespace LCNS
