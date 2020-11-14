#include "Vector.hpp"

using namespace MatouMalin;

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
    Vector lMyVector(0.0);

    lMyVector[0] = _coords[0] + vector._coords[0];
    lMyVector[1] = _coords[1] + vector._coords[1];
    lMyVector[2] = _coords[2] + vector._coords[2];

    return lMyVector;
}

Vector Vector::operator-(const Vector& vector) const
{
    Vector lMyVector(0.0);

    lMyVector[0] = _coords[0] - vector._coords[0];
    lMyVector[1] = _coords[1] - vector._coords[1];
    lMyVector[2] = _coords[2] - vector._coords[2];

    return lMyVector;
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
    Vector lMyVector(0.0);

    lMyVector[0] = scalar * _coords[0];
    lMyVector[1] = scalar * _coords[1];
    lMyVector[2] = scalar * _coords[2];

    return lMyVector;
}

Vector Vector::operator^(const Vector& vector) const
{
    Vector lMyVector(0.0);

    lMyVector[0] = _coords[1] * vector._coords[2] - _coords[2] * vector._coords[1];
    lMyVector[1] = _coords[2] * vector._coords[0] - _coords[0] * vector._coords[2];
    lMyVector[2] = _coords[0] * vector._coords[1] - _coords[1] * vector._coords[0];

    return lMyVector;
}


Vector Vector::normalize(void)
{
    double lInvLengthVector = 1.0 / (this->length());

    _coords[0] *= lInvLengthVector;
    _coords[1] *= lInvLengthVector;
    _coords[2] *= lInvLengthVector;

    return *this;
}