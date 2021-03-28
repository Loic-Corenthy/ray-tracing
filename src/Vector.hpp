//===============================================================================================//
/*!
 *  \file      Vector.hpp
 *  \author    Loïc Corenthy
 *  \version   1.2
 *  \date      14/10/2012
 *  \copyright (c) 2012 Loïc Corenthy. All rights reserved.
 */
//===============================================================================================//

#pragma once

#include <cmath>
#include <array>
#include <cassert>

namespace LCNS
{
    class Vector
    {
    public:
        /// Default constructor
        Vector(void) = default;

        /// Constructor with coordinates parameters
        Vector(double x, double y, double z);

        /// Constructor with same value for all coordinates
        explicit Vector(double commonValue);

        /// Copy constructor
        Vector(const Vector& vector) = default;

        /// Move constructor
        Vector(Vector&& vector) = default;

        /// Copy the coordinates of a vector to another one
        Vector& operator=(const Vector& vector) = default;

        /// Move assignment operator
        Vector& operator=(Vector&& vector) = default;

        /// Destructor
        ~Vector(void) = default;

        /// Coordinate operator (read only)
        double operator[](unsigned int index) const;

        /// Coordinate operator (read, write)
        double& operator[](unsigned int index);

        /// Set all coordinates at once
        void setVector(double x, double y, double z) noexcept;

        /// Set X coordinate
        void setX(double x) noexcept;

        /// Set Y coordinate
        void setY(double y) noexcept;

        /// Set Z coordinate
        void setZ(double z) noexcept;

        /// Get X coordinate
        double x(void) const noexcept;

        /// Get X coordinate
        double y(void) const noexcept;

        /// Get X coordinate
        double z(void) const noexcept;

        /// Return the vector sum of 2 vectors
        Vector operator+(const Vector& vector) const;

        /// Return the vector difference of 2 vectors
        Vector operator-(const Vector& vector) const;

        /// Add a vector to the current one
        Vector operator+=(const Vector& vector);

        /// Substract a vector to the current one
        Vector operator-=(const Vector& vector);

        /// Multiply a vector by a scalar
        Vector operator*(double scalar) const;

        /// Scalar product of 2 vectors
        double operator*(const Vector& vector) const;

        /// Dot product of 2 vectors
        Vector operator^(const Vector& vector) const;

        /// Return the length of the vector
        double length(void) const;

        /// Return the square length of a the vector
        double lengthSqr(void) const;

        /// Divide a vector by it's length and return it.
        Vector normalize(void);

    private:
        std::array<double, 3> _coords = { 0.0, 0.0, 0.0 };

    };  // class Vector

}  // namespace LCNS
