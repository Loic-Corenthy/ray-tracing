#include "Vector.hpp"

using namespace LCNS;

Vector::Vector(void)
{
    _coords[0] = 0.0;
    _coords[1] = 0.0;
    _coords[2] = 0.0;
}

Vector::Vector(double commonValue)
{
    _coords[0] = commonValue;
    _coords[1] = commonValue;
    _coords[2] = commonValue;
}

Vector::Vector(double x, double y, double z)
{
    _coords[0] = x;
    _coords[1] = y;
    _coords[2] = z;
}

Vector::Vector(const Vector& vector)
{
    _coords[0] = vector._coords[0];
    _coords[1] = vector._coords[1];
    _coords[2] = vector._coords[2];
}

Vector::~Vector(void)
{
}

Vector Vector::operator=(const Vector& vector)
{
    if (this == &vector)
        return *this;

    _coords[0] = vector._coords[0];
    _coords[1] = vector._coords[1];
    _coords[2] = vector._coords[2];

    return *this;
}

Vector Vector::operator+(const Vector& vector) const
{
    Vector myVector(0.0);

    myVector[0] = _coords[0] + vector._coords[0];
    myVector[1] = _coords[1] + vector._coords[1];
    myVector[2] = _coords[2] + vector._coords[2];

    return myVector;
}

Vector Vector::operator-(const Vector& vector) const
{
    Vector myVector(0.0);

    myVector[0] = _coords[0] - vector._coords[0];
    myVector[1] = _coords[1] - vector._coords[1];
    myVector[2] = _coords[2] - vector._coords[2];

    return myVector;
}

Vector Vector::operator+=(const Vector& vector)
{
    _coords[0] = _coords[0] + vector._coords[0];
    _coords[1] = _coords[1] + vector._coords[1];
    _coords[2] = _coords[2] + vector._coords[2];

    return *this;
}

Vector Vector::operator-=(const Vector& vector)
{
    _coords[0] = _coords[0] - vector._coords[0];
    _coords[1] = _coords[1] - vector._coords[1];
    _coords[2] = _coords[2] - vector._coords[2];

    return *this;
}

Vector Vector::operator*(double scalar) const
{
    Vector myVector(0.0);

    myVector[0] = scalar * _coords[0];
    myVector[1] = scalar * _coords[1];
    myVector[2] = scalar * _coords[2];

    return myVector;
}

Vector Vector::operator^(const Vector& vector) const
{
    Vector myVector(0.0);

    myVector[0] = _coords[1] * vector._coords[2] - _coords[2] * vector._coords[1];
    myVector[1] = _coords[2] * vector._coords[0] - _coords[0] * vector._coords[2];
    myVector[2] = _coords[0] * vector._coords[1] - _coords[1] * vector._coords[0];

    return myVector;
}


Vector Vector::normalize(void)
{
    double invLengthVector = 1.0 / (this->length());

    _coords[0] *= invLengthVector;
    _coords[1] *= invLengthVector;
    _coords[2] *= invLengthVector;

    return *this;
}