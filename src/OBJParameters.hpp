//===============================================================================================//
/*!
 *  \file      OBJParameters.hpp
 *  \author    Loïc Corenthy
 *  \version   1.2
 *  \date      29/09/2012
 *  \copyright (c) 2012 Loïc Corenthy. All rights reserved.
 */
//===============================================================================================//

#pragma once

#include <cassert>
#include <vector>

namespace LCNS
{
    struct OBJParameters
    {
        std::vector<unsigned int> faceCount;
        unsigned int              vertexCount      = 0u;
        unsigned int              textureCount     = 0u;
        unsigned int              normalCount      = 0u;
        unsigned int              currentFaceCount = 0u;

    };  // class OBJParameters

}  // namespace LCNS
