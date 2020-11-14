//
//  Noise.h
//  RayTracing
//
//  Created by Loïc CORENTHY on 9/23/12.
//
//

#ifndef RAYTRACING_NOISE_H
#define RAYTRACING_NOISE_H

#include <vector>
#include <cmath>

namespace MatouMalin
{
    class Noise
    {
    public:
        /// Default constructor
        Noise(void);

        /// Copy constructor
        Noise(const Noise& noise);

        /// Copy operator
        Noise operator=(const Noise& noise);

        /// Destructor
        ~Noise(void);

        /// Perlin noise
        double perlinNoise(double x, double y, double z) const;

    private:
        /// Initialize the array of permutations
        void _init(void);

        /// Return the value of a polynom for parameter t : t
        double _fade(double t) const;

        /// Position of a point in segment [AB] (1D) in fonction of parameter t
        double _lerp(double t, double a, double b) const;

        /// Some gradient?
        double _grad(int hash, double x, double y, double z) const;

        /// Pseudo random number generator
        double _prandFromInt(int value) const;

        /// Interpolation with cosine function
        double _cerp(double a, double b, double t) const;

    private:
        static const int    smPermutations[256];
        std::vector<int>    _permutations;
        static const double _pi;
    };  // class Noise

    inline double Noise::_fade(double t) const
    {
        return (t * t * t * (t * (t * 6.0 - 15.0) + 10.0));
    }

    inline double Noise::_lerp(double t, double a, double b) const
    {
        return (a + t * (b - a));
    }

    inline double Noise::_prandFromInt(int value) const
    {
        value = (value << 13) ^ value;
        return (1.0 - ((value * (value * value * 15731 + 789221) + 1376312589) & 0x7fffffff) / 1073741824.0);
    }

    inline double Noise::_cerp(double a, double b, double t) const
    {
        double lF = (1.0f - cosf(t * _pi)) * 0.5f;
        return (a * (1.0 - lF) + b * lF);
    }

}  // namespace MatouMalin


#endif
