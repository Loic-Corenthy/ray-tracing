//===============================================================================================//
/*!
 *  \file      Lambert.hpp
 *  \author    Loïc Corenthy
 *  \version   1.2
 *  \date      04/09/2012
 *  \copyright (c) 2012 Loïc Corenthy. All rights reserved.
 */
//===============================================================================================//

#pragma once

#include "BRDF.hpp"
#include "Color.hpp"

namespace LCNS
{
    class Lambert : public BRDF
    {
    public:
        /// Default constructor
        Lambert(void) = default;

        /// Constructor with parameters
        explicit Lambert(const Color& diffusionColor);

        /// Copy constructor
        Lambert(const Lambert& lambert) = delete;

        /// Copy operator
        Lambert operator=(const Lambert& lambert) = delete;

        /// Destructor
        ~Lambert(void) = default;

        /// Set the Kd coefficient
        void diffusionColor(const Color& kd) noexcept;

        /// Get the Kd coefficient
        Color diffusionColor(void) const noexcept;

        /// Implementation of virtual method from BRDF
        Color reflectance([[maybe_unused]] const Vector& vecToLight,
                          [[maybe_unused]] const Vector& vecToViewer,
                          [[maybe_unused]] const Vector& normal,
                          [[maybe_unused]] const Point&  intersection) override final;

        /// Implementation of virtual method from BRDF
        Color diffuse([[maybe_unused]] const Vector& vecToLight,
                      [[maybe_unused]] const Vector& normal,
                      [[maybe_unused]] const Point&  intersection) const override final;

        /// Implementation of virtual method from BRDF
        Color specular([[maybe_unused]] const Vector& vecToLight,
                       [[maybe_unused]] const Vector& vecToViewer,
                       [[maybe_unused]] const Vector& normal,
                       [[maybe_unused]] const Point&  intersection) const override final;

    private:
        Color _diffusionColor;

    };  // class Lambert

}  // namespace LCNS
