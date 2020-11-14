//===============================================================================================//
/*!
 *  \file      Image.hpp
 *  \author    Loïc Corenthy
 *  \version   1.1
 *  \date      10/14/2012
 *  \copyright (c) 2019 Loïc Corenthy. All rights reserved.
 */
//===============================================================================================//

#ifndef RAYTRACING_IMAGE_H
#define RAYTRACING_IMAGE_H

#include <string>
#include <OpenImageIO/imageio.h>
#include <cassert>

#include "Color.hpp"

namespace LCNS
{
    class Image
    {
    public:
        enum Interpolation : unsigned short
        {
            NEAREST,
            LINEAR
        };

    public:
        /// Default constructor
        Image(void);

        /// Constructor with parameters
        Image(const std::string& path);

        /// Destructor
        ~Image(void);

        /// Load an image from a file
        bool loadFromFile(const std::string& path);

        /// Set the interpolation method used to return the pixel value
        void setInterpolation(unsigned short method);

        /// Set the interpolation method used to return the pixel value
        unsigned short interpolation(void) const;

        /// Get the color of a pixel
        Color pixelColor(double i, double j) const;

        /// Get the width of the image
        unsigned int width(void) const;

        /// Get the height of the image
        unsigned int height(void) const;

        /// Check if the image has been loaded or not
        bool imageLoaded(void) const;

    private:
        /// Copy constructor (prevent copy)
        Image(const Image& image);

        /// Copy operator
        Image operator=(const Image& image);

        /// Implementation of the method loading an image from the file system
        bool _createImageFromFile(const std::string& path);

    private:
#ifdef __linux__
        std::unique_ptr<OIIO::ImageInput> _image;
#elif __APPLE__
        CGImageRef _image;
#elif _WIN32

#endif
        unsigned char* _rawData;
        unsigned int   _width;
        unsigned int   _height;
        unsigned int   _bytesPerPixel;
        unsigned int   _bytesPerRow;
        unsigned int   _bitsPerComponent;
        unsigned short _interpolation;
        bool           _imageLoaded;

    };  // Class Image


    inline void Image::setInterpolation(unsigned short method)
    {
        _interpolation = method;
    }

    inline unsigned short Image::interpolation(void) const
    {
        return _interpolation;
    }

    inline unsigned int Image::width(void) const
    {
        return _width;
    }

    inline unsigned int Image::height(void) const
    {
        return _height;
    }

    inline bool Image::imageLoaded(void) const
    {
        return _imageLoaded;
    }

}  // namespace LCNS

#endif
