//
//  OBJParameters.cpp
//  RayTracing
//
//  Created by Loïc CORENTHY on 8/29/12.
//
//

#include "OBJParameters.hpp"


// Namespaces
using namespace MatouMalin;

OBJParameters::OBJParameters(void)
:_vertexCount(0),
 _textureCount(0),
 _normalCount(0),
 _currentFaceCount(0)
{
}

OBJParameters::OBJParameters(const OBJParameters & oBJParameters)
:_vertexCount(oBJParameters._vertexCount),
 _textureCount(oBJParameters._textureCount),
 _normalCount(oBJParameters._normalCount),
 _faceCount(oBJParameters._faceCount),
 _currentFaceCount(oBJParameters._currentFaceCount)
{

}

OBJParameters OBJParameters::operator=(const OBJParameters & oBJParameters)
{
    if (this == &oBJParameters)
        return *this;

    _vertexCount = oBJParameters._vertexCount;
    _textureCount = oBJParameters._textureCount;
    _normalCount = oBJParameters._normalCount;
    _faceCount = oBJParameters._faceCount;
    _currentFaceCount = oBJParameters._currentFaceCount;

    return *this;

}

OBJParameters::~OBJParameters(void)
{
}

