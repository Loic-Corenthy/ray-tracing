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
        Triangle(void);

        /// Constructor with vertices parameters
        Triangle(const Point& point0, const Point& point1, const Point& point2);

        /// Copy constructor
        Triangle(const Triangle& triangle);

        /// Destructor
        ~Triangle(void);

        /// Vertex operator (read only)
        Point operator[](unsigned int index) const;

        /// Vertex operator (read, write)
        Point& operator[](unsigned int index);

        /// Get vertex 0, (read only)
        const Point& v0(void) const;

        /// Get vertex 1, (read only)
        const Point& v1(void) const;

        /// Get vertex 2, (read only)
        const Point& v2(void) const;

        /// Set vertex 0
        void setV0(const Point& point);

        /// Set vertex 1
        void setV1(const Point& point);

        /// Set vertex 2
        void setV2(const Point& point);

        /// Set vertex with index
        void setVI(unsigned int index, const Point& point);

        /// Set the normal of each vertex with index
        void setVertexNormal(unsigned int index, const Vector& vertexNormal);

        /// Calculate the normal vector of the triangle
        void updateNormal(void);

        /// Virtual function from Renderable
        bool intersect(Ray& ray);

        /// Virtual function from Renderable
        Color color(Ray& ray, unsigned int reflectionCount = 0);

        /// Virtual function, get the normal at the intersection point (the position is not taken into account for the moment :p)
        Vector normal(const Point& position) const;

        /// Virtual function, get the normal at the intersection point (interpolating from other vectors)
        Vector interpolatedNormal(const Point& position) const;

        /// Virtual function from Renderable
        bool refractedRay(const Ray& incomingRay, Ray& refractedRay);

        /// Set the normal of the triangle
        void setNormal(const Vector& normal);

    private:
        /// Calculate determinant of a 2x2 matrix
        float _det(float a1, float a2, float b1, float b2);

        /// Calculate barycentric interpolation of normal from vertex normals
        Vector _barycentricNormal(const Point& positionInTriangle) const;

    private:
        Point  _vertice[3];
        Vector _vertexNormal[3];
        Vector _normal;

    };  // class Triangle

    inline Point Triangle::operator[](unsigned int index) const
    {
        return _vertice[index];
    }

    inline Point& Triangle::operator[](unsigned int index)
    {
        return _vertice[index];
    }

    inline const Point& Triangle::v0(void) const
    {
        return _vertice[0];
    }

    inline const Point& Triangle::v1(void) const
    {
        return _vertice[1];
    }

    inline const Point& Triangle::v2(void) const
    {
        return _vertice[2];
    }

    inline void Triangle::setV0(const Point& point)
    {
        _vertice[0] = point;
    }

    inline void Triangle::setV1(const Point& point)
    {
        _vertice[1] = point;
    }

    inline void Triangle::setV2(const Point& point)
    {
        _vertice[2] = point;
    }

    inline void Triangle::setVI(unsigned int index, const LCNS::Point& point)
    {
        assert(index == 0 || index == 1 || index == 2 && "Index must be 0,1 or 2");
        _vertice[index] = point;
    }

    inline void Triangle::setVertexNormal(unsigned int index, const LCNS::Vector& vertexNormal)
    {
        assert(index == 0 || index == 1 || index == 2 && "Index must be 0,1 or 2");
        _vertexNormal[index] = vertexNormal;
    }

    inline float Triangle::_det(float a1, float a2, float b1, float b2)
    {
        return (a1 * b2 - a2 * b1);
    }

    inline Vector Triangle::normal(const Point& position) const
    {
        return _barycentricNormal(position);
        return _normal;
    }

    inline void Triangle::setNormal(const Vector& normal)
    {
        _normal = normal;
    }

}  // namespace LCNS
