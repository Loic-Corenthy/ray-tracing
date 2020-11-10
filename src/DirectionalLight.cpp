#include "DirectionalLight.hpp"
#include "Renderable.hpp"
#include "Ray.hpp"
#include "Scene.hpp"

using namespace MatouMalin;

DirectionalLight::DirectionalLight(void)
:Light(),
 _direction(Vector(0.0))
{

}

DirectionalLight::DirectionalLight(const Vector & pDirection,const Color & pIntensity)
:Light(pIntensity),
 _direction(pDirection)
{

}

DirectionalLight::DirectionalLight(const DirectionalLight & pDirectionalLight)
:Light(pDirectionalLight)
{
	_direction = pDirectionalLight._direction;
}

DirectionalLight DirectionalLight::operator=(const MatouMalin::DirectionalLight &pDirectionalLight)
{
    if(this == & pDirectionalLight)
        return *this;

    Light::operator=(pDirectionalLight);

    _direction = pDirectionalLight._direction;

    return *this;
}

DirectionalLight::~DirectionalLight(void)
{
}


Color DirectionalLight::intensityAt(const Point & pPoint,const Scene & pScene, MatouMalin::Renderable* pCurrentObject) const
{
    Ray lMyRay;

    lMyRay.setOrigin(pPoint);
    lMyRay.setDirection(_direction*(-1));
    lMyRay.setIntersected(pCurrentObject);

	bool lHasIntersection = pScene.intersect(lMyRay);

	if(lHasIntersection)
		return	Color(0.0f);
	else
	{
        double lCos = pCurrentObject->normal(pPoint)*(_direction*(-1.0));
		return _intensity*lCos;
	}

}
