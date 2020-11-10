#ifndef RAYTRACING_RAY_H
#define RAYTRACING_RAY_H

// Standard includes
#include <limits>
#include <cassert>

// Local includes
#include "Point.hpp"
#include "Vector.hpp"

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
        Point _origin;
        Vector _direction;
        float _length;
        Renderable* _intersected;

    }; // Class Ray

    inline void Ray::setOrigin(const Point & pPoint)
    {
        _origin = pPoint;
    }

    inline void Ray::setDirection(const Vector & pVector)
    {
        _direction = pVector;
    }

    inline void Ray::setLength(float pLength)
    {
        _length = pLength;
    }

    inline void Ray::setIntersected(Renderable* pIntersected)
    {
         _intersected = pIntersected;
    }

    inline const Point & Ray::origin(void) const
    {
        return _origin;
    }

    inline const Vector & Ray::direction(void) const
    {
        return _direction;
    }

    inline float Ray::length(void) const
    {
        return _length;
    }

    inline Renderable* Ray::intersected(void) const
    {
        return _intersected;
    }

    inline Point Ray::intersection(void) const
    {
        return (_origin + _direction*_length);
    }

} // namespace MatouMalin


#endif
