#ifndef RAYTRACING_BUFFER_H
#define RAYTRACING_BUFFER_H

// Local includes
#include "Color.hpp"

namespace MatouMalin
{
    class Buffer
    {
    public:
        /// Default constructor
        Buffer(void);

        /// Constructor with parameters
        Buffer(unsigned int height, unsigned int width);

        /// Copy constructor
        Buffer(const Buffer& buffer);

        /// Copy operator
        Buffer operator=(const Buffer& buffer);

        /// Destructor
        ~Buffer(void);

        /// Set the value of one pixel in the buffer
        void setPixel(unsigned int i, unsigned int j, const Color& color);

        /// Set the buffer's width and height
        void dimensions(unsigned int width, unsigned int height);

        /// Get the color corresponding to one specific pixel
        Color pixel(unsigned int i, unsigned int j) const;

        /// Get a pointer on the table containing all the pixels
        const unsigned char* allPixels(void) const;

        /// Get the height of the buffer
        unsigned int height(void) const;

        /// Get the width of the buffer
        unsigned int width(void) const;

        /// Set all the pixels values to 0
        void reset(void);

    private:
        unsigned int   _height = 0;
        unsigned int   _width  = 0;
        unsigned char* _pixels = nullptr;

    };  // class Buffer

}  // namespace MatouMalin


#endif
