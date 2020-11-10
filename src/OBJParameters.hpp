//
//  OBJParameters.h
//  RayTracing
//
//  Created by Loïc CORENTHY on 8/29/12.
//
//

#ifndef RAYTRACING_OBJPARAMETERS_H
#define RAYTRACING_OBJPARAMETERS_H

#include <cassert>
#include <vector>

namespace MatouMalin
{
    class OBJParameters
    {
    public:
        /// Default construtor
        OBJParameters(void);

        /// Copy constructor
        OBJParameters(const OBJParameters & pOBJParameters);

        /// Copy operator
        OBJParameters operator=(const OBJParameters & pOBJParameters);

        /// Destructor
        ~OBJParameters(void);

        /// Get the number of vertices
        unsigned int vertexCount(void) const;

        /// Get the number of texture coordinates
        unsigned int textureCoordinatesCount(void) const;

        /// Get the number of normals
        unsigned int normalCount(void) const;

        /// Get the number of faces of each object
        unsigned int faceCount(unsigned int pObjectIdx) const;

        /// Get the number of objects
        unsigned int objectCount(void) const;

        /// Get the current face count
        unsigned int currentFaceCount(void) const;

        /// Set the number of vertices
        void setVertexCount(unsigned int pValue);

        /// Set the number of texture coordinates
        void setTextureCoordinatesCount(unsigned int pValue);

        /// Set the number of normals
        void setNormalCount(unsigned int pValue);

        /// Set the number of faces of an object
        void setFaceCount(unsigned int pObjectIdx, unsigned int pValue);

        /// Set current face count
        void setCurrentFaceCount(unsigned int pValue);

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
        unsigned int                _vertexCount;
        unsigned int                _textureCount;
        unsigned int                _normalCount;
        std::vector<unsigned int>   _faceCount;
        unsigned int                _currentFaceCount;

    }; // class OBJParameters

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

    inline unsigned int OBJParameters::faceCount(unsigned int pObjectIdx) const
    {
        return _faceCount.at(pObjectIdx);
    }

    inline unsigned int OBJParameters::objectCount(void) const
    {
        return static_cast<unsigned int>(_faceCount.size());
    }

    inline unsigned int OBJParameters::currentFaceCount(void) const
    {
        return _currentFaceCount;
    }

    inline void OBJParameters::setVertexCount(unsigned int pValue)
    {
        assert(pValue >= 0 && "Value must be positive");
        _vertexCount = pValue;
    }

    inline void OBJParameters::setTextureCoordinatesCount(unsigned int pValue)
    {
        assert(pValue >= 0 && "Value must be positive");
        _textureCount = pValue;
    }

    inline void OBJParameters::setNormalCount(unsigned int pValue)
    {
        assert(pValue >= 0 && "Value must be positive");
        _normalCount = pValue;
    }

    inline void OBJParameters::setFaceCount(unsigned int pObjectIdx, unsigned int pValue)
    {
        assert(pValue >= 0 && "Value must be positive");
        _faceCount[pObjectIdx] = pValue;
    }

    inline void OBJParameters::setCurrentFaceCount(unsigned int pValue)
    {
        _currentFaceCount = pValue;
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


} // namespace MatouMalin

#endif
