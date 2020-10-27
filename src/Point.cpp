#include "Point.h"

using namespace MatouMalin;

Point::Point(void)
{
	mCoords[0] = 0.0;
	mCoords[1] = 0.0;
	mCoords[2] = 0.0;
}

Point::Point(double pX, double pY, double pZ)
{
	mCoords[0] = pX;
	mCoords[1] = pY;
	mCoords[2] = pZ;
}

Point::Point(double pCommonValue)
{
    mCoords[0] = pCommonValue;
	mCoords[1] = pCommonValue;
	mCoords[2] = pCommonValue;
}

Point::Point(const Point & pPoint)
{
	mCoords[0] = pPoint.mCoords[0];
	mCoords[1] = pPoint.mCoords[1];
	mCoords[2] = pPoint.mCoords[2];
}

Point::~Point(void)
{
}

Point Point::operator=(const Point & pPoint)
{
    if (this == &pPoint)
        return *this;
    
     mCoords[0] = pPoint.mCoords[0];
	 mCoords[1] = pPoint.mCoords[1];
	 mCoords[2] = pPoint.mCoords[2];
    
    return *this;
}