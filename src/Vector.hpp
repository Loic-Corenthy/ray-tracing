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
        Vector(double x,double y,double z);

        /// Constructor with same value for all coordinates
        Vector(double commonValue);

        /// Copy constructor
        Vector(const Vector & vector);

        /// Destructor
        ~Vector(void);

        /// Coordinate operator (read only)
        double operator[](unsigned int index) const;

        /// Coordinate operator (read, write)
        double & operator[](unsigned int index);

        /// Set all coordinates at once
        void setVector(double x,double y,double z);

        /// Set X coordinate
        void setX(double x);

        /// Set Y coordinate
        void setY(double y);

        /// Set Z coordinate
        void setZ(double z);

        /// Get X coordinate
        double x(void) const;

        /// Get X coordinate
        double y(void) const;

        /// Get X coordinate
        double z(void) const;

        /// Copy the coordinates of a vector to another one
        Vector operator=(const Vector & vector);

        /// Return the vector sum of 2 vectors
        Vector operator+(const Vector & vector) const;

        /// Return the vector difference of 2 vectors
        Vector operator-(const Vector & vector) const;

        /// Add a vector to the current one
        Vector operator+=(const Vector & vector);

        /// Substract a vector to the current one
        Vector operator-=(const Vector & vector);

        /// Multiply a vector by a scalar
        Vector operator*(double scalar) const;

        /// Scalar product of 2 vectors
        double  operator*(const Vector & vector) const;

        /// Dot product of 2 vectors
        Vector operator^(const Vector & vector) const;

        /// Return the length of the vector
        double length(void) const;

        /// Return the square length of a the vector
        double lengthSqr(void) const;

        /// Divide a vector by it's length and return it.
        Vector normalize(void);


    private:
        double _coords[3];

    }; // class Vector

    inline double Vector::operator[](unsigned int index) const
    {
        assert(0 <= index && index <= 2 && "Vector: index out of bounds");
        return _coords[index];
    }

    inline double & Vector::operator[](unsigned int index)
    {
        assert(0 <= index && index <= 2 && "Vector: index out of bounds");
        return _coords[index];
    }

    inline void Vector::setVector(double x,double y,double z)
    {
        _coords[0] = x;
        _coords[1] = y;
        _coords[2] = z;
    }

    inline void Vector::setX(double x)
    {
        _coords[0] = x;
    }

    inline void Vector::setY(double y)
    {
        _coords[1] = y;
    }

    inline void Vector::setZ(double z)
    {
        _coords[2] = z;
    }

    inline double Vector::x(void) const
    {
        return _coords[0];
    }

    inline double Vector::y(void) const
    {
        return _coords[1];
    }

    inline double Vector::z(void) const
    {
        return _coords[2];
    }

    inline double Vector::operator*(const Vector & vector) const
    {
        return (_coords[0]*vector._coords[0] + _coords[1]*vector._coords[1]  + _coords[2]*vector._coords[2]);
    }

    inline double Vector::length(void)const
    {
        return sqrt(_coords[0]*_coords[0] + _coords[1]*_coords[1] + _coords[2]*_coords[2]);
    }

    inline double Vector::lengthSqr(void)const
    {
        return (_coords[0]*_coords[0] + _coords[1]*_coords[1] + _coords[2]*_coords[2]);
    }

} // namespace MatouMalin

#endif
