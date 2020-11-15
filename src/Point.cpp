//===============================================================================================//
/*!
 *  \file      Point.hpp
 *  \author    Loïc Corenthy
 *  \version   1.0
 *  \date      14/10/2012
 *  \copyright (c) 2012 Loïc Corenthy. All rights reserved.
 */
//===============================================================================================//

#include "Point.hpp"

using namespace LCNS;

Point::Point(void)
{
    _coords[0] = 0.0;
    _coords[1] = 0.0;
    _coords[2] = 0.0;
}

Point::Point(double x, double y, double z)
{
    _coords[0] = x;
    _coords[1] = y;
    _coords[2] = z;
}

Point::Point(double commonValue)
{
    _coords[0] = commonValue;
    _coords[1] = commonValue;
    _coords[2] = commonValue;
}

Point::Point(const Point& point)
{
    _coords[0] = point._coords[0];
    _coords[1] = point._coords[1];
    _coords[2] = point._coords[2];
}

Point::~Point(void)
{
}

Point Point::operator=(const Point& point)
{
    if (this == &point)
        return *this;

    _coords[0] = point._coords[0];
    _coords[1] = point._coords[1];
    _coords[2] = point._coords[2];

    return *this;
}
