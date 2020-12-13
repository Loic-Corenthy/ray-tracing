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
#include <memory>
#include <stdexcept>

#include "Buffer.hpp"
#include "Scene.hpp"
#include "Camera.hpp"
#include "Vector.hpp"
#include "Point.hpp"
#include "Ray.hpp"
#include "Renderable.hpp"
#include "Shader.hpp"
#include "Phong.hpp"
#include "Noise.hpp"

using std::cerr;
using std::cout;
using std::endl;
using std::runtime_error;
using std::shared_ptr;
using std::string;

using LCNS::Buffer;
using LCNS::Renderer;

const Buffer& Renderer::getBuffer(void)
{
    return _instance()._buffer;
}

void Renderer::setScene(shared_ptr<Scene> scene, unsigned int width, unsigned int height)
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
: _buffer()
, _reflectionCount(0)
{
}

Renderer::Renderer(Scene* scene, int width, int height)
: _scene(scene)
, _buffer(height, width)
, _reflectionCount(1)
{
}

void Renderer::_render(void)
{
    auto& camera = _scene->cameraList().front();

    if (camera->aperture() == Camera::Aperture::F_SMALL || camera->aperture() == Camera::Aperture::F_MEDIUM
        || camera->aperture() == Camera::Aperture::F_BIG)
    {
        Color meanLight = _scene->meanAmbiantLight();

        for (unsigned int i = 0, bufferWidth = _buffer.width(); i < bufferWidth; i++)
        {
            for (unsigned int j = 0, bufferHeight = _buffer.height(); j < bufferHeight; j++)
            {
                // It's possible to use only one camera (front())
                Vector rayDirection = camera->pixelDirection(i, j, _buffer);
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
                                auto checkRefractionRay = ray.intersected()->refractedRay(ray);

                                if (checkRefractionRay)
                                {
                                    auto refractionRay = checkRefractionRay.value();

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
                                reflection.origin(ray.intersection());

                                Vector incidentDirection(ray.direction());
                                Vector normal(ray.intersected()->normal(ray.intersection()));
                                double reflet              = (incidentDirection * normal) * (2.0);
                                Vector reflectionDirection = incidentDirection - normal * reflet;

                                reflection.direction(reflectionDirection);
                                reflection.intersected(ray.intersected());


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
                colorAfterToneMapping.red(1.0f - exp2f(apertureColor.red() * (-1.0f)));
                colorAfterToneMapping.green(1.0f - exp2f(apertureColor.green() * (-1.0f)));
                colorAfterToneMapping.blue(1.0f - exp2f(apertureColor.blue() * (-1.0f)));

                _buffer.pixel(i, j, colorAfterToneMapping);
            }
            // Display progress in the console
            _displayProgressBar(static_cast<double>(i) / static_cast<double>(bufferWidth));
        }
        // Display a message when the render is finished
        cout << "\nDone =)\n";
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
                        Vector rayDirection = camera->pixelDirection(fragmentX, fragmentY, _buffer);
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
                                auto checkRefractionRay = ray.intersected()->refractedRay(ray);

                                if (checkRefractionRay)
                                {
                                    auto refractionRay = checkRefractionRay.value();

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
                                reflection.origin(ray.intersection());

                                const Vector incidentDirection(ray.direction());
                                const Vector normal(ray.intersected()->normal(ray.intersection()));
                                const double reflet              = (incidentDirection * normal) * 2.0;
                                const Vector reflectionDirection = incidentDirection - normal * reflet;

                                reflection.direction(reflectionDirection);
                                reflection.intersected(ray.intersected());

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
                            colorAfterToneMapping.red(1.0f - exp2f(finalColor.red() * (-1.0f)));
                            colorAfterToneMapping.green(1.0f - exp2f(finalColor.green() * (-1.0f)));
                            colorAfterToneMapping.blue(1.0f - exp2f(finalColor.blue() * (-1.0f)));

                            superSampling += colorAfterToneMapping * contribution;
                        }
                        else
                            superSampling += _scene->backgroundColor(ray) * contribution;

                        _reflectionCount = 1;
                    }
                }

                _buffer.pixel(i, j, superSampling);
            }
            // Display progress in the console
            _displayProgressBar(static_cast<double>(i) / static_cast<double>(bufferWidth));
        }
        // Display a message when the render is finished
        cout << "\nDone =)\n";
    }
    else
    {
        Color meanLight = _scene->meanAmbiantLight();

        for (unsigned int j = 0, bufferHeight = _buffer.height(); j < bufferHeight; ++j)
        {
            for (unsigned int i = 0, bufferWidth = _buffer.width(); i < bufferWidth; ++i)
            {
                // It's possible to use only one camera (front())
                Vector rayDirection = camera->pixelDirection(i, j, _buffer);
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
                        auto checkRefractionRay = ray.intersected()->refractedRay(ray);

                        if (checkRefractionRay)
                        {
                            auto refractionRay = checkRefractionRay.value();

                            if (_scene->intersect(refractionRay))
                                refractionColor = refractionRay.intersected()->color(refractionRay, 0);
                            else
                                refractionColor = _scene->backgroundColor(refractionRay);
                        }
                    }

                    // Reflections color
                    Color reflectionColor(0.0f);
                    while (_reflectionCount < objectMaxReflection && ray.intersected() != nullptr)
                    {
                        // Calculate reflected ray
                        Ray reflection;
                        reflection.origin(ray.intersection());

                        const Vector incidentDirection(ray.direction());
                        const Vector normal(ray.intersected()->normal(ray.intersection()));
                        const double reflet              = (incidentDirection * normal) * (2.0);
                        const Vector reflectionDirection = incidentDirection - normal * reflet;

                        reflection.direction(reflectionDirection);
                        reflection.intersected(ray.intersected());

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
                    colorAfterToneMapping.red(1.0f - exp2f(finalColor.red() * (-1.0f)));
                    colorAfterToneMapping.green(1.0f - exp2f(finalColor.green() * (-1.0f)));
                    colorAfterToneMapping.blue(1.0f - exp2f(finalColor.blue() * (-1.0f)));

                    _buffer.pixel(i, j, colorAfterToneMapping);
                }
                else
                {
                    _buffer.pixel(i, j, _scene->backgroundColor(ray));
                }
                _reflectionCount = 1;
            }
            // Display progress in the console
            _displayProgressBar(static_cast<double>(j) / static_cast<double>(bufferHeight));
        }
        // Display a message when the render is finished
        cout << "\nDone =)\n";
    }
}

void Renderer::_setScene(shared_ptr<Scene> scene, unsigned int width, unsigned int height)
{
    assert(scene != nullptr && "The scene assigned to the Renderer is not valid");
    _buffer.dimensions(width, height);
    _scene = scene;
}

void Renderer::_setSuperSampling(bool activate)
{
    _superSampling = activate;
}

bool Renderer::_isSuperSamplingActive(void) const
{
    return _superSampling;
}

void Renderer::_displayProgressBar(double currentProgress)
{
    if (!(0.0 <= currentProgress && currentProgress <= 1.0))
    {
        throw runtime_error("Current progress for the progress bar must be in the range [0, 1]");
    }

    // Display 50 signs when complete, i.e.
    const int  maxSign        = 50;
    const auto signCount      = (0.99 < currentProgress) ? maxSign : static_cast<int>(currentProgress * 100.0 / 2.0);
    const auto remainingCount = maxSign - signCount;

    string progressBar("[");
    for (int i = 0; i < signCount; ++i)
    {
        progressBar.append("=");
    }

    for (int i = 0; i < remainingCount; ++i)
    {
        progressBar.append(" ");
    }

    progressBar.append("]");

    const auto displayedProgress = static_cast<int>(((0.99 < currentProgress) ? 1.0 : currentProgress) * 100.0);

    cout << progressBar << " " << displayedProgress << " % \r";
}
