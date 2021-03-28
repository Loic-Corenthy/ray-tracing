//===============================================================================================//
/*!
 *  \file      Sphere.hpp
 *  \author    Loïc Corenthy
 *  \version   1.2
 *  \date      14/10/2012
 *  \copyright (c) 2012 Loïc Corenthy. All rights reserved.
 */
//===============================================================================================//

#pragma once

#include <cassert>
#include <memory>
#include <optional>
#include <tuple>

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
        Sphere(void) = default;

        /// Constructor with parameters
        Sphere(const Point& point, double radius);

        /// Copy constructor
        Sphere(const Sphere& sphere);

        /// Copy operator
        Sphere& operator=(const Sphere& sphere) = delete;

        /// Destructor
        ~Sphere(void) = default;

        /// Virtual function, determine if a ray intersect the sphere
        bool intersect(Ray& ray) override;

        /// Virtual function, get the color at the intersection point
        Color color(const Ray& ray, unsigned int type = 0) override;

        /// Virtual function, get the normal at the intersection point
        Vector normal(const Point& position) const override;

        /// Virtual function, get the normal at the intersection point (interpolating from other vectors)
        Vector interpolatedNormal(const Point& position) const override;

        /// Virtual function from Renderable
        std::optional<Ray> refractedRay(const Ray& incomingRay) override;

        /// Get the center of the sphere (read only)
        const LCNS::Point& center(void) const noexcept;

        /// Set the center of the sphere
        void center(const LCNS::Point& point) noexcept;

        /// Get the radius of the sphere (read only)
        double radius(void) const noexcept;

        /// Set the radius of the sphere
        void radius(double value) noexcept;

    private:
        /// Calculate roots of a second order polynomial.
        std::optional<std::tuple<double, double>> _solveSecDeg(double a, double b, double c) const;

    private:
        Point  _center;
        double _radius = 0.0f;

    };  // class Sphere

}  // namespace LCNS
