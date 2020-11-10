#include "Camera.hpp"

#include <cmath>

using namespace MatouMalin;

Camera::Camera(void)
:_focalPlane(),
 _position(0.0,0.0,0.0),
 _direction(0.0,0.0,0.0),
 _up(0.0,0.0,0.0),
 _right(0.0,0.0,0.0),
 _fOV(0.0),
 _aperture(ALL_SHARP),
 _focalLength(1.0),
 _apertureStepMultiplier(1.0)
{
}

Camera::Camera(Point pPosition,Vector pDirection,Vector pUp,float pFOV)
:_focalPlane(pDirection*(-1),pPosition + (pDirection*5.0f)),
 _position(pPosition),
 _direction(pDirection),
 _up(pUp),
 _fOV(pFOV),
 _aperture(ALL_SHARP),
 _focalLength(1.0),
 _apertureStepMultiplier(1.0)
{
    _right = _up^_direction;
	_up = _direction^_right;
}

Camera::Camera(const Camera & pCamera)
:_focalPlane(pCamera._focalPlane),
 _position(pCamera._position),
 _direction(pCamera._direction),
 _up(pCamera._up),
 _right(pCamera._right),
 _fOV(pCamera._fOV),
 _aperture(pCamera._aperture),
 _focalLength(pCamera._focalLength),
 _apertureStepMultiplier(pCamera._apertureStepMultiplier)
{

}

Camera Camera::operator=(const Camera & pCamera)
{
    if(this == & pCamera)
        return *this;

    _focalPlane = pCamera._focalPlane;
    _position = pCamera._position;
	_direction = pCamera._direction;
	_up = pCamera._up;
    _right = pCamera._right;
	_fOV = pCamera._fOV;
    _aperture = pCamera._aperture;
    _focalLength = pCamera._focalLength;
    _apertureStepMultiplier = pCamera._apertureStepMultiplier;

    return *this;
}

Camera::~Camera(void)
{
}

void Camera::setDirection(const Vector & pDirection)
{
	_direction = pDirection;

    _right = _up^_direction;
	_up = _direction^_right;

    _focalPlane.setNormal(pDirection*(-1.0));
    _focalPlane.setPosition(_position + pDirection*_focalLength);
}

void Camera::setUp(const Vector & pUp)
{
	_up = pUp;

    _right = _up^_direction;
	_up = _direction^_right;
}

void Camera::setAperture(unsigned short pMode, unsigned short pPrecision, double pFocalLength)
{
    // Save parameters
    _aperture = pMode;
    _focalLength = pFocalLength;
    _apertureStepMultiplier = static_cast<double>(pPrecision);

    // Update the focal plane position
    //_focalPlane.setPosition(_position + _direction*_focalLength);

    // Calculate the coefficients for the color sampling
    unsigned short lTotalCoeffCount(static_cast<unsigned short>(2.0*_apertureStepMultiplier+1.0));
    lTotalCoeffCount *= lTotalCoeffCount;

    _apertureColorCoeffs.reserve(lTotalCoeffCount);
    float lTmpTotal(0.0f);

    // Call the rand function once first to avoid a big disparity between the returned values
    rand();

    for (unsigned short i=0; i<lTotalCoeffCount; ++i)
    {
        _apertureColorCoeffs.push_back(static_cast<float>(rand()));
        lTmpTotal += _apertureColorCoeffs[i];
    }

    // Divide all the coefficients by the their sum
    float lInvSumCoeffs = 1.0f/lTmpTotal;
    for_each(_apertureColorCoeffs.begin(), _apertureColorCoeffs.end(), [lInvSumCoeffs](float & lIt){lIt *= lInvSumCoeffs;}); // (c++11)

    switch (pMode)
    {
        case F_SMALL:
            _apertureRadius = (_position - _focalPlane.position()).length()/64.0;
            break;

        case F_MEDIUM:
            _apertureRadius = (_position - _focalPlane.position()).length()/128.0;
            break;

        case F_BIG:
            _apertureRadius = (_position - _focalPlane.position()).length()/256.0;
            break;

        case ALL_SHARP:
        default:
            _apertureRadius = 0.0;
            break;
    }

    _apertureStep = _apertureRadius/_apertureStepMultiplier;

}
