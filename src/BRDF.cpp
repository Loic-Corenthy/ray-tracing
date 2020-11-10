#include "BRDF.hpp"

using namespace MatouMalin;


BRDF::BRDF(void)
:_ambientColor(Color(0.0f)),
 _cubeMap(nullptr)
{
}


BRDF::BRDF(const Color & pAmbient)
:_ambientColor(pAmbient),
 _cubeMap(nullptr)
{
}


BRDF::BRDF(const BRDF & pBRDF)
:_ambientColor(pBRDF._ambientColor),
 _cubeMap(pBRDF._cubeMap)
{

}


void BRDF::operator=(const BRDF & pBRDF)
{
    if (this == &pBRDF)
        return;

    _ambientColor = pBRDF._ambientColor;
    _cubeMap = pBRDF._cubeMap;
}

BRDF::~BRDF(void)
{
}

