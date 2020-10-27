//
//  Image.cpp
//  RayTracing
//
//  Created by Loïc CORENTHY on 10/14/12.
//
//

#include "Image.h"

// Local includes
#include "Color.h"

using namespace MatouMalin;
using namespace std;

Image::Image(void)
:mImage(nullptr),
 mRawData(nullptr),
 mWidth(0),
 mHeight(0),
 mBytesPerPixel(4),
 mBytesPerRow(0),
 mBitsPerComponent(8),
 mInterpolation(NEAREST),
 mImageLoaded(false)
{
    
}

Image::Image(const string & pPath)
:mImage(nullptr),
 mRawData(nullptr),
 mWidth(0),
 mHeight(0),
 mBytesPerPixel(4),
 mBytesPerRow(0),
 mBitsPerComponent(8),
 mInterpolation(NEAREST),
 mImageLoaded(false)
{
    _createCGImageFromFile(pPath);
}

Image::Image(const Image & pImage)
:mWidth(0),
 mHeight(0),
 mBytesPerPixel(4),
 mBytesPerRow(0),
 mBitsPerComponent(8),
 mImageLoaded(false)
{
    // If an image has already been loaded
    if (pImage.mImageLoaded)
    {
        // Copy the image
        mImage = CGImageCreateCopy(mImage);
        
        // Copy the raw data
        unsigned int lDataSize = pImage.mWidth*pImage.mHeight*pImage.mBytesPerPixel;
        mRawData = new unsigned char[lDataSize];
        memcpy(mRawData, pImage.mRawData, lDataSize);
    }
}

Image Image::operator=(const Image & pImage)
{
    if (this == & pImage)
        return *this;
    
    mWidth = pImage.mWidth;
    mHeight = pImage.mHeight;
    mBytesPerPixel = pImage.mBytesPerPixel;
    mBytesPerRow = pImage.mBytesPerRow;
    mBitsPerComponent = pImage.mBitsPerComponent;
    mInterpolation = pImage.mInterpolation;
    mImageLoaded = pImage.mImageLoaded;

    // If an image has already been loaded
    if (mImageLoaded)
    {
        // Copy the image
        mImage = CGImageCreateCopy(mImage);
        
        // Copy the raw data
        unsigned int lDataSize = pImage.mWidth*pImage.mHeight*pImage.mBytesPerPixel;
        mRawData = new unsigned char[lDataSize];
        memcpy(mRawData, pImage.mRawData, lDataSize);
    }
    return *this;
}

Image::~Image(void)
{
    delete [] mRawData;
}

bool Image::loadFromFile(const string & pPath)
{
    return _createCGImageFromFile(pPath);
}

Color Image::pixelColor(double pI, double pJ) const
{
    // mRawData contains the image data in the RGBA8888 pixel format, do not forget that mRawData[byteIndex + 3] is the alpha component
    
    assert(-0.000001<= pI && pI <= 1.000001 && "Index out of image's bounds");
    assert(-0.000001<= pJ && pJ <= 1.000001 && "Index out of image's bounds");
    
    if (mInterpolation == NEAREST)
    {
        unsigned int lI = static_cast<unsigned int>(pI*mWidth);
        unsigned int lJ = static_cast<unsigned int>(pJ*mHeight);
        
        //        unsigned int lByteIndex = mWidth*mHeight*mBytesPerPixel - (mBytesPerRow * lJ) + lI * mBytesPerPixel;
        unsigned int lByteIndex = (mBytesPerRow * lJ) + lI * mBytesPerPixel;
        float lInv255 = 0.00392157f;
        
        return Color(static_cast<float>(mRawData[lByteIndex])*lInv255, static_cast<float>(mRawData[lByteIndex+1])*lInv255, static_cast<float>(mRawData[lByteIndex+2])*lInv255);
    }
    else
    {
        // Get the decimal part
        double lDecimalPI = pI - floor(pI);
        double lDecimalPJ = pJ - floor(pJ);
        
        unsigned int lI = static_cast<unsigned int>(pI*mWidth);
        unsigned int lJ = static_cast<unsigned int>(pJ*mHeight);
        
        if (lI >= mWidth - 1)
            lI--;
        
        if (lJ >= mHeight - 1)
            lJ--;
        
        float lInv255 = 0.00392157f;
        
        unsigned int lByteIndex = (mBytesPerRow * lJ) + lI * mBytesPerPixel;
        Color lC0(static_cast<float>(mRawData[lByteIndex])*lInv255, static_cast<float>(mRawData[lByteIndex+1])*lInv255, static_cast<float>(mRawData[lByteIndex+2])*lInv255);
        
        lByteIndex = (mBytesPerRow * lJ) + (lI+1) * mBytesPerPixel;
        Color lC1(static_cast<float>(mRawData[lByteIndex])*lInv255, static_cast<float>(mRawData[lByteIndex+1])*lInv255, static_cast<float>(mRawData[lByteIndex+2])*lInv255);
        
        lByteIndex = (mBytesPerRow * (lJ+1)) + (lI) * mBytesPerPixel;
        Color lC2(static_cast<float>(mRawData[lByteIndex])*lInv255, static_cast<float>(mRawData[lByteIndex+1])*lInv255, static_cast<float>(mRawData[lByteIndex+2])*lInv255);
        
        lByteIndex = (mBytesPerRow * (lJ+1)) + (lI+1) * mBytesPerPixel;
        Color lC3(static_cast<float>(mRawData[lByteIndex])*lInv255, static_cast<float>(mRawData[lByteIndex+1])*lInv255, static_cast<float>(mRawData[lByteIndex+2])*lInv255);
        
        Color lCLine1 = lC0*lDecimalPI + lC1*(1.0 - lDecimalPI);
        Color lCLine2 = lC2*lDecimalPI + lC3*(1.0 - lDecimalPI);
        
        return (lCLine1*lDecimalPJ + lCLine2*(1.0-lDecimalPJ));
    }    
}

bool Image::_createCGImageFromFile(const string & pPath)
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
    CGImageSourceRef mImageSource = CGImageSourceCreateWithURL(lBaseURL, lOptions);
    
    // Release memory
    CFRelease(lOptions);
    CFRelease(lBaseStr);
    CFRelease(lBaseURL);
    
    // Make sure the image source exists before continuing
    if (mImageSource == NULL)
        return false;
    
    // Create an image from the first item in the image source.
    mImage = CGImageSourceCreateImageAtIndex(mImageSource,0,NULL);
    
    // Release the source image
    CFRelease(mImageSource);
    
    // Make sure the image exists before continuing
    if (mImage == NULL)
        return false;
    
    // Save image parameters
    mHeight             = static_cast<unsigned int>(CGImageGetHeight(mImage));
    mWidth              = static_cast<unsigned int>(CGImageGetWidth(mImage));
    mBitsPerComponent   = static_cast<unsigned int>(CGImageGetBitsPerComponent(mImage));
    mBytesPerPixel      = static_cast<unsigned int>(CGImageGetBitsPerPixel(mImage)/8);
    mBytesPerRow        = static_cast<unsigned int>(CGImageGetBytesPerRow(mImage));
    
    // Create a context to have acces to the raw data
    CGColorSpaceRef lColorSpace = CGColorSpaceCreateDeviceRGB();

    mRawData = new unsigned char[mHeight*mWidth*mBytesPerPixel];
    mBytesPerRow = mBytesPerPixel * mWidth;
    
    CGContextRef context = CGBitmapContextCreate(mRawData, mWidth, mHeight, mBitsPerComponent, mBytesPerRow, lColorSpace, kCGImageAlphaPremultipliedLast | kCGBitmapByteOrder32Big);
    
    CGColorSpaceRelease(lColorSpace);
    
    CGContextDrawImage(context, CGRectMake(0, 0, mWidth, mHeight), mImage);
    
    CGContextRelease(context);
    
    mImageLoaded = true;
    
    return true;
    
}





