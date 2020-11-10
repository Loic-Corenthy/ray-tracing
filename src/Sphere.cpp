#include "Sphere.hpp"

#include <cmath>

#include "Shader.hpp"

using namespace MatouMalin;

Sphere::Sphere(void)
:_center(Point(0,0,0)),_radius(0)
{
}

Sphere::Sphere(const Point & pPoint,float pRadius)
:_center(pPoint),_radius(pRadius)
{
}

Sphere::Sphere(const Sphere & pSphere)
:Renderable(pSphere),
 _center(pSphere._center),
 _radius(pSphere._radius)
{

}

Sphere Sphere::operator=(const Sphere &pSphere)
{
    if (this == & pSphere)
        return *this;

    Renderable::operator=(pSphere);

    _center = pSphere._center;
	_radius = pSphere._radius;

    return *this;
}

Sphere::~Sphere(void)
{
}

bool Sphere::intersect(Ray & pRay)
{

	float a = pRay.direction()[0]*pRay.direction()[0] + pRay.direction()[1]*pRay.direction()[1] + pRay.direction()[2]*pRay.direction()[2];
	float b = 2*(pRay.direction()[0]*(pRay.origin()[0] - _center[0]) + pRay.direction()[1]*(pRay.origin()[1] - _center[1]) + pRay.direction()[2]*(pRay.origin()[2] - _center[2]));
	float c = (pRay.origin()[0] - _center[0])*(pRay.origin()[0] - _center[0]) + (pRay.origin()[1] - _center[1])*(pRay.origin()[1] - _center[1]) + (pRay.origin()[2] - _center[2])*(pRay.origin()[2] - _center[2]) - _radius*_radius;

    float lRoot1(0.0f);
	float lRoot2(0.0f);
	bool lRootOk(false);

	lRootOk = _solveSecDeg(a,b,c,lRoot1,lRoot2);

	if(lRootOk == false)
		return false;

    if(lRoot1 > 0.0 && lRoot2 > 0.0)
    {
		pRay.setLength((lRoot1<lRoot2)?lRoot1:lRoot2);
        pRay.setIntersected(this);
		return true;
	}
    else if((lRoot1 > 0.0 && lRoot2 <= 0.0) || (lRoot2 > 0.0 && lRoot1 <= 0.0))
    {
        pRay.setLength((lRoot1>lRoot2)?lRoot1:lRoot2);
        pRay.setIntersected(this);
		return true;
    }
    else
        return false;

}

Color Sphere::color(Ray & pRay, unsigned int pReflectionCount)
{
    // Calculate normal from vertex normals
    Vector lNormalAtPt = (pRay.intersection() - _center);
    lNormalAtPt.normalize();

	return (_shader->color(pRay.direction()*(-1),lNormalAtPt,pRay.intersection(),this,pReflectionCount));

}

bool Sphere::refractedRay(const Ray & pIncomingRay, Ray & pRefractedRay)
{
    Vector lIncomingDirection = pIncomingRay.direction();
    lIncomingDirection.normalize();
    Vector lNormal = normal(pIncomingRay.intersection());
    double lAirIndex = 1.0;
    double lCurrentObjectIndex = _shader->refractionCoeff();

    Vector lRefractedDirection;

    bool lFirstRefraction = _refraction(lIncomingDirection,lNormal, lAirIndex, lCurrentObjectIndex, lRefractedDirection);

    if (lFirstRefraction)
    {
        Ray lInsideSphere(pIncomingRay.intersection()+lRefractedDirection*0.1, lRefractedDirection);

        bool lGetOut = this->intersect(lInsideSphere);
        assert(lGetOut && "Intersection not found inside the sphere");

        Vector lOutRefractionDirection;
        lIncomingDirection = lInsideSphere.direction();
        lIncomingDirection.normalize();
        bool lSecondRefraction = _refraction(lInsideSphere.direction(), normal(lInsideSphere.intersection())*(-1.0), lCurrentObjectIndex, lAirIndex, lOutRefractionDirection);

        if (!lSecondRefraction)
            return false;

        assert(lSecondRefraction && "Ray cannot get find its way out of the sphere :p ");

        pRefractedRay.setOrigin(lInsideSphere.intersection());
        pRefractedRay.setDirection(lOutRefractionDirection);
        pRefractedRay.setIntersected(this);

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

