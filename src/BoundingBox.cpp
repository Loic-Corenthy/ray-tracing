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

using namespace LCNS;

BoundingBox::BoundingBox(void)
: _min(Point(BIG_POS_VALUE, BIG_POS_VALUE, BIG_POS_VALUE))
, _max(Point(BIG_NEG_VALUE, BIG_NEG_VALUE, BIG_NEG_VALUE))
{
}

BoundingBox::BoundingBox(const Point& min, const Point& max)
: _min(min)
, _max(max)
{
}

BoundingBox::BoundingBox(const BoundingBox& boundingBox)
: _min(boundingBox._min)
, _max(boundingBox._max)
{
}

BoundingBox BoundingBox::operator=(const BoundingBox& boundingBox)
{
    if (this == &boundingBox)
        return *this;

    _min = boundingBox._min;
    _max = boundingBox._max;

    return *this;
}

BoundingBox::~BoundingBox(void)
{
}

bool BoundingBox::intersect(const Ray& ray) const
{
    bool intersectFace[7] = { false, false, false, false, false, false, false };

    // Check if ray is not parallel to the XY plane
    if (ray.direction().z() != 0.0)
    {
        // Front plane: Calculate the length the ray when intersecting the plane
        double length = (_max.z() - ray.origin().z()) / ray.direction().z();

        // Front plane: Calculate the coordinates of the intersection point
        Point p = ray.origin() + ray.direction() * length;

        // Front plane: Check if the point in the plane is really inside the rectangle
        if (p.x() >= _min.x() && p.x() <= _max.x() && p.y() >= _min.y() && p.y() <= _max.y())
            intersectFace[0] = true;

        // Same for back plane:
        length = (_min.z() - ray.origin().z()) / ray.direction().z();
        p      = ray.origin() + ray.direction() * length;
        if (p.x() >= _min.x() && p.x() <= _max.x() && p.y() >= _min.y() && p.y() <= _max.y())
            intersectFace[1] = true;
    }

    // Check if the ray is not parallel to the XZ plane
    if (ray.direction().y() != 0.0)
    {
        // Same for up plane:
        double length = (_max.y() - ray.origin().y()) / ray.direction().y();
        Point  p      = ray.origin() + ray.direction() * length;
        if (p.x() >= _min.x() && p.x() <= _max.x() && p.z() >= _min.z() && p.z() <= _max.z())
            intersectFace[2] = true;

        // Same for down plane:
        length = (_min.y() - ray.origin().y()) / ray.direction().y();
        p      = ray.origin() + ray.direction() * length;
        if (p.x() >= _min.x() && p.x() <= _max.x() && p.z() >= _min.z() && p.z() <= _max.z())
            intersectFace[3] = true;
    }

    // Check if the ray is not parallel to the YZ plane
    if (ray.direction().x() != 0.0)
    {
        // Same for right plane:
        double length = (_max.x() - ray.origin().x()) / ray.direction().x();
        Point  p      = ray.origin() + ray.direction() * length;
        if (p.y() >= _min.y() && p.y() <= _max.y() && p.z() >= _min.z() && p.z() <= _max.z())
            intersectFace[4] = true;

        // Same for left plane:
        length = (_min.x() - ray.origin().x()) / ray.direction().x();
        p      = ray.origin() + ray.direction() * length;
        if (p.y() >= _min.y() && p.y() <= _max.y() && p.z() >= _min.z() && p.z() <= _max.z())
            intersectFace[5] = true;
    }

    intersectFace[6] = intersectFace[0] || intersectFace[1] || intersectFace[2] || intersectFace[3] || intersectFace[4] || intersectFace[5];


    return intersectFace[6];
}
