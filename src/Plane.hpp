//===============================================================================================//
/*!
 *  \file      Plane.hpp
 *  \author    Loïc Corenthy
 *  \version   1.0
 *  \date      12/10/2012
 *  \copyright (c) 2012 Loïc Corenthy. All rights reserved.
 */
//===============================================================================================//

#pragma once

#include <cassert>

#include "Point.hpp"
#include "Vector.hpp"
#include "Ray.hpp"

namespace LCNS
{
    class Plane
    {
    public:
        /// Default constructor
        Plane(void) = default;

        /// Constructor with equation coefficients
        Plane(double a, double b, double c, double d);

        /// Constructor with position and normal direction
        Plane(const Vector& normal, const Point& position);

        /// Copy constructor
        Plane(const Plane& plane);

        /// Copy operator
        Plane& operator=(const Plane& plane);

        /// Destructor
        ~Plane(void) = default;

        /// Calculate the intersection with a ray
        bool intersect(Ray& ray);

        /// Set the coefficients of the equation
        void coefficient(unsigned int index, double value);

        /// Set the normal vector
        void normal(const Vector& normal);

        /// Set the position in space
        void position(const Point& position);

        /// Get the coefficients of the equation
        double coefficient(unsigned int index) const;

        /// Get the normal vector
        Vector normal(void) const;

        /// Get the position in space
        Point position(void) const;

    private:
        /// Update the equation with the normal and the position
        void _updateEquation(void);

        /// Update the normal with the equation
        void _updateNormal(void);

        /// Update the position with the equation
        void _updatePosition(void);

    private:
        double _equationCoeffs[4] = { 0.0, 0.0, 0.0, 0.0 };
        Point  _position;
        Vector _normal;

    };  // class Plane

}  // namespace LCNS
