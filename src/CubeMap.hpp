//===============================================================================================//
/*!
 *  \file      CubeMap.hpp
 *  \author    Loïc Corenthy
 *  \version   1.1
 *  \date      14/10/2012
 *  \copyright (c) 2012 Loïc Corenthy. All rights reserved.
 */
//===============================================================================================//

#pragma once

#include <memory>
#include <vector>
#include <map>
#include <string>
#include <tuple>

#include "Point.hpp"
#include "Image.hpp"

namespace LCNS
{
    class Color;
    class Ray;

    class CubeMap
    {
    public:
        enum class Faces : unsigned short
        {
            UNASSIGNED,
            UP,
            DOWN,
            LEFT,
            RIGHT,
            BACK,
            FRONT
        };

    public:
        /// Default constructor
        CubeMap(void);

        /// Constructor with parameters
        CubeMap(const Point& center, double size);

        /// Copy constructor (prevent copy)
        CubeMap(const CubeMap& cubeMap) = delete;

        /// Copy operator (prevent copy)
        CubeMap operator=(const CubeMap& cubeMap) = delete;

        /// Destructor
        ~CubeMap(void) = default;

        /// Add an image to a face of the cube
        void addImage(Faces face, const std::string& path);

        /// Specify which image correspond to each face
        void setLink(Faces face, unsigned int imageIdx);

        /// Get the color corresponding to the intersection point of a ray with one of the faces of the cube
        Color colorAt(const Ray& ray);

        /// Set the center of the cube
        void center(const Point& center) noexcept;

        /// Set the size of the cube
        void size(double size) noexcept;

        /// Get the center of the cube
        Point center(void) const noexcept;

        /// Get the size of the cube
        double size(void) const noexcept;

        /// Set the interpolation method for the images
        void interpolationMethod(Image::InterpolationMethod value) noexcept;

        /// Get the interpolation method used for the images
        Image::InterpolationMethod interpolationMethod(void) const;

    private:
        /// Calculate the intersection of a ray with the cube, return the intersected face and the coordinates of the intersection point in the face
        std::tuple<Faces, double, double> _intersect(const Ray& ray) const;

    private:
        std::vector<std::unique_ptr<Image>> _images;

        std::map<Faces, unsigned int> _faceImageIDs
        = { { Faces::UP, 0 }, { Faces::DOWN, 1 }, { Faces::LEFT, 2 }, { Faces::RIGHT, 3 }, { Faces::BACK, 4 }, { Faces::FRONT, 5 } };

        Point  _center;
        double _size = 0.0;

    };  // class CubeMap

}  // namespace LCNS
