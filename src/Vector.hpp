#ifndef RAYTRACING_VECTOR_H
#define RAYTRACING_VECTOR_H

// Standard includes
#include <cmath>
#include <cassert>

namespace MatouMalin
{
    class Vector
    {
    public:
        /// Default constructor
        Vector(void);
        
        /// Constructor with coordinates parameters
        Vector(double pX,double pY,double pZ);
        
        /// Constructor with same value for all coordinates
        Vector(double pCommonValue);
        
        /// Copy constructor
        Vector(const Vector & pVector);
        
        /// Destructor
        ~Vector(void);
        
        /// Coordinate operator (read only)
        double operator[](unsigned int pIndex) const;
        
        /// Coordinate operator (read, write)
        double & operator[](unsigned int pIndex);
        
        /// Set all coordinates at once
        void setVector(double pX,double pY,double pZ);
        
        /// Set X coordinate
        void setX(double pX);
        
        /// Set Y coordinate
        void setY(double pY);
        
        /// Set Z coordinate
        void setZ(double pZ);
        
        /// Get X coordinate
        double x(void) const;
        
        /// Get X coordinate
        double y(void) const;
        
        /// Get X coordinate
        double z(void) const;
        
        /// Copy the coordinates of a vector to another one
        Vector operator=(const Vector & pVector);
        
        /// Return the vector sum of 2 vectors
        Vector operator+(const Vector & pVector) const;
        
        /// Return the vector difference of 2 vectors
        Vector operator-(const Vector & pVector) const;
        
        /// Add a vector to the current one
        Vector operator+=(const Vector & pVector);
        
        /// Substract a vector to the current one
        Vector operator-=(const Vector & pVector);
        
        /// Multiply a vector by a scalar
        Vector operator*(double pScalar) const;
        
        /// Scalar product of 2 vectors
        double  operator*(const Vector & pVector) const;
        
        /// Dot product of 2 vectors
        Vector operator^(const Vector & pVector) const;	
        
        /// Return the length of the vector
        double length(void) const;
        
        /// Return the square length of a the vector
        double lengthSqr(void) const;
        
        /// Divide a vector by it's length and return it.
        Vector normalize(void);
        
        
    private:
        double mCoords[3];
        
    }; // class Vector
    
    inline double Vector::operator[](unsigned int pIndex) const
    {
        assert(0 <= pIndex && pIndex <= 2 && "Vector: index out of bounds");
        return mCoords[pIndex];
    }
    
    inline double & Vector::operator[](unsigned int pIndex)
    {
        assert(0 <= pIndex && pIndex <= 2 && "Vector: index out of bounds");
        return mCoords[pIndex];
    }
    
    inline void Vector::setVector(double pX,double pY,double pZ)
    {
        mCoords[0] = pX;
        mCoords[1] = pY;
        mCoords[2] = pZ;
    }
    
    inline void Vector::setX(double pX)
    {
        mCoords[0] = pX;
    }
    
    inline void Vector::setY(double pY)
    {
        mCoords[1] = pY;
    }
    
    inline void Vector::setZ(double pZ)
    {
        mCoords[2] = pZ;
    }
    
    inline double Vector::x(void) const
    {
        return mCoords[0];
    }
    
    inline double Vector::y(void) const
    {
        return mCoords[1];
    }
    
    inline double Vector::z(void) const
    {
        return mCoords[2];
    }
    
    inline double Vector::operator*(const Vector & pVector) const
    {
        return (mCoords[0]*pVector.mCoords[0] + mCoords[1]*pVector.mCoords[1]  + mCoords[2]*pVector.mCoords[2]);
    }
    
    inline double Vector::length(void)const
    {
        return sqrt(mCoords[0]*mCoords[0] + mCoords[1]*mCoords[1] + mCoords[2]*mCoords[2]);
    }
    
    inline double Vector::lengthSqr(void)const
    {
        return (mCoords[0]*mCoords[0] + mCoords[1]*mCoords[1] + mCoords[2]*mCoords[2]);
    }
    
} // namespace MatouMalin

#endif
