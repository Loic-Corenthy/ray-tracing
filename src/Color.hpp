//===============================================================================================//
/*!
 *  \file      Color.hpp
 *  \author    Loïc Corenthy
 *  \version   1.0
 *  \date      14/10/2012
 *  \copyright (c) 2012 Loïc Corenthy. All rights reserved.
 */
//===============================================================================================//

#pragma once

#include <cassert>

namespace LCNS
{
    class Color
    {
    public:
        /// Default constructor
        Color(void) = default;

        /// Constructor with the same value for each component
        explicit Color(double commonValue);

        /// Constructor with red, green and blue components (values between 0.0 and 1.0)
        Color(double red, double green, double blue);

        /// Constructor with red, green and blue components (values between 0 and 255)
        Color(int red, int green, int blue);

        /// Copy constructor
        Color(const Color& color);

        /// Copy operator
        Color operator=(const Color& color);

        /// Destructor
        ~Color(void) = default;

        /// Component operator (read, write)
        double& operator[](unsigned int index);

        /// Component operator (read only)
        double operator[](unsigned int index) const;

        /// Add 2 colors
        Color operator+(const Color& color) const;

        /// Add another color to the current one
        Color operator+=(const Color& color);

        /// Multiply two colors
        Color operator*(const Color& color) const;

        /// Multiply the current color by another one
        Color operator*=(const Color& color);

        /// Multiply a color by a scalar
        Color operator*(double scale) const;

        /// Scale a color
        void operator*=(double scale);

        /// Return true if all the coefficient for the 2 colors are the same, else return false
        bool operator==(const Color& color) const;

        /// Check if all the components of the color are zero
        bool isZero(void) const noexcept;

        /// Set the three component at the same time
        void set(double red, double green, double blue) noexcept;

        /// Set the three component at the same time
        void set(int red, int green, int blue) noexcept;

        /// Set red component (value between 0.0 and 1.0)
        void red(double value) noexcept;

        /// Set green component (value between 0.0 and 1.0)
        void green(double value) noexcept;

        /// Get blue component (value between 0.0 and 1.0)
        void blue(double value) noexcept;

        /// Set red component (values between 0 and 255)
        void red(int value) noexcept;

        /// Set green component (values between 0 and 255)
        void green(int value) noexcept;

        /// Get blue component (values between 0 and 255)
        void blue(int value) noexcept;

        /// Get red component (read only)
        double red(void) noexcept;

        /// Get green component (read only)
        double green(void) noexcept;

        /// Get blue component (read only)
        double blue(void) noexcept;

    private:
        /// Utility method to set the components using parameters in the range [0, 255] as values in the range [0, 1]
        constexpr void _componentsIn0to1Range(int red, int green, int blue);

    private:
        double _components[3] = { 0.0, 0.0, 0.0 };

    };  // Class Color

}  // namespace LCNS
