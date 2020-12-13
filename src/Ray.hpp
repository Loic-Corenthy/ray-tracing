//===============================================================================================//
/*!
 *  \file      Ray.hpp
 *  \author    Loïc Corenthy
 *  \version   1.0
 *  \date      14/10/2012
 *  \copyright (c) 2012 Loïc Corenthy. All rights reserved.
 */
//===============================================================================================//

#pragma once

#include <limits>
#include <cassert>

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
        Ray(void);

        /// Constructor with parameters
        Ray(const Point& origin, const Vector& direction);

        /// Copy constructor
        Ray(const Ray& ray);

        /// Copy operator
        Ray operator=(const Ray& ray);

        /// Destructor
        ~Ray(void);

        /// Set the origin of the ray
        void setOrigin(const Point& point);

        /// Set the direction of the ray
        void setDirection(const Vector& vector);

        /// Set the length of the ray
        void setLength(double length);

        /// Keep a pointer on the intersected object
        void setIntersected(Renderable* intersected);

        /// Get the origin of the ray
        const Point& origin(void) const;

        /// Get the direction of the ray
        const Vector& direction(void) const;

        /// Get the length of the ray
        double length(void) const;

        /// Get a pointer on the intersected object
        Renderable* intersected(void) const;

        /// Get the intersection point
        Point intersection(void) const;


    private:
        Point       _origin;
        Vector      _direction;
        double      _length;
        Renderable* _intersected;

    };  // Class Ray


}  // namespace LCNS
