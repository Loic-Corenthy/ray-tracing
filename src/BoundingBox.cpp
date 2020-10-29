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
:mMin(Point(BIG_POS_VALUE,BIG_POS_VALUE,BIG_POS_VALUE)),
 mMax(Point(BIG_NEG_VALUE,BIG_NEG_VALUE,BIG_NEG_VALUE))
{
}

BoundingBox::BoundingBox(const Point & pMin, const Point & pMax)
:mMin(pMin),
 mMax(pMax)
{
}

BoundingBox::BoundingBox(const BoundingBox & pBoundingBox)
:mMin(pBoundingBox.mMin),
 mMax(pBoundingBox.mMax)
{
}

BoundingBox BoundingBox::operator=(const BoundingBox &pBoundingBox)
{
    if (this == &pBoundingBox)
        return *this;

    mMin = pBoundingBox.mMin;
    mMax = pBoundingBox.mMax;

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
        double lLength = (mMax.z() - pRay.origin().z())/pRay.direction().z();

        // Front plane: Calculate the coordinates of the intersection point
        Point lP = pRay.origin() + pRay.direction()*lLength;

        // Front plane: Check if the point in the plane is really inside the rectangle
        if(lP.x() >= mMin.x() && lP.x() <= mMax.x() && lP.y() >= mMin.y() && lP.y() <= mMax.y())
            lIntersectFace[0] = true;

        // Same for back plane:
        lLength = (mMin.z() - pRay.origin().z())/pRay.direction().z();
        lP = pRay.origin() + pRay.direction()*lLength;
        if(lP.x() >= mMin.x() && lP.x() <= mMax.x() && lP.y() >= mMin.y() && lP.y() <= mMax.y())
            lIntersectFace[1] = true;
    }

    // Check if the ray is not parallel to the XZ plane
    if (pRay.direction().y() != 0.0)
    {
        // Same for up plane:
        double lLength = (mMax.y() - pRay.origin().y())/pRay.direction().y();
        Point lP = pRay.origin() + pRay.direction()*lLength;
        if(lP.x() >= mMin.x() && lP.x() <= mMax.x() && lP.z() >= mMin.z() && lP.z() <= mMax.z())
            lIntersectFace[2] = true;

        // Same for down plane:
        lLength = (mMin.y() - pRay.origin().y())/pRay.direction().y();
        lP = pRay.origin() + pRay.direction()*lLength;
        if(lP.x() >= mMin.x() && lP.x() <= mMax.x() && lP.z() >= mMin.z() && lP.z() <= mMax.z())
            lIntersectFace[3] = true;
    }

    // Check if the ray is not parallel to the YZ plane
    if (pRay.direction().x() != 0.0)
    {
        // Same for right plane:
        double lLength = (mMax.x() - pRay.origin().x())/pRay.direction().x();
        Point lP = pRay.origin() + pRay.direction()*lLength;
        if(lP.y() >= mMin.y() && lP.y() <= mMax.y() && lP.z() >= mMin.z() && lP.z() <= mMax.z())
            lIntersectFace[4] = true;

        // Same for left plane:
        lLength = (mMin.x() - pRay.origin().x())/pRay.direction().x();
        lP = pRay.origin() + pRay.direction()*lLength;
        if(lP.y() >= mMin.y() && lP.y() <= mMax.y() && lP.z() >= mMin.z() && lP.z() <= mMax.z())
            lIntersectFace[5] = true;

    }

    lIntersectFace[6] = lIntersectFace[0] || lIntersectFace[1] || lIntersectFace[2] || lIntersectFace[3] || lIntersectFace[4] || lIntersectFace[5];



    return lIntersectFace[6];
}


