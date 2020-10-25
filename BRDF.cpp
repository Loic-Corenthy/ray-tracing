#include "BRDF.h"

using namespace MatouMalin;


BRDF::BRDF(void)
:mAmbientColor(Color(0.0f)),
 mCubeMap(nullptr)
{
}


BRDF::BRDF(const Color & pAmbient)
:mAmbientColor(pAmbient),
 mCubeMap(nullptr)
{
}


BRDF::BRDF(const BRDF & pBRDF)
:mAmbientColor(pBRDF.mAmbientColor),
 mCubeMap(pBRDF.mCubeMap)
{

}


void BRDF::operator=(const BRDF & pBRDF)
{
    if (this == &pBRDF)
        return;
    
    mAmbientColor = pBRDF.mAmbientColor;
    mCubeMap = pBRDF.mCubeMap;
}

BRDF::~BRDF(void)
{
}

