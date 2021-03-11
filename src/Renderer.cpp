//===============================================================================================//
/*!
 *  \file      Renderer.cpp
 *  \author    Loïc Corenthy
 *  \version   1.1
 *  \date      14/10/2012
 *  \copyright (c) 2012 Loïc Corenthy. All rights reserved.
 */
//===============================================================================================//

#include "Renderer.hpp"

#include <iostream>
#include <cmath>
#include <memory>
#include <stdexcept>
#include <thread>
#include <vector>
#include <chrono>

#include "Buffer.hpp"
#include "Scene.hpp"
#include "Vector.hpp"
#include "Point.hpp"
#include "Ray.hpp"
#include "Renderable.hpp"
#include "Shader.hpp"
#include "Phong.hpp"
#include "Noise.hpp"

using std::ceil;
using std::cerr;
using std::cout;
using std::endl;
using std::make_tuple;
using std::runtime_error;
using std::shared_ptr;
using std::string;
using std::thread;
using std::tuple;
using std::vector;
using std::chrono::duration;
using std::chrono::duration_cast;
using std::chrono::milliseconds;
using std::chrono::steady_clock;

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
{
}

Renderer::Renderer(Scene* scene, unsigned int width, unsigned int height)
: _scene(scene)
, _buffer(height, width)
{
}

void Renderer::_renderInternal(unsigned int bufferI, unsigned int bufferJ, const Color& meanLight)
{
    const auto& camera = _scene->cameraList().front();

    // It's possible to use only one camera (front())
    Vector rayDirection = camera->pixelDirection(bufferI, bufferJ, _buffer);
    Point  rayOrigin    = camera->position();

    // Calculate current focal point
    Ray firstRay(rayOrigin, rayDirection);
    camera->focalPlane().intersect(firstRay);
    Point focalPt = firstRay.intersection();

    // Accumulation of the secondary buffer color
    Color        apertureColor(0.0f);
    const double apertureRadius = camera->apertureRadius();
    const double apertureStep   = camera->apertureStep();

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
                Color          reflectionColor(0.0f);
                unsigned short reflectionCount = 1u;
                while (reflectionCount < objectMaxReflection && ray.intersected() != nullptr)
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
                        reflectionColor += reflection.intersected()->color(reflection, reflectionCount);  //*specular;
                    else
                        reflectionColor
                        += _scene->backgroundColor(reflection) * (1.0 / static_cast<double>((reflectionCount + 1) * (reflectionCount + 1)));

                    ray = reflection;
                    reflectionCount++;
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
        }
    }

    // Tone mapping
    Color colorAfterToneMapping;
    colorAfterToneMapping.red(1.0 - exp2(apertureColor.red() * (-1.0)));
    colorAfterToneMapping.green(1.0 - exp2(apertureColor.green() * (-1.0)));
    colorAfterToneMapping.blue(1.0 - exp2(apertureColor.blue() * (-1.0)));

    _buffer.pixel(bufferI, bufferJ, colorAfterToneMapping);
}

void Renderer::_renderMultiSamplingInternal(unsigned int bufferI, unsigned int bufferJ, const Color& meanLight)
{
    const auto& camera = _scene->cameraList().front();

    float ii = static_cast<float>(bufferI);
    float jj = static_cast<float>(bufferJ);

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
                Color          reflectionColor(0.0f);
                unsigned short reflectionCount = 1u;
                while (reflectionCount < objectMaxReflection && ray.intersected() != nullptr)  //(c++11)
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
                        reflectionColor += reflection.intersected()->color(reflection, reflectionCount);  //*specular;
                    else
                        reflectionColor
                        += _scene->backgroundColor(reflection) * (1.0 / static_cast<double>((reflectionCount + 1) * (reflectionCount + 1)));

                    ray = reflection;
                    reflectionCount++;
                }


                // Final color equals the sum of all the components
                Color finalColor(ambientColor + diffusionColor + reflectionColor + refractionColor);

                // Tone mapping
                Color colorAfterToneMapping;
                colorAfterToneMapping.red(1.0 - exp2(finalColor.red() * (-1.0)));
                colorAfterToneMapping.green(1.0 - exp2(finalColor.green() * (-1.0)));
                colorAfterToneMapping.blue(1.0 - exp2(finalColor.blue() * (-1.0)));

                superSampling += colorAfterToneMapping * contribution;
            }
            else
            {
                superSampling += _scene->backgroundColor(ray) * contribution;
            }
        }
    }

    _buffer.pixel(bufferI, bufferJ, superSampling);
}

void Renderer::_render(void)
{
    const auto renderStarts = steady_clock::now();

    auto&      camera         = _scene->cameraList().front();
    const auto processorCount = thread::hardware_concurrency();

    if (camera->aperture() == Camera::Aperture::F_SMALL || camera->aperture() == Camera::Aperture::F_MEDIUM
        || camera->aperture() == Camera::Aperture::F_BIG)
    {
        Color meanLight = _scene->meanAmbiantLight();


        if (_multiThreaded && processorCount > 1)
        {
            cout << "Multi threading on. Processor count: " << processorCount << endl;

            for (unsigned int i = 0, bufferWidth = _buffer.width(); i < bufferWidth; i++)
            {
                for (unsigned int j = 0, bufferHeight = _buffer.height(); j < bufferHeight; /* j is incremented below */)
                {
                    vector<thread> allThreads;
                    allThreads.reserve(processorCount);

                    const auto threadToCreateCount = (processorCount < (bufferHeight - j)) ? processorCount : bufferHeight - j;

                    for (unsigned int threadNumber = 0; threadNumber < threadToCreateCount; ++threadNumber)
                    {
                        allThreads.push_back(thread(&Renderer::_renderInternal, this, i, j, meanLight));

                        // Each thread take care of a pixel in the current row
                        ++j;
                    }

                    for (auto& t : allThreads)
                    {
                        if (t.joinable())
                        {
                            t.join();
                        }
                    }
                }

                // Display progress in the console
                _displayProgressBar(static_cast<double>(i) / static_cast<double>(bufferWidth));
            }
        }
        else  // no multithreading
        {
            cout << "Single thread rendering" << endl;

            for (unsigned int i = 0, bufferWidth = _buffer.width(); i < bufferWidth; i++)
            {
                for (unsigned int j = 0, bufferHeight = _buffer.height(); j < bufferHeight; ++j)
                {
                    _renderInternal(i, j, meanLight);
                }

                // Display progress in the console
                _displayProgressBar(static_cast<double>(i) / static_cast<double>(bufferWidth));
            }
        }

        // Display a message when the render is finished
        cout << "\nDone =)\n";
    }
    else if (_superSampling)
    {
        Color meanLight = _scene->meanAmbiantLight();

        if (_multiThreaded && processorCount > 1)
        {
            cout << "Multi threading on. Processor count: " << processorCount << endl;

            for (unsigned int i = 0, bufferWidth = _buffer.width(); i < bufferWidth; i++)
            {
                for (unsigned int j = 0, bufferHeight = _buffer.height(); j < bufferHeight; /* j is incremented below */)
                {
                    vector<thread> allThreads;
                    allThreads.reserve(processorCount);

                    const auto threadToCreateCount = (processorCount < (bufferHeight - j)) ? processorCount : bufferHeight - j;

                    for (unsigned int threadNumber = 0; threadNumber < threadToCreateCount; ++threadNumber)
                    {
                        allThreads.push_back(thread(&Renderer::_renderMultiSamplingInternal, this, i, j, meanLight));

                        // Each thread take care of a pixel in the current row
                        ++j;
                    }

                    for (auto& t : allThreads)
                    {
                        if (t.joinable())
                        {
                            t.join();
                        }
                    }
                }
                // Display progress in the console
                _displayProgressBar(static_cast<double>(i) / static_cast<double>(bufferWidth));
            }
        }
        else
        {
            cout << "Single thread rendering" << endl;

            for (unsigned int i = 0, bufferWidth = _buffer.width(); i < bufferWidth; i++)
            {
                for (unsigned int j = 0, bufferHeight = _buffer.height(); j < bufferHeight; ++j)
                {
                    _renderMultiSamplingInternal(i, j, meanLight);
                }

                // Display progress in the console
                _displayProgressBar(static_cast<double>(i) / static_cast<double>(bufferWidth));
            }
        }


        // Display a message when the render is finished
        cout << "\nDone =)\n";
    }
    else
    {
        Color meanLight = _scene->meanAmbiantLight();

        if (_multiThreaded && processorCount > 1)
        {
            cout << "New Multi threading on. Processor count: " << processorCount << endl;

            const unsigned int allPixelsCount = _buffer.width() * _buffer.height();
            const auto         batchSize = static_cast<unsigned int>(ceil(static_cast<double>(allPixelsCount) / static_cast<double>(processorCount)));

            vector<thread> allThreads;
            allThreads.reserve(processorCount);

            for (unsigned int i = 0; i < allPixelsCount; i += batchSize)
            {
                allThreads.push_back(thread(&Renderer::_renderNoApertureInternal, this, i, i + batchSize, meanLight));
            }

            cout << "active threads " << allThreads.size() << '\n';
            for (auto& t : allThreads)
            {
                if (t.joinable())
                {
                    t.join();
                }
            }
        }
        else
        {
            cout << "Single thread rendering" << endl;
            _renderNoApertureInternal(0, _buffer.width() * _buffer.height(), meanLight);
        }

        // Display a message when the render is finished
        cout << "\nDone =)\n";
    }

    if (_shouldDisplayRenderTime)
    {
        const auto             renderFinished = steady_clock::now();
        const duration<double> renderDuration = renderFinished - renderStarts;
        cout << "Render time " << renderDuration.count() << " seconds\n";
    }
}

void Renderer::_renderNoApertureInternal(unsigned int startIndex, unsigned int endIndex, const Color& meanLight)
{
    const auto& camera = _scene->cameraList().front();

    for (unsigned int i = startIndex; i < endIndex; ++i)
    {
        const auto [bufferI, bufferJ] = _2DFrom1D(i, _buffer.width());

        // It's possible to use only one camera (front())
        const Vector rayDirection = camera->pixelDirection(bufferI, bufferJ, _buffer);
        const Point  rayOrigin    = camera->position();
        Ray          ray(rayOrigin, rayDirection);

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
            Color          reflectionColor(0.0f);
            unsigned short reflectionCount = 1;
            while (reflectionCount < objectMaxReflection && ray.intersected() != nullptr)
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
                {
                    reflectionColor += reflection.intersected()->color(reflection, reflectionCount);  //*specular;
                }
                else
                {
                    reflectionColor
                    += _scene->backgroundColor(reflection) * (1.0 / static_cast<double>((reflectionCount + 1) * (reflectionCount + 1)));
                }

                ray = reflection;
                reflectionCount++;
            }


            // Final color equals the sum of all the components
            Color finalColor(ambientColor + diffusionColor + reflectionColor + refractionColor);

            // Tone mapping
            Color colorAfterToneMapping;
            colorAfterToneMapping.red(1.0 - exp2(finalColor.red() * (-1.0)));
            colorAfterToneMapping.green(1.0 - exp2(finalColor.green() * (-1.0)));
            colorAfterToneMapping.blue(1.0 - exp2(finalColor.blue() * (-1.0)));

            _buffer.pixel(bufferI, bufferJ, colorAfterToneMapping);
        }
        else
        {
            _buffer.pixel(bufferI, bufferJ, _scene->backgroundColor(ray));
        }
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

bool Renderer::isMultiThreadingActive(void)
{
    return _instance()._isMultiThreadingActive();
}

bool Renderer::_isMultiThreadingActive(void) const
{
    return _multiThreaded;
}

void Renderer::setMultiThreading(bool activate)
{
    _instance()._setMultiThreading(activate);
}

void Renderer::displayRenderTime(bool activate)
{
    _instance()._displayRenderTime(activate);
}

void Renderer::_setMultiThreading(bool activate)
{
    _multiThreaded = activate;
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

void Renderer::_displayRenderTime(bool activate)
{
    _shouldDisplayRenderTime = activate;
}

tuple<unsigned int, unsigned int> Renderer::_2DFrom1D(unsigned int position, unsigned int width) const
{
    const auto i = position / width;
    const auto j = position - i * width;

    return make_tuple(j, i);
}
