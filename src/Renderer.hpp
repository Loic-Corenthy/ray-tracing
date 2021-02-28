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
        void _renderInternal(unsigned int bufferI, unsigned int bufferJ, const Color& meanLight);

        // Internal method to facilitate multi threading rendering
        void _renderMultiSamplingInternal(unsigned int bufferI, unsigned int bufferJ, const Color& meanLight);

        // Internal method to facilitate multi threading rendering
        void _renderNoApertureInternal(unsigned int bufferI, unsigned int bufferJ, const Color& meanLight);

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

    private:
        std::shared_ptr<Scene> _scene;
        Buffer                 _buffer;
        unsigned short         _reflectionCount;
        bool                   _superSampling           = false;
        bool                   _multiThreaded           = false;
        bool                   _shouldDisplayRenderTime = false;

    };  // class Renderer

}  // namespace LCNS
