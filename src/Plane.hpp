//
//  Plane.h
//  RayTracing
//
//  Created by Loïc CORENTHY on 10/12/12.
//
//

#ifndef RAYTRACING_PLANE_H
#define RAYTRACING_PLANE_H

// Standard includes
#include <cassert>

// Local includes
#include "Point.hpp"
#include "Vector.hpp"
#include "Ray.hpp"

namespace MatouMalin
{
    class Plane
    {
    public:
        /// Default constructor
        Plane(void);
        
        /// Constructor with equation coefficients
        Plane(double pA, double pB, double pC, double pD);
        
        /// Constructor with position and normal direction
        Plane(const Vector & pNormal, const Point & pPosition);
        
        /// Copy constructor
        Plane(const Plane & pPlane);
        
        /// Copy operator
        Plane operator=(const Plane & pPlane);
        
        /// Destructor
        ~Plane(void);
        
        /// Calculate the intersection with a ray
        bool intersect(Ray & pRay);
        
        /// Set the coefficients of the equation
        void setCoefficient(unsigned int pIndex, double pValue);
        
        /// Set the normal vector
        void setNormal(const Vector & pNormal);
        
        /// Set the position in space
        void setPosition(const Point & pPosition);
        
        /// Get the coefficients of the equation
        double coefficient(unsigned int pIndex) const;
        
        /// Get the normal vector
        Vector normal(void) const;
        
        /// Get the position in space
        Point position(void) const;
       
    private:
        /// Update the equation with the normal and the position
        void _updateEquation(void);
        
        /// Update the normal with the equation
        void _updateNormal(void);
        
        /// Update the position with the equation
        void _updatePosition(void);
        
    private:
        double mEquationCoeffs[4];
        Point  mPosition;
        Vector mNormal;
        
    }; // class Plane
    
    inline double Plane::coefficient(unsigned int pIndex) const
    {
        assert(0 <= pIndex && pIndex <4 && "index out of boundaries for the coefficients");
        return mEquationCoeffs[pIndex];
    }

    inline Vector Plane::normal(void) const
    {
        return mNormal;
    }

    inline Point Plane::position(void) const
    {
        return mPosition;
    }


} // namespace MatouMalin

#endif 










