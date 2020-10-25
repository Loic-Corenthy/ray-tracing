#ifndef RAYTRACING_RAY_H
#define RAYTRACING_RAY_H

// Standard includes
#include <limits>
#include <cassert>

// Local includes
#include "Point.h"
#include "Vector.h"

#ifndef MAXFLOAT
    #define MAXFLOAT std::numeric_limits<float>::max()
#endif

namespace MatouMalin
{
    // Forward declaration
    class Renderable;
    
    class Ray
    {
    public:
        /// Default constructor
        Ray(void);
        
        /// Constructor with parameters
        Ray(const Point & pOrigin, const Vector & pDirection);
        
        /// Copy constructor
        Ray(const Ray & pRay);
        
        /// Copy operator
        Ray operator=(const Ray & pRay);
        
        /// Destructor
        ~Ray(void);
        
        /// Set the origin of the ray
        void setOrigin(const Point & pPoint);
        
        /// Set the direction of the ray
        void setDirection(const Vector & pVector);
        
        /// Set the length of the ray
        void setLength(float pLength);
        
        /// Keep a pointer on the intersected object
        void setIntersected(Renderable* pIntersected);
        
        /// Get the origin of the ray
        const Point & origin(void) const;
        
        /// Get the direction of the ray
        const Vector & direction(void) const;
        
        /// Get the length of the ray
        float length(void) const;

        /// Get a pointer on the intersected object
        Renderable* intersected(void) const;
        
        /// Get the intersection point
        Point intersection(void) const;
        
        
    private:
        Point mOrigin;
        Vector mDirection;
        float mLength;
        Renderable* mIntersected;
        
    }; // Class Ray
    
    inline void Ray::setOrigin(const Point & pPoint)
    {
        mOrigin = pPoint;
    }
    
    inline void Ray::setDirection(const Vector & pVector)
    {
        mDirection = pVector;
    }
    
    inline void Ray::setLength(float pLength)
    {
        mLength = pLength;
    }
    
    inline void Ray::setIntersected(Renderable* pIntersected)
    {
         mIntersected = pIntersected;
    }
    
    inline const Point & Ray::origin(void) const
    {
        return mOrigin;
    }
    
    inline const Vector & Ray::direction(void) const
    {
        return mDirection;
    }
    
    inline float Ray::length(void) const
    {
        return mLength;
    }
    
    inline Renderable* Ray::intersected(void) const
    {
        return mIntersected;
    }
    
    inline Point Ray::intersection(void) const
    {
        return (mOrigin + mDirection*mLength);
    }

} // namespace MatouMalin


#endif
