//
//  Lambert.h
//  RayTracing
//
//  Created by Loïc CORENTHY on 9/4/12.
//
//

#ifndef RAYTRACING_LAMBERT_H
#define RAYTRACING_LAMBERT_H

// Local includes
#include "BRDF.hpp"
#include "Color.hpp"

namespace LCNS
{
    class Lambert : public BRDF
    {
    public:
        /// Default constructor
        Lambert(void);

        /// Constructor with parameters
        Lambert(const Color& diffusionColor);

        /// Copy constructor
        Lambert(const Lambert& lambert);

        /// Copy operator
        Lambert operator=(const Lambert& lambert);

        /// Destructor
        ~Lambert(void);

        /// Set the Kd coefficient
        void setDiffusionColor(Color kd);

        /// Get the Kd coefficient
        Color diffusionColor(void) const;

        /// Implementation of virtual method from BRDF
        Color reflectance(const Vector& vecToLight, const Vector& vecToViewer, const Vector& normal, const Point& intersection);

        /// Implementation of virtual method from BRDF
        Color diffuse(const Vector& vecToLight, const Vector& normal, const Point& intersection) const final;  //(c++11)

        /// Implementation of virtual method from BRDF
        Color specular(const Vector& vecToLight, const Vector& vecToViewer, const Vector& normal, const Point& intersection) const final;  //(c++11)

    private:
        Color _diffusionColor;

    };  // class Lambert

    inline void Lambert::setDiffusionColor(Color diffusionColor)
    {
        _diffusionColor = diffusionColor;
    }

    inline Color Lambert::diffusionColor(void) const
    {
        return _diffusionColor;
    }

}  // namespace LCNS

#endif
