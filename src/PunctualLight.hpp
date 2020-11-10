#ifndef RAYTRACING_PUNCTUALLIGHT_H
#define RAYTRACING_PUNCTUALLIGHT_H

// Local includes
#include "Light.hpp"
#include "Color.hpp"

namespace MatouMalin
{
    class PunctualLight : public Light
    {
    public:
        /// Default constructor
        PunctualLight(void);

        /// Constructor with parameters
        PunctualLight(const Point & pPosition,const Color & pIntensity);

        /// Copy constructor
        PunctualLight(const PunctualLight & pPunctualLight);

        /// Copy operator
        PunctualLight operator=(const PunctualLight & pPunctualLight);

        /// Destructor
        ~PunctualLight(void);

        /// Set the light position
        void setPosition(const Point & pPosition);

        /// Get the light position
        const Point & position(void) const;

        /// Implementation of virtual function from Light
        Color intensityAt(const Point & pPoint,const Scene & pScene, Renderable* pCurrentObject) const;

        /// Implementation of virtual function from Light
        Vector directionFrom(const Point & pPoint) const;

    private:
        Point _position;

    }; // class PunctualLight

    inline void PunctualLight::setPosition(const Point & pPosition)
    {
        _position = pPosition;
    }

    inline const Point & PunctualLight::position(void) const
    {
        return _position;
    }

    inline MatouMalin::Vector PunctualLight::directionFrom(const MatouMalin::Point & pPoint) const
    {
        return (_position - pPoint);
    }

} // namespace MatouMalin

#endif