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
        Color(void);

        /// Constructor with the same value for each component
        Color(float commonValue);

        /// Constructor with red, green and blue components (values between 0.0 and 1.0)
        Color(float red, float green, float blue);

        /// Constructor with red, green and blue components (values between 0 and 255)
        Color(int red, int green, int blue);

        /// Copy constructor
        Color(const Color& color);

        /// Copy operator
        Color operator=(const Color& color);

        /// Destructor
        ~Color(void);

        /// Component operator (read, write)
        float& operator[](unsigned int index);

        /// Component operator (read only)
        float operator[](unsigned int index) const;

        /// Check if all the components of the color are zero
        bool isZero(void) const;

        /// Set the three component at the same time
        void setColor(float red, float green, float blue);

        /// Set the three component at the same time
        void setColor(int red, int green, int blue);

        /// Set red component (value between 0.0 and 1.0)
        void setRed(float value);

        /// Set green component (value between 0.0 and 1.0)
        void setGreen(float value);

        /// Get blue component (value between 0.0 and 1.0)
        void setBlue(float value);

        /// Set red component (values between 0 and 255)
        void setRed(int value);

        /// Set green component (values between 0 and 255)
        void setGreen(int value);

        /// Get blue component (values between 0 and 255)
        void setBlue(int value);

        /// Set blue component (read only)
        float blue(void);

        /// Get red component (read only)
        float red(void);

        /// Get green component (read only)
        float green(void);

        /// Add 2 colors
        Color operator+(const Color& color) const;

        /// Add another color to the current one
        Color operator+=(const Color& color);

        /// Multiply two colors
        Color operator*(const Color& color) const;

        /// Multiply the current color by another one
        Color operator*=(const Color& color);

        /// Multiply a color by a scalar
        Color operator*(float scale) const;

        /// Scale a color
        void operator*=(float scale);

        /// Return true if all the coefficient for the 2 colors are the same, else return false
        bool operator==(const Color& color) const;

    private:
        float              _components[3];
        static const float _inv255;

    };  // Class Color

    inline float& Color::operator[](unsigned int index)
    {
        assert(0 <= index && index <= 2 && "error index out of bounds");
        return _components[index];
    }

    inline float Color::operator[](unsigned int index) const
    {
        assert(0 <= index && index <= 2 && "error index out of bounds");
        return _components[index];
    }

    inline bool Color::isZero(void) const
    {
        return (_components[0] == 0.0f && _components[1] == 0.0f && _components[2] == 0.0f);
    }

    inline void Color::setColor(float red, float green, float blue)
    {
        _components[0] = red;
        _components[1] = green;
        _components[2] = blue;
    }

    inline void Color::setColor(int red, int green, int blue)
    {
        _components[0] = static_cast<float>(red) * _inv255;
        _components[1] = static_cast<float>(green) * _inv255;
        _components[2] = static_cast<float>(blue) * _inv255;
    }

    inline void Color::setRed(float value)
    {
        _components[0] = value;
    }

    inline void Color::setGreen(float value)
    {
        _components[1] = value;
    }

    inline void Color::setBlue(float value)
    {
        _components[2] = value;
    }

    inline void Color::setRed(int value)
    {
        _components[0] = static_cast<float>(value) * _inv255;
    }

    inline void Color::setGreen(int value)
    {
        _components[1] = static_cast<float>(value) * _inv255;
    }

    inline void Color::setBlue(int value)
    {
        _components[2] = static_cast<float>(value) * _inv255;
    }

    inline float Color::blue(void)
    {
        return _components[2];
    }

    inline float Color::red(void)
    {
        return _components[0];
    }

    inline float Color::green(void)
    {
        return _components[1];
    }

    inline Color Color::operator+(const Color& color) const
    {
        return Color(_components[0] + color._components[0], _components[1] + color._components[1], _components[2] + color._components[2]);
    }

    inline Color Color::operator+=(const Color& color)
    {
        _components[0] += color._components[0];
        _components[1] += color._components[1];
        _components[2] += color._components[2];

        return *this;
    }

    inline Color Color::operator*(const Color& color) const
    {
        return Color(_components[0] * color._components[0], _components[1] * color._components[1], _components[2] * color._components[2]);
    }

    inline Color Color::operator*=(const LCNS::Color& color)
    {
        _components[0] *= color._components[0];
        _components[1] *= color._components[1];
        _components[2] *= color._components[2];

        return *this;
    }

    inline Color Color::operator*(float scale) const
    {
        return Color(_components[0] * scale, _components[1] * scale, _components[2] * scale);
    }

    inline void Color::operator*=(float scale)
    {
        _components[0] *= scale;
        _components[1] *= scale;
        _components[2] *= scale;
    }

    inline bool Color::operator==(const Color& color) const
    {
        return (_components[0] == color._components[0] && _components[1] == color._components[1] && _components[2] == color._components[2]);
    }

}  // namespace LCNS
