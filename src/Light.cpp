//===============================================================================================//
/*!
 *  \file      Light.cpp
 *  \author    Loïc Corenthy
 *  \version   1.0
 *  \date      14/10/2012
 *  \copyright (c) 2012 Loïc Corenthy. All rights reserved.
 */
//===============================================================================================//

#include "Light.hpp"

using namespace LCNS;

Light::Light(void)
: _intensity(Color(0.0f))
{
}

Light::Light(const Color& color)
: _intensity(color)
{
}

Light::Light(const Light& light)
{
    _intensity = light._intensity;
}

void Light::operator=(const Light& light)
{
    if (this == &light)
        return;

    _intensity = light._intensity;
}

Light::~Light(void)
{
}
