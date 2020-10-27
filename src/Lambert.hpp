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

namespace MatouMalin
{    
    class Lambert : public BRDF
    {
    public:
        /// Default constructor
        Lambert(void);
        
        /// Constructor with parameters
        Lambert(const Color & pDiffusionColor);
        
        /// Copy constructor
        Lambert(const Lambert & pLambert);
        
        /// Copy operator
        Lambert operator=(const Lambert & pLambert);
        
        /// Destructor
        ~Lambert(void);
        
        /// Set the Kd coefficient
        void setDiffusionColor(Color pKd);
        
        /// Get the Kd coefficient
        Color diffusionColor(void) const;
        
        /// Implementation of virtual method from BRDF
        Color reflectance(const Vector & pVecToLight, const Vector & pVecToViewer,const Vector & pNormal,const Point & pIntersection);
        
        /// Implementation of virtual method from BRDF
        Color diffuse(const Vector & pVecToLight, const Vector & pNormal,const Point & pIntersection) const final;//(c++11)
        
        /// Implementation of virtual method from BRDF
        Color specular(const Vector & pVecToLight, const Vector & pVecToViewer,const Vector & pNormal,const Point & pIntersection) const final;//(c++11)
        
    private:
        Color mDiffusionColor;
        
    }; // class Lambert
    
    inline void Lambert::setDiffusionColor(Color pDiffusionColor)
    {
        mDiffusionColor = pDiffusionColor;
    }
    
    inline Color Lambert::diffusionColor(void) const
    {
        return mDiffusionColor;
    }
    
} // namespace MatouMalin

#endif
