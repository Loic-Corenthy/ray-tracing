//===============================================================================================//
/*!
 *  \file      Buffer.hpp
 *  \author    Loïc Corenthy
 *  \version   1.0
 *  \date      14/10/2012
 *  \copyright (c) 2012 Loïc Corenthy. All rights reserved.
 */
//===============================================================================================//

#pragma once

#include <memory>

#include "Color.hpp"

namespace LCNS
{
    class Buffer
    {
    public:
        /// Default constructor
        Buffer(void) = default;

        /// Constructor with parameters
        Buffer(unsigned int height, unsigned int width);

        /// Copy constructor
        Buffer(const Buffer& buffer);

        /// Copy operator
        Buffer operator=(const Buffer& buffer);

        /// Destructor
        ~Buffer(void) = default;

        /// Set the value of one pixel in the buffer
        void pixel(unsigned int i, unsigned int j, const Color& color);

        /// Set the buffer's width and height
        void dimensions(unsigned int width, unsigned int height);

        /// Get the color corresponding to one specific pixel
        Color pixel(unsigned int i, unsigned int j) const;

        /// Get a pointer on the table containing all the pixels
        const std::unique_ptr<unsigned char[]>& allPixels(void) const;

        /// Get the height of the buffer
        unsigned int height(void) const noexcept;

        /// Get the width of the buffer
        unsigned int width(void) const noexcept;

        /// Set all the pixels values to 0
        void reset(void);

    private:
        std::unique_ptr<unsigned char[]> _pixels;
        unsigned int                     _height = 0;
        unsigned int                     _width  = 0;

    };  // class Buffer

}  // namespace LCNS
