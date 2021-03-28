//===============================================================================================//
/*!
 *  \file      Shader.hpp
 *  \author    Loïc Corenthy
 *  \version   1.2
 *  \date      14/10/2012
 *  \copyright (c) 2012 Loïc Corenthy. All rights reserved.
 */
//===============================================================================================//

#pragma once

#include <cassert>
#include <memory>
#include <atomic>

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
        Shader(void) = delete;

        /// Constructor with parameters
        Shader(std::shared_ptr<BRDF>  bRDF,
               double                 reflectionCoeff,
               double                 refractionCoeff,
               std::shared_ptr<Scene> scene,
               unsigned short         material = Shader::Material::NONE);

        /// Copy constructor
        Shader(const Shader& shader);

        /// Copy operator
        Shader operator=(const Shader& shader);

        /// Destructor
        ~Shader(void);

        /// Get the color at a point in function of the BRDF model
        Color color(const Vector& vecToViewer, const Vector& normal, const Point& point, Renderable* thisShader, unsigned int reflectionCount);

        /// Get a pointer on the scene
        std::shared_ptr<Scene> ptrOnScene(void);

        /// Get the ambient light coefficient
        Color ambientColor(const Ray& ray) const;

        /// Get how many reflections the object can have at maximum
        unsigned short reflectionCountMax(void) const;

        /// Get the reflection coefficient, used to attenuate the intensity of the reflection for the several reflection case
        double reflectionCoeff(void) const;

        /// Get the refraction coefficient, corresponding to the material index in Snell-Decartes' law
        double refractionCoeff(void) const;

        /// Get the BRDF
        std::shared_ptr<BRDF> reflectionModel(void);

        /// Set how many reflections the object can have at maximum (must be less than 10)
        void setReflectionCountMax(unsigned short value);

        /// Set the reflection coefficient, must be between 0 and 1
        void setReflectionCoeff(double coeff);

        /// Set the refraction coefficient, must be bigger than 1 to enable refraction
        void setRefractionCoeff(double coeff);

    private:
        std::shared_ptr<BRDF>  _bRDF;
        std::shared_ptr<Scene> _scene;
        double                 _reflectionCoeff    = 0.0;
        double                 _refractionCoeff    = 0.0;
        unsigned short         _reflectionCountMax = 1;
        unsigned short         _material           = 0;

    };  // class Shader

}  // namespace LCNS
