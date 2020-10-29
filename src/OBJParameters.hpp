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
        unsigned int                mVertexCount;
        unsigned int                mTextureCount;
        unsigned int                mNormalCount;
        std::vector<unsigned int>   mFaceCount;
        unsigned int                mCurrentFaceCount;

    }; // class OBJParameters

    inline unsigned int OBJParameters::vertexCount(void) const
    {
        return mVertexCount;
    }

    inline unsigned int OBJParameters::textureCoordinatesCount(void) const
    {
        return mTextureCount;
    }

    inline unsigned int OBJParameters::normalCount(void) const
    {
        return mNormalCount;
    }

    inline unsigned int OBJParameters::faceCount(unsigned int pObjectIdx) const
    {
        return mFaceCount.at(pObjectIdx);
    }

    inline unsigned int OBJParameters::objectCount(void) const
    {
        return static_cast<unsigned int>(mFaceCount.size());
    }

    inline unsigned int OBJParameters::currentFaceCount(void) const
    {
        return mCurrentFaceCount;
    }

    inline void OBJParameters::setVertexCount(unsigned int pValue)
    {
        assert(pValue >= 0 && "Value must be positive");
        mVertexCount = pValue;
    }

    inline void OBJParameters::setTextureCoordinatesCount(unsigned int pValue)
    {
        assert(pValue >= 0 && "Value must be positive");
        mTextureCount = pValue;
    }

    inline void OBJParameters::setNormalCount(unsigned int pValue)
    {
        assert(pValue >= 0 && "Value must be positive");
        mNormalCount = pValue;
    }

    inline void OBJParameters::setFaceCount(unsigned int pObjectIdx, unsigned int pValue)
    {
        assert(pValue >= 0 && "Value must be positive");
        mFaceCount[pObjectIdx] = pValue;
    }

    inline void OBJParameters::setCurrentFaceCount(unsigned int pValue)
    {
        mCurrentFaceCount = pValue;
    }

    inline void OBJParameters::vpp(void)
    {
        ++mVertexCount;
    }

    inline void OBJParameters::vtpp(void)
    {
        ++mTextureCount;
    }

    inline void OBJParameters::npp(void)
    {
        ++mNormalCount;
    }

    inline void OBJParameters::fpp(void)
    {
        ++mCurrentFaceCount;
    }

    inline void OBJParameters::opp(void)
    {
        mFaceCount.push_back(mCurrentFaceCount);
        mCurrentFaceCount = 0;
    }


} // namespace MatouMalin

#endif
