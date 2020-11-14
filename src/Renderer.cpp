#include "Renderer.hpp"

// Standard includes
#include <iostream>
#include <cmath>

// Local includes
#include "Scene.hpp"
#include "Camera.hpp"
#include "Vector.hpp"
#include "Point.hpp"
#include "Ray.hpp"
#include "Renderable.hpp"
#include "Shader.hpp"
#include "Phong.hpp"
#include "Noise.hpp"

using namespace MatouMalin;
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
    Camera* lCamera = _scene->cameraList().front();

    if (lCamera->aperture() == Camera::F_SMALL || lCamera->aperture() == Camera::F_MEDIUM || lCamera->aperture() == Camera::F_BIG)
    {
        Color lMeanLight = _scene->meanAmbiantLight();

        for (unsigned int i = 0, lBufferWidth = _buffer.width(); i < lBufferWidth; i++)
        {
            for (unsigned int j = 0, lBufferHeight = _buffer.height(); j < lBufferHeight; j++)
            {
                // It's possible to use only one camera (front())
                Vector lRayDirection = lCamera->pixelDirection(i, j, &_buffer);
                Point  lRayOrigin    = lCamera->position();

                // Calculate current focal point
                Ray lFirstRay(lRayOrigin, lRayDirection);
                lCamera->focalPlane().intersect(lFirstRay);
                Point lFocalPt = lFirstRay.intersection();

                // Accumulation of the secondary buffer color
                Color  lApertureColor(0.0f);
                double lApertureRadius = lCamera->apertureRadius();
                double lApertureStep   = lCamera->apertureStep();
                for (double lApertureI = lApertureRadius * (-1.0); lApertureI <= lApertureRadius; lApertureI += lApertureStep)
                {
                    for (double lApertureJ = lApertureRadius * (-1.0); lApertureJ <= lApertureRadius; lApertureJ += lApertureStep)
                    {
                        Point lApertureOrigin(lFirstRay.origin());
                        lApertureOrigin.setX(lApertureOrigin.x() + lApertureI);
                        lApertureOrigin.setY(lApertureOrigin.y() + lApertureJ);

                        Ray lRay(lApertureOrigin, (lFocalPt - lApertureOrigin));

                        if (_scene->intersect(lRay))
                        {
                            // Max reflection for the current object
                            unsigned short lObjectMaxReflection = lRay.intersected()->shader()->reflectionCountMax();

                            // Ambient color
                            Ray   lAmbiantRay(lRay.intersection(), lRay.intersected()->normal(lRay.intersection()));
                            Color lAmbientColor = lMeanLight * lRay.intersected()->shader()->ambientColor(lAmbiantRay) * 0.1f;

                            // Diffusion color
                            Color lDiffusionColor = lRay.intersected()->color(lRay, 0);

                            // Refraction color
                            Color lRefractionColor(0.0);
                            if (lRay.intersected()->shader()->refractionCoeff() > 1.0)
                            {
                                Ray  lRefractionRay;
                                bool lHasRefraction = lRay.intersected()->refractedRay(lRay, lRefractionRay);

                                if (lHasRefraction)
                                {
                                    if (_scene->intersect(lRefractionRay))
                                        lRefractionColor = lRefractionRay.intersected()->color(lRefractionRay, 0);
                                    else
                                        lRefractionColor = _scene->backgroundColor(lRefractionRay);
                                }
                            }

                            // Reflections color
                            Color lReflectionColor(0.0f);
                            while (_reflectionCount < lObjectMaxReflection && lRay.intersected() != nullptr)  //(c++11)
                            {
                                // Calculate reflected ray
                                Ray lReflection;
                                lReflection.setOrigin(lRay.intersection());

                                Vector lIncidentDirection(lRay.direction());
                                Vector lNormal(lRay.intersected()->normal(lRay.intersection()));
                                double lReflet              = (lIncidentDirection * lNormal) * (2.0);
                                Vector lReflectionDirection = lIncidentDirection - lNormal * lReflet;

                                lReflection.setDirection(lReflectionDirection);
                                lReflection.setIntersected(lRay.intersected());


                                if (_scene->intersect(lReflection))
                                    lReflectionColor += lReflection.intersected()->color(lReflection, _reflectionCount);  //*lSpecular;
                                else
                                    lReflectionColor += _scene->backgroundColor(lReflection)
                                                        * (1.0 / static_cast<double>((_reflectionCount + 1) * (_reflectionCount + 1)));

                                lRay = lReflection;
                                _reflectionCount++;
                            }


                            // Final color equals the sum of all the components
                            Color lFinalColor(lAmbientColor + lDiffusionColor + lReflectionColor + lRefractionColor);

                            lApertureColor += lFinalColor * lCamera->apertureColorCoeff(lApertureI, lApertureJ);
                        }
                        else
                        {
                            Color lTmp = _scene->backgroundColor(lRay);
                            lApertureColor += lTmp * lCamera->apertureColorCoeff(lApertureI, lApertureJ);
                        }
                        _reflectionCount = 1;
                    }
                }

                // Tone mapping
                Color lColorAfterToneMapping;
                lColorAfterToneMapping.setRed(1.0f - exp2f(lApertureColor.red() * (-1.0f)));
                lColorAfterToneMapping.setGreen(1.0f - exp2f(lApertureColor.green() * (-1.0f)));
                lColorAfterToneMapping.setBlue(1.0f - exp2f(lApertureColor.blue() * (-1.0f)));

                _buffer.setPixel(i, j, lColorAfterToneMapping);
            }
            // Display progress in the console
            cout << "Progress: " << static_cast<float>(i) / static_cast<float>(lBufferWidth) * 100.0f << " %" << endl;
        }
        // Display a message when the render is finished
        cout << "Done =)" << endl;
    }
    else if (_superSampling)
    {
        Color lMeanLight = _scene->meanAmbiantLight();

        for (unsigned int i = 0, lBufferWidth = _buffer.width(); i < lBufferWidth; i++)
        {
            for (unsigned int j = 0, lBufferHeight = _buffer.height(); j < lBufferHeight; j++)
            {
                float lI = static_cast<float>(i);
                float lJ = static_cast<float>(j);

                Color  lSuperSampling(0.0f);
                double lContribution = 0.25;

                for (float lFragmentX = lI; lFragmentX < lI + 1.0f; lFragmentX += 0.5f)
                {
                    for (float lFragmentY = lJ; lFragmentY < lJ + 1.0f; lFragmentY += 0.5f)
                    {
                        // It's possible to use only one camera (front())
                        Vector lRayDirection = lCamera->pixelDirection(lFragmentX, lFragmentY, &_buffer);
                        Point  lRayOrigin    = lCamera->position();
                        Ray    lRay(lRayOrigin, lRayDirection);

                        if (_scene->intersect(lRay))
                        {
                            // Max reflection for the current object
                            unsigned short lObjectMaxReflection = lRay.intersected()->shader()->reflectionCountMax();

                            // Ambient color
                            Ray   lAmbiantRay(lRay.intersection(), lRay.intersected()->normal(lRay.intersection()));
                            Color lAmbientColor = lMeanLight * lRay.intersected()->shader()->ambientColor(lAmbiantRay) * 0.1f;

                            // Diffusion color
                            Color lDiffusionColor = lRay.intersected()->color(lRay, 0);

                            // Refraction color
                            Color lRefractionColor(0.0);
                            if (lRay.intersected()->shader()->refractionCoeff() > 1.0)
                            {
                                Ray  lRefractionRay;
                                bool lHasRefraction = lRay.intersected()->refractedRay(lRay, lRefractionRay);

                                if (lHasRefraction)
                                {
                                    if (_scene->intersect(lRefractionRay))
                                        lRefractionColor = lRefractionRay.intersected()->color(lRefractionRay, 0);
                                    else
                                        lRefractionColor = _scene->backgroundColor(lRefractionRay);
                                }
                            }

                            // Reflections Color
                            Color lReflectionColor(0.0f);
                            while (_reflectionCount < lObjectMaxReflection && lRay.intersected() != nullptr)  //(c++11)
                            {
                                // Calculate reflected ray
                                Ray lReflection;
                                lReflection.setOrigin(lRay.intersection());

                                Vector lIncidentDirection(lRay.direction());
                                Vector lNormal(lRay.intersected()->normal(lRay.intersection()));
                                double lReflet              = (lIncidentDirection * lNormal) * (2.0);
                                Vector lReflectionDirection = lIncidentDirection - lNormal * lReflet;

                                lReflection.setDirection(lReflectionDirection);
                                lReflection.setIntersected(lRay.intersected());

                                if (_scene->intersect(lReflection))
                                    lReflectionColor += lReflection.intersected()->color(lReflection, _reflectionCount);  //*lSpecular;
                                else
                                    lReflectionColor += _scene->backgroundColor(lReflection)
                                                        * (1.0 / static_cast<double>((_reflectionCount + 1) * (_reflectionCount + 1)));

                                lRay = lReflection;
                                _reflectionCount++;
                            }


                            // Final color equals the sum of all the components
                            Color lFinalColor(lAmbientColor + lDiffusionColor + lReflectionColor + lRefractionColor);

                            // Tone mapping
                            Color lColorAfterToneMapping;
                            lColorAfterToneMapping.setRed(1.0f - exp2f(lFinalColor.red() * (-1.0f)));
                            lColorAfterToneMapping.setGreen(1.0f - exp2f(lFinalColor.green() * (-1.0f)));
                            lColorAfterToneMapping.setBlue(1.0f - exp2f(lFinalColor.blue() * (-1.0f)));

                            lSuperSampling += lColorAfterToneMapping * lContribution;
                        }
                        else
                            lSuperSampling += _scene->backgroundColor(lRay) * lContribution;

                        _reflectionCount = 1;
                    }
                }

                _buffer.setPixel(i, j, lSuperSampling);
            }
            // Display progress in the console
            cout << "Progress: " << static_cast<float>(i) / static_cast<float>(lBufferWidth) * 100.0f << " %" << endl;
        }
        // Display a message when the render is finished
        cout << "Done =)" << endl;
    }
    else
    {
        Color lMeanLight = _scene->meanAmbiantLight();

        for (unsigned int j = 0, lBufferHeight = _buffer.height(); j < lBufferHeight; ++j)
        {
            for (unsigned int i = 0, lBufferWidth = _buffer.width(); i < lBufferWidth; ++i)
            {
                // It's possible to use only one camera (front())
                Vector lRayDirection = lCamera->pixelDirection(i, j, &_buffer);
                Point  lRayOrigin    = lCamera->position();
                Ray    lRay(lRayOrigin, lRayDirection);

                if (_scene->intersect(lRay))
                {
                    // Max reflection for the current object
                    unsigned short lObjectMaxReflection = lRay.intersected()->shader()->reflectionCountMax();

                    // Ambient color
                    Ray   lAmbiantRay(lRay.intersection(), lRay.intersected()->normal(lRay.intersection()));
                    Color lAmbientColor = lMeanLight * lRay.intersected()->shader()->ambientColor(lAmbiantRay) * 0.1f;

                    // Diffusion color
                    Color lDiffusionColor = lRay.intersected()->color(lRay, 0);

                    // Refraction color
                    Color lRefractionColor(0.0);
                    if (lRay.intersected()->shader()->refractionCoeff() > 1.0)
                    {
                        Ray  lRefractionRay;
                        bool lHasRefraction = lRay.intersected()->refractedRay(lRay, lRefractionRay);

                        if (lHasRefraction)
                        {
                            if (_scene->intersect(lRefractionRay))
                                lRefractionColor = lRefractionRay.intersected()->color(lRefractionRay, 0);
                            else
                                lRefractionColor = _scene->backgroundColor(lRefractionRay);
                        }
                    }

                    // Reflections color
                    Color lReflectionColor(0.0f);
                    while (_reflectionCount < lObjectMaxReflection && lRay.intersected() != nullptr)  //(c++11)
                    {
                        // Calculate reflected ray
                        Ray lReflection;
                        lReflection.setOrigin(lRay.intersection());

                        Vector lIncidentDirection(lRay.direction());
                        Vector lNormal(lRay.intersected()->normal(lRay.intersection()));
                        double lReflet              = (lIncidentDirection * lNormal) * (2.0);
                        Vector lReflectionDirection = lIncidentDirection - lNormal * lReflet;

                        lReflection.setDirection(lReflectionDirection);
                        lReflection.setIntersected(lRay.intersected());

                        if (_scene->intersect(lReflection))
                            lReflectionColor += lReflection.intersected()->color(lReflection, _reflectionCount);  //*lSpecular;
                        else
                            lReflectionColor
                            += _scene->backgroundColor(lReflection) * (1.0 / static_cast<double>((_reflectionCount + 1) * (_reflectionCount + 1)));

                        lRay = lReflection;
                        _reflectionCount++;
                    }


                    // Final color equals the sum of all the components
                    Color lFinalColor(lAmbientColor + lDiffusionColor + lReflectionColor + lRefractionColor);

                    // Tone mapping
                    Color lColorAfterToneMapping;
                    lColorAfterToneMapping.setRed(1.0f - exp2f(lFinalColor.red() * (-1.0f)));
                    lColorAfterToneMapping.setGreen(1.0f - exp2f(lFinalColor.green() * (-1.0f)));
                    lColorAfterToneMapping.setBlue(1.0f - exp2f(lFinalColor.blue() * (-1.0f)));

                    _buffer.setPixel(i, j, lColorAfterToneMapping);
                }
                else
                {
                    _buffer.setPixel(i, j, _scene->backgroundColor(lRay));
                }
                _reflectionCount = 1;
            }
            // Display progress in the console
            cout << "Progress: " << static_cast<float>(j) / static_cast<float>(lBufferHeight) * 100.0f << " %" << endl;
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
