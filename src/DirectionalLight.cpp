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

DirectionalLight::DirectionalLight(const Vector & direction,const Color & intensity)
:Light(intensity),
 _direction(direction)
{

}

DirectionalLight::DirectionalLight(const DirectionalLight & directionalLight)
:Light(directionalLight)
{
	_direction = directionalLight._direction;
}

DirectionalLight DirectionalLight::operator=(const MatouMalin::DirectionalLight &directionalLight)
{
    if(this == & directionalLight)
        return *this;

    Light::operator=(directionalLight);

    _direction = directionalLight._direction;

    return *this;
}

DirectionalLight::~DirectionalLight(void)
{
}


Color DirectionalLight::intensityAt(const Point & point,const Scene & scene, MatouMalin::Renderable* currentObject) const
{
    Ray lMyRay;

    lMyRay.setOrigin(point);
    lMyRay.setDirection(_direction*(-1));
    lMyRay.setIntersected(currentObject);

	bool lHasIntersection = scene.intersect(lMyRay);

	if(lHasIntersection)
		return	Color(0.0f);
	else
	{
        double lCos = currentObject->normal(point)*(_direction*(-1.0));
		return _intensity*lCos;
	}

}
