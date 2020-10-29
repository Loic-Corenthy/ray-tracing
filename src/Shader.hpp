#ifndef RAYTRACING_SHADER_H
#define RAYTRACING_SHADER_H

// Standard includes
#include <cassert>

// Local includes
#include "Color.hpp"
#include "Vector.hpp"
#include "Point.hpp"
#include "BRDF.hpp"
#include "Scene.hpp"

namespace MatouMalin
{
    // Forward declaration
    class Renderable;

    class Shader
    {
    public:
        enum Material : unsigned short {NONE, MARBLE, TURBULANCE, BUMP}; // TEXTURE

    public:
        /// Default constructor
        Shader(void);

        /// Constructor with parameters
        Shader(BRDF* pBRDF, double pReflectionCoeff, double pRefractionCoeff, Scene* pScene, unsigned short pMaterial = Shader::Material::NONE);

        /// Copy constructor
        Shader(const Shader & pShader);

        /// Copy operator
        Shader operator=(const Shader & pShader);

        /// Destructor
        ~Shader(void);

        /// Get the color at a point in function of the BRDF model
        Color color(const Vector & pVecToViewer,const Vector & pNormal,const Point & pPoint, Renderable* pThis, unsigned int pReflectionCount);

        /// Get a pointer on the scene
        Scene* ptrOnScene(void);

        /// Get the ambient light coefficient
        Color ambientColor(const Ray & pRay) const;

        /// Get how many reflections the object can have at maximum
        unsigned short reflectionCountMax(void) const;

        /// Get the reflection coefficient, used to attenuate the intensity of the reflection for the several reflection case
        double reflectionCoeff(void) const;

        /// Get the refraction coefficient, corresponding to the material index in Snell-Decartes' law
        double refractionCoeff(void) const;

        /// Get the BRDF
        BRDF* reflectionModel(void);

        /// Set how many reflections the object can have at maximum (must be less than 10)
        void setReflectionCountMax(unsigned short pValue);

        /// Set the reflection coefficient, must be between 0 and 1
        void setReflectionCoeff(double pCoeff);

        /// Set the refraction coefficient, must be bigger than 1 to enable refraction
        void setRefractionCoeff(double pCoeff);

    private:
        BRDF* mBRDF;
        unsigned short mReflectionCountMax;
        double mReflectionCoeff;
        double mCurrentReflectionCoeff;
        double mRefractionCoeff;
        unsigned short mMaterial;
        Scene* mScene;

    }; // class Shader

    inline Scene* Shader::ptrOnScene(void)
    {
        return mScene;
    }

    inline unsigned short Shader::reflectionCountMax(void) const
    {
        return mReflectionCountMax;
    }

    inline double Shader::reflectionCoeff(void) const
    {
        return mReflectionCoeff;
    }

    inline double Shader::refractionCoeff(void) const
    {
        return mRefractionCoeff;
    }

    inline BRDF* Shader::reflectionModel(void)
    {
        return mBRDF;
    }

    inline void Shader::setReflectionCountMax(unsigned short pValue)
    {
        assert(0 < pValue && pValue < 11 && "reflection count max out of range");
        mReflectionCountMax = pValue;
    }

    inline void Shader::setReflectionCoeff(double pCoeff)
    {
        mReflectionCoeff = pCoeff;
    }

    inline void Shader::setRefractionCoeff(double pCoeff)
    {
        assert(pCoeff >= 1 && "Refraction coefficient must be bigger than 1");
        mRefractionCoeff = pCoeff;
    }

} // namespace MatouMalin

#endif
