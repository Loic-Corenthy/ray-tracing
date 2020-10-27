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
        DirectionalLight(const Vector & pDirection,const Color & pIntensity);
        
        /// Copy constructor
        DirectionalLight(const DirectionalLight & pDirectionalLight);
        
        /// Copy operator
        DirectionalLight operator=(const DirectionalLight & pDirectionalLight);
        
        /// Destructor
        ~DirectionalLight(void);
        
        /// Set direction of the light
        void setDirection(const MatouMalin::Vector & pDirection);
        
        /// Set intensity of the light
        void setIntensity(const Color & pIntensity);
        
        /// Get intensity of the light
        const Vector & direction(void) const;
        
        /// Get direction of the light
        const Color & intensity(void) const;
        
        /// Implementation of virtual funcion from Light
        Color intensityAt(const Point & pPoint,const Scene & pScene, Renderable* pCurrentObject) const;
        
        /// Implementation of virtual funcion from Light
        Vector directionFrom(const Point & pPoint) const;
        
    private:
        Vector mDirection;
        
    }; // class DirectionalLight
    
    inline void DirectionalLight::setDirection(const Vector & pDirection)
    {
        mDirection = pDirection;
    }
    
    inline const Vector & DirectionalLight::direction(void) const
    {
        return mDirection;
    }
    
    inline Vector DirectionalLight::directionFrom(const Point & pPoint) const
    {
        return mDirection*(-1);
    }
    
} // namespace MatouMalin

#endif