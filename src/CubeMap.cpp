//
//  CubeMap.cpp
//  RayTracing
//
//  Created by Loïc CORENTHY on 10/14/12.
//
//

#include "CubeMap.hpp"

// Local includes
#include "Color.hpp"
#include "Ray.hpp"

using namespace LCNS;
using namespace std;


CubeMap::CubeMap(void)
: _center(0.0)
, _size(0.0)
, _faceImageIDs{ { UP, 0 }, { DOWN, 1 }, { LEFT, 2 }, { RIGHT, 3 }, { BACK, 4 }, { FRONT, 5 } }  // (c++11)
{
    // At most 6 images per cube
    _images.reserve(6);
}

CubeMap::CubeMap(const Point& center, double size)
: _center(center)
, _size(size)
, _faceImageIDs{ { UP, 0 }, { DOWN, 1 }, { LEFT, 2 }, { RIGHT, 3 }, { BACK, 4 }, { FRONT, 5 } }  // (c++11)
{
    // At most 6 images per cube
    _images.reserve(6);
}

CubeMap::~CubeMap(void)
{
    //    for_each(_images.begin(), _images.end(), [](vector<Image*>::iterator image){delete *image;});
    for (auto it = _images.begin(), end = _images.end(); it != end; it++)
        delete *it;
}

void CubeMap::addImage(unsigned short face, const std::string& path)
{
    Image* rImage = new Image(path);
    _images.push_back(rImage);

    setLink(face, static_cast<unsigned int>(_images.size() - 1));
}

void CubeMap::setLink(unsigned short face, unsigned int imageIdx)
{
    _faceImageIDs[face] = imageIdx;
}

Color CubeMap::colorAt(const Ray& ray)
{
    unsigned short face(UNASSIGNED);
    double         i(0.0);
    double         j(0.0);

    _intersect(ray, face, i, j);

    unsigned int imageIdx = _faceImageIDs[face];

    return _images[imageIdx]->pixelColor(i, j);
}

void CubeMap::setInterpolationMethod(unsigned short method)
{
    for (auto it = _images.begin(), end = _images.end(); it != end; it++)
        (*it)->setInterpolation(method);
}

void CubeMap::_intersect(const Ray& ray, unsigned short& face, double& i, double& j) const
{
    double radius(_size * 0.5);
    double invSize(1.0 / _size);
    Vector max(_center.x() + radius, _center.y() + radius, _center.z() + radius);
    Vector min(_center.x() - radius, _center.y() - radius, _center.z() - radius);

    // Need to add/substract an epsilon value to min and max because of numerical error when comparing them with p coordinate values.
    static Vector epsilon(0.00001);

    min -= epsilon;
    max += epsilon;

    // Check if ray is not parallel to the XY plane
    if (ray.direction().z() > 0.0)
    {
        // Front plane: Calculate the lenght the ray when intersecting the plane
        double length = (max.z() - ray.origin().z()) / ray.direction().z();

        // Front plane: Calculate the coordinates of the intersection point
        Point p = ray.origin() + ray.direction() * length;

        // Front plane: Check if the point in the plane is really inside the rectangle
        if (p.x() >= min.x() && p.x() <= max.x() && p.y() >= min.y() && p.y() <= max.y())
        {
            face = FRONT;
            i    = (p.x() - min.x()) * invSize;
            j    = (p.y() - min.y()) * invSize;
            return;
        }
    }

    if (ray.direction().z() < 0.0)
    {
        // Same for back plane:
        double length = (min.z() - ray.origin().z()) / ray.direction().z();
        Point  p      = ray.origin() + ray.direction() * length;
        if (p.x() >= min.x() && p.x() <= max.x() && p.y() >= min.y() && p.y() <= max.y())
        {
            face = BACK;
            i    = (p.x() - min.x()) * invSize;
            j    = (p.y() - min.y()) * invSize;
            return;
        }
    }

    if (ray.direction().y() > 0.0)  // Check if the ray is not parallel to the XZ plane
    {
        // Same for up plane:
        double length = (max.y() - ray.origin().y()) / ray.direction().y();
        Point  p      = ray.origin() + ray.direction() * length;

        if (p.x() >= min.x() && p.x() <= max.x() && p.z() >= min.z() && p.z() <= max.z())
        {
            face = UP;
            i    = (p.x() - min.x()) * invSize;
            j    = (p.z() - min.z()) * invSize;
            return;
        }
    }

    if (ray.direction().y() < 0.0)
    {
        // Same for down plane:
        double length = (min.y() - ray.origin().y()) / ray.direction().y();
        Point  p      = ray.origin() + ray.direction() * length;
        if (p.x() >= min.x() && p.x() <= max.x() && p.z() >= min.z() && p.z() <= max.z())
        {
            face = DOWN;
            i    = (p.x() - min.x()) * invSize;
            j    = (p.z() - min.z()) * invSize;
            return;
        }
    }

    if (ray.direction().x() > 0.0)  // Check if the ray is not parallel to the YZ plane
    {
        // Same for right plane:
        double length = (max.x() - ray.origin().x()) / ray.direction().x();
        Point  p      = ray.origin() + ray.direction() * length;
        if (p.y() >= min.y() && p.y() <= max.y() && p.z() >= min.z() && p.z() <= max.z())
        {
            face = RIGHT;
            i    = (p.z() - min.z()) * invSize;
            j    = (p.y() - min.y()) * invSize;
            return;
        }
    }

    if (ray.direction().x() < 0.0)
    {
        // Same for left plane:
        double length = (min.x() - ray.origin().x()) / ray.direction().x();
        Point  p      = ray.origin() + ray.direction() * length;
        if (p.y() >= min.y() && p.y() <= max.y() && p.z() >= min.z() && p.z() <= max.z())
        {
            face = LEFT;
            i    = (p.z() - min.z()) * invSize;
            j    = (p.y() - min.y()) * invSize;
            return;
        }
    }

    int STOP = 42;
    STOP++;

    assert(false && "There must be an intersection, impossible to arrive here!!");
}
