//===============================================================================================//
/*!
 *  \file      Color.cpp
 *  \author    Loïc Corenthy
 *  \version   1.2
 *  \date      14/10/2012
 *  \copyright (c) 2012 Loïc Corenthy. All rights reserved.
 */
//===============================================================================================//

#include "Color.hpp"

using namespace LCNS;

Color::Color(double commonValue)
: _components{ commonValue, commonValue, commonValue }
{
}

Color::Color(double red, double green, double blue)
: _components{ red, green, blue }
{
}

Color::Color(int red, int green, int blue)
{
    _componentsIn0to1Range(red, green, blue);
}

Color::Color(const Color& color)
{
    for (unsigned int i = 0; i < 3; ++i)
        _components[i].exchange(color._components[i].load());
}

Color Color::operator=(const Color& color)
{
    if (this == &color)
        return *this;

    for (unsigned int i = 0; i < 3; ++i)
        _components[i].exchange(color._components[i].load());

    return *this;
}

void Color::_componentsIn0to1Range(int red, int green, int blue)
{
    _components[0].exchange(static_cast<double>(red) / 255.0);
    _components[1].exchange(static_cast<double>(green) / 255.0);
    _components[2].exchange(static_cast<double>(blue) / 255.0);
}

double Color::operator[](unsigned int index) const
{
    assert(index <= 2 && "error index out of bounds");
    return _components[index];
}

Color Color::operator+(const Color& color) const
{
    return Color(_components[0].load() + color._components[0].load(),
                 _components[1].load() + color._components[1].load(),
                 _components[2].load() + color._components[2].load());
}

Color Color::operator+=(const Color& color)
{
    for (unsigned int i = 0; i < 3; ++i)
        _components[i].exchange(_components[i].load() + color._components[i].load());

    return *this;
}

Color Color::operator*(const Color& color) const
{
    return Color(_components[0].load() * color._components[0].load(),
                 _components[1].load() * color._components[1].load(),
                 _components[2].load() * color._components[2].load());
}

Color Color::operator*=(const LCNS::Color& color)
{
    for (unsigned int i = 0; i < 3; ++i)
        _components[i].exchange(_components[i].load() * color._components[i].load());

    return *this;
}

Color Color::operator*(double scale) const
{
    return Color(_components[0].load() * scale, _components[1].load() * scale, _components[2].load() * scale);
}

void Color::operator*=(double scale)
{
    for (unsigned int i = 0; i < 3; ++i)
        _components[i].exchange(_components[i].load() * scale);
}

bool Color::operator==(const Color& color) const
{
    return (_components[0].load() == color._components[0].load() && _components[1].load() == color._components[1].load()
            && _components[2].load() == color._components[2].load());
}

bool Color::isZero(void) const noexcept
{
    return (_components[0].load() == 0.0 && _components[1].load() == 0.0 && _components[2].load() == 0.0);
}

void Color::set(double red, double green, double blue) noexcept
{
    _components[0].exchange(red);
    _components[1].exchange(green);
    _components[2].exchange(blue);
}

void Color::set(int red, int green, int blue) noexcept
{
    _componentsIn0to1Range(red, green, blue);
}

void Color::red(double value) noexcept
{
    _components[0].exchange(value);
}

void Color::green(double value) noexcept
{
    _components[1].exchange(value);
}

void Color::blue(double value) noexcept
{
    _components[2].exchange(value);
}

void Color::red(int value) noexcept
{
    _components[0].exchange(static_cast<double>(value) / 255.0);
}

void Color::green(int value) noexcept
{
    _components[1].exchange(static_cast<double>(value) / 255.0);
}

void Color::blue(int value) noexcept
{
    _components[2].exchange(static_cast<double>(value) / 255.0);
}

double Color::red(void) const noexcept
{
    return _components[0].load();
}

double Color::green(void) const noexcept
{
    return _components[1].load();
}

double Color::blue(void) const noexcept
{
    return _components[2].load();
}

void Color::clampBetweenZeroAndOne(void) noexcept
{
    for (unsigned int i = 0; i < 3; ++i)
    {
        if (_components[i].load() < 0.0)
        {
            _components[i].exchange(0.0);
        }
        else if (1.0 < _components[i].load())
        {
            _components[i].exchange(1.0);
        }
    }
}
