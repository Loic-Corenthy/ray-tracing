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

Shader::Shader(BRDF* pBRDF, double pReflectionCoeff, double pRefractionCoeff, Scene* pScene, unsigned short pMaterial)
:_bRDF(pBRDF),
 _reflectionCountMax(1),
 _reflectionCoeff(pReflectionCoeff),
 _currentReflectionCoeff(pReflectionCoeff),
 _refractionCoeff(pRefractionCoeff),
 _material(pMaterial),
 _scene(pScene)
{
    assert(pRefractionCoeff >= 1 && "Refraction coefficient must be bigger than 1");
}

Shader::Shader(const Shader & pShader)
{
	_bRDF = pShader._bRDF;
    _reflectionCoeff = pShader._reflectionCoeff;
    _currentReflectionCoeff = pShader._currentReflectionCoeff;
	_refractionCoeff = pShader._refractionCoeff;
	_material = pShader._material;
	_scene = pShader._scene;
}

Shader Shader::operator=(const Shader & pShader)
{
    if(this == &pShader)
        return *this;

    _bRDF = pShader._bRDF;
    _reflectionCountMax = pShader._reflectionCountMax;
	_reflectionCoeff = pShader._reflectionCoeff;
    _currentReflectionCoeff = pShader._currentReflectionCoeff;
	_refractionCoeff = pShader._refractionCoeff;
	_material = pShader._material;
	_scene = pShader._scene;

    return *this;
}

Shader::~Shader(void)
{
}

Color Shader::color(const Vector & pVecToViewer, const Vector & pNormal, const Point & pPoint, Renderable* pThis, unsigned int pReflectionCount)
{
    Color lMyColor(0.0f);

    if (pReflectionCount>0)
    {
//        _currentReflectionCoeff = pow(_reflectionCoeff,pReflectionCount);
        _currentReflectionCoeff = _reflectionCoeff/static_cast<double>(pReflectionCount*pReflectionCount);
//        _currentReflectionCoeff = _reflectionCoeff/static_cast<double>(pReflectionCount);
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
                lLightIntensity = (*lIt)->intensityAt(pPoint,*_scene,pThis);

                if (!(lLightIntensity == Color(0.0f)))
                {
                    // Calculate diffuse component
                    lMyColor += lLightIntensity*_bRDF->diffuse((*lIt)->directionFrom(pPoint),pNormal,pPoint);//*_currentReflectionCoeff;

                    // Add turbulance noise to diffuse component
                    for (double lLevel=1.0f; lLevel<10.0f; lLevel += 1.0f)
                        lNoiseCoeff += (1.0f/lLevel)*fabs(lNoise.perlinNoise(lLevel*pPoint.x(), lLevel*pPoint.y(), lLevel*pPoint.z()));

                    lMyColor *= lNoiseCoeff;

                    // Add specular compoment
                    lMyColor += lLightIntensity*_bRDF->specular((*lIt)->directionFrom(pPoint),pVecToViewer,pNormal,pPoint);//*_currentReflectionCoeff;
                }

                lIt++;
            }
            break;

        case TURBULANCE:
            while( lIt != lEnd )
            {
                lLightIntensity = (*lIt)->intensityAt(pPoint,*_scene,pThis);

                if (!(lLightIntensity == Color(0.0f)))
                {
                    // Calculate diffuse component
                    lMyColor += lLightIntensity*_bRDF->diffuse((*lIt)->directionFrom(pPoint),pNormal,pPoint);//*_currentReflectionCoeff;

                    // Add turbulance noise to diffuse component
                    for (double lLevel=1.0f; lLevel<10.0f; lLevel += 1.0f)
                        lNoiseCoeff += (1.0f/lLevel)*fabs(lNoise.perlinNoise(lLevel*pPoint.x(), lLevel*pPoint.y(), lLevel*pPoint.z()));

                    lNoiseCoeff = 0.5f * sin( (pPoint.x() + pPoint.y()) + lNoiseCoeff) + 0.5f;

                    lMyColor *= lNoiseCoeff;

                    // Add specular compoment
                    lMyColor += lLightIntensity*_bRDF->specular((*lIt)->directionFrom(pPoint),pVecToViewer,pNormal,pPoint);//*_currentReflectionCoeff;
                }

                lIt++;
            }
            break;

        case BUMP:
            while( lIt != lEnd )
            {
                lLightIntensity = (*lIt)->intensityAt(pPoint,*_scene,pThis);

                if (!(lLightIntensity == Color(0.0f)))
                {
                    double lNoiseX = lNoise.perlinNoise(pPoint.x(), pPoint.y(), pPoint.z());
                    double lNoiseY = lNoise.perlinNoise(pPoint.y(), pPoint.z(), pPoint.x());
                    double lNoiseZ = lNoise.perlinNoise(pPoint.z(), pPoint.x(), pPoint.y());

                    Vector lBumpNormal(pNormal.x()*lNoiseX, pNormal.y()*lNoiseY, pNormal.z()*lNoiseZ);

                    lBumpNormal.normalize();

                    // Calculate diffuse component
                    lMyColor += lLightIntensity*_bRDF->diffuse((*lIt)->directionFrom(pPoint),lBumpNormal,pPoint);//*_currentReflectionCoeff;

                    // Add turbulance noise to diffuse component
                    for (double lLevel=1.0f; lLevel<10.0f; lLevel += 1.0f)
                        lNoiseCoeff += (1.0f/lLevel)*fabs(lNoise.perlinNoise(lLevel*pPoint.x(), lLevel*pPoint.y(), lLevel*pPoint.z()));

                    // Add specular compoment
                    lMyColor += lLightIntensity*_bRDF->specular((*lIt)->directionFrom(pPoint),pVecToViewer,lBumpNormal,pPoint);//*_currentReflectionCoeff;
                }

                lIt++;
            }

        case NONE:
        default:
            while( lIt != lEnd )
            {
                lLightIntensity = (*lIt)->intensityAt(pPoint,*_scene,pThis);

                if (!(lLightIntensity == Color(0.0f)))
                    lMyColor += lLightIntensity*_bRDF->reflectance((*lIt)->directionFrom(pPoint),pVecToViewer,pNormal,pPoint);//*_currentReflectionCoeff;

                lIt++;
            }
            break;
    }

    return (lMyColor*_currentReflectionCoeff);

}

Color Shader::ambientColor(const Ray & pRay) const
{
    if(_bRDF->ambient() == Color(0.0))
        return Color(0.0f);
    else if (_bRDF->cubeMap())
        return const_cast<CubeMap*>(_bRDF->cubeMap())->colorAt(pRay);
    else
        return _bRDF->ambient();
}

