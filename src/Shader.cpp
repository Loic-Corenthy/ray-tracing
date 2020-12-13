//===============================================================================================//
/*!
 *  \file      Shader.cpp
 *  \author    Loïc Corenthy
 *  \version   1.0
 *  \date      14/10/2012
 *  \copyright (c) 2012 Loïc Corenthy. All rights reserved.
 */
//===============================================================================================//

#include "Shader.hpp"

#include <list>
#include <iostream>
#include <cmath>
#include <memory>

#include "Color.hpp"
#include "Scene.hpp"
#include "Light.hpp"
#include "Phong.hpp"
#include "Renderable.hpp"
#include "Noise.hpp"
#include "CubeMap.hpp"

using std::shared_ptr;

using LCNS::BRDF;
using LCNS::Color;
using LCNS::Scene;
using LCNS::Shader;

Shader::Shader(shared_ptr<BRDF> bRDF, double reflectionCoeff, double refractionCoeff, shared_ptr<Scene> scene, unsigned short material)
: _bRDF(bRDF)
, _scene(scene)
, _reflectionCoeff(reflectionCoeff)
, _currentReflectionCoeff(reflectionCoeff)
, _refractionCoeff(refractionCoeff)
, _material(material)
{
    assert(refractionCoeff >= 1 && "Refraction coefficient must be bigger than 1");
}

Shader::Shader(const Shader& shader)
{
    _bRDF                   = shader._bRDF;
    _reflectionCoeff        = shader._reflectionCoeff;
    _currentReflectionCoeff = shader._currentReflectionCoeff;
    _refractionCoeff        = shader._refractionCoeff;
    _material               = shader._material;
    _scene                  = shader._scene;
}

Shader Shader::operator=(const Shader& shader)
{
    if (this == &shader)
        return *this;

    _bRDF                   = shader._bRDF;
    _reflectionCountMax     = shader._reflectionCountMax;
    _reflectionCoeff        = shader._reflectionCoeff;
    _currentReflectionCoeff = shader._currentReflectionCoeff;
    _refractionCoeff        = shader._refractionCoeff;
    _material               = shader._material;
    _scene                  = shader._scene;

    return *this;
}

Shader::~Shader(void)
{
}

shared_ptr<Scene> Shader::ptrOnScene(void)
{
    return _scene;
}

unsigned short Shader::reflectionCountMax(void) const
{
    return _reflectionCountMax;
}

double Shader::reflectionCoeff(void) const
{
    return _reflectionCoeff;
}

double Shader::refractionCoeff(void) const
{
    return _refractionCoeff;
}

shared_ptr<BRDF> Shader::reflectionModel(void)
{
    return _bRDF;
}

void Shader::setReflectionCountMax(unsigned short value)
{
    assert(value < 11 && "reflection count max out of range");
    _reflectionCountMax = value;
}

void Shader::setReflectionCoeff(double coeff)
{
    _reflectionCoeff = coeff;
}

void Shader::setRefractionCoeff(double coeff)
{
    assert(coeff >= 1 && "Refraction coefficient must be bigger than 1");
    _refractionCoeff = coeff;
}

Color Shader::color(
const Vector& vecToViewer, const Vector& normal, const Point& point, shared_ptr<Renderable> thisShader, unsigned int reflectionCount)
{
    Color myColor(0.0);

    if (reflectionCount > 0)
    {
        _currentReflectionCoeff = _reflectionCoeff / static_cast<double>(reflectionCount * reflectionCount);
    }
    else
        _currentReflectionCoeff = 1.0;

    auto it  = _scene->lightList().begin();
    auto end = _scene->lightList().end();

    Color  lightIntensity(0.0);
    double noiseCoeff = 0.0;
    Noise  noise;

    switch (_material)
    {
        case MARBLE:
            while (it != end)
            {
                lightIntensity = (*it)->intensityAt(point, *_scene, thisShader);

                if (!(lightIntensity == Color(0.0f)))
                {
                    // Calculate diffuse component
                    myColor += lightIntensity * _bRDF->diffuse((*it)->directionFrom(point), normal, point);  //*_currentReflectionCoeff;

                    // Add turbulance noise to diffuse component
                    for (double level = 1.0f; level < 10.0f; level += 1.0f)
                        noiseCoeff += (1.0f / level) * fabs(noise.perlinNoise(level * point.x(), level * point.y(), level * point.z()));

                    myColor *= noiseCoeff;

                    // Add specular compoment
                    myColor += lightIntensity * _bRDF->specular((*it)->directionFrom(point), vecToViewer, normal, point);  //*_currentReflectionCoeff;
                }

                it++;
            }
            break;

        case TURBULANCE:
            while (it != end)
            {
                lightIntensity = (*it)->intensityAt(point, *_scene, thisShader);

                if (!(lightIntensity == Color(0.0f)))
                {
                    // Calculate diffuse component
                    myColor += lightIntensity * _bRDF->diffuse((*it)->directionFrom(point), normal, point);  //*_currentReflectionCoeff;

                    // Add turbulance noise to diffuse component
                    for (double level = 1.0f; level < 10.0f; level += 1.0f)
                        noiseCoeff += (1.0f / level) * fabs(noise.perlinNoise(level * point.x(), level * point.y(), level * point.z()));

                    noiseCoeff = 0.5f * sin((point.x() + point.y()) + noiseCoeff) + 0.5f;

                    myColor *= noiseCoeff;

                    // Add specular compoment
                    myColor += lightIntensity * _bRDF->specular((*it)->directionFrom(point), vecToViewer, normal, point);  //*_currentReflectionCoeff;
                }

                it++;
            }
            break;

        case BUMP:
            while (it != end)
            {
                lightIntensity = (*it)->intensityAt(point, *_scene, thisShader);

                if (!(lightIntensity == Color(0.0f)))
                {
                    double noiseX = noise.perlinNoise(point.x(), point.y(), point.z());
                    double noiseY = noise.perlinNoise(point.y(), point.z(), point.x());
                    double noiseZ = noise.perlinNoise(point.z(), point.x(), point.y());

                    Vector bumpNormal(normal.x() * noiseX, normal.y() * noiseY, normal.z() * noiseZ);

                    bumpNormal.normalize();

                    // Calculate diffuse component
                    myColor += lightIntensity * _bRDF->diffuse((*it)->directionFrom(point), bumpNormal, point);  //*_currentReflectionCoeff;

                    // Add turbulance noise to diffuse component
                    for (double level = 1.0f; level < 10.0f; level += 1.0f)
                        noiseCoeff += (1.0f / level) * fabs(noise.perlinNoise(level * point.x(), level * point.y(), level * point.z()));

                    // Add specular compoment
                    myColor
                    += lightIntensity * _bRDF->specular((*it)->directionFrom(point), vecToViewer, bumpNormal, point);  //*_currentReflectionCoeff;
                }

                it++;
            }

        case NONE:
        default:
            while (it != end)
            {
                lightIntensity = (*it)->intensityAt(point, *_scene, thisShader);

                if (!(lightIntensity == Color(0.0f)))
                    myColor
                    += lightIntensity * _bRDF->reflectance((*it)->directionFrom(point), vecToViewer, normal, point);  //*_currentReflectionCoeff;

                it++;
            }
            break;
    }

    return (myColor * _currentReflectionCoeff);
}

Color Shader::ambientColor(const Ray& ray) const
{
    if (_bRDF->ambient() == Color(0.0))
        return Color(0.0f);
    else if (_bRDF->cubeMap())
        return _bRDF->cubeMap()->colorAt(ray);
    else
        return _bRDF->ambient();
}
