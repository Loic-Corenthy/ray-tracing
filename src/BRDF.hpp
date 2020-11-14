#ifndef RAYTRACING_BRDF_H
#define RAYTRACING_BRDF_H

// Local includes
#include "Color.hpp"
#include "CubeMap.hpp"

namespace LCNS
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
        virtual Color reflectance(const Vector& vecToLight, const Vector& vecToViewer, const Vector& normal, const Point& intersection) = 0;

        /// Set ambient color
        void setAmbient(const Color& ambient);

        /// Get ambient color
        Color ambient(void) const;

        /// Set a pointer on a CubeMap
        void setCubeMap(CubeMap* cubeMap);

        /// Get the pointer on the associated CubeMap
        const CubeMap* cubeMap(void) const;

        /// Implement how the diffuse color is calculated
        virtual Color diffuse(const Vector& vecToLight, const Vector& normal, const Point& intersection) const = 0;

        /// Implement how the specular effect is calculated
        virtual Color specular(const Vector& vecToLight, const Vector& vecToViewer, const Vector& normal, const Point& intersection) const = 0;

    protected:
        /// Default constructor
        BRDF(void);

        /// Constructor with parameter
        BRDF(const Color& ambiant);

        /// Copy constructor
        BRDF(const BRDF& brdf);

        /// Copy operator
        void operator=(const BRDF& brdf);

    private:
        Color    _ambientColor;
        CubeMap* _cubeMap;

    };  // class BRDF

    inline void BRDF::setAmbient(const Color& ambient)
    {
        _ambientColor = ambient;
    }

    inline Color BRDF::ambient(void) const
    {
        return _ambientColor;
    }

    inline void BRDF::setCubeMap(CubeMap* cubeMap)
    {
        _cubeMap = cubeMap;
    }

    inline const CubeMap* BRDF::cubeMap(void) const
    {
        return _cubeMap;
    }


}  // namespace LCNS


#endif
