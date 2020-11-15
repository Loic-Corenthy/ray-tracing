//===============================================================================================//
/*!
 *  \file      Image.cpp
 *  \author    Loïc Corenthy
 *  \version   1.0
 *  \date      10/14/2012
 *  \copyright (c) 2019 Loïc Corenthy. All rights reserved.
 */
//===============================================================================================//

#include "Image.hpp"

using std::string;

using LCNS::Color;
using LCNS::Image;

using OIIO::ImageInput;
using OIIO::ImageSpec;
using OIIO::TypeDesc;

Image::Image(void)
: _image(nullptr)
, _rawData(nullptr)
, _width(0)
, _height(0)
, _bytesPerPixel(4)
, _bytesPerRow(0)
, _bitsPerComponent(8)
, _interpolation(NEAREST)
, _imageLoaded(false)
{
}

Image::Image(const string& path)
: _image(nullptr)
, _rawData(nullptr)
, _width(0)
, _height(0)
, _bytesPerPixel(4)
, _bytesPerRow(0)
, _bitsPerComponent(8)
, _interpolation(NEAREST)
, _imageLoaded(false)
{
    _createImageFromFile(path);
}

Image::Image(const Image& image)
: _width(0)
, _height(0)
, _bytesPerPixel(4)
, _bytesPerRow(0)
, _bitsPerComponent(8)
, _imageLoaded(false)
{
    // If an image has already been loaded
    if (image._imageLoaded)
    {
#ifdef __linux__

#elif __APPLE__
        // Copy the image
        _image = CGImageCreateCopy(_image);
#elif _WIN32

#endif
        // Copy the raw data
        unsigned int dataSize = image._width * image._height * image._bytesPerPixel;
        _rawData               = new unsigned char[dataSize];
        memcpy(_rawData, image._rawData, dataSize);
    }
}

Image Image::operator=(const Image& image)
{
    if (this == &image)
        return *this;

    _width            = image._width;
    _height           = image._height;
    _bytesPerPixel    = image._bytesPerPixel;
    _bytesPerRow      = image._bytesPerRow;
    _bitsPerComponent = image._bitsPerComponent;
    _interpolation    = image._interpolation;
    _imageLoaded      = image._imageLoaded;

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
        unsigned int dataSize = image._width * image._height * image._bytesPerPixel;
        _rawData               = new unsigned char[dataSize];
        memcpy(_rawData, image._rawData, dataSize);
    }
    return *this;
}

Image::~Image(void)
{
    delete[] _rawData;
}

bool Image::loadFromFile(const string& path)
{
    return _createImageFromFile(path);
}

Color Image::pixelColor(double i, double j) const
{
    // _rawData contains the image data in the RGBA8888 pixel format, do not forget that _rawData[byteIndex + 3] is the alpha component

    assert(-0.000001 <= i && i <= 1.000001 && "Index out of image's bounds");
    assert(-0.000001 <= j && j <= 1.000001 && "Index out of image's bounds");

    if (_interpolation == NEAREST)
    {
        unsigned int i = static_cast<unsigned int>(i * _width);
        unsigned int j = static_cast<unsigned int>(j * _height);

        //        unsigned int byteIndex = _width*_height*_bytesPerPixel - (_bytesPerRow * j) + i * _bytesPerPixel;
        unsigned int byteIndex = (_bytesPerRow * j) + i * _bytesPerPixel;
        float        inv255    = 0.00392157f;

        return Color(static_cast<float>(_rawData[byteIndex]) * inv255,
                     static_cast<float>(_rawData[byteIndex + 1]) * inv255,
                     static_cast<float>(_rawData[byteIndex + 2]) * inv255);
    }
    else
    {
        // Get the decimal part
        double decimalPI = i - floor(i);
        double decimalPJ = j - floor(j);

        unsigned int i = static_cast<unsigned int>(i * _width);
        unsigned int j = static_cast<unsigned int>(j * _height);

        if (i >= _width - 1)
            i--;

        if (j >= _height - 1)
            j--;

        float inv255 = 0.00392157f;

        unsigned int byteIndex = (_bytesPerRow * j) + i * _bytesPerPixel;
        Color        c0(static_cast<float>(_rawData[byteIndex]) * inv255,
                  static_cast<float>(_rawData[byteIndex + 1]) * inv255,
                  static_cast<float>(_rawData[byteIndex + 2]) * inv255);

        byteIndex = (_bytesPerRow * j) + (i + 1) * _bytesPerPixel;
        Color c1(static_cast<float>(_rawData[byteIndex]) * inv255,
                  static_cast<float>(_rawData[byteIndex + 1]) * inv255,
                  static_cast<float>(_rawData[byteIndex + 2]) * inv255);

        byteIndex = (_bytesPerRow * (j + 1)) + (i) *_bytesPerPixel;
        Color c2(static_cast<float>(_rawData[byteIndex]) * inv255,
                  static_cast<float>(_rawData[byteIndex + 1]) * inv255,
                  static_cast<float>(_rawData[byteIndex + 2]) * inv255);

        byteIndex = (_bytesPerRow * (j + 1)) + (i + 1) * _bytesPerPixel;
        Color c3(static_cast<float>(_rawData[byteIndex]) * inv255,
                  static_cast<float>(_rawData[byteIndex + 1]) * inv255,
                  static_cast<float>(_rawData[byteIndex + 2]) * inv255);

        Color cLine1 = c0 * decimalPI + c1 * (1.0 - decimalPI);
        Color cLine2 = c2 * decimalPI + c3 * (1.0 - decimalPI);

        return (cLine1 * decimalPJ + cLine2 * (1.0 - decimalPJ));
    }
}


#ifdef __linux__
bool Image::_createImageFromFile(const string& path)
{
    _image = ImageInput::open(path);

    if (!_image)
        return false;

    const ImageSpec& spec = _image->spec();
    _width                = spec.width;
    _height               = spec.height;
    _bytesPerPixel        = spec.nchannels;

    _rawData     = new unsigned char[_width * _height * _bytesPerPixel];
    _bytesPerRow = _bytesPerPixel * _width;

    _image->read_image(TypeDesc::UINT8, _rawData);
    _image->close();

    _imageLoaded = true;
    return true;
}
#elif __APPLE__
bool Image::_createImageFromFile(const string& path)
{
    // Set up options. The options here are for caching the image in a decoded form and for using floating-point values if the image format supports
    // them.
    CFStringRef keys[2] = { kCGImageSourceShouldCache, kCGImageSourceShouldAllowFloat };
    CFTypeRef values[2] = { (CFTypeRef) kCFBooleanTrue, (CFTypeRef) kCFBooleanTrue };

    // Create the dictionary
    CFDictionaryRef options
    = CFDictionaryCreate(NULL, (const void**) keys, (const void**) values, 2, &kCFTypeDictionaryKeyCallBacks, &kCFTypeDictionaryValueCallBacks);

    // Create an URL from the path
    string filePath("file://");
    filePath.append(path);

    CFStringRef baseStr = CFStringCreateWithCString(kCFAllocatorDefault, filePath.c_str(), kCFStringEncodingASCII);
    CFURLRef baseURL = CFURLCreateWithString(NULL, baseStr, NULL);

    // Create an image source from the URL
    CGImageSourceRef _imageSource = CGImageSourceCreateWithURL(baseURL, options);

    // Release memory
    CFRelease(options);
    CFRelease(baseStr);
    CFRelease(baseURL);

    // Make sure the image source exists before continuing
    if (_imageSource == NULL)
        return false;

    // Create an image from the first item in the image source.
    _image = CGImageSourceCreateImageAtIndex(_imageSource, 0, NULL);

    // Release the source image
    CFRelease(_imageSource);

    // Make sure the image exists before continuing
    if (_image == NULL)
        return false;

    // Save image parameters
    _height = static_cast<unsigned int>(CGImageGetHeight(_image));
    _width = static_cast<unsigned int>(CGImageGetWidth(_image));
    _bitsPerComponent = static_cast<unsigned int>(CGImageGetBitsPerComponent(_image));
    _bytesPerPixel = static_cast<unsigned int>(CGImageGetBitsPerPixel(_image) / 8);
    _bytesPerRow = static_cast<unsigned int>(CGImageGetBytesPerRow(_image));

    // Create a context to have acces to the raw data
    CGColorSpaceRef colorSpace = CGColorSpaceCreateDeviceRGB();

    _rawData = new unsigned char[_height * _width * _bytesPerPixel];
    _bytesPerRow = _bytesPerPixel * _width;

    CGContextRef context = CGBitmapContextCreate(
    _rawData, _width, _height, _bitsPerComponent, _bytesPerRow, colorSpace, kCGImageAlphaPremultipliedLast | kCGBitmapByteOrder32Big);

    CGColorSpaceRelease(colorSpace);

    CGContextDrawImage(context, CGRectMake(0, 0, _width, _height), _image);

    CGContextRelease(context);

    _imageLoaded = true;

    return true;
}
#elif _WIN32
bool Image::_createImageFromFile(const string& path)
{
    static_assert(false && "method not implemented");
    return false;
}
#endif
