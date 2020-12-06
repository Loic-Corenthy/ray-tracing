//===============================================================================================//
/*!
 *  \file      Phong.hpp
 *  \author    Loïc Corenthy
 *  \version   1.0
 *  \date      14/10/2012
 *  \copyright (c) 2012 Loïc Corenthy. All rights reserved.
 */
//===============================================================================================//

#pragma once

#include "BRDF.hpp"
#include "Color.hpp"

namespace LCNS
{
    class Phong : public BRDF
    {
    public:
        /// Default constructor
        Phong(void) = default;

        /// Constructor with parameters
        Phong(const Color& diffusionColor, const Color& specularColor, int exponent);

        /// Copy constructor
        Phong(const Phong& phong) = delete;

        /// Copy operator
        Phong operator=(const Phong& phong) = delete;

        /// Destructor
        ~Phong(void) = default;

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

        /// Set the diffusion color coefficient
        void diffusionColor(const Color& diffusionColor) noexcept;

        /// Get the DiffusionColor coefficient
        Color diffusionColor(void) const noexcept;

        /// Set the specular color coefficient
        void specularColor(const Color& specularColor) noexcept;

        /// Get the SpecularColor coefficient
        Color specularColor(void) const noexcept;

        /// Get the exponent
        int exponent(void) const noexcept;

        /// Set the exponent
        void exponent(int exponent) noexcept;

    private:
        Color _diffusionColor;
        Color _specularColor;
        int   _exponent = 0;

    };  // class Phong

}  // namespace LCNS
