#include "Vector.hpp"

using namespace MatouMalin;

Vector::Vector(void)
{
	_coords[0] = 0.0;
	_coords[1] = 0.0;
	_coords[2] = 0.0;
}

Vector::Vector(double pCommonValue)
{
	_coords[0] = pCommonValue;
	_coords[1] = pCommonValue;
	_coords[2] = pCommonValue;
}

Vector::Vector(double pX,double pY,double pZ)
{
	_coords[0] = pX;
	_coords[1] = pY;
	_coords[2] = pZ;
}

Vector::Vector(const Vector & pVector)
{
	_coords[0] = pVector._coords[0];
	_coords[1] = pVector._coords[1];
	_coords[2] = pVector._coords[2];
}

Vector::~Vector(void)
{
}

Vector Vector::operator=(const Vector & pVector)
{
    if(this == &pVector)
        return *this;

    _coords[0] = pVector._coords[0];
	_coords[1] = pVector._coords[1];
	_coords[2] = pVector._coords[2];

    return *this;
}

Vector Vector::operator+(const Vector & pVector) const
{
	Vector lMyVector(0.0);

	lMyVector[0] = _coords[0] + pVector._coords[0];
	lMyVector[1] = _coords[1] + pVector._coords[1];
	lMyVector[2] = _coords[2] + pVector._coords[2];

	return lMyVector;
}

Vector Vector::operator-(const Vector & pVector) const
{
	Vector lMyVector(0.0);

	lMyVector[0] = _coords[0] - pVector._coords[0];
	lMyVector[1] = _coords[1] - pVector._coords[1];
	lMyVector[2] = _coords[2] - pVector._coords[2];

	return lMyVector;
}

Vector Vector::operator+=(const Vector & pVector)
{
	_coords[0] = _coords[0] + pVector._coords[0];
	_coords[1] = _coords[1] + pVector._coords[1];
	_coords[2] = _coords[2] + pVector._coords[2];

	return *this;
}

Vector Vector::operator-=(const Vector & pVector)
{
	_coords[0] = _coords[0] - pVector._coords[0];
	_coords[1] = _coords[1] - pVector._coords[1];
	_coords[2] = _coords[2] - pVector._coords[2];

	return *this;
}

Vector Vector::operator*(double pScalar) const
{
	Vector lMyVector(0.0);

	lMyVector[0] = pScalar*_coords[0];
	lMyVector[1] = pScalar*_coords[1];
	lMyVector[2] = pScalar*_coords[2];

	return lMyVector;
}

Vector Vector::operator^(const Vector & pVector) const
{
	Vector lMyVector(0.0);

	lMyVector[0] = _coords[1]*pVector._coords[2] - _coords[2]*pVector._coords[1];
	lMyVector[1] = _coords[2]*pVector._coords[0] - _coords[0]*pVector._coords[2];
	lMyVector[2] = _coords[0]*pVector._coords[1] - _coords[1]*pVector._coords[0];

	return lMyVector;
}


Vector Vector::normalize(void)
{
	double lInvLengthVector = 1.0/(this->length());

	_coords[0] *= lInvLengthVector;
	_coords[1] *= lInvLengthVector;
	_coords[2] *= lInvLengthVector;

	return *this;
}