#include "Renderable.hpp"

// Local includes
#include "Ray.hpp"

using namespace LCNS;
using namespace std;

Renderable::Renderable(void)
: _shader(nullptr)
, _name(" ")
{
}

Renderable::Renderable(const Renderable& renderable)
: _shader(renderable._shader)
, _name(renderable._name)
{
}

void Renderable::operator=(const Renderable& renderable)
{
    if (this == &renderable)
        return;

    _shader = renderable._shader;
    _name   = renderable._name;
}

Renderable::~Renderable(void)
{
}

bool Renderable::_refraction(const Vector& incomingDirection, const Vector& normal, double n1, double n2, Vector& refractedDirection) const
{
    double lMinusCosTheta1 = incomingDirection * normal;
    double lN              = n1 / n2;

    // Test for total reflection
    double lSqrSinTheta2 = lN * lN * (1.0 - lMinusCosTheta1 * lMinusCosTheta1);

    if (lSqrSinTheta2 > 1.0)
    {
        return false;
    }
    else
    {
        double lCosTheta2  = sqrt(1.0 - lSqrSinTheta2);
        refractedDirection = (incomingDirection - normal * lMinusCosTheta1) * lN - normal * lCosTheta2;
        return true;
    }
}
