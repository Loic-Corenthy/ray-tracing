//===============================================================================================//
/*!
 *  \file      Color.cpp
 *  \author    Loïc Corenthy
 *  \version   1.0
 *  \date      14/10/2012
 *  \copyright (c) 2012 Loïc Corenthy. All rights reserved.
 */
//===============================================================================================//

#include "Color.hpp"

using namespace LCNS;

Color::Color(float commonValue)
: _components{ commonValue, commonValue, commonValue }
{
}

Color::Color(float red, float green, float blue)
: _components{ red, green, blue }
{
}

Color::Color(int red, int green, int blue)
{
    _componentsIn0to1Range(red, green, blue);
}

Color::Color(const Color& color)
{
    _components[0] = color._components[0];
    _components[1] = color._components[1];
    _components[2] = color._components[2];
}

Color Color::operator=(const Color& color)
{
    if (this == &color)
        return *this;

    _components[0] = color._components[0];
    _components[1] = color._components[1];
    _components[2] = color._components[2];

    return *this;
}

constexpr void Color::_componentsIn0to1Range(int red, int green, int blue)
{
    _components[0] = static_cast<float>(red) / 255.0f;
    _components[1] = static_cast<float>(green) / 255.0f;
    _components[2] = static_cast<float>(blue) / 255.0f;
}

float& Color::operator[](unsigned int index)
{
    assert(index <= 2 && "error index out of bounds");
    return _components[index];
}

float Color::operator[](unsigned int index) const
{
    assert(index <= 2 && "error index out of bounds");
    return _components[index];
}

Color Color::operator+(const Color& color) const
{
    return Color(_components[0] + color._components[0], _components[1] + color._components[1], _components[2] + color._components[2]);
}

Color Color::operator+=(const Color& color)
{
    _components[0] += color._components[0];
    _components[1] += color._components[1];
    _components[2] += color._components[2];

    return *this;
}

Color Color::operator*(const Color& color) const
{
    return Color(_components[0] * color._components[0], _components[1] * color._components[1], _components[2] * color._components[2]);
}

Color Color::operator*=(const LCNS::Color& color)
{
    _components[0] *= color._components[0];
    _components[1] *= color._components[1];
    _components[2] *= color._components[2];

    return *this;
}

Color Color::operator*(float scale) const
{
    return Color(_components[0] * scale, _components[1] * scale, _components[2] * scale);
}

void Color::operator*=(float scale)
{
    _components[0] *= scale;
    _components[1] *= scale;
    _components[2] *= scale;
}

bool Color::operator==(const Color& color) const
{
    return (_components[0] == color._components[0] && _components[1] == color._components[1] && _components[2] == color._components[2]);
}

bool Color::isZero(void) const noexcept
{
    return (_components[0] == 0.0f && _components[1] == 0.0f && _components[2] == 0.0f);
}

void Color::set(float red, float green, float blue) noexcept
{
    _components[0] = red;
    _components[1] = green;
    _components[2] = blue;
}

void Color::set(int red, int green, int blue) noexcept
{
    _componentsIn0to1Range(red, green, blue);
}

void Color::red(float value) noexcept
{
    _components[0] = value;
}

void Color::green(float value) noexcept
{
    _components[1] = value;
}

void Color::blue(float value) noexcept
{
    _components[2] = value;
}

void Color::red(int value) noexcept
{
    _components[0] = static_cast<float>(value) / 255.0f;
}

void Color::green(int value) noexcept
{
    _components[1] = static_cast<float>(value) / 255.0f;
}

void Color::blue(int value) noexcept
{
    _components[2] = static_cast<float>(value) / 255.0f;
}

float Color::red(void) noexcept
{
    return _components[0];
}

float Color::green(void) noexcept
{
    return _components[1];
}

float Color::blue(void) noexcept
{
    return _components[2];
}
