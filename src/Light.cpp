//===============================================================================================//
/*!
 *  \file      Light.cpp
 *  \author    Loïc Corenthy
 *  \version   1.2
 *  \date      14/10/2012
 *  \copyright (c) 2012 Loïc Corenthy. All rights reserved.
 */
//===============================================================================================//

#include "Light.hpp"
#include "Color.hpp"

using LCNS::Color;
using LCNS::Light;

Light::Light(const Color& color)
: _intensity(color)
{
}

void Light::intensity(const LCNS::Color& color)
{
    _intensity = color;
}

Color Light::intensity(void) const
{
    return _intensity;
}
