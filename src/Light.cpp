#include "Light.hpp"

using namespace MatouMalin;

Light::Light(void)
:mIntensity(Color(0.0f))
{
    
}

Light::Light(const Color & pColor)
:mIntensity(pColor)
{
    
}

Light::Light(const Light & pLight)
{
    mIntensity = pLight.mIntensity;
}

void Light::operator=(const Light & pLight)
{
    if(this == & pLight)
        return;
    
    mIntensity = pLight.mIntensity;
}

Light::~Light(void)
{
}
