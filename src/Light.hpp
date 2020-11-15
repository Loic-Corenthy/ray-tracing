//===============================================================================================//
/*!
 *  \file      Light.hpp
 *  \author    Loïc Corenthy
 *  \version   1.0
 *  \date      14/10/2012
 *  \copyright (c) 2012 Loïc Corenthy. All rights reserved.
 */
//===============================================================================================//

#pragma once

#include "Point.hpp"
#include "Vector.hpp"
#include "Color.hpp"
#include "Scene.hpp"

namespace LCNS
{
    // Forward declaration
    class Renderable;

    class Light
    {
    public:
        /// Default constructor
        Light(void);

        /// Constructor with parameters
        Light(const Color& color);

        /// Copy constructor
        Light(const Light& light);

        /// Copy operator
        void operator=(const Light& light);

        /// Destructor
        virtual ~Light(void);

        /// Get the intensity of the light on a point of an object in the scene
        virtual Color intensityAt(const Point& point, const Scene& scene, Renderable* currentObject) const = 0;

        /// Get the direction of the light from a point of an object in the scene
        virtual Vector directionFrom(const Point& point) const = 0;

        /// Set the intensity (color) of the light
        void setIntensity(const Color& color);

        /// Get the intensity (color) of the light
        Color intensity(void) const;

    protected:
        Color _intensity;

    };  // class Light

    inline void Light::setIntensity(const LCNS::Color& color)
    {
        _intensity = color;
    }

    inline Color Light::intensity(void) const
    {
        return _intensity;
    }

}  // namespace LCNS
