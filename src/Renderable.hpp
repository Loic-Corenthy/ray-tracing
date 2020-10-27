#ifndef RAYTRACING_RENDERABLE_H
#define RAYTRACING_RENDERABLE_H

// Standard includes
#include <string>
#include <cassert>

namespace MatouMalin 
{
    // Forward declaration
    class Ray;
    class Color;
    class Shader;
    class Vector;
    class Point;
    
    class Renderable
    {
    public:
        enum ColorType : unsigned short {REFLECTANCE = 0, DIFFUSE = 1, SPECULAR = 2}; // (c++11)
        
    public:
        /// Destructor
        virtual ~Renderable(void);
        
        /// Calculate the intersection with a ray
        virtual bool intersect(Ray & pRay) = 0;
        
        /// Get the color of the object at the intersection with the ray
        virtual Color color(Ray & pRay, unsigned int pReflectionCount = 0) = 0;
        
        /// Get the normal of the object at a specific position
        virtual Vector normal(const Point & pPosition) const = 0;
        
        /// Get the normal of the object at a specific position as the interpolation of close other parts of the object
        virtual Vector interpolatedNormal(const Point & pPosition) const = 0;
        
        /// Set a pointer on a shader
        virtual void setShader(Shader* pShader);
        
        /// Calculate refracted ray from incoming ray
        virtual bool refractedRay(const Ray & pIncomingRay, Ray & pRefractedRay) = 0;
        
        /// Set a pointer on the name of the object
        void setName(const std::string & pName);
        
        /// Get the pointer on the shader
        Shader* shader(void) const;
        
        /// Get the pointer on the name
        std::string name(void) const;
        
    protected:
        /// Default constructor
        Renderable(void);
        
        /// Copy constructor
        Renderable(const Renderable & pRenderable);
        
        /// Copy operator (to be used by derived classes)
        void operator=(const Renderable & pRenderable);
        
        /// Calculate the refraction on the surface of an object
        bool _refraction(const Vector & pIncomingDirection, const Vector & pNormal, double pN1, double pN2, Vector & pRefractedDirection) const;
        
    protected:
        Shader* mShader;
        std::string mName;

        
    }; // class Renderable
    
    inline void Renderable::setShader(Shader* pShader)
    {
        mShader = pShader;
    }
    
    inline void Renderable::setName(const std::string & pName)
    {
        mName = pName;
    }
    
    inline Shader* Renderable::shader(void) const
    {
        return mShader;
    }
    
    inline std::string Renderable::name(void) const
    {
        return mName;
    }
    
} // namespace MatouMalin 

#endif