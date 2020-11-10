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
        Phong(const Color & pDiffusionColor, const Color &  pSpecularColor, int pExponent);

        /// Copy constructor
        Phong(const Phong & pPhong);

        /// Copy operator
        Phong operator=(const Phong & pPhong);

        /// Destructor
        ~Phong(void);

        /// Set the diffusion color coefficient
        void setDiffusionColor(const Color & pDiffusionColor);

        /// Set the specular color coefficient
        void setSpecularColor(const Color & pSpecularColor);

        /// Set the exponent
        void setExponent(int pExponent);

        /// Get the DiffusionColor coefficient
        Color diffusionColor(void) const;

        /// Get the SpecularColor coefficient
        Color specularColor(void) const;

        /// Get the exponent
        int exponent(void) const;

        /// Implementation of virtual method from BRDF
        Color reflectance(const Vector & pVecToLight, const Vector & pVecToViewer,const Vector & pNormal,const Point & pIntersection);

        /// Implementation of virtual method from BRDF
        Color diffuse(const Vector & pVecToLight, const Vector & pNormal,const Point & pIntersection) const final;

        /// Implementation of virtual method from BRDF
        Color specular(const Vector & pVecToLight, const Vector & pVecToViewer,const Vector & pNormal,const Point & pIntersection) const final;

    private:
        Color _diffusionColor;
        Color _specularColor;
        int _exponent;

    }; // class Phong

    inline void Phong::setDiffusionColor(const Color & pDiffusionColor)
    {
        _diffusionColor = pDiffusionColor;
    }

    inline void Phong::setSpecularColor(const Color &  pSpecularColor)
    {
        _specularColor = pSpecularColor;
    }

    inline void Phong::setExponent(int pExponent)
    {
        _exponent = pExponent;
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

} // namespace MatouMalin

#endif