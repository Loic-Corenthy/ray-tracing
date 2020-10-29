//
//  CubeMap.h
//  RayTracing
//
//  Created by Loïc CORENTHY on 10/14/12.
//
//

#ifndef RAYTRACING_CUBEMAP_H
#define RAYTRACING_CUBEMAP_H

// Standard includes
#include <vector>
#include <map>
#include <string>

// Local includes
#include "Point.hpp"
#include "Image.hpp"

namespace MatouMalin
{
    class Color;
    class Ray;

    class CubeMap
    {
    public:
        enum Faces : unsigned short {UNASSIGNED, UP, DOWN, LEFT, RIGHT, BACK, FRONT};

    public:
        /// Default constructor
        CubeMap(void);

        /// Constructor with parameters
        CubeMap(const Point & pCenter, double pSize);

        /// Destructor
        ~CubeMap(void);

        /// Add an image to a face of the cube
        void addImage(unsigned short pFace, const std::string & pPath);

        /// Specify which image correspond to each face
        void setLink(unsigned short pFace, unsigned int pImageIdx);

        /// Get the color corresponding to the intersection point of a ray with one of the faces of the cube
        Color colorAt(const Ray & pRay);

        /// Set the center of the cube
        void setCenter(const Point & pCenter);

        /// Set the size of the cube
        void setSize(double pSize);

        /// Set the interpolation method for the images
        void setInterpolationMethod(unsigned short pMethod);

        /// Get the center of the cube
        Point center(void) const;

        /// Get the size of the cube
        double size(void) const;

        /// Get the interpolation method used for the images
        unsigned short interpolationMethod(void) const;

    private:
        /// Copy constructor (prevent copy)
        CubeMap(const CubeMap & pCubeMap);

        /// Copy operator (prevent copy)
        CubeMap operator=(const CubeMap & pCubeMap);

        /// Calculate the intersection of a ray with the cube, return the intersected face and the coordinates of the intersection point in the face
        void _intersect(const Ray & pRay, unsigned short & pFace, double & pI, double & pJ) const;

    private:
        std::vector<Image*> mImages;
        std::map<unsigned short, unsigned int> mFaceImageIDs;
        Point mCenter;
        double mSize;

    }; // class CubeMap

    inline void CubeMap::setCenter(const Point & pCenter)
    {
        mCenter = pCenter;
    }

    inline void CubeMap::setSize(double pSize)
    {
        mSize = pSize;
    }

    inline unsigned short CubeMap::interpolationMethod(void) const
    {
        return mImages[0]->interpolation();
    }

    inline Point CubeMap::center(void) const
    {
        return mCenter;
    }

    inline double CubeMap::size(void) const
    {
        return mSize;
    }

} // namespace MatouMalin

#endif
