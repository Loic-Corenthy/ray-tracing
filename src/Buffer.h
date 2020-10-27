#ifndef RAYTRACING_BUFFER_H
#define RAYTRACING_BUFFER_H

// Local includes
#include "Color.h"

namespace MatouMalin 
{
    class Buffer
    {
    public:
        /// Default constructor
        Buffer(void);
        
        /// Constructor with parameters
        Buffer(unsigned int pHeight,unsigned int pWidth);
        
        /// Copy constructor
        Buffer(const Buffer & pBuffer);
        
        /// Copy operator
        Buffer operator=(const Buffer & pBuffer);
        
        /// Destructor
        ~Buffer(void);
        
        /// Set the value of one pixel in the buffer
        void setPixel(unsigned int pI,unsigned int pJ,const Color & pColor);
        
        /// Set the buffer's height
        void setHeight(unsigned int pHeight);

        /// Set the buffer's width
        void setWidth(unsigned int pWidth);

        /// Get the color corresponding to one specific pixel
        Color pixel(unsigned int pI,unsigned int pJ) const;
        
        /// Get a pointer on the table containing all the pixels
        const unsigned char* allPixels(void) const;
        
        /// Get the height of the buffer
        unsigned int height(void) const;
        
        /// Get the width of the buffer
        unsigned int width(void) const;
               
        /// Set all the pixels values to 0
        void reset(void);
        
    private:
        unsigned int mHeight;
        unsigned int mWidth;
        unsigned char* mPixels;
        
    }; // class Buffer
    
    inline unsigned int Buffer::height(void) const
    {
        return mHeight;
    }
    
    inline unsigned int Buffer::width(void) const
    {
        return mWidth;
    }
    
    inline void Buffer::setHeight(unsigned int pHeight)
    {
        mHeight = pHeight;
    }
    
    inline void Buffer::setWidth(unsigned int pWidth)
    {
        mWidth = pWidth;
    }
    
    inline const unsigned char* Buffer::allPixels(void) const
    {
        return mPixels;
    }
     
} // namespace MatouMalin


#endif