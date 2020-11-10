#include "Color.hpp"

using namespace MatouMalin;

const float Color::_inv255 = 0.00392156862f;

Color::Color(void)
{
	_components[0] = 0.0f;
	_components[1] = 0.0f;
	_components[2] = 0.0f;
}

Color::Color(float commonValue)
{
    _components[0] = commonValue;
	_components[1] = commonValue;
	_components[2] = commonValue;
}

Color::Color(float red,float green, float blue)
{
	_components[0] = red;
	_components[1] = green;
	_components[2] = blue;
}

Color::Color(int red, int green, int blue)
{
    _components[0] = static_cast<float>(red)*_inv255;
	_components[1] = static_cast<float>(green)*_inv255;
	_components[2] = static_cast<float>(blue)*_inv255;
}

Color::Color(const Color & color)
{
	_components[0] = color._components[0];
	_components[1] = color._components[1];
	_components[2] = color._components[2];
}

Color Color::operator=(const Color & color)
{
    if (this == & color)
        return *this;

	_components[0] = color._components[0];
	_components[1] = color._components[1];
	_components[2] = color._components[2];

    return *this;
}

Color::~Color(void)
{
}



