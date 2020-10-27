#include "Camera.h"

#include <math.h>

using namespace MatouMalin;

Camera::Camera(void)
:mFocalPlane(),
 mPosition(0.0,0.0,0.0),
 mDirection(0.0,0.0,0.0),
 mUp(0.0,0.0,0.0),
 mRight(0.0,0.0,0.0),
 mFOV(0.0),
 mAperture(ALL_SHARP),
 mFocalLength(1.0),
 mApertureStepMultiplier(1.0)
{
}

Camera::Camera(Point pPosition,Vector pDirection,Vector pUp,float pFOV)
:mFocalPlane(pDirection*(-1),pPosition + (pDirection*5.0f)),
 mPosition(pPosition),
 mDirection(pDirection),
 mUp(pUp),
 mFOV(pFOV),
 mAperture(ALL_SHARP),
 mFocalLength(1.0),
 mApertureStepMultiplier(1.0)
{
    mRight = mUp^mDirection;
	mUp = mDirection^mRight;
}

Camera::Camera(const Camera & pCamera)
:mFocalPlane(pCamera.mFocalPlane),
 mPosition(pCamera.mPosition),
 mDirection(pCamera.mDirection),
 mUp(pCamera.mUp),
 mRight(pCamera.mRight),
 mFOV(pCamera.mFOV),
 mAperture(pCamera.mAperture),
 mFocalLength(pCamera.mFocalLength),
 mApertureStepMultiplier(pCamera.mApertureStepMultiplier)
{

}

Camera Camera::operator=(const Camera & pCamera)
{
    if(this == & pCamera)
        return *this;
    
    mFocalPlane = pCamera.mFocalPlane;
    mPosition = pCamera.mPosition;
	mDirection = pCamera.mDirection;
	mUp = pCamera.mUp;
    mRight = pCamera.mRight;
	mFOV = pCamera.mFOV;
    mAperture = pCamera.mAperture;
    mFocalLength = pCamera.mFocalLength;
    mApertureStepMultiplier = pCamera.mApertureStepMultiplier;
    
    return *this;
}

Camera::~Camera(void)
{
}

void Camera::setDirection(const Vector & pDirection)
{
	mDirection = pDirection;

    mRight = mUp^mDirection;
	mUp = mDirection^mRight;

    mFocalPlane.setNormal(pDirection*(-1.0));
    mFocalPlane.setPosition(mPosition + pDirection*mFocalLength);
}

void Camera::setUp(const Vector & pUp)
{
	mUp = pUp;

    mRight = mUp^mDirection;
	mUp = mDirection^mRight;
}

void Camera::setAperture(unsigned short pMode, unsigned short pPrecision, double pFocalLength)
{
    // Save parameters
    mAperture = pMode;
    mFocalLength = pFocalLength;
    mApertureStepMultiplier = static_cast<double>(pPrecision);
    
    // Update the focal plane position
    //mFocalPlane.setPosition(mPosition + mDirection*mFocalLength);
    
    // Calculate the coefficients for the color sampling
    unsigned short lTotalCoeffCount(static_cast<unsigned short>(2.0*mApertureStepMultiplier+1.0));
    lTotalCoeffCount *= lTotalCoeffCount;
    
    mApertureColorCoeffs.reserve(lTotalCoeffCount);
    float lTmpTotal(0.0f);
    
    // Call the rand function once first to avoid a big disparity between the returned values
    rand();
    
    for (unsigned short i=0; i<lTotalCoeffCount; ++i)
    {
        mApertureColorCoeffs.push_back(static_cast<float>(rand()));
        lTmpTotal += mApertureColorCoeffs[i];
    }

    // Divide all the coefficients by the their sum
    float lInvSumCoeffs = 1.0f/lTmpTotal;
    for_each(mApertureColorCoeffs.begin(), mApertureColorCoeffs.end(), [lInvSumCoeffs](float & lIt){lIt *= lInvSumCoeffs;}); // (c++11)
    
    switch (pMode)
    {
        case F_SMALL:
            mApertureRadius = (mPosition - mFocalPlane.position()).length()/64.0;
            break;
            
        case F_MEDIUM:
            mApertureRadius = (mPosition - mFocalPlane.position()).length()/128.0;
            break;
            
        case F_BIG:
            mApertureRadius = (mPosition - mFocalPlane.position()).length()/256.0;
            break;
            
        case ALL_SHARP:
        default:
            mApertureRadius = 0.0;
            break;
    }
    
    mApertureStep = mApertureRadius/mApertureStepMultiplier;
    
}
