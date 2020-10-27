#ifndef RAYTRACING_BRDF_H
#define RAYTRACING_BRDF_H

// Local includes
#include "Color.h"
#include "CubeMap.h"

namespace MatouMalin 
{
    // Forward declaration
    class Point;
    class Vector;
    
    class BRDF
    {
    public:        
        /// Destructor
        virtual ~BRDF(void);
        
        /// Implement how the reflectance is calculated
        virtual Color reflectance(const Vector & pVecToLight, const Vector & pVecToViewer,const Vector & pNormal,const Point & pIntersection) = 0;
        
        /// Set ambient color
        void setAmbient(const Color & pAmbient);
        
        /// Get ambient color
        Color ambient(void) const;
        
        /// Set a pointer on a CubeMap
        void setCubeMap(CubeMap* pCubeMap);

        /// Get the pointer on the associated CubeMap
        const CubeMap* cubeMap(void) const;
        
        /// Implement how the diffuse color is calculated
        virtual Color diffuse(const Vector & pVecToLight, const Vector & pNormal,const Point & pIntersection) const = 0;
        
        /// Implement how the specular effect is calculated
        virtual Color specular(const Vector & pVecToLight, const Vector & pVecToViewer,const Vector & pNormal,const Point & pIntersection) const = 0;
        
    protected:
        /// Default constructor
        BRDF(void);
        
        /// Constructor with parameter
        BRDF(const Color & pAmbiant);
        
        /// Copy constructor
        BRDF(const BRDF & pBRDF);
        
        /// Copy operator
        void operator=(const BRDF & pBRDF);

    private:
        Color mAmbientColor;
        CubeMap* mCubeMap;
        
    }; // class BRDF
    
    inline void BRDF::setAmbient(const Color & pAmbient)
    {
        mAmbientColor = pAmbient;
    }
    
    inline Color BRDF::ambient(void) const
    {
        return mAmbientColor;
    }
    
    inline void BRDF::setCubeMap(CubeMap* pCubeMap)
    {
        mCubeMap = pCubeMap;
    }
    
    inline const CubeMap* BRDF::cubeMap(void) const
    {
        return mCubeMap;
    }

    
} // namespace MatouMalin


#endif
