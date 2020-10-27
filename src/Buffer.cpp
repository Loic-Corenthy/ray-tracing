#include "Buffer.hpp"

// Standard includes
#include <cassert>
#include <iostream>

using namespace MatouMalin;

Buffer::Buffer(void)
:mHeight(0),
 mWidth(0),
 mPixels(nullptr)
{
}

Buffer::Buffer(unsigned int pHeight,unsigned int pWidth)
:mHeight(pHeight),
 mWidth(pWidth)
{
	mPixels = new unsigned char[3*pHeight*pWidth];
	for (unsigned int i=0, lEnd=3*pHeight*pWidth; i<lEnd; i++)
		mPixels[i] = 0;
	
}

Buffer::Buffer(const Buffer & pBuffer)
{
    if (mHeight == pBuffer.mHeight && mWidth == pBuffer.mWidth)
    {
        // No need to re allocate memory, just overwrite the values
        for (unsigned int i=0, lEnd = 3*mHeight*mWidth; i<lEnd; i++)
            mPixels[i] = (pBuffer.mPixels)[i];
    }
    else
    {
        mHeight = pBuffer.mHeight;
        mWidth = pBuffer.mWidth;
        
        // delete the existing pixels
        if (mPixels)
        {
            delete [] mPixels;
            mPixels = nullptr;
        }
        
        // Create a new array of pixels
        mPixels = new unsigned char[3*mHeight*mWidth];
        for (unsigned int i=0, lEnd = 3*mHeight*mWidth; i<lEnd; i++)
        {
            mPixels[i] = (pBuffer.mPixels)[i];
        }
    }
	
}

Buffer Buffer::operator=(const Buffer & pBuffer)
{
    if(this == & pBuffer)
        return *this;
    
    if (mHeight == pBuffer.mHeight && mWidth == pBuffer.mWidth)
    {
        // No need to re allocate memory, just overwrite the values
        for (unsigned int i=0, lEnd = 3*mHeight*mWidth; i<lEnd; i++)
            mPixels[i] = (pBuffer.mPixels)[i];
    }
    else
    {
        mHeight = pBuffer.mHeight;
        mWidth = pBuffer.mWidth;
        
        // delete the existing pixels
        if (mPixels)
        {
            delete [] mPixels;
            mPixels = nullptr;
        }
        
        // Create a new array of pixels
        mPixels = new unsigned char[3*mHeight*mWidth];
        for (unsigned int i=0, lEnd = 3*mHeight*mWidth; i<lEnd; i++)
        {
            mPixels[i] = (pBuffer.mPixels)[i];
        }
    }

    
    return *this;
}


Buffer::~Buffer(void)
{
	delete [] mPixels;
}


void Buffer::setPixel(unsigned int pI,unsigned int pJ,const Color & pColor)
{
	assert(0 <= pI && pI<=mWidth && 0 <= pJ && pJ<=mHeight);
	unsigned int lIndex = 3*(mWidth*pJ + pI);
	
	Color lColor(pColor);

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

	mPixels[lIndex + 0] = r;
	mPixels[lIndex + 1] = g;
	mPixels[lIndex + 2] = b;
}

Color Buffer::pixel(unsigned int pI,unsigned int pJ) const
{
	assert(0 <= pI && pI<=mWidth && 0 <= pJ && pJ<=mHeight);
	unsigned int lIndex = 3*(mWidth*pJ + pI);

    return Color(mPixels[lIndex + 0],mPixels[lIndex + 1],mPixels[lIndex + 2]);

}

void Buffer::reset(void)
{
	for (unsigned int i=0, lEnd = 3*mHeight*mWidth; i<lEnd; i++)
		mPixels[i] = 0;
}