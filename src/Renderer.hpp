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
        Renderer(Scene* pScene,int pWidth, int pHeight);
        
        /// Destructor
        ~Renderer(void);
        
        /// Get buffer (read only)
        const Buffer & getBuffer(void) const;
        
        /// Copy a pointer to the scene to render
        void setScene(Scene* pScene);
        
        /// Render the specified scene
        void render(void);
        
        /// Check if the super sampling has been activated
        bool superSampling(void) const;
        
        /// Activate of not the super sampling as an antialiazing method
        void setSuperSampling(bool pActivate);
        
    private:
        /// Copy constructor (copy not allowed)
        Renderer(const Renderer & pRenderer);
        
        /// Copy operator (copy not allowed)
        Renderer operator=(const Renderer & pRenderer);
        
    private:
        Scene* mScene;
        Buffer mBuffer;
        unsigned short mReflectionCount;
        bool mSuperSampling;
        
    }; // class Renderer
    
    inline void Renderer::setScene(Scene *pScene)
    {
        assert(pScene != nullptr && "The scene assigned to the Renderer is not valid");
        mScene = pScene;
    }
    
    inline const Buffer & Renderer::getBuffer(void) const
    {
        return mBuffer;
    }
    
    inline bool Renderer::superSampling(void) const
    {
        return mSuperSampling;
    }
    
    inline void Renderer::setSuperSampling(bool pActivate)
    {
        mSuperSampling = pActivate;
    }
    
} // namespace MatouMalin 

#endif