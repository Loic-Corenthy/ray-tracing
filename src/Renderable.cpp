#include "Renderable.hpp"

// Local includes
#include "Ray.hpp"

using namespace MatouMalin;
using namespace std;

Renderable::Renderable(void)
:mShader(nullptr),
 mName(" ")
{

}

Renderable::Renderable(const Renderable & pRenderable)
:mShader(pRenderable.mShader),
 mName(pRenderable.mName)
{

}

void Renderable::operator=(const Renderable &pRenderable)
{
    if(this == & pRenderable)
        return;
    
    mShader = pRenderable.mShader;
    mName = pRenderable.mName;

}

Renderable::~Renderable(void)
{

}

bool Renderable::_refraction(const Vector & pIncomingDirection, const Vector & pNormal, double pN1, double pN2, Vector & pRefractedDirection) const
{
    double lMinusCosTheta1 = pIncomingDirection*pNormal;
    double lN = pN1/pN2;
    
    // Test for total reflection
    double lSqrSinTheta2 = lN*lN*(1.0 - lMinusCosTheta1*lMinusCosTheta1);
    
    if (lSqrSinTheta2 > 1.0 )
    {
        return false;
    }
    else
    {
        double lCosTheta2 = sqrt(1.0 - lSqrSinTheta2);
        pRefractedDirection = (pIncomingDirection - pNormal*lMinusCosTheta1)*lN - pNormal*lCosTheta2;
        return true;
    }
}
