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

OBJParameters::OBJParameters(const OBJParameters & pOBJParameters)
:_vertexCount(pOBJParameters._vertexCount),
 _textureCount(pOBJParameters._textureCount),
 _normalCount(pOBJParameters._normalCount),
 _faceCount(pOBJParameters._faceCount),
 _currentFaceCount(pOBJParameters._currentFaceCount)
{

}

OBJParameters OBJParameters::operator=(const OBJParameters & pOBJParameters)
{
    if (this == &pOBJParameters)
        return *this;

    _vertexCount = pOBJParameters._vertexCount;
    _textureCount = pOBJParameters._textureCount;
    _normalCount = pOBJParameters._normalCount;
    _faceCount = pOBJParameters._faceCount;
    _currentFaceCount = pOBJParameters._currentFaceCount;

    return *this;

}

OBJParameters::~OBJParameters(void)
{
}

