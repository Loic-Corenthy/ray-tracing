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

//Local includes
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
        BoundingBox(const Point & pMin, const Point & pMax);

        /// Copy constructor
        BoundingBox(const BoundingBox & pBoundingBox);

        /// Copy operator
        BoundingBox operator=(const BoundingBox & pBoundingBox);

        /// Destructor
        ~BoundingBox(void);

        /// Check if a ray intersect the bounding box
        bool intersect(const Ray & pRay) const;

        /// Get the more left, down, back point
        Point min(void) const;

        /// Get the more right, up, front point
        Point max(void) const;

        /// Set the point with the minimum coordinate values
        void setMin(const Point & pMin);

        /// Set the more right, up, front point
        void setMax(const Point & pMax);

    private:
        Point _min;
        Point _max;

    }; // class BoundingBox

    inline Point BoundingBox::min(void) const
    {
        return _min;
    }

    inline Point BoundingBox::max(void) const
    {
        return _max;
    }

    inline void BoundingBox::setMin(const Point & pMin)
    {
        assert(pMin.x() <= _min.x() && pMin.y() <= _min.y() && pMin.z() <= _min.z() && "The point has at least one coordinate which is not minimum");
        _min = pMin;
    }

    inline void BoundingBox::setMax(const Point & pMax)
    {
        assert(pMax.x() >= _max.x() && pMax.y() >= _max.y() && pMax.z() >= _max.z() && "The point has at least one coordinate which is not maximum");
        _max = pMax;
    }

} // namespace MatouMalin

#endif
