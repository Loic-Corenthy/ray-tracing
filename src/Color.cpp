#include "Color.hpp"

using namespace MatouMalin;

const float Color::mInv255 = 0.00392156862f;

Color::Color(void)
{
	mComponents[0] = 0.0f;
	mComponents[1] = 0.0f;
	mComponents[2] = 0.0f;
}

Color::Color(float pCommonValue)
{
    mComponents[0] = pCommonValue;
	mComponents[1] = pCommonValue;
	mComponents[2] = pCommonValue;
}

Color::Color(float pRed,float pGreen, float pBlue)
{
	mComponents[0] = pRed;
	mComponents[1] = pGreen;
	mComponents[2] = pBlue;
}

Color::Color(int pRed, int pGreen, int pBlue)
{
    mComponents[0] = static_cast<float>(pRed)*mInv255;
	mComponents[1] = static_cast<float>(pGreen)*mInv255;
	mComponents[2] = static_cast<float>(pBlue)*mInv255;
}

Color::Color(const Color & pColor)
{
	mComponents[0] = pColor.mComponents[0];
	mComponents[1] = pColor.mComponents[1];
	mComponents[2] = pColor.mComponents[2];
}

Color Color::operator=(const Color & pColor)
{
    if (this == & pColor)
        return *this;
    
	mComponents[0] = pColor.mComponents[0];
	mComponents[1] = pColor.mComponents[1];
	mComponents[2] = pColor.mComponents[2];

    return *this;
}

Color::~Color(void)
{
}



