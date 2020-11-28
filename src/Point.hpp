//===============================================================================================//
/*!
 *  \file      Point.hpp
 *  \author    Loïc Corenthy
 *  \version   1.0
 *  \date      14/10/2012
 *  \copyright (c) 2012 Loïc Corenthy. All rights reserved.
 */
//===============================================================================================//

#pragma once

#include <cassert>

// Local includes
#include "Vector.hpp"

namespace LCNS
{
    class Point
    {
    public:
        /// Default constructor
        Point(void) = default;

        /// Constructor with position parameters
        Point(double x, double y, double z);

        /// Constructor with same value for all coordinates
        explicit Point(double commonValue);

        /// Copy constructor
        Point(const Point& point);

        /// Destructor
        ~Point(void) = default;

        /// Copy operator
        Point& operator=(const Point& point);

        /// Coordinate operator (read only)
        double operator[](unsigned int index) const;

        /// Coordinate operator (read,write)
        double& operator[](unsigned int index);

        /// Create a vector by subtracting 2 points
        Vector operator-(const Point point) const noexcept;

        /// Translate a point by a vector
        Point operator+(const Vector vector) const noexcept;

        /// Set 3 coordinates
        void set(double x, double y, double z) noexcept;

        /// Set X coordinate
        void x(double x) noexcept;

        /// Set Y coordinate
        void y(double y) noexcept;

        /// Set Z coordinate
        void z(double z) noexcept;

        /// Get X coordinate (read only)
        double x(void) const noexcept;

        /// Get X coordinate (read only)
        double y(void) const noexcept;

        /// Get X coordinate (read only)
        double z(void) const noexcept;

        /// Get X coordinate (read/write )
        double& x(void) noexcept;

        /// Get X coordinate (read/write)
        double& y(void) noexcept;

        /// Get X coordinate (read/write)
        double& z(void) noexcept;

    private:
        double _coords[3] = { 0.0, 0.0, 0.0 };

    };  // class Point

}  // namespace LCNS
