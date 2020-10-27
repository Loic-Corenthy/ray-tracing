#include "Renderer.hpp"

// Standard includes
#include <iostream>
#include <math.hpp>

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

Renderer::Renderer(void)
:mScene(nullptr),
mBuffer(),
mReflectionCount(0),
mSuperSampling(false)
{
}

Renderer::Renderer(Scene* pScene,int pWidth, int pHeight)
:mScene(pScene),
mReflectionCount(1),
mBuffer(pHeight,pWidth),
mSuperSampling(false)
{
}

Renderer::Renderer(const Renderer & pRenderer)
:mScene(pRenderer.mScene),
mBuffer(pRenderer.mBuffer),
mReflectionCount(pRenderer.mReflectionCount),
mSuperSampling(pRenderer.mSuperSampling)
{
    
}

Renderer Renderer::operator=(const Renderer & pRenderer)
{
    if(this == &pRenderer)
        return *this;
    
    mScene = pRenderer.mScene;
	mBuffer = pRenderer.mBuffer;
	mReflectionCount = pRenderer.mReflectionCount;
    mSuperSampling = pRenderer.mSuperSampling;
    
    return *this;
}

Renderer::~Renderer(void)
{
}


void Renderer::render(void)
{
    Camera* lCamera = mScene->cameraList().front();
    
    if (lCamera->aperture() == Camera::F_SMALL || lCamera->aperture() == Camera::F_MEDIUM || lCamera->aperture() == Camera::F_BIG )
    {
        Color lMeanLight = mScene->meanAmbiantLight();
        
        for(unsigned int i=0, lBufferWidth = mBuffer.width(); i<lBufferWidth; i++)
        {
            for(unsigned int j=0, lBufferHeight = mBuffer.height(); j<lBufferHeight; j++)
            {
                // It's possible to use only one camera (front())
                Vector lRayDirection = lCamera->pixelDirection(i,j,&mBuffer);
                Point lRayOrigin = lCamera->position();
                
                // Calculate current focal point
                Ray lFirstRay(lRayOrigin,lRayDirection);
                lCamera->focalPlane().intersect(lFirstRay);
                Point lFocalPt = lFirstRay.intersection();
                
                // Accumulation of the secondary buffer color
                Color lApertureColor(0.0f);
                double lApertureRadius = lCamera->apertureRadius();
                double lApertureStep = lCamera->apertureStep();
                for (double lApertureI = lApertureRadius*(-1.0); lApertureI<=lApertureRadius; lApertureI += lApertureStep)
                {
                    for (double lApertureJ = lApertureRadius*(-1.0); lApertureJ<=lApertureRadius; lApertureJ += lApertureStep)
                    {
                        Point lApertureOrigin(lFirstRay.origin());
                        lApertureOrigin.setX(lApertureOrigin.x()+lApertureI);
                        lApertureOrigin.setY(lApertureOrigin.y()+lApertureJ);
                        
                        Ray lRay(lApertureOrigin,(lFocalPt - lApertureOrigin));
                        
                        if(mScene->intersect(lRay))
                        {
                            // Max reflection for the current object
                            unsigned short lObjectMaxReflection = lRay.intersected()->shader()->reflectionCountMax();
                            
                            // Ambient color
                            Ray lAmbiantRay(lRay.intersection(),lRay.intersected()->normal(lRay.intersection()));
                            Color lAmbientColor = lMeanLight*lRay.intersected()->shader()->ambientColor(lAmbiantRay)*0.1f;
                            
                            // Diffusion color
                            Color lDiffusionColor = lRay.intersected()->color(lRay,0);
                            
                            // Refraction color
                            Color lRefractionColor(0.0);
                            if (lRay.intersected()->shader()->refractionCoeff() > 1.0)
                            {
                                Ray lRefractionRay;
                                bool lHasRefraction = lRay.intersected()->refractedRay(lRay, lRefractionRay);
                                
                                if (lHasRefraction)
                                {
                                    if (mScene->intersect(lRefractionRay))
                                        lRefractionColor = lRefractionRay.intersected()->color(lRefractionRay,0);
                                    else
                                        lRefractionColor = mScene->backgroundColor(lRefractionRay);
                                }
                            }
                            
                            // Reflections color
                            Color lReflectionColor(0.0f);
                            while (mReflectionCount < lObjectMaxReflection && lRay.intersected() != nullptr) //(c++11)
                            {
                                // Calculate reflected ray
                                Ray lReflection;
                                lReflection.setOrigin(lRay.intersection());
                                
                                Vector lIncidentDirection(lRay.direction());
                                Vector lNormal(lRay.intersected()->normal(lRay.intersection()));
                                double lReflet = (lIncidentDirection*lNormal)*(2.0);
                                Vector lReflectionDirection = lIncidentDirection - lNormal*lReflet;
                                
                                lReflection.setDirection(lReflectionDirection);
                                lReflection.setIntersected(lRay.intersected());
                                
                                
                                if (mScene->intersect(lReflection))
                                    lReflectionColor += lReflection.intersected()->color(lReflection,mReflectionCount);//*lSpecular;
                                else
                                    lReflectionColor += mScene->backgroundColor(lReflection)*(1.0/static_cast<double>((mReflectionCount+1)*(mReflectionCount+1)));
                                
                                lRay = lReflection;
                                mReflectionCount++;
                                
                            }
                            
                            
                            // Final color equals the sum of all the components
                            Color lFinalColor(lAmbientColor + lDiffusionColor + lReflectionColor + lRefractionColor);
                            
                            lApertureColor += lFinalColor*lCamera->apertureColorCoeff(lApertureI, lApertureJ);
                            
                        }
                        else
                        {
                            Color lTmp = mScene->backgroundColor(lRay);
                            lApertureColor += lTmp*lCamera->apertureColorCoeff(lApertureI, lApertureJ);
                        }
                        mReflectionCount = 1;
                    }
                }
                
                // Tone mapping
                Color lColorAfterToneMapping;
                lColorAfterToneMapping.setRed(1.0f - exp2f(lApertureColor.red()*(-1.0f)));
                lColorAfterToneMapping.setGreen(1.0f - exp2f(lApertureColor.green()*(-1.0f)));
                lColorAfterToneMapping.setBlue(1.0f - exp2f(lApertureColor.blue()*(-1.0f)));
                
                mBuffer.setPixel(i,j,lColorAfterToneMapping) ;
                
                
            }
            // Display progress in the console
            cout << "Progress: " << static_cast<float>(i)/static_cast<float>(lBufferWidth)*100.0f << " %" << endl;
        }
        // Display a message when the render is finished
        cout << "Done =)" << endl;
    }
    else if (mSuperSampling)
    {
        Color lMeanLight = mScene->meanAmbiantLight();
        
        for(unsigned int i=0, lBufferWidth = mBuffer.width(); i<lBufferWidth; i++)
        {
            for(unsigned int j=0, lBufferHeight = mBuffer.height(); j<lBufferHeight; j++)
            {
                float lI = static_cast<float>(i);
                float lJ = static_cast<float>(j);
                
                Color lSuperSampling(0.0f);
                double lContribution = 0.25;
                
                for (float lFragmentX = lI; lFragmentX < lI + 1.0f; lFragmentX += 0.5f)
                {
                    for (float lFragmentY = lJ; lFragmentY < lJ + 1.0f; lFragmentY += 0.5f)
                    {
                        // It's possible to use only one camera (front())
                        Vector lRayDirection = lCamera->pixelDirection(lFragmentX,lFragmentY,&mBuffer);
                        Point lRayOrigin = lCamera->position();
                        Ray lRay(lRayOrigin,lRayDirection);
                        
                        if(mScene->intersect(lRay))
                        {
                            // Max reflection for the current object
                            unsigned short lObjectMaxReflection = lRay.intersected()->shader()->reflectionCountMax();
                            
                            // Ambient color
                            Ray lAmbiantRay(lRay.intersection(),lRay.intersected()->normal(lRay.intersection()));
                            Color lAmbientColor = lMeanLight*lRay.intersected()->shader()->ambientColor(lAmbiantRay)*0.1f;
                            
                            // Diffusion color
                            Color lDiffusionColor = lRay.intersected()->color(lRay,0);
                            
                            // Refraction color
                            Color lRefractionColor(0.0);
                            if (lRay.intersected()->shader()->refractionCoeff() > 1.0)
                            {
                                Ray lRefractionRay;
                                bool lHasRefraction = lRay.intersected()->refractedRay(lRay, lRefractionRay);
                                
                                if (lHasRefraction)
                                {
                                    if (mScene->intersect(lRefractionRay))
                                        lRefractionColor = lRefractionRay.intersected()->color(lRefractionRay,0);
                                    else
                                        lRefractionColor = mScene->backgroundColor(lRefractionRay);
                                }
                                
                            }
                            
                            // Reflections Color
                            Color lReflectionColor(0.0f);
                            while (mReflectionCount < lObjectMaxReflection && lRay.intersected() != nullptr) //(c++11)
                            {
                                // Calculate reflected ray
                                Ray lReflection;
                                lReflection.setOrigin(lRay.intersection());
                                
                                Vector lIncidentDirection(lRay.direction());
                                Vector lNormal(lRay.intersected()->normal(lRay.intersection()));
                                double lReflet = (lIncidentDirection*lNormal)*(2.0);
                                Vector lReflectionDirection = lIncidentDirection - lNormal*lReflet;
                                
                                lReflection.setDirection(lReflectionDirection);
                                lReflection.setIntersected(lRay.intersected());
                                
                                if (mScene->intersect(lReflection))
                                    lReflectionColor += lReflection.intersected()->color(lReflection,mReflectionCount);//*lSpecular;
                                else
                                    lReflectionColor += mScene->backgroundColor(lReflection)*(1.0/static_cast<double>((mReflectionCount+1)*(mReflectionCount+1)));
                                
                                lRay = lReflection;
                                mReflectionCount++;
                                
                            }
                            
                            
                            // Final color equals the sum of all the components
                            Color lFinalColor(lAmbientColor+lDiffusionColor+lReflectionColor+lRefractionColor);
                            
                            // Tone mapping
                            Color lColorAfterToneMapping;
                            lColorAfterToneMapping.setRed(1.0f - exp2f(lFinalColor.red()*(-1.0f)));
                            lColorAfterToneMapping.setGreen(1.0f - exp2f(lFinalColor.green()*(-1.0f)));
                            lColorAfterToneMapping.setBlue(1.0f - exp2f(lFinalColor.blue()*(-1.0f)));
                            
                            lSuperSampling += lColorAfterToneMapping*lContribution;
                        }
                        else
                            lSuperSampling += mScene->backgroundColor(lRay)*lContribution;
                        
                        mReflectionCount = 1;
                    }
                }
                
                mBuffer.setPixel(i, j, lSuperSampling);
                
            }
            // Display progress in the console
            cout << "Progress: " << static_cast<float>(i)/static_cast<float>(lBufferWidth)*100.0f << " %" << endl;
        }
        // Display a message when the render is finished
        cout << "Done =)" << endl;
    }
    else
    {
        Color lMeanLight = mScene->meanAmbiantLight();
        
        for(unsigned int j=0, lBufferHeight = mBuffer.height(); j<lBufferHeight; ++j)
        {
            for(unsigned int i=0, lBufferWidth = mBuffer.width(); i<lBufferWidth; ++i)
            {
                // It's possible to use only one camera (front())
                Vector lRayDirection = lCamera->pixelDirection(i,j,&mBuffer);
                Point lRayOrigin = lCamera->position();
                Ray lRay(lRayOrigin,lRayDirection);
                
                if(mScene->intersect(lRay))
                {
                    // Max reflection for the current object
                    unsigned short lObjectMaxReflection = lRay.intersected()->shader()->reflectionCountMax();
                    
                    // Ambient color
                    Ray lAmbiantRay(lRay.intersection(),lRay.intersected()->normal(lRay.intersection()));
                    Color lAmbientColor = lMeanLight*lRay.intersected()->shader()->ambientColor(lAmbiantRay)*0.1f;
                    
                    // Diffusion color
                    Color lDiffusionColor = lRay.intersected()->color(lRay,0);
                    
                    // Refraction color
                    Color lRefractionColor(0.0);
                    if (lRay.intersected()->shader()->refractionCoeff() > 1.0)
                    {
                        Ray lRefractionRay;
                        bool lHasRefraction = lRay.intersected()->refractedRay(lRay, lRefractionRay);
                        
                        if (lHasRefraction)
                        {
                            if (mScene->intersect(lRefractionRay))
                                lRefractionColor = lRefractionRay.intersected()->color(lRefractionRay,0);
                            else
                                lRefractionColor = mScene->backgroundColor(lRefractionRay);
                        }
                        
                    }
                    
                    // Reflections color
                    Color lReflectionColor(0.0f);
                    while (mReflectionCount < lObjectMaxReflection && lRay.intersected() != nullptr) //(c++11)
                    {
                        // Calculate reflected ray
                        Ray lReflection;
                        lReflection.setOrigin(lRay.intersection());
                        
                        Vector lIncidentDirection(lRay.direction());
                        Vector lNormal(lRay.intersected()->normal(lRay.intersection()));
                        double lReflet = (lIncidentDirection*lNormal)*(2.0);
                        Vector lReflectionDirection = lIncidentDirection - lNormal*lReflet;
                        
                        lReflection.setDirection(lReflectionDirection);
                        lReflection.setIntersected(lRay.intersected());
                        
                        if (mScene->intersect(lReflection))
                            lReflectionColor += lReflection.intersected()->color(lReflection,mReflectionCount);//*lSpecular;
                        else
                            lReflectionColor += mScene->backgroundColor(lReflection)*(1.0/static_cast<double>((mReflectionCount+1)*(mReflectionCount+1)));
                        
                        lRay = lReflection;
                        mReflectionCount++;
                    }
                    
                    
                    // Final color equals the sum of all the components
                    Color lFinalColor(lAmbientColor+lDiffusionColor+lReflectionColor+lRefractionColor);
                    
                    // Tone mapping
                    Color lColorAfterToneMapping;
                    lColorAfterToneMapping.setRed(1.0f - exp2f(lFinalColor.red()*(-1.0f)));
                    lColorAfterToneMapping.setGreen(1.0f - exp2f(lFinalColor.green()*(-1.0f)));
                    lColorAfterToneMapping.setBlue(1.0f - exp2f(lFinalColor.blue()*(-1.0f)));
                    
                    mBuffer.setPixel(i,j,lColorAfterToneMapping) ;
                    
                }
                else
                {
                    mBuffer.setPixel(i,j,mScene->backgroundColor(lRay));
                }
                mReflectionCount = 1;
            }
            // Display progress in the console
            cout << "Progress: " << static_cast<float>(j)/static_cast<float>(lBufferHeight)*100.0f << " %" << endl;
        }
        // Display a message when the render is finished
        cout << "Done =)" << endl;
        
    }
    
}