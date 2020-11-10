//
//  Image.cpp
//  RayTracing
//
//  Created by Loïc CORENTHY on 10/14/12.
//
//

#include <OpenImageIO/imageio.h>
#include <OpenImageIO/typedesc.h>

#include "Image.hpp"

// Local includes
#include "Color.hpp"

using std::string;

using MatouMalin::Image;
using MatouMalin::Color;

using OIIO::ImageInput;
using OIIO::ImageSpec;
using OIIO::TypeDesc;

Image::Image(void)
:_image(nullptr),
 _rawData(nullptr),
 _width(0),
 _height(0),
 _bytesPerPixel(4),
 _bytesPerRow(0),
 _bitsPerComponent(8),
 _interpolation(NEAREST),
 _imageLoaded(false)
{

}

Image::Image(const string & pPath)
:_image(nullptr),
 _rawData(nullptr),
 _width(0),
 _height(0),
 _bytesPerPixel(4),
 _bytesPerRow(0),
 _bitsPerComponent(8),
 _interpolation(NEAREST),
 _imageLoaded(false)
{
    _createImageFromFile(pPath);
}

Image::Image(const Image & pImage)
:_width(0),
 _height(0),
 _bytesPerPixel(4),
 _bytesPerRow(0),
 _bitsPerComponent(8),
 _imageLoaded(false)
{
    // If an image has already been loaded
    if (pImage._imageLoaded)
    {
#ifdef __linux__

#elif __APPLE__
        // Copy the image
        _image = CGImageCreateCopy(_image);
#elif _WIN32

#endif
        // Copy the raw data
        unsigned int lDataSize = pImage._width*pImage._height*pImage._bytesPerPixel;
        _rawData = new unsigned char[lDataSize];
        memcpy(_rawData, pImage._rawData, lDataSize);
    }
}

Image Image::operator=(const Image & pImage)
{
    if (this == & pImage)
        return *this;

    _width = pImage._width;
    _height = pImage._height;
    _bytesPerPixel = pImage._bytesPerPixel;
    _bytesPerRow = pImage._bytesPerRow;
    _bitsPerComponent = pImage._bitsPerComponent;
    _interpolation = pImage._interpolation;
    _imageLoaded = pImage._imageLoaded;

    // If an image has already been loaded
    if (_imageLoaded)
    {
#ifdef __linux__

#elif __APPLE__
        // Copy the image
        _image = CGImageCreateCopy(_image);
#elif _WIN32

#endif
        // Copy the raw data
        unsigned int lDataSize = pImage._width*pImage._height*pImage._bytesPerPixel;
        _rawData = new unsigned char[lDataSize];
        memcpy(_rawData, pImage._rawData, lDataSize);
    }
    return *this;
}

Image::~Image(void)
{
    delete [] _rawData;
}

bool Image::loadFromFile(const string & pPath)
{
    return _createImageFromFile(pPath);
}

Color Image::pixelColor(double pI, double pJ) const
{
    // _rawData contains the image data in the RGBA8888 pixel format, do not forget that _rawData[byteIndex + 3] is the alpha component

    assert(-0.000001<= pI && pI <= 1.000001 && "Index out of image's bounds");
    assert(-0.000001<= pJ && pJ <= 1.000001 && "Index out of image's bounds");

    if (_interpolation == NEAREST)
    {
        unsigned int lI = static_cast<unsigned int>(pI*_width);
        unsigned int lJ = static_cast<unsigned int>(pJ*_height);

        //        unsigned int lByteIndex = _width*_height*_bytesPerPixel - (_bytesPerRow * lJ) + lI * _bytesPerPixel;
        unsigned int lByteIndex = (_bytesPerRow * lJ) + lI * _bytesPerPixel;
        float lInv255 = 0.00392157f;

        return Color(static_cast<float>(_rawData[lByteIndex])*lInv255, static_cast<float>(_rawData[lByteIndex+1])*lInv255, static_cast<float>(_rawData[lByteIndex+2])*lInv255);
    }
    else
    {
        // Get the decimal part
        double lDecimalPI = pI - floor(pI);
        double lDecimalPJ = pJ - floor(pJ);

        unsigned int lI = static_cast<unsigned int>(pI*_width);
        unsigned int lJ = static_cast<unsigned int>(pJ*_height);

        if (lI >= _width - 1)
            lI--;

        if (lJ >= _height - 1)
            lJ--;

        float lInv255 = 0.00392157f;

        unsigned int lByteIndex = (_bytesPerRow * lJ) + lI * _bytesPerPixel;
        Color lC0(static_cast<float>(_rawData[lByteIndex])*lInv255, static_cast<float>(_rawData[lByteIndex+1])*lInv255, static_cast<float>(_rawData[lByteIndex+2])*lInv255);

        lByteIndex = (_bytesPerRow * lJ) + (lI+1) * _bytesPerPixel;
        Color lC1(static_cast<float>(_rawData[lByteIndex])*lInv255, static_cast<float>(_rawData[lByteIndex+1])*lInv255, static_cast<float>(_rawData[lByteIndex+2])*lInv255);

        lByteIndex = (_bytesPerRow * (lJ+1)) + (lI) * _bytesPerPixel;
        Color lC2(static_cast<float>(_rawData[lByteIndex])*lInv255, static_cast<float>(_rawData[lByteIndex+1])*lInv255, static_cast<float>(_rawData[lByteIndex+2])*lInv255);

        lByteIndex = (_bytesPerRow * (lJ+1)) + (lI+1) * _bytesPerPixel;
        Color lC3(static_cast<float>(_rawData[lByteIndex])*lInv255, static_cast<float>(_rawData[lByteIndex+1])*lInv255, static_cast<float>(_rawData[lByteIndex+2])*lInv255);

        Color lCLine1 = lC0*lDecimalPI + lC1*(1.0 - lDecimalPI);
        Color lCLine2 = lC2*lDecimalPI + lC3*(1.0 - lDecimalPI);

        return (lCLine1*lDecimalPJ + lCLine2*(1.0-lDecimalPJ));
    }
}


#ifdef __linux__
    bool Image::_createImageFromFile(const string & pPath)
    {
        _image = ImageInput::open(pPath);

        if (!_image)
            return false;

        const ImageSpec & spec = _image->spec();
        _width = spec.width;
        _height = spec.height;
        _bytesPerPixel = spec.nchannels;

        _rawData = new unsigned char[_width * _height * _bytesPerPixel];
        _bytesPerRow = _bytesPerPixel * _width;

        _image->read_image(TypeDesc::UINT8, _rawData);
        _image->close();

        _imageLoaded = true;
        return true;
    }
#elif __APPLE__
    bool Image::_createImageFromFile(const string & pPath)
    {
        // Set up options. The options here are for caching the image in a decoded form and for using floating-point values if the image format supports them.
        CFStringRef lKeys[2]   = {kCGImageSourceShouldCache, kCGImageSourceShouldAllowFloat};
        CFTypeRef   lValues[2] = {(CFTypeRef)kCFBooleanTrue, (CFTypeRef)kCFBooleanTrue};

        // Create the dictionary
        CFDictionaryRef lOptions = CFDictionaryCreate(NULL, (const void **) lKeys, (const void **) lValues, 2, & kCFTypeDictionaryKeyCallBacks, & kCFTypeDictionaryValueCallBacks);

        // Create an URL from the path
        string lFilePath("file://");
        lFilePath.append(pPath);

        CFStringRef lBaseStr = CFStringCreateWithCString ( kCFAllocatorDefault, lFilePath.c_str(), kCFStringEncodingASCII);
        CFURLRef lBaseURL = CFURLCreateWithString(NULL, lBaseStr, NULL);

        // Create an image source from the URL
        CGImageSourceRef _imageSource = CGImageSourceCreateWithURL(lBaseURL, lOptions);

        // Release memory
        CFRelease(lOptions);
        CFRelease(lBaseStr);
        CFRelease(lBaseURL);

        // Make sure the image source exists before continuing
        if (_imageSource == NULL)
            return false;

        // Create an image from the first item in the image source.
        _image = CGImageSourceCreateImageAtIndex(_imageSource,0,NULL);

        // Release the source image
        CFRelease(_imageSource);

        // Make sure the image exists before continuing
        if (_image == NULL)
            return false;

        // Save image parameters
        _height             = static_cast<unsigned int>(CGImageGetHeight(_image));
        _width              = static_cast<unsigned int>(CGImageGetWidth(_image));
        _bitsPerComponent   = static_cast<unsigned int>(CGImageGetBitsPerComponent(_image));
        _bytesPerPixel      = static_cast<unsigned int>(CGImageGetBitsPerPixel(_image)/8);
        _bytesPerRow        = static_cast<unsigned int>(CGImageGetBytesPerRow(_image));

        // Create a context to have acces to the raw data
        CGColorSpaceRef lColorSpace = CGColorSpaceCreateDeviceRGB();

        _rawData = new unsigned char[_height*_width*_bytesPerPixel];
        _bytesPerRow = _bytesPerPixel * _width;

        CGContextRef context = CGBitmapContextCreate(_rawData, _width, _height, _bitsPerComponent, _bytesPerRow, lColorSpace, kCGImageAlphaPremultipliedLast | kCGBitmapByteOrder32Big);

        CGColorSpaceRelease(lColorSpace);

        CGContextDrawImage(context, CGRectMake(0, 0, _width, _height), _image);

        CGContextRelease(context);

        _imageLoaded = true;

        return true;
    }
#elif _WIN32
    bool Image::_createImageFromFile(const string & pPath)
    {
        static_assert(false && "method not implemented");
        return false;
    }
#endif
