//===============================================================================================//
/*!
 *  \file      DirectionalLight.hpp
 *  \author    Loïc Corenthy
 *  \version   1.0
 *  \date      14/10/2012
 *  \copyright (c) 2012 Loïc Corenthy. All rights reserved.
 */
//===============================================================================================//

#pragma once

#include "Vector.hpp"
#include "Color.hpp"
#include "Light.hpp"

namespace LCNS
{
    class DirectionalLight : public Light
    {
    public:
        /// Default constructor
        DirectionalLight(void) = default;

        /// Constructor with parameters
        DirectionalLight(const Vector& direction, const Color& intensity);

        /// Copy constructor
        DirectionalLight(const DirectionalLight& directionalLight);

        /// Copy operator
        DirectionalLight operator=(const DirectionalLight& directionalLight);

        /// Destructor
        ~DirectionalLight(void) = default;

        /// Set direction of the light
        void direction(const LCNS::Vector& direction) noexcept;

        /// Get direction of the light
        const Vector& direction(void) const noexcept;

        /// Implementation of virtual funcion from Light
        Color intensityAt(const Point& point, const Scene& scene, Renderable* currentObject) const override;

        /// Implementation of virtual funcion from Light
        Vector directionFrom([[maybe_unused]] const Point& point) const override;

    private:
        Vector _direction;

    };  // class DirectionalLight

}  // namespace LCNS
