//===============================================================================================//
/*!
 *  \file      Ray.hpp
 *  \author    Loïc Corenthy
 *  \version   1.1
 *  \date      14/10/2012
 *  \copyright (c) 2012 Loïc Corenthy. All rights reserved.
 */
//===============================================================================================//

#pragma once

#include <limits>
#include <cassert>
#include <memory>

#include "Point.hpp"
#include "Vector.hpp"

namespace LCNS
{
    // Forward declaration
    class Renderable;

    class Ray
    {
    public:
        /// Default constructor
        Ray(void) = default;

        /// Constructor with parameters
        Ray(const Point& origin, const Vector& direction);

        /// Copy constructor
        Ray(const Ray& ray) = default;

        /// Copy operator
        Ray& operator=(const Ray& ray) = default;

        /// Destructor
        ~Ray(void) = default;

        /// Get the origin of the ray
        const Point& origin(void) const;

        /// Set the origin of the ray
        void origin(const Point& point);

        /// Get the direction of the ray
        const Vector& direction(void) const;

        /// Set the direction of the ray
        void direction(const Vector& vector);

        /// Get the length of the ray
        double length(void) const;

        /// Set the length of the ray
        void length(double length);

        /// Get a pointer on the intersected object
        Renderable* intersected(void);

        /// Keep a pointer on the intersected object
        void intersected(Renderable* intersected);

        /// Get the intersection point
        Point intersection(void) const;

    private:
        Point       _origin;
        Vector      _direction;
        double      _length      = std::numeric_limits<double>::max();
        Renderable* _intersected = nullptr;

    };  // Class Ray

}  // namespace LCNS
