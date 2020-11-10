#ifndef RAYTRACING_POINT_H
#define RAYTRACING_POINT_H

// Standard includes
#include <cassert>

// Local includes
#include "Vector.hpp"

namespace MatouMalin
{
    class Point
    {
    public:
        /// Default constructor
        Point(void);

        /// Constructor with position parameters
        Point(double pX,double pY,double pZ);

        /// Constructor with position parameters
        Point(double pCommonValue);

        /// Copy constructor
        Point(const Point & pPoint);

        /// Destructor
        ~Point(void);

        /// Coordinate operator (read only)
        double operator[](unsigned int pIndex) const;

        /// Coordinate operator (read,write)
        double & operator[](unsigned int pIndex);

        /// Set 3 coordinates
        void setPoint(double pX,double pY,double pZ);

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

        /// Create a vector by substracting 2 points
        Vector operator-(const Point pPoint) const;

        /// Translate a point by a vector
        Point operator+(const Vector pVector) const;

        /// Copy operator
        Point operator=(const Point & pPoint);

    private:
        double _coords[3];

    }; // class Point

    inline double Point::operator[](unsigned int pIndex) const
    {
        assert(0 <= pIndex && pIndex < 3 && "Point: index out of bounds");
        return _coords[pIndex];
    }

    inline double & Point::operator[](unsigned int pIndex)
    {
        assert(0 <= pIndex && pIndex < 3 && "Point: index out of bounds");
        return _coords[pIndex];
    }

    inline Vector Point::operator-(const Point pPoint) const
    {
        return Vector(_coords[0] - pPoint._coords[0], _coords[1] - pPoint._coords[1], _coords[2] - pPoint._coords[2]);
    }

    inline Point Point::operator+(const Vector pVector) const
    {
        return Point(_coords[0] + pVector[0], _coords[1] + pVector[1], _coords[2] + pVector[2]);
    }

    inline void Point::setPoint(double pX,double pY,double pZ)
    {
        _coords[0] = pX;
        _coords[1] = pY;
        _coords[2] = pZ;
    }

    inline void Point::setX(double pX)
    {
        _coords[0] = pX;
    }

    inline void Point::setY(double pY)
    {
        _coords[1] = pY;
    }

    inline void Point::setZ(double pZ)
    {
        _coords[2] = pZ;
    }

    inline double Point::x(void) const
    {
        return _coords[0];
    }

    inline double Point::y(void) const
    {
        return _coords[1];
    }

    inline double Point::z(void) const
    {
        return _coords[2];
    }

} // namespace MatouMalin

#endif