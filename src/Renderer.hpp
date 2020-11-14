#ifndef RAYTRACING_RENDERER_H
#define RAYTRACING_RENDERER_H

// Standard includes
#include <cassert>

// Local includes
#include "Buffer.hpp"

namespace MatouMalin
{
    // Forward declaration
    class Scene;

    class Renderer
    {
    public:
        /// Get buffer (read only)
        static const Buffer& getBuffer(void);

        /// Copy a pointer to the scene to render
        static void setScene(Scene* scene, int width, int height);

        /// Render the specified scene
        static void render(void);

        /// Check if the super sampling has been activated
        static bool isSuperSamplingActive(void);

        /// Activate of not the super sampling as an antialiazing method
        static void setSuperSampling(bool activate);

        /// Destructor
        ~Renderer(void);

    private:
        /// Default constructor
        Renderer(void);

        /// Constructor with parameters
        Renderer(Scene* scene, int width, int height);

        /// Copy constructor (copy not allowed)
        Renderer(const Renderer& renderer);

        /// Copy operator (copy not allowed)
        Renderer operator=(const Renderer& renderer);

        /// Get a reference on the instance
        static Renderer& _instance(void);

        /// Get buffer (read only)
        const Buffer& _getBuffer(void) const;

        /// Copy a pointer to the scene to render
        void _setScene(Scene* scene, int width, int height);

        /// Render the specified scene
        void _render(void);

        /// Check if the super sampling has been activated
        bool _isSuperSamplingActive(void) const;

        /// Activate of not the super sampling as an antialiazing method
        void _setSuperSampling(bool activate);

    private:
        Scene*         _scene;
        Buffer         _buffer;
        unsigned short _reflectionCount;
        bool           _superSampling;

    };  // class Renderer

}  // namespace MatouMalin

#endif
