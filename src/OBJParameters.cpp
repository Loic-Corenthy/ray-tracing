//===============================================================================================//
/*!
 *  \file      OBJParameters.cpp
 *  \author    Loïc Corenthy
 *  \version   1.0
 *  \date      29/09/2012
 *  \copyright (c) 2012 Loïc Corenthy. All rights reserved.
 */
//===============================================================================================//

#include "OBJParameters.hpp"

using namespace LCNS;

OBJParameters::OBJParameters(void)
: _vertexCount(0)
, _textureCount(0)
, _normalCount(0)
, _currentFaceCount(0)
{
}

OBJParameters::OBJParameters(const OBJParameters& oBJParameters)
: _vertexCount(oBJParameters._vertexCount)
, _textureCount(oBJParameters._textureCount)
, _normalCount(oBJParameters._normalCount)
, _faceCount(oBJParameters._faceCount)
, _currentFaceCount(oBJParameters._currentFaceCount)
{
}

OBJParameters OBJParameters::operator=(const OBJParameters& oBJParameters)
{
    if (this == &oBJParameters)
        return *this;

    _vertexCount      = oBJParameters._vertexCount;
    _textureCount     = oBJParameters._textureCount;
    _normalCount      = oBJParameters._normalCount;
    _faceCount        = oBJParameters._faceCount;
    _currentFaceCount = oBJParameters._currentFaceCount;

    return *this;
}

OBJParameters::~OBJParameters(void)
{
}
