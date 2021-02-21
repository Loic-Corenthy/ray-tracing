//===============================================================================================//
/*!
 *  \file      CubeMap.cpp
 *  \author    Loïc Corenthy
 *  \version   1.1
 *  \date      14/10/2012
 *  \copyright (c) 2012 Loïc Corenthy. All rights reserved.
 */
//===============================================================================================//

#include "CubeMap.hpp"

#include <memory>
#include <tuple>

#include "Color.hpp"
#include "Image.hpp"
#include "Point.hpp"
#include "Ray.hpp"

using std::make_tuple;
using std::make_unique;
using std::move;
using std::tuple;

using LCNS::Color;
using LCNS::CubeMap;
using LCNS::Image;
using LCNS::Point;
using LCNS::Ray;

CubeMap::CubeMap(void)
: _center(0.0)
{
    // At most 6 images per cube
    _images.reserve(6);
}

CubeMap::CubeMap(const Point& center, double size)
: _center(center)
, _size(size)
{
    // At most 6 images per cube
    _images.reserve(6);
}

void CubeMap::addImage(Faces face, const std::string& path)
{
    auto image = make_unique<Image>(path);
    _images.push_back(move(image));

    setLink(face, static_cast<unsigned int>(_images.size() - 1));
}

void CubeMap::setLink(Faces face, unsigned int imageIdx)
{
    _faceImageIDs[face] = imageIdx;
}

Color CubeMap::colorAt(const Ray& ray)
{
    // Get the face intersecting with the ray (in the cubemap) as well as
    // the coordinates of the intersection
    auto [face, i, j] = _intersect(ray);

    // Get the index corresponding to the face
    auto imageIdx = _faceImageIDs[face];

    return _images[imageIdx]->pixelColor(i, j);
}

void CubeMap::center(const Point& center) noexcept
{
    _center = center;
}

void CubeMap::size(double size) noexcept
{
    _size = size;
}

Point CubeMap::center(void) const noexcept
{
    return _center;
}

double CubeMap::size(void) const noexcept
{
    return _size;
}

Image::InterpolationMethod CubeMap::interpolationMethod(void) const
{
    return _images[0]->interpolation();
}

void CubeMap::interpolationMethod(Image::InterpolationMethod value) noexcept
{
    for (auto& it : _images)
        it->interpolation(value);
}

tuple<CubeMap::Faces, double, double> CubeMap::_intersect(const Ray& ray) const
{
    double radius  = _size * 0.5;
    double invSize = 1.0 / _size;
    Vector max(_center.x() + radius, _center.y() + radius, _center.z() + radius);
    Vector min(_center.x() - radius, _center.y() - radius, _center.z() - radius);

    // Need to add/substract an epsilon value to min and max because of numerical error when comparing them with p coordinate values.
    const Vector epsilon(0.00001);

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
            return make_tuple(Faces::FRONT, (p.x() - min.x()) * invSize, (p.y() - min.y()) * invSize);
        }
    }

    if (ray.direction().z() < 0.0)
    {
        // Same for back plane:
        double length = (min.z() - ray.origin().z()) / ray.direction().z();
        Point  p      = ray.origin() + ray.direction() * length;
        if (p.x() >= min.x() && p.x() <= max.x() && p.y() >= min.y() && p.y() <= max.y())
        {
            return make_tuple(Faces::BACK, (p.x() - min.x()) * invSize, (p.y() - min.y()) * invSize);
        }
    }

    if (ray.direction().y() > 0.0)  // Check if the ray is not parallel to the XZ plane
    {
        // Same for up plane:
        double length = (max.y() - ray.origin().y()) / ray.direction().y();
        Point  p      = ray.origin() + ray.direction() * length;

        if (p.x() >= min.x() && p.x() <= max.x() && p.z() >= min.z() && p.z() <= max.z())
        {
            return make_tuple(Faces::UP, (p.x() - min.x()) * invSize, (p.z() - min.z()) * invSize);
        }
    }

    if (ray.direction().y() < 0.0)
    {
        // Same for down plane:
        double length = (min.y() - ray.origin().y()) / ray.direction().y();
        Point  p      = ray.origin() + ray.direction() * length;
        if (p.x() >= min.x() && p.x() <= max.x() && p.z() >= min.z() && p.z() <= max.z())
        {
            return make_tuple(Faces::DOWN, (p.x() - min.x()) * invSize, (p.z() - min.z()) * invSize);
        }
    }

    if (ray.direction().x() > 0.0)  // Check if the ray is not parallel to the YZ plane
    {
        // Same for right plane:
        double length = (max.x() - ray.origin().x()) / ray.direction().x();
        Point  p      = ray.origin() + ray.direction() * length;
        if (p.y() >= min.y() && p.y() <= max.y() && p.z() >= min.z() && p.z() <= max.z())
        {
            return make_tuple(Faces::RIGHT, (p.z() - min.z()) * invSize, (p.y() - min.y()) * invSize);
        }
    }

    if (ray.direction().x() < 0.0)
    {
        // Same for left plane:
        double length = (min.x() - ray.origin().x()) / ray.direction().x();
        Point  p      = ray.origin() + ray.direction() * length;
        if (p.y() >= min.y() && p.y() <= max.y() && p.z() >= min.z() && p.z() <= max.z())
        {
            return make_tuple(Faces::LEFT, (p.z() - min.z()) * invSize, (p.y() - min.y()) * invSize);
        }
    }

    assert(false && "There must be an intersection, impossible to arrive here!!");
    return make_tuple(Faces::UNASSIGNED, 0.0, 0.0);
}
