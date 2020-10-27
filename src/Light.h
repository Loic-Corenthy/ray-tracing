#ifndef RAYTRACING_LIGHT_H
#define RAYTRACING_LIGHT_H

// Local includes
#include "Point.h"
#include "Vector.h"
#include "Color.h"
#include "Scene.h"

namespace MatouMalin 
{
    // Forward declaration
    class Renderable;
    
    class Light
    {
    public:
        /// Default constructor
        Light(void);
        
        /// Constructor with parameters
        Light(const Color & pColor);
        
        /// Copy constructor
        Light(const Light & pLight);
        
        /// Copy operator
        void operator=(const Light & pLight);
        
        /// Destructor
        virtual ~Light(void);
        
        /// Get the intensity of the light on a point of an object in the scene
        virtual Color intensityAt(const Point & pPoint,const Scene & pScene, Renderable* pCurrentObject) const = 0;
        
        /// Get the direction of the light from a point of an object in the scene
        virtual Vector directionFrom(const Point & pPoint) const = 0;
        
        /// Set the intensity (color) of the light
        void setIntensity(const Color & pColor);
        
        /// Get the intensity (color) of the light
        Color intensity(void) const;
        
    protected:
        Color mIntensity;
        
    }; // class Light
    
    inline void Light::setIntensity(const MatouMalin::Color &pColor)
    {
        mIntensity = pColor;
    }
    
    inline Color Light::intensity(void) const
    {
        return mIntensity;
    }
    
} // namespace MatouMalin

#endif