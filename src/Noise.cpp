//===============================================================================================//
/*!
 *  \file      Noise.cpp
 *  \author    Loïc Corenthy
 *  \version   1.1
 *  \date      23/09/2012
 *  \copyright (c) 2012 Loïc Corenthy. All rights reserved.
 */
//===============================================================================================//

#include "Noise.hpp"

using namespace LCNS;
using namespace std;

const int Noise::smPermutations[]
= { 151, 160, 137, 91,  90,  15,  131, 13,  201, 95,  96,  53,  194, 233, 7,   225, 140, 36,  103, 30,  69,  142, 8,   99,  37,  240, 21,  10,  23,
    190, 6,   148, 247, 120, 234, 75,  0,   26,  197, 62,  94,  252, 219, 203, 117, 35,  11,  32,  57,  177, 33,  88,  237, 149, 56,  87,  174, 20,
    125, 136, 171, 168, 68,  175, 74,  165, 71,  134, 139, 48,  27,  166, 77,  146, 158, 231, 83,  111, 229, 122, 60,  211, 133, 230, 220, 105, 92,
    41,  55,  46,  245, 40,  244, 102, 143, 54,  65,  25,  63,  161, 1,   216, 80,  73,  209, 76,  132, 187, 208, 89,  18,  169, 200, 196, 135, 130,
    116, 188, 159, 86,  164, 100, 109, 198, 173, 186, 3,   64,  52,  217, 226, 250, 124, 123, 5,   202, 38,  147, 118, 126, 255, 82,  85,  212, 207,
    206, 59,  227, 47,  16,  58,  17,  182, 189, 28,  42,  23,  183, 170, 213, 119, 248, 152, 2,   44,  154, 163, 70,  221, 153, 101, 155, 167, 43,
    172, 9,   129, 22,  39,  253, 19,  98,  108, 110, 79,  113, 224, 232, 178, 185, 112, 104, 218, 246, 97,  228, 251, 34,  242, 193, 238, 210, 144,
    12,  191, 179, 162, 241, 81,  51,  145, 235, 249, 14,  239, 107, 49,  192, 214, 31,  181, 199, 106, 157, 184, 84,  204, 176, 115, 121, 50,  45,
    127, 4,   150, 254, 138, 236, 205, 93,  222, 114, 67,  29,  24,  72,  243, 141, 128, 195, 78,  66,  215, 61,  156, 180 };

const double Noise::_pi = 3.141592653589793238462643383279;

Noise::Noise(void)
{
    _init();
}

double Noise::perlinNoise(double x, double y, double z) const
{
    const auto xx = static_cast<size_t>(floor(x)) & 255;
    const auto yy = static_cast<size_t>(floor(y)) & 255;
    const auto zz = static_cast<size_t>(floor(z)) & 255;

    x -= floor(x);
    y -= floor(y);
    z -= floor(z);

    const double u = _fade(x);
    const double v = _fade(y);
    const double w = _fade(z);

    const auto a  = _permutations[xx] + yy;
    const auto aA = _permutations[a] + zz;
    const auto aB = _permutations[a + 1] + zz;
    const auto b  = _permutations[xx + 1] + yy;
    const auto bA = _permutations[b] + zz;
    const auto bB = _permutations[b + 1] + zz;

    double tmp1 = _lerp(v,
                        _lerp(u, _grad(_permutations[aA], x, y, z), _grad(_permutations[bA], x - 1.0, y, z)),
                        _lerp(u, _grad(_permutations[aB], x, y - 1.0, z), _grad(_permutations[bB], x - 1.0, y - 1.0, z)));

    double tmp2 = _lerp(v,
                        _lerp(u, _grad(_permutations[aA + 1], x, y, z - 1.0), _grad(_permutations[bA + 1], x - 1.0, y, z - 1.0)),
                        _lerp(u, _grad(_permutations[aB + 1], x, y - 1.0, z - 1.0), _grad(_permutations[bB + 1], x - 1.0, y - 1.0, z - 1.0)));

    return _lerp(w, tmp1, tmp2);
}

void Noise::_init(void) noexcept
{
    for (unsigned int i = 0; i < 256; i++)
        _permutations.push_back(smPermutations[i]);

    for (unsigned int i = 0; i < 256; i++)
        _permutations.push_back(smPermutations[i]);
}

double Noise::_grad(int hash, double x, double y, double z) const noexcept
{
    int h = hash & 15;
    // CONVERT LO 4 BITS OF HASH CODE
    const auto u = (h < 8 || h == 12 || h == 13) ? x : y;  // INTO 12 GRADIENT DIRECTIONS.
    const auto v = (h < 4 || h == 12 || h == 13) ? y : z;

    return (((h & 1) == 0 ? u : -u) + ((h & 2) == 0 ? v : -v));
}

double Noise::_fade(double t) const noexcept
{
    return (t * t * t * (t * (t * 6.0 - 15.0) + 10.0));
}

constexpr double Noise::_lerp(double t, double a, double b) const noexcept
{
    return (a + t * (b - a));
}

double Noise::_prandFromInt(int value) const noexcept
{
    value = (value << 13) ^ value;
    return (1.0 - ((value * (value * value * 15731 + 789221) + 1376312589) & 0x7fffffff) / 1073741824.0);
}

double Noise::_cerp(double a, double b, double t) const noexcept
{
    const auto f = (1.0 - cos(t * _pi)) * 0.5;
    return (a * (1.0 - f) + b * f);
}
