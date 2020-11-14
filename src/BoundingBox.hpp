//
//  BoundingBox.h
//  RayTracing
//
//  Created by Loïc CORENTHY on 9/6/12.
//
//

#ifndef RAYTRACING_BOUNDINGBOX_H
#define RAYTRACING_BOUNDINGBOX_H

// Standard includes
#include <cassert>

// Local includes
#include "Point.hpp"
#include "Vector.hpp"
#include "Ray.hpp"

// Namespace
namespace MatouMalin
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
        Point min(void) const;

        /// Get the more right, up, front point
        Point max(void) const;

        /// Set the point with the minimum coordinate values
        void setMin(const Point& min);

        /// Set the more right, up, front point
        void setMax(const Point& max);

    private:
        Point _min;
        Point _max;

    };  // class BoundingBox

    inline Point BoundingBox::min(void) const
    {
        return _min;
    }

    inline Point BoundingBox::max(void) const
    {
        return _max;
    }

    inline void BoundingBox::setMin(const Point& min)
    {
        assert(min.x() <= _min.x() && min.y() <= _min.y() && min.z() <= _min.z() && "The point has at least one coordinate which is not minimum");
        _min = min;
    }

    inline void BoundingBox::setMax(const Point& max)
    {
        assert(max.x() >= _max.x() && max.y() >= _max.y() && max.z() >= _max.z() && "The point has at least one coordinate which is not maximum");
        _max = max;
    }

}  // namespace MatouMalin

#endif
