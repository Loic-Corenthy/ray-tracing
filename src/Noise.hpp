//===============================================================================================//
/*!
 *  \file      Noise.hpp
 *  \author    Loïc Corenthy
 *  \version   1.1
 *  \date      23/09/2012
 *  \copyright (c) 2012 Loïc Corenthy. All rights reserved.
 */
//===============================================================================================//

#pragma once

#include <vector>
#include <cmath>

namespace LCNS
{
    class Noise
    {
    public:
        /// Default constructor
        Noise(void);

        /// Copy constructor
        Noise(const Noise& noise) = default;

        /// Copy operator
        Noise& operator=(const Noise& noise) = default;

        /// Destructor
        ~Noise(void) = default;

        /// Perlin noise
        double perlinNoise(double x, double y, double z) const;

    private:
        /// Initialize the array of permutations
        void _init(void) noexcept;

        /// Return the value of a polynom for parameter t : t
        double _fade(double t) const noexcept;

        /// Position of a point in segment [AB] (1D) in fonction of parameter t
        constexpr double _lerp(double t, double a, double b) const noexcept;

        /// Some gradient?
        double _grad(int hash, double x, double y, double z) const noexcept;

        /// Pseudo random number generator
        double _prandFromInt(int value) const noexcept;

        /// Interpolation with cosine function
        double _cerp(double a, double b, double t) const noexcept;

    private:
        static const int    smPermutations[256];
        static const double _pi;
        std::vector<size_t> _permutations;

    };  // class Noise

}  // namespace LCNS
