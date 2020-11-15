//===============================================================================================//
/*!
 *  \file      Buffer.cpp
 *  \author    Loïc Corenthy
 *  \version   1.0
 *  \date      14/10/2012
 *  \copyright (c) 2012 Loïc Corenthy. All rights reserved.
 */
//===============================================================================================//

#include "Buffer.hpp"

#include <cassert>
#include <iostream>

using namespace LCNS;

Buffer::Buffer(void)
{
}

Buffer::Buffer(unsigned int height, unsigned int width)
: _height(height)
, _width(width)
{
    reset();
}

Buffer::Buffer(const Buffer& buffer)
{
    if (_height == buffer._height && _width == buffer._width)
    {
        // No need to re allocate memory, just overwrite the values
        for (unsigned int i = 0, end = 3 * _height * _width; i < end; i++)
            _pixels[i] = (buffer._pixels)[i];
    }
    else
    {
        _height = buffer._height;
        _width  = buffer._width;

        // delete the existing pixels
        if (_pixels)
        {
            delete[] _pixels;
            _pixels = nullptr;
        }

        // Create a new array of pixels
        _pixels = new unsigned char[3 * _height * _width];
        for (unsigned int i = 0, end = 3 * _height * _width; i < end; i++)
        {
            _pixels[i] = (buffer._pixels)[i];
        }
    }
}

Buffer Buffer::operator=(const Buffer& buffer)
{
    if (this == &buffer)
        return *this;

    if (_height == buffer._height && _width == buffer._width)
    {
        // No need to re allocate memory, just overwrite the values
        for (unsigned int i = 0, end = 3 * _height * _width; i < end; i++)
            _pixels[i] = (buffer._pixels)[i];
    }
    else
    {
        _height = buffer._height;
        _width  = buffer._width;

        // delete the existing pixels
        if (_pixels)
        {
            delete[] _pixels;
            _pixels = nullptr;
        }

        // Create a new array of pixels
        _pixels = new unsigned char[3 * _height * _width];
        for (unsigned int i = 0, end = 3 * _height * _width; i < end; i++)
        {
            _pixels[i] = (buffer._pixels)[i];
        }
    }


    return *this;
}


Buffer::~Buffer(void)
{
    delete[] _pixels;
}


void Buffer::setPixel(unsigned int i, unsigned int j, const Color& color)
{
    assert(0 <= i && i <= _width && 0 <= j && j <= _height);
    unsigned int index = 3 * (_width * j + i);

    Color pixelColor(color);

    if (pixelColor[0] < 0)
    {
        pixelColor[0] = 0;
    }
    if (1 < pixelColor[0])
    {
        pixelColor[0] = 1;
    }

    if (pixelColor[1] < 0)
    {
        pixelColor[1] = 0;
    }
    if (1 < pixelColor[1])
    {
        pixelColor[1] = 1;
    }

    if (pixelColor[2] < 0)
    {
        pixelColor[2] = 0;
    }
    if (1 < pixelColor[2])
    {
        pixelColor[2] = 1;
    }

    unsigned char r = static_cast<unsigned char>(pixelColor[0] * 255.f);
    unsigned char g = static_cast<unsigned char>(pixelColor[1] * 255.f);
    unsigned char b = static_cast<unsigned char>(pixelColor[2] * 255.f);

    _pixels[index + 0] = r;
    _pixels[index + 1] = g;
    _pixels[index + 2] = b;
}

Color Buffer::pixel(unsigned int i, unsigned int j) const
{
    assert(0 <= i && i <= _width && 0 <= j && j <= _height);
    unsigned int index = 3 * (_width * j + i);

    return Color(_pixels[index + 0], _pixels[index + 1], _pixels[index + 2]);
}


unsigned int Buffer::height(void) const
{
    return _height;
}

unsigned int Buffer::width(void) const
{
    return _width;
}

void Buffer::dimensions(unsigned int width, unsigned int height)
{
    _width  = width;
    _height = height;

    reset();
}

const unsigned char* Buffer::allPixels(void) const
{
    return _pixels;
}

void Buffer::reset(void)
{
    if (_width == 0 || _height == 0)
        return;

    if (_pixels)
    {
        delete[] _pixels;
        _pixels = nullptr;
    }

    _pixels = new unsigned char[3 * _height * _width];

    for (unsigned int i = 0, end = 3 * _height * _width; i < end; i++)
        _pixels[i] = 0;
}
