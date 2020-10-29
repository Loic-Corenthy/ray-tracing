#ifndef RAYTRACING_SPHERE_H
#define RAYTRACING_SPHERE_H

// Standard includes
#include <cassert>

// Local includes
#include "Point.hpp"
#include "Ray.hpp"
#include "Renderable.hpp"
#include "Color.hpp"
#include "Shader.hpp"

namespace MatouMalin
{
    class Sphere : public Renderable
    {
    public:
        /// Default Constructor
        Sphere(void);

        /// Constructor with parameters
        Sphere(const MatouMalin::Point & pPoint,float pRadius);

        /// Copy constructor
        Sphere(const Sphere & pSphere);

        /// Copy operator
        Sphere operator=(const Sphere & pSphere);

        /// Destructor
        ~Sphere(void);

        /// Get the center of the sphere (read only)
        const MatouMalin::Point & center(void) const;

        /// Set the center of the sphere
        void setCenter(const MatouMalin::Point & pPoint);

        /// Get the radius of the sphere (read only)
        float radius(void) const;

        /// Set the radius of the sphere
        void setRadius(float pRadius);

        /// Virtual function, determine if a ray intersect the sphere
        bool intersect(Ray & pRay);

        /// Virtual function, get the color at the intersection point
        Color color(Ray & pRay, unsigned int pType = 0);

        /// Virtual function, get the normal at the intersection point
        Vector normal(const Point & pPosition) const;

        /// Virtual function, get the normal at the intersection point (interpolating from other vectors)
        Vector interpolatedNormal(const Point & pPosition) const;

        /// Virtual function from Renderable
        bool refractedRay(const Ray & pIncomingRay, Ray & pRefractedRay);

    private:
        /// Calculate roots of a second order polynom.
        bool _solveSecDeg(float a,float b,float c,float & root1,float & root2);

    private:
        Point mCenter;
        float mRadius;

    }; // class Sphere

    inline const MatouMalin::Point & Sphere::center(void) const
    {
        return mCenter;
    }

    inline void Sphere::setCenter(const MatouMalin::Point & pPoint)
    {
        mCenter = pPoint;
    }

    inline float Sphere::radius(void) const
    {
        return mRadius;
    }

    inline void Sphere::setRadius(float pRadius)
    {
        mRadius = pRadius;
    }

    inline Vector Sphere::normal(const Point & pPosition) const
    {
        return ((pPosition - mCenter).normalize());
    }

    inline Vector Sphere::interpolatedNormal(const Point & pPosition) const
    {
        return ((pPosition - mCenter).normalize());
    }

} // namespace MatouMalin

#endif
