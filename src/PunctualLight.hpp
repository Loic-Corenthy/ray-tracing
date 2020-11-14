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

    inline MatouMalin::Vector PunctualLight::directionFrom(const MatouMalin::Point& point) const
    {
        return (_position - point);
    }

}  // namespace MatouMalin

#endif