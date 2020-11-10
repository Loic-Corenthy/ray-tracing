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
        /// Default constructor
        Renderer(void);

        /// Constructor with parameters
        Renderer(Scene* scene,int width, int height);

        /// Destructor
        ~Renderer(void);

        /// Get buffer (read only)
        const Buffer & getBuffer(void) const;

        /// Copy a pointer to the scene to render
        void setScene(Scene* scene);

        /// Render the specified scene
        void render(void);

        /// Check if the super sampling has been activated
        bool superSampling(void) const;

        /// Activate of not the super sampling as an antialiazing method
        void setSuperSampling(bool activate);

    private:
        /// Copy constructor (copy not allowed)
        Renderer(const Renderer & renderer);

        /// Copy operator (copy not allowed)
        Renderer operator=(const Renderer & renderer);

    private:
        Scene* _scene;
        Buffer _buffer;
        unsigned short _reflectionCount;
        bool _superSampling;

    }; // class Renderer

    inline void Renderer::setScene(Scene *scene)
    {
        assert(scene != nullptr && "The scene assigned to the Renderer is not valid");
        _scene = scene;
    }

    inline const Buffer & Renderer::getBuffer(void) const
    {
        return _buffer;
    }

    inline bool Renderer::superSampling(void) const
    {
        return _superSampling;
    }

    inline void Renderer::setSuperSampling(bool activate)
    {
        _superSampling = activate;
    }

} // namespace MatouMalin

#endif