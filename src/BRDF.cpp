//===============================================================================================//
/*!
 *  \file      BRDF.cpp
 *  \author    Loïc Corenthy
 *  \version   1.1
 *  \date      14/10/2012
 *  \copyright (c) 2012 Loïc Corenthy. All rights reserved.
 */
//===============================================================================================//

#include "BRDF.hpp"

#include <memory>

#include "Color.hpp"
#include "CubeMap.hpp"
#include "Point.hpp"

using std::shared_ptr;

using LCNS::BRDF;
using LCNS::Color;
using LCNS::CubeMap;
using LCNS::Point;

BRDF::BRDF(const Color& ambient)
: _ambientColor(ambient)
{
}

void BRDF::ambient(const Color& ambient)
{
    _ambientColor = ambient;
}

Color BRDF::ambient(void) const
{
    return _ambientColor;
}

void BRDF::cubeMap(shared_ptr<CubeMap> cubeMap)
{
    _cubeMap = cubeMap;
}

const shared_ptr<CubeMap> BRDF::cubeMap(void) const
{
    return _cubeMap;
}
