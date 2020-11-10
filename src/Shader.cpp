#include "Shader.hpp"

// Standard includes
#include <list>
#include <iostream>
#include <cmath>

// Local includes
#include "Scene.hpp"
#include "Light.hpp"
#include "Phong.hpp"
#include "Renderable.hpp"
#include "Noise.hpp"
#include "CubeMap.hpp"

using namespace std;
using namespace MatouMalin;

Shader::Shader(void)
:_bRDF(nullptr), //(c++11)
 _reflectionCountMax(1),
 _reflectionCoeff(0.0f),
 _currentReflectionCoeff(0.0f),
 _refractionCoeff(0.0f),
 _material(0),
 _scene(nullptr) //(c++11)
{
}

Shader::Shader(BRDF* bRDF, double reflectionCoeff, double refractionCoeff, Scene* scene, unsigned short material)
:_bRDF(bRDF),
 _reflectionCountMax(1),
 _reflectionCoeff(reflectionCoeff),
 _currentReflectionCoeff(reflectionCoeff),
 _refractionCoeff(refractionCoeff),
 _material(material),
 _scene(scene)
{
    assert(refractionCoeff >= 1 && "Refraction coefficient must be bigger than 1");
}

Shader::Shader(const Shader & shader)
{
	_bRDF = shader._bRDF;
    _reflectionCoeff = shader._reflectionCoeff;
    _currentReflectionCoeff = shader._currentReflectionCoeff;
	_refractionCoeff = shader._refractionCoeff;
	_material = shader._material;
	_scene = shader._scene;
}

Shader Shader::operator=(const Shader & shader)
{
    if(this == &shader)
        return *this;

    _bRDF = shader._bRDF;
    _reflectionCountMax = shader._reflectionCountMax;
	_reflectionCoeff = shader._reflectionCoeff;
    _currentReflectionCoeff = shader._currentReflectionCoeff;
	_refractionCoeff = shader._refractionCoeff;
	_material = shader._material;
	_scene = shader._scene;

    return *this;
}

Shader::~Shader(void)
{
}

Color Shader::color(const Vector & vecToViewer, const Vector & normal, const Point & point, Renderable* thisShader, unsigned int reflectionCount)
{
    Color lMyColor(0.0f);

    if (reflectionCount>0)
    {
//        _currentReflectionCoeff = pow(_reflectionCoeff,reflectionCount);
        _currentReflectionCoeff = _reflectionCoeff/static_cast<double>(reflectionCount*reflectionCount);
//        _currentReflectionCoeff = _reflectionCoeff/static_cast<double>(reflectionCount);
    }
    else
        _currentReflectionCoeff = 1.0;

    auto lIt = _scene->lightList().begin(); //(c++11)
    auto lEnd = _scene->lightList().end();

    Color lLightIntensity(0.0);
    double lNoiseCoeff(0.0f);
    Noise lNoise;

    switch (_material)
    {
        case MARBLE:
            while( lIt != lEnd )
            {
                lLightIntensity = (*lIt)->intensityAt(point,*_scene,thisShader);

                if (!(lLightIntensity == Color(0.0f)))
                {
                    // Calculate diffuse component
                    lMyColor += lLightIntensity*_bRDF->diffuse((*lIt)->directionFrom(point),normal,point);//*_currentReflectionCoeff;

                    // Add turbulance noise to diffuse component
                    for (double lLevel=1.0f; lLevel<10.0f; lLevel += 1.0f)
                        lNoiseCoeff += (1.0f/lLevel)*fabs(lNoise.perlinNoise(lLevel*point.x(), lLevel*point.y(), lLevel*point.z()));

                    lMyColor *= lNoiseCoeff;

                    // Add specular compoment
                    lMyColor += lLightIntensity*_bRDF->specular((*lIt)->directionFrom(point),vecToViewer,normal,point);//*_currentReflectionCoeff;
                }

                lIt++;
            }
            break;

        case TURBULANCE:
            while( lIt != lEnd )
            {
                lLightIntensity = (*lIt)->intensityAt(point,*_scene,thisShader);

                if (!(lLightIntensity == Color(0.0f)))
                {
                    // Calculate diffuse component
                    lMyColor += lLightIntensity*_bRDF->diffuse((*lIt)->directionFrom(point),normal,point);//*_currentReflectionCoeff;

                    // Add turbulance noise to diffuse component
                    for (double lLevel=1.0f; lLevel<10.0f; lLevel += 1.0f)
                        lNoiseCoeff += (1.0f/lLevel)*fabs(lNoise.perlinNoise(lLevel*point.x(), lLevel*point.y(), lLevel*point.z()));

                    lNoiseCoeff = 0.5f * sin( (point.x() + point.y()) + lNoiseCoeff) + 0.5f;

                    lMyColor *= lNoiseCoeff;

                    // Add specular compoment
                    lMyColor += lLightIntensity*_bRDF->specular((*lIt)->directionFrom(point),vecToViewer,normal,point);//*_currentReflectionCoeff;
                }

                lIt++;
            }
            break;

        case BUMP:
            while( lIt != lEnd )
            {
                lLightIntensity = (*lIt)->intensityAt(point,*_scene,thisShader);

                if (!(lLightIntensity == Color(0.0f)))
                {
                    double lNoiseX = lNoise.perlinNoise(point.x(), point.y(), point.z());
                    double lNoiseY = lNoise.perlinNoise(point.y(), point.z(), point.x());
                    double lNoiseZ = lNoise.perlinNoise(point.z(), point.x(), point.y());

                    Vector lBumpNormal(normal.x()*lNoiseX, normal.y()*lNoiseY, normal.z()*lNoiseZ);

                    lBumpNormal.normalize();

                    // Calculate diffuse component
                    lMyColor += lLightIntensity*_bRDF->diffuse((*lIt)->directionFrom(point),lBumpNormal,point);//*_currentReflectionCoeff;

                    // Add turbulance noise to diffuse component
                    for (double lLevel=1.0f; lLevel<10.0f; lLevel += 1.0f)
                        lNoiseCoeff += (1.0f/lLevel)*fabs(lNoise.perlinNoise(lLevel*point.x(), lLevel*point.y(), lLevel*point.z()));

                    // Add specular compoment
                    lMyColor += lLightIntensity*_bRDF->specular((*lIt)->directionFrom(point),vecToViewer,lBumpNormal,point);//*_currentReflectionCoeff;
                }

                lIt++;
            }

        case NONE:
        default:
            while( lIt != lEnd )
            {
                lLightIntensity = (*lIt)->intensityAt(point,*_scene,thisShader);

                if (!(lLightIntensity == Color(0.0f)))
                    lMyColor += lLightIntensity*_bRDF->reflectance((*lIt)->directionFrom(point),vecToViewer,normal,point);//*_currentReflectionCoeff;

                lIt++;
            }
            break;
    }

    return (lMyColor*_currentReflectionCoeff);

}

Color Shader::ambientColor(const Ray & ray) const
{
    if(_bRDF->ambient() == Color(0.0))
        return Color(0.0f);
    else if (_bRDF->cubeMap())
        return const_cast<CubeMap*>(_bRDF->cubeMap())->colorAt(ray);
    else
        return _bRDF->ambient();
}

