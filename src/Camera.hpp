//===============================================================================================//
/*!
 *  \file      Camera.hpp
 *  \author    Loïc Corenthy
 *  \version   1.2
 *  \date      14/10/2012
 *  \copyright (c) 2012 Loïc Corenthy. All rights reserved.
 */
//===============================================================================================//

#pragma once

#include <vector>
#include <algorithm>
#include <iostream>

#include "Point.hpp"
#include "Buffer.hpp"
#include "Vector.hpp"
#include "Plane.hpp"

namespace LCNS
{
    class Camera
    {
    public:
        enum class Aperture
        {
            ALL_SHARP,
            F_SMALL,
            F_MEDIUM,
            F_BIG
        };
        enum class Precision
        {
            LOW           = 1,
            MEDIUM        = 2,
            HIGH          = 3,
            EXCELLENT     = 4,
            SUPER_AWESOME = 5
        };

    public:
        /// Default constructor
        Camera(void) = default;

        /// Constructor with parameters
        Camera(const Point& position, const Vector& direction, const Vector& up, double fOV);

        /// Copy constructor
        Camera(const Camera& camera);

        /// Copy operator
        Camera& operator=(const Camera& camera);

        /// Destructor
        ~Camera(void) = default;

        /// Get the direction of a pixel in the buffer
        Vector pixelDirection(double x, double y, const Buffer& buffer) const;

        /// Set the position of the camera
        void position(const Point& position) noexcept;

        /// Set the direction of the camera
        void direction(const Vector& direction);

        /// Set the upward direction of the camera
        void up(const Vector& up);

        /// Set the field of view of the camera
        void FOV(double fOV) noexcept;

        /// Set the aperture type of the camera. If not using the ALL_SHARP mode, specify the focal length (distance between the focal plane and the
        /// buffer
        void aperture(Aperture mode, Precision precision = Precision::LOW, double focalLength = 0.0);

        /// Set the focal length
        void focalLength(double focalLength) noexcept;

        /// Set the point contained by the focal plane
        void focalPoint(const Point& focalPoint);

        /// Get the position of the camera (read only)
        const Point& position(void) const noexcept;

        /// Get the direction of the camera (read only)
        const Vector& direction(void) const noexcept;

        /// Get the upward direction of the camera (read only)
        const Vector& up(void) const noexcept;

        /// Get the field of view of the camera
        double FOV(void) const noexcept;

        /// Get the aperture mode
        Aperture aperture(void) const noexcept;

        /// Get the radius of the matrix superposed on a pixel to simulate the aperture
        double apertureRadius(void) const noexcept;

        /// Get the displacement step in the matrix
        double apertureStep(void) const noexcept;

        /// Get the coefficent corresponding to the color sampling when simulating the aperture
        double apertureColorCoeff(double i, double j) const;

        /// Get the focal length
        double focalLength(void) const noexcept;

        /// Get the focal plane (read/write)
        Plane& focalPlane(void) noexcept;

    private:
        Plane               _focalPlane;
        Point               _position;
        Vector              _direction;
        Vector              _up;
        Vector              _right;
        std::vector<double> _apertureColorCoeffs;
        double              _apertureRadius         = 0.0;
        double              _apertureStep           = 1.0;
        double              _apertureStepMultiplier = 1.0;
        double              _focalLength            = 1.0;
        Aperture            _aperture               = Aperture::ALL_SHARP;
        double              _fOV                    = 1.0f;

    };  // class Camera

}  // namespace LCNS
