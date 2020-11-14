#ifndef RAYTRACING_POINT_H
#define RAYTRACING_POINT_H

// Standard includes
#include <cassert>

// Local includes
#include "Vector.hpp"

namespace LCNS
{
    class Point
    {
    public:
        /// Default constructor
        Point(void);

        /// Constructor with position parameters
        Point(double x, double y, double z);

        /// Constructor with position parameters
        Point(double commonValue);

        /// Copy constructor
        Point(const Point& point);

        /// Destructor
        ~Point(void);

        /// Coordinate operator (read only)
        double operator[](unsigned int index) const;

        /// Coordinate operator (read,write)
        double& operator[](unsigned int index);

        /// Set 3 coordinates
        void setPoint(double x, double y, double z);

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

        /// Create a vector by substracting 2 points
        Vector operator-(const Point point) const;

        /// Translate a point by a vector
        Point operator+(const Vector vector) const;

        /// Copy operator
        Point operator=(const Point& point);

    private:
        double _coords[3];

    };  // class Point

    inline double Point::operator[](unsigned int index) const
    {
        assert(0 <= index && index < 3 && "Point: index out of bounds");
        return _coords[index];
    }

    inline double& Point::operator[](unsigned int index)
    {
        assert(0 <= index && index < 3 && "Point: index out of bounds");
        return _coords[index];
    }

    inline Vector Point::operator-(const Point point) const
    {
        return Vector(_coords[0] - point._coords[0], _coords[1] - point._coords[1], _coords[2] - point._coords[2]);
    }

    inline Point Point::operator+(const Vector vector) const
    {
        return Point(_coords[0] + vector[0], _coords[1] + vector[1], _coords[2] + vector[2]);
    }

    inline void Point::setPoint(double x, double y, double z)
    {
        _coords[0] = x;
        _coords[1] = y;
        _coords[2] = z;
    }

    inline void Point::setX(double x)
    {
        _coords[0] = x;
    }

    inline void Point::setY(double y)
    {
        _coords[1] = y;
    }

    inline void Point::setZ(double z)
    {
        _coords[2] = z;
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

}  // namespace LCNS

#endif