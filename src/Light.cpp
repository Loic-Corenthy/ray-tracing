#include "Light.hpp"

using namespace MatouMalin;

Light::Light(void)
:_intensity(Color(0.0f))
{

}

Light::Light(const Color & pColor)
:_intensity(pColor)
{

}

Light::Light(const Light & pLight)
{
    _intensity = pLight._intensity;
}

void Light::operator=(const Light & pLight)
{
    if(this == & pLight)
        return;

    _intensity = pLight._intensity;
}

Light::~Light(void)
{
}
