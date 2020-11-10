#include "Buffer.hpp"

// Standard includes
#include <cassert>
#include <iostream>

using namespace MatouMalin;

Buffer::Buffer(void)
:_height(0),
 _width(0),
 _pixels(nullptr)
{
}

Buffer::Buffer(unsigned int height,unsigned int width)
:_height(height),
 _width(width)
{
	_pixels = new unsigned char[3*height*width];
	for (unsigned int i=0, lEnd=3*height*width; i<lEnd; i++)
		_pixels[i] = 0;

}

Buffer::Buffer(const Buffer & buffer)
{
    if (_height == buffer._height && _width == buffer._width)
    {
        // No need to re allocate memory, just overwrite the values
        for (unsigned int i=0, lEnd = 3*_height*_width; i<lEnd; i++)
            _pixels[i] = (buffer._pixels)[i];
    }
    else
    {
        _height = buffer._height;
        _width = buffer._width;

        // delete the existing pixels
        if (_pixels)
        {
            delete [] _pixels;
            _pixels = nullptr;
        }

        // Create a new array of pixels
        _pixels = new unsigned char[3*_height*_width];
        for (unsigned int i=0, lEnd = 3*_height*_width; i<lEnd; i++)
        {
            _pixels[i] = (buffer._pixels)[i];
        }
    }

}

Buffer Buffer::operator=(const Buffer & buffer)
{
    if(this == & buffer)
        return *this;

    if (_height == buffer._height && _width == buffer._width)
    {
        // No need to re allocate memory, just overwrite the values
        for (unsigned int i=0, lEnd = 3*_height*_width; i<lEnd; i++)
            _pixels[i] = (buffer._pixels)[i];
    }
    else
    {
        _height = buffer._height;
        _width = buffer._width;

        // delete the existing pixels
        if (_pixels)
        {
            delete [] _pixels;
            _pixels = nullptr;
        }

        // Create a new array of pixels
        _pixels = new unsigned char[3*_height*_width];
        for (unsigned int i=0, lEnd = 3*_height*_width; i<lEnd; i++)
        {
            _pixels[i] = (buffer._pixels)[i];
        }
    }


    return *this;
}


Buffer::~Buffer(void)
{
	delete [] _pixels;
}


void Buffer::setPixel(unsigned int i,unsigned int j,const Color & color)
{
	assert(0 <= i && i<=mWidth && 0 <= j && j<=mHeight);
	unsigned int lIndex = 3*(_width*j + i);

	Color lColor(color);

	if(lColor[0] < 0)
	{
		lColor[0] = 0;
	}
	if(1 < lColor[0])
	{
		lColor[0] = 1;
	}

	if(lColor[1] < 0)
	{
		lColor[1] = 0;
	}
	if(1 < lColor[1])
	{
		lColor[1] = 1;
	}

	if(lColor[2] < 0)
	{
		lColor[2] = 0;
	}
	if(1 < lColor[2])
	{
		lColor[2] = 1;
	}

	unsigned char r = static_cast<unsigned char>(lColor[0]*255.f);
	unsigned char g = static_cast<unsigned char>(lColor[1]*255.f);
	unsigned char b = static_cast<unsigned char>(lColor[2]*255.f);

	_pixels[lIndex + 0] = r;
	_pixels[lIndex + 1] = g;
	_pixels[lIndex + 2] = b;
}

Color Buffer::pixel(unsigned int i,unsigned int j) const
{
	assert(0 <= i && i<=mWidth && 0 <= j && j<=mHeight);
	unsigned int lIndex = 3*(_width*j + i);

    return Color(_pixels[lIndex + 0],_pixels[lIndex + 1],_pixels[lIndex + 2]);

}

void Buffer::reset(void)
{
	for (unsigned int i=0, lEnd = 3*_height*_width; i<lEnd; i++)
		_pixels[i] = 0;
}