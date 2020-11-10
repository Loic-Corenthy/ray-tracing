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

Camera::Camera(Point position,Vector direction,Vector up,float fOV)
:_focalPlane(direction*(-1),position + (direction*5.0f)),
 _position(position),
 _direction(direction),
 _up(up),
 _fOV(fOV),
 _aperture(ALL_SHARP),
 _focalLength(1.0),
 _apertureStepMultiplier(1.0)
{
    _right = _up^_direction;
	_up = _direction^_right;
}

Camera::Camera(const Camera & camera)
:_focalPlane(camera._focalPlane),
 _position(camera._position),
 _direction(camera._direction),
 _up(camera._up),
 _right(camera._right),
 _fOV(camera._fOV),
 _aperture(camera._aperture),
 _focalLength(camera._focalLength),
 _apertureStepMultiplier(camera._apertureStepMultiplier)
{

}

Camera Camera::operator=(const Camera & camera)
{
    if(this == & camera)
        return *this;

    _focalPlane = camera._focalPlane;
    _position = camera._position;
	_direction = camera._direction;
	_up = camera._up;
    _right = camera._right;
	_fOV = camera._fOV;
    _aperture = camera._aperture;
    _focalLength = camera._focalLength;
    _apertureStepMultiplier = camera._apertureStepMultiplier;

    return *this;
}

Camera::~Camera(void)
{
}

void Camera::setDirection(const Vector & direction)
{
	_direction = direction;

    _right = _up^_direction;
	_up = _direction^_right;

    _focalPlane.setNormal(direction*(-1.0));
    _focalPlane.setPosition(_position + direction*_focalLength);
}

void Camera::setUp(const Vector & up)
{
	_up = up;

    _right = _up^_direction;
	_up = _direction^_right;
}

void Camera::setAperture(unsigned short mode, unsigned short precision, double focalLength)
{
    // Save parameters
    _aperture = mode;
    _focalLength = focalLength;
    _apertureStepMultiplier = static_cast<double>(precision);

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

    switch (mode)
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
