#include "Triangle.hpp"

// Local includes
#include "Ray.hpp"
#include "Color.hpp"
#include "Scene.hpp"
#include "Shader.hpp"

using namespace MatouMalin;

Triangle::Triangle(void)
:_normal(Vector(0.0,0.0,0.0))
{
	_vertice[0] = Point(0.0);
	_vertice[1] = Point(0.0);
	_vertice[2] = Point(0.0);

    _vertexNormal[0] = Vector(0.0);
    _vertexNormal[1] = Vector(0.0);
    _vertexNormal[2] = Vector(0.0);

}

Triangle::Triangle(const Point & pPoint0,const Point & pPoint1,const Point & pPoint2)
{
	_vertice[0] = pPoint0;
	_vertice[1] = pPoint1;
	_vertice[2] = pPoint2;

    _vertexNormal[0] = Vector(0.0);
    _vertexNormal[1] = Vector(0.0);
    _vertexNormal[2] = Vector(0.0);

    updateNormal();
}

Triangle::Triangle(const Triangle & pTriangle)
{
	_vertice[0] = pTriangle._vertice[0];
	_vertice[1] = pTriangle._vertice[1];
	_vertice[2] = pTriangle._vertice[2];

    _vertexNormal[0] = pTriangle._vertexNormal[0];
    _vertexNormal[1] = pTriangle._vertexNormal[1];
    _vertexNormal[2] = pTriangle._vertexNormal[2];

    _normal = pTriangle._normal;
}

Triangle::~Triangle(void)
{
}

void Triangle::updateNormal(void)
{
	Vector lAB(_vertice[1] - _vertice[0]);
	Vector lAC(_vertice[2] - _vertice[0]);

	_normal = lAB^lAC;
    _normal.normalize();
}

bool Triangle::intersect(Ray & pRay)
{
    double lScalarProd = pRay.direction()*_normal;

    // Check if ray is not parallel to triangle
    if (lScalarProd != 0.0)
    {
        Vector lPointInTriangle(_vertice[0][0],_vertice[0][1],_vertice[0][2]);
        Vector lOrigin(pRay.origin().x(),pRay.origin().y(),pRay.origin().z());

        // Calculate coeffient in the equation of the plane containing the triangle
        double lD = (_normal*lPointInTriangle)*(-1.0);

        // Calculate the lenght the ray when intersecting the plane
        double lLength = (-1.0)*(lOrigin*_normal + lD)/(lScalarProd);

        // Calculate the coordinates of the intersection point
        Point lP = pRay.origin() + pRay.direction()*lLength;

        // Check if the point in the plane is really inside the triangle
        Vector lAB = _vertice[1] - _vertice[0];
        Vector lBC = _vertice[2] - _vertice[1];
        Vector lCA = _vertice[0] - _vertice[2];

        Vector lAP = lP - _vertice[0];
        Vector lBP = lP - _vertice[1];
        Vector lCP = lP - _vertice[2];

        if( (lAB^lAP)*_normal >= 0.0 && (lBC^lBP)*_normal >= 0.0 && (lCA^lCP)*_normal >= 0.0 && lLength > 0.0)
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

	return (_shader->color(pRay.direction()*(-1),lNormalAtPt,pRay.intersection(),this,pReflectionCount));
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
    Vector lAB(_vertice[1] - _vertice[0]);
	Vector lAC(_vertice[2] - _vertice[0]);

	Vector lNormal = lAB^lAC;
    double lInvNormalLengthSqr = 1.0/(lNormal*lNormal);

    double lAlpha = lNormal*((_vertice[2] - _vertice[1])^(pPositionInTriangle - _vertice[1]));
    lAlpha *= lInvNormalLengthSqr;

    double lBeta = lNormal*((_vertice[0] - _vertice[2])^(pPositionInTriangle - _vertice[2]));
    lBeta *= lInvNormalLengthSqr;

    double lGamma = 1.0 - lAlpha - lBeta;

    assert(lAlpha + lBeta + lGamma > 0.999 && lAlpha + lBeta + lGamma < 1.001);

    return (_vertexNormal[0]*lAlpha + _vertexNormal[1]*lBeta + _vertexNormal[2]*lGamma);

}

