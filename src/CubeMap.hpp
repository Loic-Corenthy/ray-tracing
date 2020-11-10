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
        CubeMap(const Point & center, double size);

        /// Destructor
        ~CubeMap(void);

        /// Add an image to a face of the cube
        void addImage(unsigned short face, const std::string & path);

        /// Specify which image correspond to each face
        void setLink(unsigned short face, unsigned int imageIdx);

        /// Get the color corresponding to the intersection point of a ray with one of the faces of the cube
        Color colorAt(const Ray & ray);

        /// Set the center of the cube
        void setCenter(const Point & center);

        /// Set the size of the cube
        void setSize(double size);

        /// Set the interpolation method for the images
        void setInterpolationMethod(unsigned short method);

        /// Get the center of the cube
        Point center(void) const;

        /// Get the size of the cube
        double size(void) const;

        /// Get the interpolation method used for the images
        unsigned short interpolationMethod(void) const;

    private:
        /// Copy constructor (prevent copy)
        CubeMap(const CubeMap & cubeMap);

        /// Copy operator (prevent copy)
        CubeMap operator=(const CubeMap & cubeMap);

        /// Calculate the intersection of a ray with the cube, return the intersected face and the coordinates of the intersection point in the face
        void _intersect(const Ray & ray, unsigned short & face, double & i, double & j) const;

    private:
        std::vector<Image*> _images;
        std::map<unsigned short, unsigned int> _faceImageIDs;
        Point _center;
        double _size;

    }; // class CubeMap

    inline void CubeMap::setCenter(const Point & center)
    {
        _center = center;
    }

    inline void CubeMap::setSize(double size)
    {
        _size = size;
    }

    inline unsigned short CubeMap::interpolationMethod(void) const
    {
        return _images[0]->interpolation();
    }

    inline Point CubeMap::center(void) const
    {
        return _center;
    }

    inline double CubeMap::size(void) const
    {
        return _size;
    }

} // namespace MatouMalin

#endif
