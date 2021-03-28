//===============================================================================================//
/*!
 *  \file      Image.hpp
 *  \author    Loïc Corenthy
 *  \version   1.2
 *  \date      10/14/2012
 *  \copyright (c) 2019 Loïc Corenthy. All rights reserved.
 */
//===============================================================================================//

#pragma once

#include <string>
#include <cassert>

#include <OpenImageIO/imageio.h>
#include <OpenImageIO/typedesc.h>

#include "Color.hpp"

namespace LCNS
{
    class Image
    {
    public:
        enum class InterpolationMethod : unsigned short
        {
            NEAREST,
            LINEAR
        };

    public:
        /// Default constructor
        Image(void) = default;

        /// Constructor with parameters
        explicit Image(const std::string& path);

        /// Copy constructor (prevent copy)
        Image(const Image& image) = delete;

        /// Copy operator
        Image operator=(const Image& image) = delete;

        /// Destructor
        ~Image(void) = default;

        /// Load an image from a file
        bool loadFromFile(const std::string& path);

        /// Set the interpolation method used to return the pixel value
        void interpolation(InterpolationMethod value) noexcept;

        /// Set the interpolation method used to return the pixel value
        InterpolationMethod interpolation(void) const noexcept;

        /// Get the color of a pixel
        Color pixelColor(double i, double j) const;

        /// Get the width of the image
        unsigned int width(void) const noexcept;

        /// Get the height of the image
        unsigned int height(void) const noexcept;

        /// Check if the image has been loaded or not
        bool imageLoaded(void) const noexcept;

    private:
        /// Implementation of the method loading an image from the file system
        bool _createImageFromFile(const std::string& path);

    private:
        std::unique_ptr<OIIO::ImageInput> _image;
        std::unique_ptr<unsigned char[]>  _rawData;
        unsigned int                      _width            = 0u;
        unsigned int                      _height           = 0u;
        unsigned int                      _bytesPerPixel    = 4u;
        unsigned int                      _bytesPerRow      = 0u;
        unsigned int                      _bitsPerComponent = 8u;
        InterpolationMethod               _interpolation    = InterpolationMethod::NEAREST;
        bool                              _imageLoaded      = false;

    };  // Class Image

}  // namespace LCNS
