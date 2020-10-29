#include "Vector.hpp"

using namespace MatouMalin;

Vector::Vector(void)
{
	mCoords[0] = 0.0;
	mCoords[1] = 0.0;
	mCoords[2] = 0.0;
}

Vector::Vector(double pCommonValue)
{
	mCoords[0] = pCommonValue;
	mCoords[1] = pCommonValue;
	mCoords[2] = pCommonValue;
}

Vector::Vector(double pX,double pY,double pZ)
{
	mCoords[0] = pX;
	mCoords[1] = pY;
	mCoords[2] = pZ;
}

Vector::Vector(const Vector & pVector)
{
	mCoords[0] = pVector.mCoords[0];
	mCoords[1] = pVector.mCoords[1];
	mCoords[2] = pVector.mCoords[2];
}

Vector::~Vector(void)
{
}

Vector Vector::operator=(const Vector & pVector)
{
    if(this == &pVector)
        return *this;

    mCoords[0] = pVector.mCoords[0];
	mCoords[1] = pVector.mCoords[1];
	mCoords[2] = pVector.mCoords[2];

    return *this;
}

Vector Vector::operator+(const Vector & pVector) const
{
	Vector lMyVector(0.0);

	lMyVector[0] = mCoords[0] + pVector.mCoords[0];
	lMyVector[1] = mCoords[1] + pVector.mCoords[1];
	lMyVector[2] = mCoords[2] + pVector.mCoords[2];

	return lMyVector;
}

Vector Vector::operator-(const Vector & pVector) const
{
	Vector lMyVector(0.0);

	lMyVector[0] = mCoords[0] - pVector.mCoords[0];
	lMyVector[1] = mCoords[1] - pVector.mCoords[1];
	lMyVector[2] = mCoords[2] - pVector.mCoords[2];

	return lMyVector;
}

Vector Vector::operator+=(const Vector & pVector)
{
	mCoords[0] = mCoords[0] + pVector.mCoords[0];
	mCoords[1] = mCoords[1] + pVector.mCoords[1];
	mCoords[2] = mCoords[2] + pVector.mCoords[2];

	return *this;
}

Vector Vector::operator-=(const Vector & pVector)
{
	mCoords[0] = mCoords[0] - pVector.mCoords[0];
	mCoords[1] = mCoords[1] - pVector.mCoords[1];
	mCoords[2] = mCoords[2] - pVector.mCoords[2];

	return *this;
}

Vector Vector::operator*(double pScalar) const
{
	Vector lMyVector(0.0);

	lMyVector[0] = pScalar*mCoords[0];
	lMyVector[1] = pScalar*mCoords[1];
	lMyVector[2] = pScalar*mCoords[2];

	return lMyVector;
}

Vector Vector::operator^(const Vector & pVector) const
{
	Vector lMyVector(0.0);

	lMyVector[0] = mCoords[1]*pVector.mCoords[2] - mCoords[2]*pVector.mCoords[1];
	lMyVector[1] = mCoords[2]*pVector.mCoords[0] - mCoords[0]*pVector.mCoords[2];
	lMyVector[2] = mCoords[0]*pVector.mCoords[1] - mCoords[1]*pVector.mCoords[0];

	return lMyVector;
}


Vector Vector::normalize(void)
{
	double lInvLengthVector = 1.0/(this->length());

	mCoords[0] *= lInvLengthVector;
	mCoords[1] *= lInvLengthVector;
	mCoords[2] *= lInvLengthVector;

	return *this;
}