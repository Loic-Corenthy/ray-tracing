#ifndef RAYTRACING_COLOR_H
#define RAYTRACING_COLOR_H

// Standard include
#include <cassert>

namespace MatouMalin
{
    class Color
    {
    public:
        /// Default constructor
        Color(void);

        /// Constructor with the same value for each component
        Color(float pCommonValue);

        /// Constructor with red, green and blue components (values between 0.0 and 1.0)
        Color(float pRed,float pGreen, float pBlue);

        /// Constructor with red, green and blue components (values between 0 and 255)
        Color(int pRed, int pGreen, int pBlue);

        /// Copy constructor
        Color(const Color & pColor);

        /// Copy operator
        Color operator=(const Color & pColor);

        /// Destructor
        ~Color(void);

        /// Component operator (read, write)
        float & operator[](unsigned int pIndex);

        /// Component operator (read only)
        float operator[](unsigned int pIndex) const;

        /// Check if all the components of the color are zero
        bool isZero(void) const;

        /// Set the three component at the same time
        void setColor(float pRed,float pGreen, float pBlue);

        /// Set the three component at the same time
        void setColor(int pRed,int pGreen, int pBlue);

        /// Set red component (value between 0.0 and 1.0)
        void setRed(float pValue);

        /// Set green component (value between 0.0 and 1.0)
        void setGreen(float pValue);

        /// Get blue component (value between 0.0 and 1.0)
        void setBlue(float pValue);

        /// Set red component (values between 0 and 255)
        void setRed(int pValue);

        /// Set green component (values between 0 and 255)
        void setGreen(int pValue);

        /// Get blue component (values between 0 and 255)
        void setBlue(int pValue);

        /// Set blue component (read only)
        float blue(void);

        /// Get red component (read only)
        float red(void);

        /// Get green component (read only)
        float green(void);

        /// Add 2 colors
        Color operator+(const Color & pColor) const;

        /// Add another color to the current one
        Color operator+=(const Color & pColor);

        /// Multiply two colors
        Color operator*(const Color & pColor) const;

        /// Multiply the current color by another one
        Color operator*=(const Color & pColor);

        /// Multiply a color by a scalar
        Color operator*(float pScale) const;

        /// Scale a color
        void operator*=(float pScale);

        /// Return true if all the coefficient for the 2 colors are the same, else return false
        bool operator==(const Color & pColor) const;

    private:
        float               _components[3];
        static const float  _inv255;

    }; // Class Color

    inline float & Color::operator[](unsigned int pIndex)
    {
        assert(0 <= pIndex && pIndex <= 2 && "error index out of bounds");
        return _components[pIndex];
    }

    inline float Color::operator[](unsigned int pIndex) const
    {
        assert(0 <= pIndex && pIndex <= 2 && "error index out of bounds");
        return _components[pIndex];
    }

    inline bool Color::isZero(void) const
    {
        return (_components[0] == 0.0f && _components[1] == 0.0f && _components[2] == 0.0f);
    }

    inline void Color::setColor(float pRed, float pGreen, float pBlue)
    {
        _components[0] = pRed;
        _components[1] = pGreen;
        _components[2] = pBlue;
    }

    inline void Color::setColor(int pRed, int pGreen, int pBlue)
    {
        _components[0] = static_cast<float>(pRed)*_inv255;
        _components[1] = static_cast<float>(pGreen)*_inv255;
        _components[2] = static_cast<float>(pBlue)*_inv255;
    }

    inline void Color::setRed(float pValue)
    {
        _components[0] = pValue;
    }

    inline void Color::setGreen(float pValue)
    {
        _components[1] = pValue;
    }

    inline void Color::setBlue(float pValue)
    {
        _components[2] = pValue;
    }

    inline void Color::setRed(int pValue)
    {
        _components[0] = static_cast<float>(pValue)*_inv255;
    }

    inline void Color::setGreen(int pValue)
    {
        _components[1] = static_cast<float>(pValue)*_inv255;
    }

    inline void Color::setBlue(int pValue)
    {
        _components[2] = static_cast<float>(pValue)*_inv255;
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

    inline Color Color::operator+(const Color & pColor) const
    {
        return Color(_components[0] + pColor._components[0], _components[1] + pColor._components[1], _components[2] + pColor._components[2]);
    }

    inline Color Color::operator+=(const Color & pColor)
    {
        _components[0] += pColor._components[0];
        _components[1] += pColor._components[1];
        _components[2] += pColor._components[2];

        return *this;
    }

    inline Color Color::operator*(const Color & pColor) const
    {
        return Color(_components[0]*pColor._components[0], _components[1]*pColor._components[1], _components[2]*pColor._components[2]);
    }

    inline Color Color::operator*=(const MatouMalin::Color & pColor)
    {
        _components[0] *= pColor._components[0];
        _components[1] *= pColor._components[1];
        _components[2] *= pColor._components[2];

        return *this;
    }

    inline Color Color::operator*(float pScale) const
    {
        return Color(_components[0]*pScale,_components[1]*pScale,_components[2]*pScale);
    }

    inline void Color::operator*=(float pScale)
    {
        _components[0] *= pScale;
        _components[1] *= pScale;
        _components[2] *= pScale;
    }

    inline bool Color::operator==(const Color & pColor) const
    {
        return (_components[0] == pColor._components[0] && _components[1] == pColor._components[1] && _components[2] == pColor._components[2]);
    }

} // namespace MatouMalin

#endif