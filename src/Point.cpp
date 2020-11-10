#include "Point.hpp"

using namespace MatouMalin;

Point::Point(void)
{
	_coords[0] = 0.0;
	_coords[1] = 0.0;
	_coords[2] = 0.0;
}

Point::Point(double pX, double pY, double pZ)
{
	_coords[0] = pX;
	_coords[1] = pY;
	_coords[2] = pZ;
}

Point::Point(double pCommonValue)
{
    _coords[0] = pCommonValue;
	_coords[1] = pCommonValue;
	_coords[2] = pCommonValue;
}

Point::Point(const Point & pPoint)
{
	_coords[0] = pPoint._coords[0];
	_coords[1] = pPoint._coords[1];
	_coords[2] = pPoint._coords[2];
}

Point::~Point(void)
{
}

Point Point::operator=(const Point & pPoint)
{
    if (this == &pPoint)
        return *this;

     _coords[0] = pPoint._coords[0];
	 _coords[1] = pPoint._coords[1];
	 _coords[2] = pPoint._coords[2];

    return *this;
}