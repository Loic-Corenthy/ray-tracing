#include "Shader.hpp"

// Standard includes
#include <list>
#include <iostream>
#include <math.hpp>

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
:mBRDF(nullptr), //(c++11)
 mReflectionCountMax(1),
 mReflectionCoeff(0.0f),
 mCurrentReflectionCoeff(0.0f),
 mRefractionCoeff(0.0f),
 mMaterial(0),
 mScene(nullptr) //(c++11)
{
}

Shader::Shader(BRDF* pBRDF, double pReflectionCoeff, double pRefractionCoeff, Scene* pScene, unsigned short pMaterial)
:mBRDF(pBRDF),
 mReflectionCountMax(1),
 mReflectionCoeff(pReflectionCoeff),
 mCurrentReflectionCoeff(pReflectionCoeff),
 mRefractionCoeff(pRefractionCoeff),
 mMaterial(pMaterial),
 mScene(pScene)
{
    assert(pRefractionCoeff >= 1 && "Refraction coefficient must be bigger than 1");
}

Shader::Shader(const Shader & pShader)
{
	mBRDF = pShader.mBRDF;
    mReflectionCoeff = pShader.mReflectionCoeff;
    mCurrentReflectionCoeff = pShader.mCurrentReflectionCoeff;
	mRefractionCoeff = pShader.mRefractionCoeff;
	mMaterial = pShader.mMaterial;
	mScene = pShader.mScene;
}

Shader Shader::operator=(const Shader & pShader)
{
    if(this == &pShader)
        return *this;

    mBRDF = pShader.mBRDF;
    mReflectionCountMax = pShader.mReflectionCountMax;
	mReflectionCoeff = pShader.mReflectionCoeff;
    mCurrentReflectionCoeff = pShader.mCurrentReflectionCoeff;
	mRefractionCoeff = pShader.mRefractionCoeff;
	mMaterial = pShader.mMaterial;
	mScene = pShader.mScene;

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
//        mCurrentReflectionCoeff = pow(mReflectionCoeff,pReflectionCount);
        mCurrentReflectionCoeff = mReflectionCoeff/static_cast<double>(pReflectionCount*pReflectionCount);
//        mCurrentReflectionCoeff = mReflectionCoeff/static_cast<double>(pReflectionCount);
    }
    else
        mCurrentReflectionCoeff = 1.0;

    auto lIt = mScene->lightList().begin(); //(c++11)
    auto lEnd = mScene->lightList().end();

    Color lLightIntensity(0.0);
    double lNoiseCoeff(0.0f);
    Noise lNoise;

    switch (mMaterial)
    {
        case MARBLE:
            while( lIt != lEnd )
            {
                lLightIntensity = (*lIt)->intensityAt(pPoint,*mScene,pThis);

                if (!(lLightIntensity == Color(0.0f)))
                {
                    // Calculate diffuse component
                    lMyColor += lLightIntensity*mBRDF->diffuse((*lIt)->directionFrom(pPoint),pNormal,pPoint);//*mCurrentReflectionCoeff;

                    // Add turbulance noise to diffuse component
                    for (double lLevel=1.0f; lLevel<10.0f; lLevel += 1.0f)
                        lNoiseCoeff += (1.0f/lLevel)*fabs(lNoise.perlinNoise(lLevel*pPoint.x(), lLevel*pPoint.y(), lLevel*pPoint.z()));

                    lMyColor *= lNoiseCoeff;

                    // Add specular compoment
                    lMyColor += lLightIntensity*mBRDF->specular((*lIt)->directionFrom(pPoint),pVecToViewer,pNormal,pPoint);//*mCurrentReflectionCoeff;
                }

                lIt++;
            }
            break;

        case TURBULANCE:
            while( lIt != lEnd )
            {
                lLightIntensity = (*lIt)->intensityAt(pPoint,*mScene,pThis);

                if (!(lLightIntensity == Color(0.0f)))
                {
                    // Calculate diffuse component
                    lMyColor += lLightIntensity*mBRDF->diffuse((*lIt)->directionFrom(pPoint),pNormal,pPoint);//*mCurrentReflectionCoeff;

                    // Add turbulance noise to diffuse component
                    for (double lLevel=1.0f; lLevel<10.0f; lLevel += 1.0f)
                        lNoiseCoeff += (1.0f/lLevel)*fabs(lNoise.perlinNoise(lLevel*pPoint.x(), lLevel*pPoint.y(), lLevel*pPoint.z()));

                    lNoiseCoeff = 0.5f * sin( (pPoint.x() + pPoint.y()) + lNoiseCoeff) + 0.5f;

                    lMyColor *= lNoiseCoeff;

                    // Add specular compoment
                    lMyColor += lLightIntensity*mBRDF->specular((*lIt)->directionFrom(pPoint),pVecToViewer,pNormal,pPoint);//*mCurrentReflectionCoeff;
                }

                lIt++;
            }
            break;

        case BUMP:
            while( lIt != lEnd )
            {
                lLightIntensity = (*lIt)->intensityAt(pPoint,*mScene,pThis);

                if (!(lLightIntensity == Color(0.0f)))
                {
                    double lNoiseX = lNoise.perlinNoise(pPoint.x(), pPoint.y(), pPoint.z());
                    double lNoiseY = lNoise.perlinNoise(pPoint.y(), pPoint.z(), pPoint.x());
                    double lNoiseZ = lNoise.perlinNoise(pPoint.z(), pPoint.x(), pPoint.y());

                    Vector lBumpNormal(pNormal.x()*lNoiseX, pNormal.y()*lNoiseY, pNormal.z()*lNoiseZ);

                    lBumpNormal.normalize();

                    // Calculate diffuse component
                    lMyColor += lLightIntensity*mBRDF->diffuse((*lIt)->directionFrom(pPoint),lBumpNormal,pPoint);//*mCurrentReflectionCoeff;

                    // Add turbulance noise to diffuse component
                    for (double lLevel=1.0f; lLevel<10.0f; lLevel += 1.0f)
                        lNoiseCoeff += (1.0f/lLevel)*fabs(lNoise.perlinNoise(lLevel*pPoint.x(), lLevel*pPoint.y(), lLevel*pPoint.z()));

                    // Add specular compoment
                    lMyColor += lLightIntensity*mBRDF->specular((*lIt)->directionFrom(pPoint),pVecToViewer,lBumpNormal,pPoint);//*mCurrentReflectionCoeff;
                }

                lIt++;
            }

        case NONE:
        default:
            while( lIt != lEnd )
            {
                lLightIntensity = (*lIt)->intensityAt(pPoint,*mScene,pThis);

                if (!(lLightIntensity == Color(0.0f)))
                    lMyColor += lLightIntensity*mBRDF->reflectance((*lIt)->directionFrom(pPoint),pVecToViewer,pNormal,pPoint);//*mCurrentReflectionCoeff;

                lIt++;
            }
            break;
    }

    return (lMyColor*mCurrentReflectionCoeff);

}

Color Shader::ambientColor(const Ray & pRay) const
{
    if(mBRDF->ambient() == Color(0.0))
        return Color(0.0f);
    else if (mBRDF->cubeMap())
        return const_cast<CubeMap*>(mBRDF->cubeMap())->colorAt(pRay);
    else
        return mBRDF->ambient();
}

