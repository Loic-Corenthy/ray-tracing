#include "DirectionalLight.hpp"
#include "Renderable.hpp"
#include "Ray.hpp"
#include "Scene.hpp"

using namespace MatouMalin;

DirectionalLight::DirectionalLight(void)
:Light(),
 mDirection(Vector(0.0))
{
    
}

DirectionalLight::DirectionalLight(const Vector & pDirection,const Color & pIntensity)
:Light(pIntensity),
 mDirection(pDirection)
{
    
}

DirectionalLight::DirectionalLight(const DirectionalLight & pDirectionalLight)
:Light(pDirectionalLight)
{
	mDirection = pDirectionalLight.mDirection;
}

DirectionalLight DirectionalLight::operator=(const MatouMalin::DirectionalLight &pDirectionalLight)
{
    if(this == & pDirectionalLight)
        return *this;
    
    Light::operator=(pDirectionalLight);
    
    mDirection = pDirectionalLight.mDirection;
    
    return *this;
}

DirectionalLight::~DirectionalLight(void)
{
}


Color DirectionalLight::intensityAt(const Point & pPoint,const Scene & pScene, MatouMalin::Renderable* pCurrentObject) const
{
    Ray lMyRay;

    lMyRay.setOrigin(pPoint);
    lMyRay.setDirection(mDirection*(-1));
    lMyRay.setIntersected(pCurrentObject);
    
	bool lHasIntersection = pScene.intersect(lMyRay);
    
	if(lHasIntersection)
		return	Color(0.0f);
	else
	{
        double lCos = pCurrentObject->normal(pPoint)*(mDirection*(-1.0));
		return mIntensity*lCos;
	}

}
