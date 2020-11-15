#include "DirectionalLight.hpp"
#include "Renderable.hpp"
#include "Ray.hpp"
#include "Scene.hpp"

using namespace LCNS;

DirectionalLight::DirectionalLight(void)
: Light()
, _direction(Vector(0.0))
{
}

DirectionalLight::DirectionalLight(const Vector& direction, const Color& intensity)
: Light(intensity)
, _direction(direction)
{
}

DirectionalLight::DirectionalLight(const DirectionalLight& directionalLight)
: Light(directionalLight)
{
    _direction = directionalLight._direction;
}

DirectionalLight DirectionalLight::operator=(const LCNS::DirectionalLight& directionalLight)
{
    if (this == &directionalLight)
        return *this;

    Light::operator=(directionalLight);

    _direction = directionalLight._direction;

    return *this;
}

DirectionalLight::~DirectionalLight(void)
{
}


Color DirectionalLight::intensityAt(const Point& point, const Scene& scene, LCNS::Renderable* currentObject) const
{
    Ray myRay;

    myRay.setOrigin(point);
    myRay.setDirection(_direction * (-1));
    myRay.setIntersected(currentObject);

    bool hasIntersection = scene.intersect(myRay);

    if (hasIntersection)
        return Color(0.0f);
    else
    {
        double cos = currentObject->normal(point) * (_direction * (-1.0));
        return _intensity * cos;
    }
}
