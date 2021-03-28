//===============================================================================================//
/*!
 *  \file      Renderer.hpp
 *  \author    Loïc Corenthy
 *  \version   1.1
 *  \date      14/10/2012
 *  \copyright (c) 2012 Loïc Corenthy. All rights reserved.
 */
//===============================================================================================//

#pragma once

#include <cassert>
#include <memory>
#include <atomic>
#include <thread>

#include "Buffer.hpp"
#include "Camera.hpp"

namespace LCNS
{
    // Forward declaration
    class Scene;

    class Renderer
    {
    public:
        /// Copy constructor (copy not allowed)
        Renderer(const Renderer& renderer) = delete;

        /// Copy operator (copy not allowed)
        Renderer operator=(const Renderer& renderer) = delete;

        /// Destructor
        ~Renderer(void) = default;

        /// Get buffer (read only)
        static const Buffer& getBuffer(void);

        /// Copy a pointer to the scene to render
        static void setScene(std::shared_ptr<Scene> scene, unsigned int width, unsigned int height);

        /// Render the specified scene
        static void render(void);

        /// Check if the super sampling has been activated
        static bool isSuperSamplingActive(void);

        /// Activate of not the super sampling as an antialiazing method
        static void setSuperSampling(bool activate);

        /// Check if multi threaded rendering is active (function of the number of cores)
        static bool isMultiThreadingActive(void);

        /// Activate or not multi threaded rendering
        static void setMultiThreading(bool activate);

        /// Display the time it took to render the image
        static void displayRenderTime(bool activate);

    private:
        /// Private member used in ThreadData to illustrate the current state of a thread
        enum class RunState
        {
            sleeping = 0,
            running  = 1,
            done     = 2
        };

        struct ThreadData
        {
            std::atomic<unsigned int> startIndex = 0;
            std::atomic<unsigned int> endIndex   = 0;
            std::atomic<RunState>     runState   = RunState::sleeping;
        };

    private:
        /// Default constructor
        Renderer(void);

        /// Constructor with parameters
        Renderer(Scene* scene, unsigned int width, unsigned int height);

        /// Get a reference on the instance
        static Renderer& _instance(void);

        /// Copy a pointer to the scene to render
        void _setScene(std::shared_ptr<Scene> scene, unsigned int width, unsigned int height);

        /// Render the specified scene
        void _render(void);

        // Internal method to facilitate multi threading rendering
        void _renderWithApertureInternal(ThreadData* allIndices, unsigned int index, const Color& meanLight);

        // Internal method to facilitate multi threading rendering
        void _renderMultiSamplingInternal(ThreadData* allIndices, unsigned int index, const Color& meanLight);

        // Internal method to facilitate multi threading rendering
        void _renderNoApertureInternal(ThreadData* allIndices, unsigned int index, const Color& meanLight);

        /// Internal method to check if the super sampling has been activated
        bool _isSuperSamplingActive(void) const;

        /// Internal method to activate or not the super sampling as an antialiazing method
        void _setSuperSampling(bool activate);

        /// Internal method to check if multi threaded rendering is active (function of the number of cores)
        bool _isMultiThreadingActive(void) const;

        /// Internal method to activate or not multi threaded rendering
        void _setMultiThreading(bool activate);

        /// Display a progress bar with ascii characters
        void _displayProgressBar(double currentProgress);

        /// Internal method to activate/deactivate the render time being displayed
        void _displayRenderTime(bool activate);

        /// Internal helper method to manage multiple threads and their data batches
        template <typename T>
        void _threadHandler(
        T renderingMethod, unsigned int allPixelsCount, unsigned int processorCount, double reductionCoeff, const Color& meanLight);

        /// Helper method to get the 2D position in a buffer from 1D array
        std::tuple<unsigned int, unsigned int> _2DFrom1D(unsigned int position, unsigned int width) const;

    private:
        std::shared_ptr<Scene> _scene;
        Buffer                 _buffer;
        bool                   _superSampling           = false;
        bool                   _multiThreaded           = false;
        bool                   _shouldDisplayRenderTime = false;

    };  // class Renderer

    template <typename T>
    void Renderer::_threadHandler(
    T renderingMethod, unsigned int allPixelsCount, unsigned int processorCount, double reductionCoeff, const Color& meanLight)
    {
        const auto batchSize
        = static_cast<unsigned int>(ceil(static_cast<double>(allPixelsCount) / static_cast<double>(processorCount)) / reductionCoeff);

        std::vector<std::thread> allThreads;
        allThreads.reserve(processorCount);

        ThreadData* allRanges = new ThreadData[processorCount];

        // Create threads
        unsigned int range = 0;
        for (unsigned int i = 0; i < processorCount; ++i)
        {
            allRanges[i].startIndex = range;
            allRanges[i].endIndex   = range + batchSize;
            allRanges[i].runState   = RunState::running;

            allThreads.push_back(std::thread(renderingMethod, this, allRanges, i, meanLight));
            range += batchSize;
        }

        unsigned int j = 0u;
        while (range < allPixelsCount)
        {
            if (allRanges[j].runState == RunState::done)
            {
                allRanges[j].startIndex = range;
                allRanges[j].endIndex   = range + batchSize;
                allRanges[j].runState   = RunState::running;
                range += batchSize;

                if (range > allPixelsCount)
                {
                    range = allPixelsCount;
                }
                // std::cout << "new data for process " << j << std::endl;
                _displayProgressBar(static_cast<double>(range) / static_cast<double>(allPixelsCount));
            }

            ++j;

            if (j >= processorCount)
            {
                j = 0;
            }
        }

        for (unsigned int i = 0; i < processorCount; ++i)
        {
            allRanges[i].runState = RunState::sleeping;
        }

        for (auto& t : allThreads)
        {
            if (t.joinable())
            {
                t.join();
            }
        }

        delete[] allRanges;
    }

}  // namespace LCNS
