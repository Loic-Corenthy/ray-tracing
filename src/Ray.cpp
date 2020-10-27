#include "Ray.h"

using namespace MatouMalin;

Ray::Ray(void)
:mOrigin(Point(0.0f,0.0f,0.0f)),
 mDirection(Vector(0.0f,0.0f,0.0f)),
 mIntersected(nullptr)
{
    mLength = (float)MAXFLOAT;
}

Ray::Ray(const Point & pOrigin, const Vector & pDirection)
:mOrigin(pOrigin),
 mDirection(pDirection),
 mIntersected(nullptr)
{
	mLength = (float)MAXFLOAT;
}

Ray::Ray(const Ray & pRay)
:mOrigin(pRay.mOrigin),
 mDirection(pRay.mDirection),
 mLength(pRay.mLength),
 mIntersected(pRay.mIntersected)
{
}

Ray Ray::operator=(const Ray & pRay)
{
    if(this == & pRay)
        return *this;
    
    mOrigin = pRay.mOrigin;
	mDirection = pRay.mDirection;
	mLength = pRay.mLength;
	mIntersected = pRay.mIntersected;
    
    return *this;
}

Ray::~Ray(void)
{
}

	
