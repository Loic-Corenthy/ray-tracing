//===============================================================================================//
/*!
 *  \file      BoundingBox.hpp
 *  \author    Loïc Corenthy
 *  \version   1.2
 *  \date      06/09/2012
 *  \copyright (c) 2012 Loïc Corenthy. All rights reserved.
 */
//===============================================================================================//

#pragma once

#include <cassert>

#include "Point.hpp"
#include "Vector.hpp"
#include "Ray.hpp"

// Namespace
namespace LCNS
{
    class BoundingBox
    {
    public:
        /// Default constructor
        BoundingBox(void);

        /// Constructor with parameter
        BoundingBox(const Point& min, const Point& max);

        /// Copy constructor
        BoundingBox(const BoundingBox& boundingBox);

        /// Copy operator
        BoundingBox operator=(const BoundingBox& boundingBox);

        /// Destructor
        ~BoundingBox(void);

        /// Check if a ray intersect the bounding box
        bool intersect(const Ray& ray) const;

        /// Get the more left, down, back point
        Point min(void) const noexcept;

        /// Get the more right, up, front point
        Point max(void) const noexcept;

        /// Set the point with the minimum coordinate values
        void min(const Point& min) noexcept;

        /// Set the more right, up, front point
        void max(const Point& max) noexcept;

    private:
        Point _min;
        Point _max;

    };  // class BoundingBox

}  // namespace LCNS
