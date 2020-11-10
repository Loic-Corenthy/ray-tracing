#include "Color.hpp"

using namespace MatouMalin;

const float Color::_inv255 = 0.00392156862f;

Color::Color(void)
{
	_components[0] = 0.0f;
	_components[1] = 0.0f;
	_components[2] = 0.0f;
}

Color::Color(float pCommonValue)
{
    _components[0] = pCommonValue;
	_components[1] = pCommonValue;
	_components[2] = pCommonValue;
}

Color::Color(float pRed,float pGreen, float pBlue)
{
	_components[0] = pRed;
	_components[1] = pGreen;
	_components[2] = pBlue;
}

Color::Color(int pRed, int pGreen, int pBlue)
{
    _components[0] = static_cast<float>(pRed)*_inv255;
	_components[1] = static_cast<float>(pGreen)*_inv255;
	_components[2] = static_cast<float>(pBlue)*_inv255;
}

Color::Color(const Color & pColor)
{
	_components[0] = pColor._components[0];
	_components[1] = pColor._components[1];
	_components[2] = pColor._components[2];
}

Color Color::operator=(const Color & pColor)
{
    if (this == & pColor)
        return *this;

	_components[0] = pColor._components[0];
	_components[1] = pColor._components[1];
	_components[2] = pColor._components[2];

    return *this;
}

Color::~Color(void)
{
}



