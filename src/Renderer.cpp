//===============================================================================================//
/*!
 *  \file      Renderer.cpp
 *  \author    Loïc Corenthy
 *  \version   1.0
 *  \date      14/10/2012
 *  \copyright (c) 2012 Loïc Corenthy. All rights reserved.
 */
//===============================================================================================//

#include "Renderer.hpp"

#include <iostream>
#include <cmath>

#include "Scene.hpp"
#include "Camera.hpp"
#include "Vector.hpp"
#include "Point.hpp"
#include "Ray.hpp"
#include "Renderable.hpp"
#include "Shader.hpp"
#include "Phong.hpp"
#include "Noise.hpp"

using namespace LCNS;
using namespace std;

const Buffer& Renderer::getBuffer(void)
{
    return _instance()._buffer;
}

void Renderer::setScene(Scene* scene, int width, int height)
{
    _instance()._setScene(scene, width, height);
}

void Renderer::render(void)
{
    _instance()._render();
}

bool Renderer::isSuperSamplingActive(void)
{
    return _instance()._isSuperSamplingActive();
}

void Renderer::setSuperSampling(bool activate)
{
    _instance()._setSuperSampling(activate);
}

Renderer& Renderer::_instance(void)
{
    static Renderer instance;
    return instance;
}

Renderer::Renderer(void)
: _scene(nullptr)
, _buffer()
, _reflectionCount(0)
, _superSampling(false)
{
}

Renderer::Renderer(Scene* scene, int width, int height)
: _scene(scene)
, _reflectionCount(1)
, _buffer(height, width)
, _superSampling(false)
{
}

Renderer::Renderer(const Renderer& renderer)
: _scene(renderer._scene)
, _buffer(renderer._buffer)
, _reflectionCount(renderer._reflectionCount)
, _superSampling(renderer._superSampling)
{
}

Renderer Renderer::operator=(const Renderer& renderer)
{
    if (this == &renderer)
        return *this;

    _scene           = renderer._scene;
    _buffer          = renderer._buffer;
    _reflectionCount = renderer._reflectionCount;
    _superSampling   = renderer._superSampling;

    return *this;
}

Renderer::~Renderer(void)
{
}

void Renderer::_render(void)
{
    Camera* camera = _scene->cameraList().front();

    if (camera->aperture() == Camera::F_SMALL || camera->aperture() == Camera::F_MEDIUM || camera->aperture() == Camera::F_BIG)
    {
        Color meanLight = _scene->meanAmbiantLight();

        for (unsigned int i = 0, bufferWidth = _buffer.width(); i < bufferWidth; i++)
        {
            for (unsigned int j = 0, bufferHeight = _buffer.height(); j < bufferHeight; j++)
            {
                // It's possible to use only one camera (front())
                Vector rayDirection = camera->pixelDirection(i, j, &_buffer);
                Point  rayOrigin    = camera->position();

                // Calculate current focal point
                Ray firstRay(rayOrigin, rayDirection);
                camera->focalPlane().intersect(firstRay);
                Point focalPt = firstRay.intersection();

                // Accumulation of the secondary buffer color
                Color  apertureColor(0.0f);
                double apertureRadius = camera->apertureRadius();
                double apertureStep   = camera->apertureStep();
                for (double apertureI = apertureRadius * (-1.0); apertureI <= apertureRadius; apertureI += apertureStep)
                {
                    for (double apertureJ = apertureRadius * (-1.0); apertureJ <= apertureRadius; apertureJ += apertureStep)
                    {
                        Point apertureOrigin(firstRay.origin());
                        apertureOrigin.x(apertureOrigin.x() + apertureI);
                        apertureOrigin.y(apertureOrigin.y() + apertureJ);

                        Ray ray(apertureOrigin, (focalPt - apertureOrigin));

                        if (_scene->intersect(ray))
                        {
                            // Max reflection for the current object
                            unsigned short objectMaxReflection = ray.intersected()->shader()->reflectionCountMax();

                            // Ambient color
                            Ray   ambiantRay(ray.intersection(), ray.intersected()->normal(ray.intersection()));
                            Color ambientColor = meanLight * ray.intersected()->shader()->ambientColor(ambiantRay) * 0.1f;

                            // Diffusion color
                            Color diffusionColor = ray.intersected()->color(ray, 0);

                            // Refraction color
                            Color refractionColor(0.0);
                            if (ray.intersected()->shader()->refractionCoeff() > 1.0)
                            {
                                Ray  refractionRay;
                                bool hasRefraction = ray.intersected()->refractedRay(ray, refractionRay);

                                if (hasRefraction)
                                {
                                    if (_scene->intersect(refractionRay))
                                        refractionColor = refractionRay.intersected()->color(refractionRay, 0);
                                    else
                                        refractionColor = _scene->backgroundColor(refractionRay);
                                }
                            }

                            // Reflections color
                            Color reflectionColor(0.0f);
                            while (_reflectionCount < objectMaxReflection && ray.intersected() != nullptr)  //(c++11)
                            {
                                // Calculate reflected ray
                                Ray reflection;
                                reflection.setOrigin(ray.intersection());

                                Vector incidentDirection(ray.direction());
                                Vector normal(ray.intersected()->normal(ray.intersection()));
                                double reflet              = (incidentDirection * normal) * (2.0);
                                Vector reflectionDirection = incidentDirection - normal * reflet;

                                reflection.setDirection(reflectionDirection);
                                reflection.setIntersected(ray.intersected());


                                if (_scene->intersect(reflection))
                                    reflectionColor += reflection.intersected()->color(reflection, _reflectionCount);  //*specular;
                                else
                                    reflectionColor += _scene->backgroundColor(reflection)
                                                       * (1.0 / static_cast<double>((_reflectionCount + 1) * (_reflectionCount + 1)));

                                ray = reflection;
                                _reflectionCount++;
                            }


                            // Final color equals the sum of all the components
                            Color finalColor(ambientColor + diffusionColor + reflectionColor + refractionColor);

                            apertureColor += finalColor * camera->apertureColorCoeff(apertureI, apertureJ);
                        }
                        else
                        {
                            Color tmp = _scene->backgroundColor(ray);
                            apertureColor += tmp * camera->apertureColorCoeff(apertureI, apertureJ);
                        }
                        _reflectionCount = 1;
                    }
                }

                // Tone mapping
                Color colorAfterToneMapping;
                colorAfterToneMapping.setRed(1.0f - exp2f(apertureColor.red() * (-1.0f)));
                colorAfterToneMapping.setGreen(1.0f - exp2f(apertureColor.green() * (-1.0f)));
                colorAfterToneMapping.setBlue(1.0f - exp2f(apertureColor.blue() * (-1.0f)));

                _buffer.setPixel(i, j, colorAfterToneMapping);
            }
            // Display progress in the console
            cout << "Progress: " << static_cast<float>(i) / static_cast<float>(bufferWidth) * 100.0f << " %" << endl;
        }
        // Display a message when the render is finished
        cout << "Done =)" << endl;
    }
    else if (_superSampling)
    {
        Color meanLight = _scene->meanAmbiantLight();

        for (unsigned int i = 0, bufferWidth = _buffer.width(); i < bufferWidth; i++)
        {
            for (unsigned int j = 0, bufferHeight = _buffer.height(); j < bufferHeight; j++)
            {
                float ii = static_cast<float>(i);
                float jj = static_cast<float>(j);

                Color  superSampling(0.0f);
                double contribution = 0.25;

                for (float fragmentX = ii; fragmentX < ii + 1.0f; fragmentX += 0.5f)
                {
                    for (float fragmentY = jj; fragmentY < jj + 1.0f; fragmentY += 0.5f)
                    {
                        // It's possible to use only one camera (front())
                        Vector rayDirection = camera->pixelDirection(fragmentX, fragmentY, &_buffer);
                        Point  rayOrigin    = camera->position();
                        Ray    ray(rayOrigin, rayDirection);

                        if (_scene->intersect(ray))
                        {
                            // Max reflection for the current object
                            unsigned short objectMaxReflection = ray.intersected()->shader()->reflectionCountMax();

                            // Ambient color
                            Ray   ambiantRay(ray.intersection(), ray.intersected()->normal(ray.intersection()));
                            Color ambientColor = meanLight * ray.intersected()->shader()->ambientColor(ambiantRay) * 0.1f;

                            // Diffusion color
                            Color diffusionColor = ray.intersected()->color(ray, 0);

                            // Refraction color
                            Color refractionColor(0.0);
                            if (ray.intersected()->shader()->refractionCoeff() > 1.0)
                            {
                                Ray  refractionRay;
                                bool hasRefraction = ray.intersected()->refractedRay(ray, refractionRay);

                                if (hasRefraction)
                                {
                                    if (_scene->intersect(refractionRay))
                                        refractionColor = refractionRay.intersected()->color(refractionRay, 0);
                                    else
                                        refractionColor = _scene->backgroundColor(refractionRay);
                                }
                            }

                            // Reflections Color
                            Color reflectionColor(0.0f);
                            while (_reflectionCount < objectMaxReflection && ray.intersected() != nullptr)  //(c++11)
                            {
                                // Calculate reflected ray
                                Ray reflection;
                                reflection.setOrigin(ray.intersection());

                                Vector incidentDirection(ray.direction());
                                Vector normal(ray.intersected()->normal(ray.intersection()));
                                double reflet              = (incidentDirection * normal) * (2.0);
                                Vector reflectionDirection = incidentDirection - normal * reflet;

                                reflection.setDirection(reflectionDirection);
                                reflection.setIntersected(ray.intersected());

                                if (_scene->intersect(reflection))
                                    reflectionColor += reflection.intersected()->color(reflection, _reflectionCount);  //*specular;
                                else
                                    reflectionColor += _scene->backgroundColor(reflection)
                                                       * (1.0 / static_cast<double>((_reflectionCount + 1) * (_reflectionCount + 1)));

                                ray = reflection;
                                _reflectionCount++;
                            }


                            // Final color equals the sum of all the components
                            Color finalColor(ambientColor + diffusionColor + reflectionColor + refractionColor);

                            // Tone mapping
                            Color colorAfterToneMapping;
                            colorAfterToneMapping.setRed(1.0f - exp2f(finalColor.red() * (-1.0f)));
                            colorAfterToneMapping.setGreen(1.0f - exp2f(finalColor.green() * (-1.0f)));
                            colorAfterToneMapping.setBlue(1.0f - exp2f(finalColor.blue() * (-1.0f)));

                            superSampling += colorAfterToneMapping * contribution;
                        }
                        else
                            superSampling += _scene->backgroundColor(ray) * contribution;

                        _reflectionCount = 1;
                    }
                }

                _buffer.setPixel(i, j, superSampling);
            }
            // Display progress in the console
            cout << "Progress: " << static_cast<float>(i) / static_cast<float>(bufferWidth) * 100.0f << " %" << endl;
        }
        // Display a message when the render is finished
        cout << "Done =)" << endl;
    }
    else
    {
        Color meanLight = _scene->meanAmbiantLight();

        for (unsigned int j = 0, bufferHeight = _buffer.height(); j < bufferHeight; ++j)
        {
            for (unsigned int i = 0, bufferWidth = _buffer.width(); i < bufferWidth; ++i)
            {
                // It's possible to use only one camera (front())
                Vector rayDirection = camera->pixelDirection(i, j, &_buffer);
                Point  rayOrigin    = camera->position();
                Ray    ray(rayOrigin, rayDirection);

                if (_scene->intersect(ray))
                {
                    // Max reflection for the current object
                    unsigned short objectMaxReflection = ray.intersected()->shader()->reflectionCountMax();

                    // Ambient color
                    Ray   ambiantRay(ray.intersection(), ray.intersected()->normal(ray.intersection()));
                    Color ambientColor = meanLight * ray.intersected()->shader()->ambientColor(ambiantRay) * 0.1f;

                    // Diffusion color
                    Color diffusionColor = ray.intersected()->color(ray, 0);

                    // Refraction color
                    Color refractionColor(0.0);
                    if (ray.intersected()->shader()->refractionCoeff() > 1.0)
                    {
                        Ray  refractionRay;
                        bool hasRefraction = ray.intersected()->refractedRay(ray, refractionRay);

                        if (hasRefraction)
                        {
                            if (_scene->intersect(refractionRay))
                                refractionColor = refractionRay.intersected()->color(refractionRay, 0);
                            else
                                refractionColor = _scene->backgroundColor(refractionRay);
                        }
                    }

                    // Reflections color
                    Color reflectionColor(0.0f);
                    while (_reflectionCount < objectMaxReflection && ray.intersected() != nullptr)  //(c++11)
                    {
                        // Calculate reflected ray
                        Ray reflection;
                        reflection.setOrigin(ray.intersection());

                        Vector incidentDirection(ray.direction());
                        Vector normal(ray.intersected()->normal(ray.intersection()));
                        double reflet              = (incidentDirection * normal) * (2.0);
                        Vector reflectionDirection = incidentDirection - normal * reflet;

                        reflection.setDirection(reflectionDirection);
                        reflection.setIntersected(ray.intersected());

                        if (_scene->intersect(reflection))
                            reflectionColor += reflection.intersected()->color(reflection, _reflectionCount);  //*specular;
                        else
                            reflectionColor
                            += _scene->backgroundColor(reflection) * (1.0 / static_cast<double>((_reflectionCount + 1) * (_reflectionCount + 1)));

                        ray = reflection;
                        _reflectionCount++;
                    }


                    // Final color equals the sum of all the components
                    Color finalColor(ambientColor + diffusionColor + reflectionColor + refractionColor);

                    // Tone mapping
                    Color colorAfterToneMapping;
                    colorAfterToneMapping.setRed(1.0f - exp2f(finalColor.red() * (-1.0f)));
                    colorAfterToneMapping.setGreen(1.0f - exp2f(finalColor.green() * (-1.0f)));
                    colorAfterToneMapping.setBlue(1.0f - exp2f(finalColor.blue() * (-1.0f)));

                    _buffer.setPixel(i, j, colorAfterToneMapping);
                }
                else
                {
                    _buffer.setPixel(i, j, _scene->backgroundColor(ray));
                }
                _reflectionCount = 1;
            }
            // Display progress in the console
            cout << "Progress: " << static_cast<float>(j) / static_cast<float>(bufferHeight) * 100.0f << " %" << endl;
        }
        // Display a message when the render is finished
        cout << "Done =)" << endl;
    }
}

void Renderer::_setScene(Scene* scene, int width, int height)
{
    assert(scene != nullptr && "The scene assigned to the Renderer is not valid");
    _buffer.dimensions(width, height);
    _scene = scene;
}

const Buffer& Renderer::_getBuffer(void) const
{
    return _buffer;
}

void Renderer::_setSuperSampling(bool activate)
{
    _superSampling = activate;
}

bool Renderer::_isSuperSamplingActive(void) const
{
    return _superSampling;
}
