#ifndef RAYTRACING_CAMERA_H
#define RAYTRACING_CAMERA_H

// Standard includes
#include <vector>
#include <algorithm>
#include <iostream>

// Local includes
#include "Point.hpp"
#include "Buffer.hpp"
#include "Vector.hpp"
#include "Plane.hpp"

namespace LCNS
{
    class Camera
    {
    public:
        enum Aperture : unsigned short
        {
            ALL_SHARP,
            F_SMALL,
            F_MEDIUM,
            F_BIG
        };
        enum Precision : unsigned short
        {
            LOW           = 1,
            MEDIUM        = 2,
            HIGH          = 3,
            EXCELLENT     = 4,
            SUPER_AWESOME = 5
        };

    public:
        /// Default constructor
        Camera(void);

        /// Constructor with parameters
        Camera(Point position, Vector direction, Vector up, float fOV);

        /// Copy constructor
        Camera(const Camera& camera);

        /// Copy operator
        Camera operator=(const Camera& camera);

        /// Destructor
        ~Camera(void);

        /// Get the direction of a pixel in the buffer
        template <typename NumType>
        Vector pixelDirection(NumType x, NumType y, Buffer* buffer) const;

        /// Set the position of the camera
        void setPosition(const Point& position);

        /// Set the direction of the camera
        void setDirection(const Vector& direction);

        /// Set the upward direction of the camera
        void setUp(const Vector& up);

        /// Set the field of view of the camera
        void setFOV(float fOV);

        /// Set the aperture type of the camera. If not using the ALL_SHARP mode, specify the focal length (distance between the focal plane and the
        /// buffer
        void setAperture(unsigned short mode, unsigned short precision = LOW, double focalLength = 0.0);

        /// Set the focal length
        void setFocalLength(double focalLength);

        /// Set the point contained by the focal plane
        void setFocalPoint(const Point& focalPoint);

        /// Get the position of the camera (read only)
        const Point& position(void) const;

        /// Get the direction of the camera (read only)
        const Vector& direction(void) const;

        /// Get the upward direction of the camera (read only)
        const Vector& up(void) const;

        /// Get the field of view of the camera
        float FOV(void) const;

        /// Get the aperture mode
        unsigned short aperture(void) const;

        /// Get the radius of the matrix superposed on a pixel to simulate the aperture
        double apertureRadius(void) const;

        /// Get the displacement step in the matrix
        double apertureStep(void) const;

        /// Get the coefficent corresponding to the color sampling when simulating the aperture
        float apertureColorCoeff(double i, double j) const;

        /// Get the focal length
        double focalLength(void) const;

        /// Get the focal plane
        Plane& focalPlane(void);

    private:
        Plane              _focalPlane;
        std::vector<float> _apertureColorCoeffs;
        double             _apertureRadius;
        double             _apertureStep;
        Point              _position;
        Vector             _direction;
        Vector             _up;
        Vector             _right;
        float              _fOV;
        unsigned short     _aperture;
        double             _focalLength;
        double             _apertureStepMultiplier;

    };  // class Camera

    template <typename NumType>
    Vector Camera::pixelDirection(NumType x, NumType y, Buffer* buffer) const
    {
        Vector pixelDirection(0.0, 0.0, 0.0);

        float rightValue = (2 * tan(_fOV / 2) / (buffer->width())) * (buffer->width() / 2.f - x);
        float upValue    = (2 * tan(_fOV / 2) / (buffer->width())) * (y - buffer->height() / 2.f);

        pixelDirection = _right * rightValue + _up * upValue + _direction;

        return pixelDirection;
    }

    inline void Camera::setPosition(const Point& position)
    {
        _position = position;
    }

    inline void Camera::setFOV(float fOV)
    {
        _fOV = fOV;
    }

    inline void Camera::setFocalLength(double focalLength)
    {
        _focalLength = focalLength;
    }

    inline void Camera::setFocalPoint(const Point& focalPoint)
    {
        _focalPlane.setPosition(focalPoint);
    }

    inline const Point& Camera::position(void) const
    {
        return _position;
    }

    inline const Vector& Camera::direction(void) const
    {
        return _direction;
    }

    inline const Vector& Camera::up(void) const
    {
        return _up;
    }

    inline float Camera::FOV(void) const
    {
        return _fOV;
    }

    inline unsigned short Camera::aperture(void) const
    {
        return _aperture;
    }

    inline double Camera::apertureRadius(void) const
    {
        return _apertureRadius;
    }

    inline double Camera::apertureStep(void) const
    {
        return _apertureStep;
    }

    inline float Camera::apertureColorCoeff(double i, double j) const
    {
        static double slCoeffCount = _apertureStepMultiplier * 2.0 + 1.0;
        return _apertureColorCoeffs[static_cast<unsigned int>((i / _apertureStep + _apertureStepMultiplier) * slCoeffCount + j / _apertureStep
                                                              + _apertureStepMultiplier)];
    }

    inline double Camera::focalLength(void) const
    {
        return _focalLength;
    }

    inline Plane& Camera::focalPlane(void)
    {
        return _focalPlane;
    }
}  // namespace LCNS

#endif
