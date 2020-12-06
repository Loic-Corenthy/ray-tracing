//===============================================================================================//
/*!
 *  \file      Camera.cpp
 *  \author    Loïc Corenthy
 *  \version   1.0
 *  \date      14/10/2012
 *  \copyright (c) 2012 Loïc Corenthy. All rights reserved.
 */
//===============================================================================================//

#include "Camera.hpp"
#include "Plane.hpp"
#include "Point.hpp"
#include "Vector.hpp"

#include <random>
#include <cmath>
#include <limits>

using std::mt19937;
using std::numeric_limits;
using std::random_device;
using std::uniform_real_distribution;

using LCNS::Camera;
using LCNS::Plane;
using LCNS::Point;
using LCNS::Vector;

Camera::Camera(const Point& position, const Vector& direction, const Vector& up, double fOV)
: _focalPlane(direction * (-1), position + (direction * 5.0f))
, _position(position)
, _direction(direction)
, _up(up)
, _aperture(Aperture::ALL_SHARP)
, _fOV(fOV)
{
    _right = _up ^ _direction;
    _up    = _direction ^ _right;
}

Camera::Camera(const Camera& camera)
: _focalPlane(camera._focalPlane)
, _position(camera._position)
, _direction(camera._direction)
, _up(camera._up)
, _right(camera._right)
, _apertureColorCoeffs(camera._apertureColorCoeffs)
, _apertureRadius(camera._apertureRadius)
, _apertureStep(camera._apertureStep)
, _apertureStepMultiplier(camera._apertureStepMultiplier)
, _focalLength(camera._focalLength)
, _aperture(camera._aperture)
, _fOV(camera._fOV)
{
}

Camera& Camera::operator=(const Camera& camera)
{
    if (this == &camera)
        return *this;

    _focalPlane             = camera._focalPlane;
    _position               = camera._position;
    _direction              = camera._direction;
    _up                     = camera._up;
    _right                  = camera._right;
    _fOV                    = camera._fOV;
    _aperture               = camera._aperture;
    _focalLength            = camera._focalLength;
    _apertureStepMultiplier = camera._apertureStepMultiplier;

    return *this;
}

Vector Camera::pixelDirection(double x, double y, const Buffer& buffer) const
{
    const auto rightValue = (2.0 * tan(_fOV / 2.0) / (buffer.width())) * (buffer.width() / 2.0 - x);
    const auto upValue    = (2.0 * tan(_fOV / 2.0) / (buffer.width())) * (y - buffer.height() / 2.0);

    return _right * rightValue + _up * upValue + _direction;
}

void Camera::direction(const Vector& direction)
{
    _direction = direction;

    _right = _up ^ _direction;
    _up    = _direction ^ _right;

    _focalPlane.normal(direction * (-1.0));
    _focalPlane.position(_position + direction * _focalLength);
}

void Camera::up(const Vector& up)
{
    _up = up;

    _right = _up ^ _direction;
    _up    = _direction ^ _right;
}

void Camera::aperture(Aperture mode, Precision precision, double focalLength)
{
    // Save parameters
    _aperture               = mode;
    _focalLength            = focalLength;
    _apertureStepMultiplier = static_cast<double>(precision);

    // Calculate the coefficients for the color sampling
    auto totalCoeffCount = static_cast<size_t>(2.0 * _apertureStepMultiplier + 1.0);
    totalCoeffCount *= totalCoeffCount;

    _apertureColorCoeffs.reserve(totalCoeffCount);
    double sumCoefficients = 0.0f;

    // Setup random number generator
    std::random_device             rd;               // Will be used to obtain a seed for the random number engine
    std::mt19937                   generator(rd());  // Standard mersenne_twister_engine seeded with rd()
    std::uniform_real_distribution distribution(1.0, static_cast<double>(numeric_limits<int>::max()));

    for (unsigned short i = 0; i < totalCoeffCount; ++i)
    {
        const double randomNumber = distribution(generator);
        _apertureColorCoeffs.push_back(randomNumber);
        sumCoefficients += _apertureColorCoeffs[i];
    }

    // Divide all the coefficients by the their sum
    for (auto& coeff : _apertureColorCoeffs)
    {
        coeff /= sumCoefficients;
    }

    switch (mode)
    {
        case Aperture::F_SMALL:
            _apertureRadius = (_position - _focalPlane.position()).length() / 64.0;
            break;

        case Aperture::F_MEDIUM:
            _apertureRadius = (_position - _focalPlane.position()).length() / 128.0;
            break;

        case Aperture::F_BIG:
            _apertureRadius = (_position - _focalPlane.position()).length() / 256.0;
            break;

        case Aperture::ALL_SHARP:
        default:
            _apertureRadius = 0.0;
            break;
    }

    _apertureStep = _apertureRadius / _apertureStepMultiplier;
}

void Camera::position(const Point& position) noexcept
{
    _position = position;
}

void Camera::FOV(double fOV) noexcept
{
    _fOV = fOV;
}

void Camera::focalLength(double focalLength) noexcept
{
    _focalLength = focalLength;
}

void Camera::focalPoint(const Point& focalPoint)
{
    _focalPlane.position(focalPoint);
}

const Point& Camera::position(void) const noexcept
{
    return _position;
}

const Vector& Camera::direction(void) const noexcept
{
    return _direction;
}

const Vector& Camera::up(void) const noexcept
{
    return _up;
}

double Camera::FOV(void) const noexcept
{
    return _fOV;
}

Camera::Aperture Camera::aperture(void) const noexcept
{
    return _aperture;
}

double Camera::apertureRadius(void) const noexcept
{
    return _apertureRadius;
}

double Camera::apertureStep(void) const noexcept
{
    return _apertureStep;
}

double Camera::apertureColorCoeff(double i, double j) const
{
    static double slCoeffCount = _apertureStepMultiplier * 2.0 + 1.0;
    return _apertureColorCoeffs[static_cast<unsigned int>((i / _apertureStep + _apertureStepMultiplier) * slCoeffCount + j / _apertureStep
                                                          + _apertureStepMultiplier)];
}

double Camera::focalLength(void) const noexcept
{
    return _focalLength;
}

Plane& Camera::focalPlane(void) noexcept
{
    return _focalPlane;
}
