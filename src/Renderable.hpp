//===============================================================================================//
/*!
 *  \file      Renderable.hpp
 *  \author    Loïc Corenthy
 *  \version   1.0
 *  \date      14/10/2012
 *  \copyright (c) 2012 Loïc Corenthy. All rights reserved.
 */
//===============================================================================================//

#pragma once

#include <optional>
#include <string>
#include <cassert>
#include <memory>

namespace LCNS
{
    // Forward declaration
    class Ray;
    class Color;
    class Shader;
    class Vector;
    class Point;

    class Renderable : public std::enable_shared_from_this<Renderable>
    {
    public:
        enum class ColorType
        {
            REFLECTANCE = 0,
            DIFFUSE     = 1,
            SPECULAR    = 2
        };

    public:
        /// Destructor
        virtual ~Renderable(void) = default;

        /// Calculate the intersection with a ray
        virtual bool intersect(Ray& ray) = 0;

        /// Get the color of the object at the intersection with the ray
        virtual Color color(const Ray& ray, unsigned int reflectionCount = 0) = 0;

        /// Get the normal of the object at a specific position
        virtual Vector normal(const Point& position) const = 0;

        /// Get the normal of the object at a specific position as the interpolation of close other parts of the object
        virtual Vector interpolatedNormal(const Point& position) const = 0;

        /// Calculate refracted ray from incoming ray
        virtual std::optional<Ray> refractedRay(const Ray& incomingRay) = 0;

        /// Set a shader
        virtual void shader(std::shared_ptr<Shader> shader);

        /// Get the shader
        std::shared_ptr<Shader> shader(void);

        /// Set the object name
        void name(const std::string& name);

        /// Get the object name
        std::string name(void) const;

    protected:
        /// Default constructor
        Renderable(void) = default;

        /// Copy constructor
        Renderable(const Renderable& renderable) = delete;

        /// Copy operator (to be used by derived classes)
        void operator=(const Renderable& renderable) = delete;

        /// Calculate the refraction on the surface of an object
        bool _refraction(const Vector& incomingDirection, const Vector& normal, double n1, double n2, Vector& refractedDirection) const;

    protected:
        std::shared_ptr<Shader> _shader;
        std::string             _name = "";

    };  // class Renderable

}  // namespace LCNS
