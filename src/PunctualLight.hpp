//===============================================================================================//
/*!
 *  \file      PunctualLight.hpp
 *  \author    Loïc Corenthy
 *  \version   1.0
 *  \date      14/10/2012
 *  \copyright (c) 2012 Loïc Corenthy. All rights reserved.
 */
//===============================================================================================//

#pragma once

#include <memory>

#include "Light.hpp"
#include "Color.hpp"
#include "Vector.hpp"
#include "Point.hpp"

namespace LCNS
{
    // Forward declaration
    class Renderable;

    class PunctualLight : public Light
    {
    public:
        /// Default constructor
        PunctualLight(void) = default;

        /// Constructor with parameters
        PunctualLight(const Point& position, const Color& intensity);

        /// Copy constructor
        PunctualLight(const PunctualLight& punctualLight);

        /// Copy operator
        PunctualLight operator=(const PunctualLight& punctualLight);

        /// Destructor
        ~PunctualLight(void) = default;

        /// Set the light position
        void position(const Point& position) noexcept;

        /// Get the light position
        const Point& position(void) const noexcept;

        /// Implementation of virtual function from Light
        Color intensityAt(const Point& point, const Scene& scene, std::shared_ptr<Renderable> currentObject) const override;

        /// Implementation of virtual function from Light
        Vector directionFrom(const Point& point) const override;

    private:
        Point _position;

    };  // class PunctualLight

}  // namespace LCNS
