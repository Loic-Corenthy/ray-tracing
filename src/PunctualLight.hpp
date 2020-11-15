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

#include "Light.hpp"
#include "Color.hpp"

namespace LCNS
{
    class PunctualLight : public Light
    {
    public:
        /// Default constructor
        PunctualLight(void);

        /// Constructor with parameters
        PunctualLight(const Point& position, const Color& intensity);

        /// Copy constructor
        PunctualLight(const PunctualLight& punctualLight);

        /// Copy operator
        PunctualLight operator=(const PunctualLight& punctualLight);

        /// Destructor
        ~PunctualLight(void);

        /// Set the light position
        void setPosition(const Point& position);

        /// Get the light position
        const Point& position(void) const;

        /// Implementation of virtual function from Light
        Color intensityAt(const Point& point, const Scene& scene, Renderable* currentObject) const;

        /// Implementation of virtual function from Light
        Vector directionFrom(const Point& point) const;

    private:
        Point _position;

    };  // class PunctualLight

    inline void PunctualLight::setPosition(const Point& position)
    {
        _position = position;
    }

    inline const Point& PunctualLight::position(void) const
    {
        return _position;
    }

    inline LCNS::Vector PunctualLight::directionFrom(const LCNS::Point& point) const
    {
        return (_position - point);
    }

}  // namespace LCNS
