//===============================================================================================//
/*!
 *  \file      OBJParameters.hpp
 *  \author    Loïc Corenthy
 *  \version   1.0
 *  \date      29/09/2012
 *  \copyright (c) 2012 Loïc Corenthy. All rights reserved.
 */
//===============================================================================================//

#pragma once

#include <cassert>
#include <vector>

namespace LCNS
{
    class OBJParameters
    {
    public:
        /// Default construtor
        OBJParameters(void);

        /// Copy constructor
        OBJParameters(const OBJParameters& oBJParameters);

        /// Copy operator
        OBJParameters operator=(const OBJParameters& oBJParameters);

        /// Destructor
        ~OBJParameters(void);

        /// Get the number of vertices
        unsigned int vertexCount(void) const;

        /// Get the number of texture coordinates
        unsigned int textureCoordinatesCount(void) const;

        /// Get the number of normals
        unsigned int normalCount(void) const;

        /// Get the number of faces of each object
        unsigned int faceCount(unsigned int objectIdx) const;

        /// Get the number of objects
        unsigned int objectCount(void) const;

        /// Get the current face count
        unsigned int currentFaceCount(void) const;

        /// Set the number of vertices
        void setVertexCount(unsigned int value);

        /// Set the number of texture coordinates
        void setTextureCoordinatesCount(unsigned int value);

        /// Set the number of normals
        void setNormalCount(unsigned int value);

        /// Set the number of faces of an object
        void setFaceCount(unsigned int objectIdx, unsigned int value);

        /// Set current face count
        void setCurrentFaceCount(unsigned int value);

        /// Increase the number of vertices by one
        void vpp(void);

        /// Increase the number of texture coordinates by one
        void vtpp(void);

        /// Increase the number of normals by one
        void npp(void);

        /// Increase the number of faces by one
        void fpp(void);

        /// Increase the number of objects by one
        void opp(void);

    private:
        unsigned int              _vertexCount;
        unsigned int              _textureCount;
        unsigned int              _normalCount;
        std::vector<unsigned int> _faceCount;
        unsigned int              _currentFaceCount;

    };  // class OBJParameters

    inline unsigned int OBJParameters::vertexCount(void) const
    {
        return _vertexCount;
    }

    inline unsigned int OBJParameters::textureCoordinatesCount(void) const
    {
        return _textureCount;
    }

    inline unsigned int OBJParameters::normalCount(void) const
    {
        return _normalCount;
    }

    inline unsigned int OBJParameters::faceCount(unsigned int objectIdx) const
    {
        return _faceCount.at(objectIdx);
    }

    inline unsigned int OBJParameters::objectCount(void) const
    {
        return static_cast<unsigned int>(_faceCount.size());
    }

    inline unsigned int OBJParameters::currentFaceCount(void) const
    {
        return _currentFaceCount;
    }

    inline void OBJParameters::setVertexCount(unsigned int value)
    {
        assert(value >= 0 && "Value must be positive");
        _vertexCount = value;
    }

    inline void OBJParameters::setTextureCoordinatesCount(unsigned int value)
    {
        assert(value >= 0 && "Value must be positive");
        _textureCount = value;
    }

    inline void OBJParameters::setNormalCount(unsigned int value)
    {
        assert(value >= 0 && "Value must be positive");
        _normalCount = value;
    }

    inline void OBJParameters::setFaceCount(unsigned int objectIdx, unsigned int value)
    {
        assert(value >= 0 && "Value must be positive");
        _faceCount[objectIdx] = value;
    }

    inline void OBJParameters::setCurrentFaceCount(unsigned int value)
    {
        _currentFaceCount = value;
    }

    inline void OBJParameters::vpp(void)
    {
        ++_vertexCount;
    }

    inline void OBJParameters::vtpp(void)
    {
        ++_textureCount;
    }

    inline void OBJParameters::npp(void)
    {
        ++_normalCount;
    }

    inline void OBJParameters::fpp(void)
    {
        ++_currentFaceCount;
    }

    inline void OBJParameters::opp(void)
    {
        _faceCount.push_back(_currentFaceCount);
        _currentFaceCount = 0;
    }


}  // namespace LCNS
