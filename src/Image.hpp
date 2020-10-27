//
//  Image.h
//  RayTracing
//
//  Created by Loïc CORENTHY on 10/14/12.
//
//

#ifndef RAYTRACING_IMAGE_H
#define RAYTRACING_IMAGE_H

// Local includes
#include "Color.hpp"

// Standard includes
#include <string>
#include <ImageIO/ImageIO.hpp>
#include <cassert>

namespace MatouMalin
{
    class Image
    {
    public:
        enum Interpolation: unsigned short {NEAREST, LINEAR};
        
    public:
        /// Default constructor
        Image(void);
        
        /// Constructor with parameters
        Image(const std::string & pPath);
        
        /// Destructor
        ~Image(void);
        
        /// Load an image from a file
        bool loadFromFile(const std::string & pPath);
        
        /// Set the interpolation method used to return the pixel value
        void setInterpolation(unsigned short pMethod);
        
        /// Set the interpolation method used to return the pixel value
        unsigned short interpolation(void) const;
        
        /// Get the color of a pixel
        Color pixelColor(double pI, double pJ) const;
        
        /// Get the width of the image
        unsigned int width(void) const;
        
        /// Get the height of the image
        unsigned int height(void) const;
        
        /// Check if the image has been loaded or not
        bool imageLoaded(void) const;
        
    private:
        /// Copy constructor (prevent copy)
        Image(const Image & pImage);
        
        /// Copy operator
        Image operator=(const Image & pImage);
        
        /// Function using the funcionnalities of the ImageIO framework
        bool _createCGImageFromFile(const std::string & pPath);
        
    private:
        CGImageRef     mImage;
        unsigned char* mRawData;
        unsigned int   mWidth;
        unsigned int   mHeight;
        unsigned int   mBytesPerPixel;
        unsigned int   mBytesPerRow;
        unsigned int   mBitsPerComponent;
        unsigned short mInterpolation;
        bool           mImageLoaded;
        
    }; // Class Image
    
    
    inline void Image::setInterpolation(unsigned short pMethod)
    {
        mInterpolation = pMethod;
    }
    
    inline unsigned short Image::interpolation(void) const
    {
        return mInterpolation;
    }
    
    inline unsigned int Image::width(void) const
    {
        return mWidth;
    }
    
    inline unsigned int Image::height(void) const
    {
        return mHeight;
    }
    
    inline bool Image::imageLoaded(void) const
    {
        return mImageLoaded;
    }
    
} // namespace MatouMalin

#endif 
