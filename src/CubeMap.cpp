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

CubeMap::CubeMap(const Point & pCenter, double pSize)
:_center(pCenter),
 _size(pSize),
 _faceImageIDs{{UP,0},{DOWN,1},{LEFT,2},{RIGHT,3},{BACK,4},{FRONT,5}} // (c++11)
{
    // At most 6 images per cube
    _images.reserve(6);
}

CubeMap::~CubeMap(void)
{
//    for_each(_images.begin(), _images.end(), [](vector<Image*>::iterator pImage){delete *pImage;});
    for (auto lIt = _images.begin(), lEnd = _images.end(); lIt != lEnd; lIt++)
        delete *lIt;

}

void CubeMap::addImage(unsigned short pFace, const std::string & pPath)
{
    Image* rImage = new Image(pPath);
    _images.push_back(rImage);

    setLink(pFace, static_cast<unsigned int>(_images.size()-1));
}

void CubeMap::setLink(unsigned short pFace, unsigned int pImageIdx)
{
    _faceImageIDs[pFace] = pImageIdx;
}

Color CubeMap::colorAt(const Ray & pRay)
{
    unsigned short lFace(UNASSIGNED);
    double lI(0.0);
    double lJ(0.0);

    _intersect(pRay, lFace, lI, lJ);

    unsigned int lImageIdx = _faceImageIDs[lFace];

    return _images[lImageIdx]->pixelColor(lI,lJ);
}

void CubeMap::setInterpolationMethod(unsigned short pMethod)
{
    for (auto lIt = _images.begin(), lEnd = _images.end(); lIt != lEnd; lIt++)
        (*lIt)->setInterpolation(pMethod);
}

void CubeMap::_intersect(const Ray & pRay, unsigned short & pFace, double & pI, double & pJ) const
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
    if (pRay.direction().z() > 0.0)
    {
        // Front plane: Calculate the lenght the ray when intersecting the plane
        double lLength = (lMax.z() - pRay.origin().z())/pRay.direction().z();

        // Front plane: Calculate the coordinates of the intersection point
        Point lP = pRay.origin() + pRay.direction()*lLength;

        // Front plane: Check if the point in the plane is really inside the rectangle
        if(lP.x() >= lMin.x() && lP.x() <= lMax.x() && lP.y() >= lMin.y() && lP.y() <= lMax.y())
        {
            pFace = FRONT;
            pI = (lP.x() - lMin.x())*lInvSize;
            pJ = (lP.y() - lMin.y())*lInvSize;
            return;
        }
    }

    if (pRay.direction().z() < 0.0)
    {
        // Same for back plane:
        double lLength = (lMin.z() - pRay.origin().z())/pRay.direction().z();
        Point lP = pRay.origin() + pRay.direction()*lLength;
        if(lP.x() >= lMin.x() && lP.x() <= lMax.x() && lP.y() >= lMin.y() && lP.y() <= lMax.y())
        {
            pFace = BACK;
            pI = (lP.x() - lMin.x())*lInvSize;
            pJ = (lP.y() - lMin.y())*lInvSize;
            return;
        }

    }

    if (pRay.direction().y() > 0.0) // Check if the ray is not parallel to the XZ plane
    {
        // Same for up plane:
        double lLength = (lMax.y() - pRay.origin().y())/pRay.direction().y();
        Point lP = pRay.origin() + pRay.direction()*lLength;

        if(lP.x() >= lMin.x() && lP.x() <= lMax.x() &&  lP.z() >= lMin.z() && lP.z() <= lMax.z())
        {
            pFace = UP;
            pI = (lP.x() - lMin.x())*lInvSize;
            pJ = (lP.z() - lMin.z())*lInvSize;
            return;
        }
    }

    if (pRay.direction().y() < 0.0)
    {
        // Same for down plane:
        double lLength = (lMin.y() - pRay.origin().y())/pRay.direction().y();
        Point lP = pRay.origin() + pRay.direction()*lLength;
        if(lP.x() >= lMin.x() && lP.x() <= lMax.x() && lP.z() >= lMin.z() && lP.z() <= lMax.z())
        {
            pFace = DOWN;
            pI = (lP.x() - lMin.x())*lInvSize;
            pJ = (lP.z() - lMin.z())*lInvSize;
            return;
        }
    }

    if (pRay.direction().x() > 0.0) // Check if the ray is not parallel to the YZ plane
    {
        // Same for right plane:
        double lLength = (lMax.x() - pRay.origin().x())/pRay.direction().x();
        Point lP = pRay.origin() + pRay.direction()*lLength;
        if(lP.y() >= lMin.y() && lP.y() <= lMax.y() && lP.z() >= lMin.z() && lP.z() <= lMax.z())
        {
            pFace = RIGHT;
            pI = (lP.z() - lMin.z())*lInvSize;
            pJ = (lP.y() - lMin.y())*lInvSize;
            return;
        }
    }

    if (pRay.direction().x() < 0.0)
    {
        // Same for left plane:
        double lLength = (lMin.x() - pRay.origin().x())/pRay.direction().x();
        Point lP = pRay.origin() + pRay.direction()*lLength;
        if(lP.y() >= lMin.y() && lP.y() <= lMax.y() && lP.z() >= lMin.z() && lP.z() <= lMax.z())
        {
            pFace = LEFT;
            pI = (lP.z() - lMin.z())*lInvSize;
            pJ = (lP.y() - lMin.y())*lInvSize;
            return;
        }

    }

    int STOP = 42;
    STOP++;

    assert(false && "There must be an intersection, impossible to arrive here!!");
}



