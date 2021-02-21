//===============================================================================================//
/*!
 *  \file      BRDF.hpp
 *  \author    Loïc Corenthy
 *  \version   1.1
 *  \date      14/10/2012
 *  \copyright (c) 2012 Loïc Corenthy. All rights reserved.
 */
//===============================================================================================//

#pragma once

#include <memory>

#include "Color.hpp"
#include "CubeMap.hpp"

namespace LCNS
{
    // Forward declaration
    class Point;
    class Vector;

    class BRDF
    {
    public:
        /// Destructor
        virtual ~BRDF(void) = default;

        /// Implement how the reflectance is calculated
        virtual Color reflectance([[maybe_unused]] const Vector& vecToLight,
                                  [[maybe_unused]] const Vector& vecToViewer,
                                  [[maybe_unused]] const Vector& normal,
                                  [[maybe_unused]] const Point&  intersection)
        = 0;

        /// Implement how the diffuse color is calculated
        virtual Color diffuse([[maybe_unused]] const Vector& vecToLight,
                              [[maybe_unused]] const Vector& normal,
                              [[maybe_unused]] const Point&  intersection) const = 0;

        /// Implement how the specular effect is calculated
        virtual Color specular([[maybe_unused]] const Vector& vecToLight,
                               [[maybe_unused]] const Vector& vecToViewer,
                               [[maybe_unused]] const Vector& normal,
                               [[maybe_unused]] const Point&  intersection) const = 0;

        /// Set ambient color
        void ambient(const Color& ambient);

        /// Get ambient color
        Color ambient(void) const;

        /// Set a pointer on a CubeMap
        void cubeMap(std::shared_ptr<CubeMap> cubeMap);

        /// Get the pointer on the associated CubeMap
        const std::shared_ptr<CubeMap> cubeMap(void) const;

    protected:
        /// Default constructor
        BRDF(void) = default;

        /// Constructor with parameter
        BRDF(const Color& ambiant);

        /// Copy constructor
        BRDF(const BRDF& brdf) = delete;

        /// Copy operator
        void operator=(const BRDF& brdf) = delete;

    private:
        Color                    _ambientColor;
        std::shared_ptr<CubeMap> _cubeMap;

    };  // class BRDF

}  // namespace LCNS
