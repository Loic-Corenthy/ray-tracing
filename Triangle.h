#ifndef RAYTRACING_TRIANGLE_H
#define RAYTRACING_TRIANGLE_H

// Standard includes
#include <cassert>

// Local includes
#include "Renderable.h"
#include "Point.h"
#include "Vector.h"
#include "Shader.h"

namespace MatouMalin 
{
    // Forward declaration
    class Ray;
    
    class Triangle : public Renderable
    {
    public:
        /// Default constructor
        Triangle(void);
        
        /// Constructor with vertices parameters
        Triangle(const Point & pPoint0,const Point & pPoint1,const Point & pPoint2);
        
        /// Copy constructor
        Triangle(const Triangle & pTriangle);
        
        /// Destructor
        ~Triangle(void);
        
        /// Vertex operator (read only)
        Point operator[](unsigned int pIndex) const;
        
        /// Vertex operator (read, write)
        Point & operator[](unsigned int pIndex);
        
        /// Get vertex 0, (read only)
        const Point & v0(void) const;
        
        /// Get vertex 1, (read only)
        const Point & v1(void) const;
        
        /// Get vertex 2, (read only)
        const Point & v2(void) const;
        
        /// Set vertex 0 
        void setV0(const Point & pPoint);
        
        /// Set vertex 1     
        void setV1(const Point & pPoint);
        
        /// Set vertex 2 
        void setV2(const Point & pPoint);
        
        /// Set vertex with index
        void setVI(unsigned int pIndex, const Point & pPoint);
        
        /// Set the normal of each vertex with index
        void setVertexNormal(unsigned int pIndex, const Vector & pVertexNormal);
        
        /// Calculate the normal vector of the triangle
        void updateNormal(void);
        
        /// Virtual function from Renderable
        bool intersect(Ray & pRay);
        
        /// Virtual function from Renderable
        Color color(Ray & pRay, unsigned int pReflectionCount = 0);
        
        /// Virtual function, get the normal at the intersection point (the position is not taken into account for the moment :p)
        Vector normal(const Point & pPosition) const;
                
        /// Virtual function, get the normal at the intersection point (interpolating from other vectors)
        Vector interpolatedNormal(const Point & pPosition) const;
        
        /// Virtual function from Renderable
        bool refractedRay(const Ray & pIncomingRay, Ray & pRefractedRay);
        
        /// Set the normal of the triangle
        void setNormal(const Vector & pNormal);
        
    private:
        /// Calculate determinant of a 2x2 matrix
        float _det(float pA1,float pA2,float pB1,float pB2);
        
        /// Calculate barycentric interpolation of normal from vertex normals
        Vector _barycentricNormal(const Point & pPositionInTriangle) const;
        
    private:
        Point  mVertice[3];
        Vector mVertexNormal[3];
        Vector mNormal;
        
    }; // class Triangle
    
    inline Point Triangle::operator[](unsigned int pIndex) const
    {
        return mVertice[pIndex];
    }
    
    inline Point & Triangle::operator[](unsigned int pIndex)
    {
        return mVertice[pIndex];
    }
    
    inline const Point & Triangle::v0(void) const
    {
        return mVertice[0];
    }
    
    inline const Point & Triangle::v1(void) const
    {
        return mVertice[1];
    }
    
    inline const Point & Triangle::v2(void) const
    {
        return mVertice[2];
    }
    
    inline void Triangle::setV0(const Point & pPoint)
    {
        mVertice[0] = pPoint;
    }
    
    inline void Triangle::setV1(const Point & pPoint)
    {
        mVertice[1] = pPoint;
    }
    
    inline void Triangle::setV2(const Point & pPoint)
    {
        mVertice[2] = pPoint;
    }
    
    inline void Triangle::setVI(unsigned int pIndex, const MatouMalin::Point &pPoint)
    {
        assert(pIndex == 0 || pIndex == 1 || pIndex == 2 && "Index must be 0,1 or 2");
        mVertice[pIndex] = pPoint;
    }
    
    inline void Triangle::setVertexNormal(unsigned int pIndex, const MatouMalin::Vector & pVertexNormal)
    {
        assert(pIndex == 0 || pIndex == 1 || pIndex == 2 && "Index must be 0,1 or 2");
        mVertexNormal[pIndex] = pVertexNormal;
    }
    
    inline float Triangle::_det(float pA1,float pA2,float pB1,float pB2)
    {
        return (pA1*pB2 - pA2*pB1);
    }
    
    inline Vector Triangle::normal(const Point & pPosition) const
    {
        return _barycentricNormal(pPosition);
        return mNormal;
    }
    
    inline void Triangle::setNormal(const Vector & pNormal)
    {
        mNormal = pNormal;
    }
    
} // namespace MatouMalin

#endif