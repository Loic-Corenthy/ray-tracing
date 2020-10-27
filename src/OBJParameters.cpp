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
:mVertexCount(0),
 mTextureCount(0),
 mNormalCount(0),
 mCurrentFaceCount(0)
{
}

OBJParameters::OBJParameters(const OBJParameters & pOBJParameters)
:mVertexCount(pOBJParameters.mVertexCount),
 mTextureCount(pOBJParameters.mTextureCount),
 mNormalCount(pOBJParameters.mNormalCount),
 mFaceCount(pOBJParameters.mFaceCount),
 mCurrentFaceCount(pOBJParameters.mCurrentFaceCount)
{

}

OBJParameters OBJParameters::operator=(const OBJParameters & pOBJParameters)
{
    if (this == &pOBJParameters)
        return *this;
    
    mVertexCount = pOBJParameters.mVertexCount;
    mTextureCount = pOBJParameters.mTextureCount;
    mNormalCount = pOBJParameters.mNormalCount;
    mFaceCount = pOBJParameters.mFaceCount;
    mCurrentFaceCount = pOBJParameters.mCurrentFaceCount;
    
    return *this;
    
}

OBJParameters::~OBJParameters(void)
{
}

