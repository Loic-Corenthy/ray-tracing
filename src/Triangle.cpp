#include "Triangle.hpp"

// Local includes
#include "Ray.hpp"
#include "Color.hpp"
#include "Scene.hpp"
#include "Shader.hpp"

using namespace MatouMalin;

Triangle::Triangle(void)
:mNormal(Vector(0.0,0.0,0.0))
{
	mVertice[0] = Point(0.0);
	mVertice[1] = Point(0.0);
	mVertice[2] = Point(0.0);

    mVertexNormal[0] = Vector(0.0);
    mVertexNormal[1] = Vector(0.0);
    mVertexNormal[2] = Vector(0.0);

}

Triangle::Triangle(const Point & pPoint0,const Point & pPoint1,const Point & pPoint2)
{
	mVertice[0] = pPoint0;
	mVertice[1] = pPoint1;
	mVertice[2] = pPoint2;

    mVertexNormal[0] = Vector(0.0);
    mVertexNormal[1] = Vector(0.0);
    mVertexNormal[2] = Vector(0.0);

    updateNormal();
}

Triangle::Triangle(const Triangle & pTriangle)
{
	mVertice[0] = pTriangle.mVertice[0];
	mVertice[1] = pTriangle.mVertice[1];
	mVertice[2] = pTriangle.mVertice[2];

    mVertexNormal[0] = pTriangle.mVertexNormal[0];
    mVertexNormal[1] = pTriangle.mVertexNormal[1];
    mVertexNormal[2] = pTriangle.mVertexNormal[2];

    mNormal = pTriangle.mNormal;
}

Triangle::~Triangle(void)
{
}

void Triangle::updateNormal(void)
{
	Vector lAB(mVertice[1] - mVertice[0]);
	Vector lAC(mVertice[2] - mVertice[0]);

	mNormal = lAB^lAC;
    mNormal.normalize();
}

bool Triangle::intersect(Ray & pRay)
{
    double lScalarProd = pRay.direction()*mNormal;

    // Check if ray is not parallel to triangle
    if (lScalarProd != 0.0)
    {
        Vector lPointInTriangle(mVertice[0][0],mVertice[0][1],mVertice[0][2]);
        Vector lOrigin(pRay.origin().x(),pRay.origin().y(),pRay.origin().z());

        // Calculate coeffient in the equation of the plane containing the triangle
        double lD = (mNormal*lPointInTriangle)*(-1.0);

        // Calculate the lenght the ray when intersecting the plane
        double lLength = (-1.0)*(lOrigin*mNormal + lD)/(lScalarProd);

        // Calculate the coordinates of the intersection point
        Point lP = pRay.origin() + pRay.direction()*lLength;

        // Check if the point in the plane is really inside the triangle
        Vector lAB = mVertice[1] - mVertice[0];
        Vector lBC = mVertice[2] - mVertice[1];
        Vector lCA = mVertice[0] - mVertice[2];

        Vector lAP = lP - mVertice[0];
        Vector lBP = lP - mVertice[1];
        Vector lCP = lP - mVertice[2];

        if( (lAB^lAP)*mNormal >= 0.0 && (lBC^lBP)*mNormal >= 0.0 && (lCA^lCP)*mNormal >= 0.0 && lLength > 0.0)
        {
            pRay.setLength(lLength);
            pRay.setIntersected(this);
            return true;
        }
        else
            return  false;
    }
    else
        return false;

}

Color Triangle::color(Ray & pRay, unsigned int pReflectionCount)
{
    // Calculate normal from vertex normals
    Vector lNormalAtPt = _barycentricNormal(pRay.intersection());

	return (mShader->color(pRay.direction()*(-1),lNormalAtPt,pRay.intersection(),this,pReflectionCount));
}

Vector Triangle::interpolatedNormal(const MatouMalin::Point &pPosition) const
{
    return _barycentricNormal(pPosition);
}

bool Triangle::refractedRay(const Ray &pIncomingRay, Ray & pRefractedRay)
{
    assert(false && "Not implemented yet :)");
    return false;
}

Vector Triangle::_barycentricNormal(const MatouMalin::Point & pPositionInTriangle) const
{
    Vector lAB(mVertice[1] - mVertice[0]);
	Vector lAC(mVertice[2] - mVertice[0]);

	Vector lNormal = lAB^lAC;
    double lInvNormalLengthSqr = 1.0/(lNormal*lNormal);

    double lAlpha = lNormal*((mVertice[2] - mVertice[1])^(pPositionInTriangle - mVertice[1]));
    lAlpha *= lInvNormalLengthSqr;

    double lBeta = lNormal*((mVertice[0] - mVertice[2])^(pPositionInTriangle - mVertice[2]));
    lBeta *= lInvNormalLengthSqr;

    double lGamma = 1.0 - lAlpha - lBeta;

    assert(lAlpha + lBeta + lGamma > 0.999 && lAlpha + lBeta + lGamma < 1.001);

    return (mVertexNormal[0]*lAlpha + mVertexNormal[1]*lBeta + mVertexNormal[2]*lGamma);

}

