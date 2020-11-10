#include "Sphere.hpp"

#include <cmath>

#include "Shader.hpp"

using namespace MatouMalin;

Sphere::Sphere(void)
:_center(Point(0,0,0)),_radius(0)
{
}

Sphere::Sphere(const Point & point,float radius)
:_center(point),_radius(radius)
{
}

Sphere::Sphere(const Sphere & sphere)
:Renderable(sphere),
 _center(sphere._center),
 _radius(sphere._radius)
{

}

Sphere Sphere::operator=(const Sphere &sphere)
{
    if (this == & sphere)
        return *this;

    Renderable::operator=(sphere);

    _center = sphere._center;
	_radius = sphere._radius;

    return *this;
}

Sphere::~Sphere(void)
{
}

bool Sphere::intersect(Ray & ray)
{

	float a = ray.direction()[0]*ray.direction()[0] + ray.direction()[1]*ray.direction()[1] + ray.direction()[2]*ray.direction()[2];
	float b = 2*(ray.direction()[0]*(ray.origin()[0] - _center[0]) + ray.direction()[1]*(ray.origin()[1] - _center[1]) + ray.direction()[2]*(ray.origin()[2] - _center[2]));
	float c = (ray.origin()[0] - _center[0])*(ray.origin()[0] - _center[0]) + (ray.origin()[1] - _center[1])*(ray.origin()[1] - _center[1]) + (ray.origin()[2] - _center[2])*(ray.origin()[2] - _center[2]) - _radius*_radius;

    float lRoot1(0.0f);
	float lRoot2(0.0f);
	bool lRootOk(false);

	lRootOk = _solveSecDeg(a,b,c,lRoot1,lRoot2);

	if(lRootOk == false)
		return false;

    if(lRoot1 > 0.0 && lRoot2 > 0.0)
    {
		ray.setLength((lRoot1<lRoot2)?lRoot1:lRoot2);
        ray.setIntersected(this);
		return true;
	}
    else if((lRoot1 > 0.0 && lRoot2 <= 0.0) || (lRoot2 > 0.0 && lRoot1 <= 0.0))
    {
        ray.setLength((lRoot1>lRoot2)?lRoot1:lRoot2);
        ray.setIntersected(this);
		return true;
    }
    else
        return false;

}

Color Sphere::color(Ray & ray, unsigned int reflectionCount)
{
    // Calculate normal from vertex normals
    Vector lNormalAtPt = (ray.intersection() - _center);
    lNormalAtPt.normalize();

	return (_shader->color(ray.direction()*(-1),lNormalAtPt,ray.intersection(),this,reflectionCount));

}

bool Sphere::refractedRay(const Ray & incomingRay, Ray & refractedRay)
{
    Vector lIncomingDirection = incomingRay.direction();
    lIncomingDirection.normalize();
    Vector lNormal = normal(incomingRay.intersection());
    double lAirIndex = 1.0;
    double lCurrentObjectIndex = _shader->refractionCoeff();

    Vector lRefractedDirection;

    bool lFirstRefraction = _refraction(lIncomingDirection,lNormal, lAirIndex, lCurrentObjectIndex, lRefractedDirection);

    if (lFirstRefraction)
    {
        Ray lInsideSphere(incomingRay.intersection()+lRefractedDirection*0.1, lRefractedDirection);

        bool lGetOut = this->intersect(lInsideSphere);
        assert(lGetOut && "Intersection not found inside the sphere");

        Vector lOutRefractionDirection;
        lIncomingDirection = lInsideSphere.direction();
        lIncomingDirection.normalize();
        bool lSecondRefraction = _refraction(lInsideSphere.direction(), normal(lInsideSphere.intersection())*(-1.0), lCurrentObjectIndex, lAirIndex, lOutRefractionDirection);

        if (!lSecondRefraction)
            return false;

        assert(lSecondRefraction && "Ray cannot get find its way out of the sphere :p ");

        refractedRay.setOrigin(lInsideSphere.intersection());
        refractedRay.setDirection(lOutRefractionDirection);
        refractedRay.setIntersected(this);

        return true;
    }
    else
    {
        return false;
    }

}


bool Sphere::_solveSecDeg(float a,float b,float c,float & root1,float & root2)
{
	float lDelta = 0;
	lDelta = b*b - 4*a*c;

	if(lDelta < 0)
	{
		root1 = 0;
		root2 = 0;
		return false;
	}
	else if (lDelta == 0)
	{
		root1 = -b/(2*a);
		root2 = -b/(2*a);
		return true;
	}
	else
	{
		root1 = (-b - sqrt(lDelta))/(2*a);
		root2 = (-b + sqrt(lDelta))/(2*a);
		return true;
	}

}

