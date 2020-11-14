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

namespace LCNS
{
    class Sphere : public Renderable
    {
    public:
        /// Default Constructor
        Sphere(void);

        /// Constructor with parameters
        Sphere(const LCNS::Point& point, float radius);

        /// Copy constructor
        Sphere(const Sphere& sphere);

        /// Copy operator
        Sphere operator=(const Sphere& sphere);

        /// Destructor
        ~Sphere(void);

        /// Get the center of the sphere (read only)
        const LCNS::Point& center(void) const;

        /// Set the center of the sphere
        void setCenter(const LCNS::Point& point);

        /// Get the radius of the sphere (read only)
        float radius(void) const;

        /// Set the radius of the sphere
        void setRadius(float radius);

        /// Virtual function, determine if a ray intersect the sphere
        bool intersect(Ray& ray);

        /// Virtual function, get the color at the intersection point
        Color color(Ray& ray, unsigned int type = 0);

        /// Virtual function, get the normal at the intersection point
        Vector normal(const Point& position) const;

        /// Virtual function, get the normal at the intersection point (interpolating from other vectors)
        Vector interpolatedNormal(const Point& position) const;

        /// Virtual function from Renderable
        bool refractedRay(const Ray& incomingRay, Ray& refractedRay);

    private:
        /// Calculate roots of a second order polynom.
        bool _solveSecDeg(float a, float b, float c, float& root1, float& root2);

    private:
        Point _center;
        float _radius;

    };  // class Sphere

    inline const LCNS::Point& Sphere::center(void) const
    {
        return _center;
    }

    inline void Sphere::setCenter(const LCNS::Point& point)
    {
        _center = point;
    }

    inline float Sphere::radius(void) const
    {
        return _radius;
    }

    inline void Sphere::setRadius(float radius)
    {
        _radius = radius;
    }

    inline Vector Sphere::normal(const Point& position) const
    {
        return ((position - _center).normalize());
    }

    inline Vector Sphere::interpolatedNormal(const Point& position) const
    {
        return ((position - _center).normalize());
    }

}  // namespace LCNS

#endif
