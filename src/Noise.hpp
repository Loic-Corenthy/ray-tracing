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
        Noise(const Noise & pNoise);

        /// Copy operator
        Noise operator=(const Noise & pNoise);

        /// Destructor
        ~Noise(void);

        /// Perlin noise
        double perlinNoise(double pX, double pY, double pZ) const;

    private:
        /// Initialize the array of permutations
        void _init(void);

        /// Return the value of a polynom for parameter t : pT
        double _fade(double pT) const;

        /// Position of a point in segment [AB] (1D) in fonction of parameter t
        double _lerp(double pT, double pA, double pB) const;

        /// Some gradient?
        double _grad(int pHash, double pX, double pY, double pZ) const;

        /// Pseudo random number generator
        double _prandFromInt(int pValue) const;

        /// Interpolation with cosine function
        double _cerp(double pA, double pB, double pT) const;

    private:
        static const int smPermutations[256];
        std::vector<int> mPermutations;
        static const double mPi;
    }; // class Noise

    inline double Noise::_fade(double pT) const
    {
        return (pT * pT * pT * (pT * (pT * 6.0 - 15.0) + 10.0));
    }

    inline double Noise::_lerp(double pT, double pA, double pB) const
    {
        return (pA + pT*(pB - pA));
    }

    inline double Noise::_prandFromInt(int pValue) const
    {
        pValue = (pValue<<13) ^ pValue;
        return (1.0 - ( (pValue * (pValue * pValue * 15731 + 789221) + 1376312589) & 0x7fffffff) / 1073741824.0);
    }

    inline double Noise::_cerp(double pA, double pB, double pT) const
    {
        double lF = (1.0f - cosf(pT*mPi))*0.5f;
        return (pA*(1.0-lF)+pB*lF);
    }

} // namespace MatouMalin


#endif
