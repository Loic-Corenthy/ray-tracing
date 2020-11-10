#ifndef RAYTRACING_DIRECTIONALLIGHT_H
#define RAYTRACING_DIRECTIONALLIGHT_H

// Local includes
#include "Vector.hpp"
#include "Color.hpp"
#include "Light.hpp"

namespace MatouMalin
{
    class DirectionalLight : public Light
    {
    public:
        /// Default constructor
        DirectionalLight(void);

        /// Constructor with parameters
        DirectionalLight(const Vector & direction,const Color & intensity);

        /// Copy constructor
        DirectionalLight(const DirectionalLight & directionalLight);

        /// Copy operator
        DirectionalLight operator=(const DirectionalLight & directionalLight);

        /// Destructor
        ~DirectionalLight(void);

        /// Set direction of the light
        void setDirection(const MatouMalin::Vector & direction);

        /// Set intensity of the light
        void setIntensity(const Color & intensity);

        /// Get intensity of the light
        const Vector & direction(void) const;

        /// Get direction of the light
        const Color & intensity(void) const;

        /// Implementation of virtual funcion from Light
        Color intensityAt(const Point & point,const Scene & scene, Renderable* currentObject) const;

        /// Implementation of virtual funcion from Light
        Vector directionFrom(const Point & point) const;

    private:
        Vector _direction;

    }; // class DirectionalLight

    inline void DirectionalLight::setDirection(const Vector & direction)
    {
        _direction = direction;
    }

    inline const Vector & DirectionalLight::direction(void) const
    {
        return _direction;
    }

    inline Vector DirectionalLight::directionFrom(const Point & point) const
    {
        return _direction*(-1);
    }

} // namespace MatouMalin

#endif