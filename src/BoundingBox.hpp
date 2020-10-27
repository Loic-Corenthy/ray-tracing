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
        Point mMin;
        Point mMax;
        
    }; // class BoundingBox
    
    inline Point BoundingBox::min(void) const
    {
        return mMin;
    }
    
    inline Point BoundingBox::max(void) const
    {
        return mMax;
    }
    
    inline void BoundingBox::setMin(const Point & pMin)
    {
        assert(pMin.x() <= mMin.x() && pMin.y() <= mMin.y() && pMin.z() <= mMin.z() && "The point has at least one coordinate which is not minimum");
        mMin = pMin;
    }
    
    inline void BoundingBox::setMax(const Point & pMax)
    {
        assert(pMax.x() >= mMax.x() && pMax.y() >= mMax.y() && pMax.z() >= mMax.z() && "The point has at least one coordinate which is not maximum");
        mMax = pMax;
    }
    
} // namespace MatouMalin

#endif
