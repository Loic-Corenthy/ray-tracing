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

#include <string>
#include <cassert>

namespace LCNS
{
    // Forward declaration
    class Ray;
    class Color;
    class Shader;
    class Vector;
    class Point;

    class Renderable
    {
    public:
        enum ColorType : unsigned short
        {
            REFLECTANCE = 0,
            DIFFUSE     = 1,
            SPECULAR    = 2
        };  // (c++11)

    public:
        /// Destructor
        virtual ~Renderable(void);

        /// Calculate the intersection with a ray
        virtual bool intersect(Ray& ray) = 0;

        /// Get the color of the object at the intersection with the ray
        virtual Color color(Ray& ray, unsigned int reflectionCount = 0) = 0;

        /// Get the normal of the object at a specific position
        virtual Vector normal(const Point& position) const = 0;

        /// Get the normal of the object at a specific position as the interpolation of close other parts of the object
        virtual Vector interpolatedNormal(const Point& position) const = 0;

        /// Set a pointer on a shader
        virtual void setShader(Shader* shader);

        /// Calculate refracted ray from incoming ray
        virtual bool refractedRay(const Ray& incomingRay, Ray& refractedRay) = 0;

        /// Set a pointer on the name of the object
        void setName(const std::string& name);

        /// Get the pointer on the shader
        Shader* shader(void) const;

        /// Get the pointer on the name
        std::string name(void) const;

    protected:
        /// Default constructor
        Renderable(void);

        /// Copy constructor
        Renderable(const Renderable& renderable);

        /// Copy operator (to be used by derived classes)
        void operator=(const Renderable& renderable);

        /// Calculate the refraction on the surface of an object
        bool _refraction(const Vector& incomingDirection, const Vector& normal, double n1, double n2, Vector& refractedDirection) const;

    protected:
        Shader*     _shader;
        std::string _name;


    };  // class Renderable

    inline void Renderable::setShader(Shader* shader)
    {
        _shader = shader;
    }

    inline void Renderable::setName(const std::string& name)
    {
        _name = name;
    }

    inline Shader* Renderable::shader(void) const
    {
        return _shader;
    }

    inline std::string Renderable::name(void) const
    {
        return _name;
    }

}  // namespace LCNS
