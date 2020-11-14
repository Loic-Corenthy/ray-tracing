#ifndef RAYTRACING_PHONG_H
#define RAYTRACING_PHONG_H

// Local includes
#include "BRDF.hpp"
#include "Color.hpp"

namespace MatouMalin
{
    class Phong : public BRDF
    {
    public:
        /// Default constructor
        Phong(void);

        /// Constructor with parameters
        Phong(const Color& diffusionColor, const Color& specularColor, int exponent);

        /// Copy constructor
        Phong(const Phong& phong);

        /// Copy operator
        Phong operator=(const Phong& phong);

        /// Destructor
        ~Phong(void);

        /// Set the diffusion color coefficient
        void setDiffusionColor(const Color& diffusionColor);

        /// Set the specular color coefficient
        void setSpecularColor(const Color& specularColor);

        /// Set the exponent
        void setExponent(int exponent);

        /// Get the DiffusionColor coefficient
        Color diffusionColor(void) const;

        /// Get the SpecularColor coefficient
        Color specularColor(void) const;

        /// Get the exponent
        int exponent(void) const;

        /// Implementation of virtual method from BRDF
        Color reflectance(const Vector& vecToLight, const Vector& vecToViewer, const Vector& normal, const Point& intersection);

        /// Implementation of virtual method from BRDF
        Color diffuse(const Vector& vecToLight, const Vector& normal, const Point& intersection) const final;

        /// Implementation of virtual method from BRDF
        Color specular(const Vector& vecToLight, const Vector& vecToViewer, const Vector& normal, const Point& intersection) const final;

    private:
        Color _diffusionColor;
        Color _specularColor;
        int   _exponent;

    };  // class Phong

    inline void Phong::setDiffusionColor(const Color& diffusionColor)
    {
        _diffusionColor = diffusionColor;
    }

    inline void Phong::setSpecularColor(const Color& specularColor)
    {
        _specularColor = specularColor;
    }

    inline void Phong::setExponent(int exponent)
    {
        _exponent = exponent;
    }

    inline Color Phong::diffusionColor(void) const
    {
        return _diffusionColor;
    }

    inline Color Phong::specularColor(void) const
    {
        return _specularColor;
    }

    inline int Phong::exponent(void) const
    {
        return _exponent;
    }

}  // namespace MatouMalin

#endif