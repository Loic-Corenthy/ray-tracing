#ifndef RAYTRACING_CAMERA_H
#define RAYTRACING_CAMERA_H

// Standard includes
#include <vector>
#include <algorithm>
#include <iostream>

// Local includes
#include "Point.h"
#include "Buffer.h"
#include "Vector.h"
#include "Plane.h"

namespace MatouMalin 
{
    class Camera
    {
    public:
        enum Aperture : unsigned short {ALL_SHARP, F_SMALL, F_MEDIUM, F_BIG};
        enum Precision: unsigned short {LOW = 1, MEDIUM = 2, HIGH = 3, EXCELLENT = 4, SUPER_AWESOME = 5};
        
    public:
        /// Default constructor
        Camera(void);
        
        /// Constructor with parameters
        Camera(Point pPosition,Vector pDirection,Vector pUp,float pFOV);
        
        /// Copy constructor
        Camera(const Camera & pCamera);
        
        /// Copy operator
        Camera operator=(const Camera & pCamera);
        
        /// Destructor
        ~Camera(void);
        
        /// Get the direction of a pixel in the buffer
        template<typename NumType>
        Vector pixelDirection(NumType pX, NumType pY,Buffer* pBuffer) const;
        
        /// Set the position of the camera
        void setPosition(const Point & pPosition);
        
        /// Set the direction of the camera
        void setDirection(const Vector & pDirection);
        
        /// Set the upward direction of the camera
        void setUp(const Vector & pUp);
        
        /// Set the field of view of the camera
        void setFOV(float pFOV);
        
        /// Set the aperture type of the camera. If not using the ALL_SHARP mode, specify the focal length (distance between the focal plane and the buffer
        void setAperture(unsigned short pMode, unsigned short pPrecision = LOW, double pFocalLength = 0.0);
        
        /// Set the focal length
        void setFocalLength(double pFocalLength);
        
        /// Set the point contained by the focal plane
        void setFocalPoint(const Point & pFocalPoint);
        
        /// Get the position of the camera (read only)
        const Point & position(void) const;
        
        /// Get the direction of the camera (read only)
        const Vector & direction(void) const;
        
        /// Get the upward direction of the camera (read only)
        const Vector & up(void) const;
        
        /// Get the field of view of the camera
        float FOV(void) const;
        
        /// Get the aperture mode
        unsigned short aperture(void) const;
        
        /// Get the radius of the matrix superposed on a pixel to simulate the aperture
        double apertureRadius(void) const;
        
        /// Get the displacement step in the matrix
        double apertureStep(void) const;
        
        /// Get the coefficent corresponding to the color sampling when simulating the aperture
        float apertureColorCoeff(double pI, double pJ) const;
        
        /// Get the focal length
        double focalLength(void) const;
        
        /// Get the focal plane 
        Plane & focalPlane(void);
        
    private:
        Plane               mFocalPlane;
        std::vector<float>  mApertureColorCoeffs;
        double              mApertureRadius;
        double              mApertureStep;
        Point               mPosition;
        Vector              mDirection;
        Vector              mUp;
        Vector              mRight;
        float               mFOV;
        unsigned short      mAperture;
        double              mFocalLength;
        double              mApertureStepMultiplier;

    }; // class Camera
    
    template <typename NumType>
    Vector Camera::pixelDirection(NumType pX,NumType pY,Buffer* pBuffer) const
    {
        Vector lPixelDirection(0.0,0.0,0.0);
        
        float lRightValue = (2*tan(mFOV/2)/(pBuffer->width()))*(pBuffer->width()/2.f - pX);
        float lUpValue= (2*tan(mFOV/2)/(pBuffer->width()))*(pY - pBuffer->height()/2.f);
        
        lPixelDirection = mRight*lRightValue + mUp*lUpValue + mDirection;
        
        return lPixelDirection;
    }

    inline void Camera::setPosition(const Point & pPosition)
    {
        mPosition = pPosition;
    }
    
    inline void Camera::setFOV(float pFOV)
    {
        mFOV = pFOV;
    }
    
    inline void Camera::setFocalLength(double pFocalLength)
    {
        mFocalLength = pFocalLength;
    }
    
    inline void Camera::setFocalPoint(const Point &pFocalPoint)
    {
        mFocalPlane.setPosition(pFocalPoint);
    }
    
    inline const Point & Camera::position(void) const
    {
        return mPosition;
    }

    inline const Vector & Camera::direction(void) const
    {
        return mDirection;
    }
    
    inline const Vector & Camera::up(void) const
    {
        return mUp;
    }
    
    inline float Camera::FOV(void) const
    {
        return mFOV;
    }
    
    inline unsigned short Camera::aperture(void) const
    {
        return mAperture;
    }

    inline double Camera::apertureRadius(void) const
    {
        return mApertureRadius;
    }
    
    inline double Camera::apertureStep(void) const
    {
        return mApertureStep;
    }
    
    inline float Camera::apertureColorCoeff(double pI, double pJ) const
    {
        static double slCoeffCount = mApertureStepMultiplier*2.0+1.0;   
        return mApertureColorCoeffs[static_cast<unsigned int>((pI/mApertureStep + mApertureStepMultiplier)*slCoeffCount + pJ/mApertureStep + mApertureStepMultiplier)];
    }
    
    inline double Camera::focalLength(void) const
    {
        return mFocalLength;
    }
    
    inline Plane & Camera::focalPlane(void)
    {
        return mFocalPlane;
    }
} // namespace MatouMalin 

#endif
