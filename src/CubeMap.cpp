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

using namespace MatouMalin;
using namespace std;


CubeMap::CubeMap(void)
:_center(0.0),
 _size(0.0),
 _faceImageIDs{{UP,0},{DOWN,1},{LEFT,2},{RIGHT,3},{BACK,4},{FRONT,5}} // (c++11)
{
    // At most 6 images per cube
    _images.reserve(6);
}

CubeMap::CubeMap(const Point & center, double size)
:_center(center),
 _size(size),
 _faceImageIDs{{UP,0},{DOWN,1},{LEFT,2},{RIGHT,3},{BACK,4},{FRONT,5}} // (c++11)
{
    // At most 6 images per cube
    _images.reserve(6);
}

CubeMap::~CubeMap(void)
{
//    for_each(_images.begin(), _images.end(), [](vector<Image*>::iterator image){delete *image;});
    for (auto lIt = _images.begin(), lEnd = _images.end(); lIt != lEnd; lIt++)
        delete *lIt;

}

void CubeMap::addImage(unsigned short face, const std::string & path)
{
    Image* rImage = new Image(path);
    _images.push_back(rImage);

    setLink(face, static_cast<unsigned int>(_images.size()-1));
}

void CubeMap::setLink(unsigned short face, unsigned int imageIdx)
{
    _faceImageIDs[face] = imageIdx;
}

Color CubeMap::colorAt(const Ray & ray)
{
    unsigned short lFace(UNASSIGNED);
    double lI(0.0);
    double lJ(0.0);

    _intersect(ray, lFace, lI, lJ);

    unsigned int lImageIdx = _faceImageIDs[lFace];

    return _images[lImageIdx]->pixelColor(lI,lJ);
}

void CubeMap::setInterpolationMethod(unsigned short method)
{
    for (auto lIt = _images.begin(), lEnd = _images.end(); lIt != lEnd; lIt++)
        (*lIt)->setInterpolation(method);
}

void CubeMap::_intersect(const Ray & ray, unsigned short & face, double & i, double & j) const
{
    double lRadius(_size*0.5);
    double lInvSize(1.0/_size);
    Vector lMax(_center.x()+lRadius, _center.y()+lRadius, _center.z()+lRadius);
    Vector lMin(_center.x()-lRadius, _center.y()-lRadius, _center.z()-lRadius);

    // Need to add/substract an epsilon value to min and max because of numerical error when comparing them with lP coordinate values.
    static Vector lEpsilon(0.00001);

    lMin -= lEpsilon;
    lMax += lEpsilon;

    // Check if ray is not parallel to the XY plane
    if (ray.direction().z() > 0.0)
    {
        // Front plane: Calculate the lenght the ray when intersecting the plane
        double lLength = (lMax.z() - ray.origin().z())/ray.direction().z();

        // Front plane: Calculate the coordinates of the intersection point
        Point lP = ray.origin() + ray.direction()*lLength;

        // Front plane: Check if the point in the plane is really inside the rectangle
        if(lP.x() >= lMin.x() && lP.x() <= lMax.x() && lP.y() >= lMin.y() && lP.y() <= lMax.y())
        {
            face = FRONT;
            i = (lP.x() - lMin.x())*lInvSize;
            j = (lP.y() - lMin.y())*lInvSize;
            return;
        }
    }

    if (ray.direction().z() < 0.0)
    {
        // Same for back plane:
        double lLength = (lMin.z() - ray.origin().z())/ray.direction().z();
        Point lP = ray.origin() + ray.direction()*lLength;
        if(lP.x() >= lMin.x() && lP.x() <= lMax.x() && lP.y() >= lMin.y() && lP.y() <= lMax.y())
        {
            face = BACK;
            i = (lP.x() - lMin.x())*lInvSize;
            j = (lP.y() - lMin.y())*lInvSize;
            return;
        }

    }

    if (ray.direction().y() > 0.0) // Check if the ray is not parallel to the XZ plane
    {
        // Same for up plane:
        double lLength = (lMax.y() - ray.origin().y())/ray.direction().y();
        Point lP = ray.origin() + ray.direction()*lLength;

        if(lP.x() >= lMin.x() && lP.x() <= lMax.x() &&  lP.z() >= lMin.z() && lP.z() <= lMax.z())
        {
            face = UP;
            i = (lP.x() - lMin.x())*lInvSize;
            j = (lP.z() - lMin.z())*lInvSize;
            return;
        }
    }

    if (ray.direction().y() < 0.0)
    {
        // Same for down plane:
        double lLength = (lMin.y() - ray.origin().y())/ray.direction().y();
        Point lP = ray.origin() + ray.direction()*lLength;
        if(lP.x() >= lMin.x() && lP.x() <= lMax.x() && lP.z() >= lMin.z() && lP.z() <= lMax.z())
        {
            face = DOWN;
            i = (lP.x() - lMin.x())*lInvSize;
            j = (lP.z() - lMin.z())*lInvSize;
            return;
        }
    }

    if (ray.direction().x() > 0.0) // Check if the ray is not parallel to the YZ plane
    {
        // Same for right plane:
        double lLength = (lMax.x() - ray.origin().x())/ray.direction().x();
        Point lP = ray.origin() + ray.direction()*lLength;
        if(lP.y() >= lMin.y() && lP.y() <= lMax.y() && lP.z() >= lMin.z() && lP.z() <= lMax.z())
        {
            face = RIGHT;
            i = (lP.z() - lMin.z())*lInvSize;
            j = (lP.y() - lMin.y())*lInvSize;
            return;
        }
    }

    if (ray.direction().x() < 0.0)
    {
        // Same for left plane:
        double lLength = (lMin.x() - ray.origin().x())/ray.direction().x();
        Point lP = ray.origin() + ray.direction()*lLength;
        if(lP.y() >= lMin.y() && lP.y() <= lMax.y() && lP.z() >= lMin.z() && lP.z() <= lMax.z())
        {
            face = LEFT;
            i = (lP.z() - lMin.z())*lInvSize;
            j = (lP.y() - lMin.y())*lInvSize;
            return;
        }

    }

    int STOP = 42;
    STOP++;

    assert(false && "There must be an intersection, impossible to arrive here!!");
}



