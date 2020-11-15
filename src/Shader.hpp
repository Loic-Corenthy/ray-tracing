//===============================================================================================//
/*!
 *  \file      Shader.hpp
 *  \author    Loïc Corenthy
 *  \version   1.0
 *  \date      14/10/2012
 *  \copyright (c) 2012 Loïc Corenthy. All rights reserved.
 */
//===============================================================================================//

#pragma once

#include <cassert>

#include "Color.hpp"
#include "Vector.hpp"
#include "Point.hpp"
#include "BRDF.hpp"
#include "Scene.hpp"

namespace LCNS
{
    // Forward declaration
    class Renderable;

    class Shader
    {
    public:
        enum Material : unsigned short
        {
            NONE,
            MARBLE,
            TURBULANCE,
            BUMP
        };  // TEXTURE

    public:
        /// Default constructor
        Shader(void);

        /// Constructor with parameters
        Shader(BRDF* bRDF, double reflectionCoeff, double refractionCoeff, Scene* scene, unsigned short material = Shader::Material::NONE);

        /// Copy constructor
        Shader(const Shader& shader);

        /// Copy operator
        Shader operator=(const Shader& shader);

        /// Destructor
        ~Shader(void);

        /// Get the color at a point in function of the BRDF model
        Color color(const Vector& vecToViewer, const Vector& normal, const Point& point, Renderable* thisShader, unsigned int reflectionCount);

        /// Get a pointer on the scene
        Scene* ptrOnScene(void);

        /// Get the ambient light coefficient
        Color ambientColor(const Ray& ray) const;

        /// Get how many reflections the object can have at maximum
        unsigned short reflectionCountMax(void) const;

        /// Get the reflection coefficient, used to attenuate the intensity of the reflection for the several reflection case
        double reflectionCoeff(void) const;

        /// Get the refraction coefficient, corresponding to the material index in Snell-Decartes' law
        double refractionCoeff(void) const;

        /// Get the BRDF
        BRDF* reflectionModel(void);

        /// Set how many reflections the object can have at maximum (must be less than 10)
        void setReflectionCountMax(unsigned short value);

        /// Set the reflection coefficient, must be between 0 and 1
        void setReflectionCoeff(double coeff);

        /// Set the refraction coefficient, must be bigger than 1 to enable refraction
        void setRefractionCoeff(double coeff);

    private:
        BRDF*          _bRDF;
        unsigned short _reflectionCountMax;
        double         _reflectionCoeff;
        double         _currentReflectionCoeff;
        double         _refractionCoeff;
        unsigned short _material;
        Scene*         _scene;

    };  // class Shader

    inline Scene* Shader::ptrOnScene(void)
    {
        return _scene;
    }

    inline unsigned short Shader::reflectionCountMax(void) const
    {
        return _reflectionCountMax;
    }

    inline double Shader::reflectionCoeff(void) const
    {
        return _reflectionCoeff;
    }

    inline double Shader::refractionCoeff(void) const
    {
        return _refractionCoeff;
    }

    inline BRDF* Shader::reflectionModel(void)
    {
        return _bRDF;
    }

    inline void Shader::setReflectionCountMax(unsigned short value)
    {
        assert(0 < value && value < 11 && "reflection count max out of range");
        _reflectionCountMax = value;
    }

    inline void Shader::setReflectionCoeff(double coeff)
    {
        _reflectionCoeff = coeff;
    }

    inline void Shader::setRefractionCoeff(double coeff)
    {
        assert(coeff >= 1 && "Refraction coefficient must be bigger than 1");
        _refractionCoeff = coeff;
    }

}  // namespace LCNS
