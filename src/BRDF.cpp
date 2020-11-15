//===============================================================================================//
/*!
 *  \file      BRDF.cpp
 *  \author    Loïc Corenthy
 *  \version   1.0
 *  \date      14/10/2012
 *  \copyright (c) 2012 Loïc Corenthy. All rights reserved.
 */
//===============================================================================================//

#include "BRDF.hpp"

using namespace LCNS;


BRDF::BRDF(void)
: _ambientColor(Color(0.0f))
, _cubeMap(nullptr)
{
}


BRDF::BRDF(const Color& ambient)
: _ambientColor(ambient)
, _cubeMap(nullptr)
{
}


BRDF::BRDF(const BRDF& bRDF)
: _ambientColor(bRDF._ambientColor)
, _cubeMap(bRDF._cubeMap)
{
}


void BRDF::operator=(const BRDF& brdf)
{
    if (this == &brdf)
        return;

    _ambientColor = brdf._ambientColor;
    _cubeMap      = brdf._cubeMap;
}

BRDF::~BRDF(void)
{
}
