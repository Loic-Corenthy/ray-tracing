//
//  BoundingBox.cpp
//  RayTracing
//
//  Created by Loïc CORENTHY on 9/6/12.
//
//

#include "BoundingBox.hpp"

#define BIG_POS_VALUE 1000000.0
#define BIG_NEG_VALUE -1000000.0

using namespace MatouMalin;

BoundingBox::BoundingBox(void)
:_min(Point(BIG_POS_VALUE,BIG_POS_VALUE,BIG_POS_VALUE)),
 _max(Point(BIG_NEG_VALUE,BIG_NEG_VALUE,BIG_NEG_VALUE))
{
}

BoundingBox::BoundingBox(const Point & pMin, const Point & pMax)
:_min(pMin),
 _max(pMax)
{
}

BoundingBox::BoundingBox(const BoundingBox & pBoundingBox)
:_min(pBoundingBox._min),
 _max(pBoundingBox._max)
{
}

BoundingBox BoundingBox::operator=(const BoundingBox &pBoundingBox)
{
    if (this == &pBoundingBox)
        return *this;

    _min = pBoundingBox._min;
    _max = pBoundingBox._max;

    return *this;
}

BoundingBox::~BoundingBox(void)
{
}

bool BoundingBox::intersect(const Ray & pRay) const
{
    bool lIntersectFace[7] = {false,false,false,false,false,false,false};

    // Check if ray is not parallel to the XY plane
    if (pRay.direction().z() != 0.0)
    {
        // Front plane: Calculate the length the ray when intersecting the plane
        double lLength = (_max.z() - pRay.origin().z())/pRay.direction().z();

        // Front plane: Calculate the coordinates of the intersection point
        Point lP = pRay.origin() + pRay.direction()*lLength;

        // Front plane: Check if the point in the plane is really inside the rectangle
        if(lP.x() >= _min.x() && lP.x() <= _max.x() && lP.y() >= _min.y() && lP.y() <= _max.y())
            lIntersectFace[0] = true;

        // Same for back plane:
        lLength = (_min.z() - pRay.origin().z())/pRay.direction().z();
        lP = pRay.origin() + pRay.direction()*lLength;
        if(lP.x() >= _min.x() && lP.x() <= _max.x() && lP.y() >= _min.y() && lP.y() <= _max.y())
            lIntersectFace[1] = true;
    }

    // Check if the ray is not parallel to the XZ plane
    if (pRay.direction().y() != 0.0)
    {
        // Same for up plane:
        double lLength = (_max.y() - pRay.origin().y())/pRay.direction().y();
        Point lP = pRay.origin() + pRay.direction()*lLength;
        if(lP.x() >= _min.x() && lP.x() <= _max.x() && lP.z() >= _min.z() && lP.z() <= _max.z())
            lIntersectFace[2] = true;

        // Same for down plane:
        lLength = (_min.y() - pRay.origin().y())/pRay.direction().y();
        lP = pRay.origin() + pRay.direction()*lLength;
        if(lP.x() >= _min.x() && lP.x() <= _max.x() && lP.z() >= _min.z() && lP.z() <= _max.z())
            lIntersectFace[3] = true;
    }

    // Check if the ray is not parallel to the YZ plane
    if (pRay.direction().x() != 0.0)
    {
        // Same for right plane:
        double lLength = (_max.x() - pRay.origin().x())/pRay.direction().x();
        Point lP = pRay.origin() + pRay.direction()*lLength;
        if(lP.y() >= _min.y() && lP.y() <= _max.y() && lP.z() >= _min.z() && lP.z() <= _max.z())
            lIntersectFace[4] = true;

        // Same for left plane:
        lLength = (_min.x() - pRay.origin().x())/pRay.direction().x();
        lP = pRay.origin() + pRay.direction()*lLength;
        if(lP.y() >= _min.y() && lP.y() <= _max.y() && lP.z() >= _min.z() && lP.z() <= _max.z())
            lIntersectFace[5] = true;

    }

    lIntersectFace[6] = lIntersectFace[0] || lIntersectFace[1] || lIntersectFace[2] || lIntersectFace[3] || lIntersectFace[4] || lIntersectFace[5];



    return lIntersectFace[6];
}


