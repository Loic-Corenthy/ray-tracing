#ifndef RAYTRACING_SCENE_H
#define RAYTRACING_SCENE_H

// Standard includes
#include <list>
#include <map>
#include <string>

// Local includes
#include "Color.hpp"
#include "OBJParameters.hpp"
#include "Ray.hpp"
#include "CubeMap.hpp"

namespace MatouMalin
{
    // Forward declaration
    class Renderable;
    class Camera;
    class Light;
    class Shader;
    class BRDF;

    struct DeleteObject
    {
        template<typename T>
        void operator()(const T* pObject) const
        {
            delete pObject;
            pObject = nullptr;
        }
    }; // struct DeleteObject


    class Scene
    {
    private:
        enum BackgroundType : short {BACKGRD_UNDEFINED, BACKGRD_COLOR, BACKGRD_CUBEMAP};

    public:
        /// Default constructor
        Scene(void);

        /// Destructor, the scene is responsable to free ALL the memory allocated to create the scene
        ~Scene(void);

        /// Get the list of camera in the scene
        std::list<Camera*> & cameraList(void);

        /// Get the list of lights in the scene
        std::list<Light*> &  lightList(void);

        /// Get the list of object in the scene
        std::list<Renderable*> & renderableList(void);

        /// Get an object of the list of renderables with its name
        Renderable* objectNamed(const std::string & pName);

        /// Add a pointer on a camera to the scene
        void add(Camera*  pCamera);

        /// Add a pointer on a light to the scene
        void add(Light*  pLight);

        /// Add a pointer on an object to render to the scene
        void add(Renderable*  pRenderable);

        /// Add a pointer on a shader, must also provide a name for the shader
        void add(Shader* pShader, const std::string & pName);

        /// Add a pointer on a BRDF, must also provide a name for the shader
        void add(BRDF* pBRDF, const std::string & pName);

        /// Add a pointer on a CubeMap used as texture for an object
        void add(CubeMap* pCubeMap);

        /// Check if a ray intersect one of the object of the scene
        bool intersect(Ray & pRay) const;

        /// Create a scene from a .obj file
        void createFromFile(const std::string & pObjFilePath);

        /// Set the color of the background in the scene
        void setBackgroundColor(const Color & pColor);

        /// Set a cubemap all around the scene
        void setBackgroundCubeMap(CubeMap* pCubeMap);

        /// Get the color of the background
        Color backgroundColor(const Ray & pRay) const;

        /// Calculate the mean of the light intensity in the entire scene
        Color meanAmbiantLight(void) const;

    private:
        /// Copy constructor (copy is not allowed)
        Scene(const Scene & pScene);

        /// Copy constructor (copy is not allowed)
        Scene operator=(const Scene & pScene);

        /// Utility function to count the number of vertices and faces in a .obj file
        void _countVerticesAndFaces(const std::string & pObjFilePath, OBJParameters & pParameters) const;

    private:
        std::list<Camera*>      mCameraList;
        std::list<Light*>       mLightList;
        std::list<Renderable*>  mRenderableList;
        std::list<CubeMap*>     mCubeMapList;
        std::map<std::string, Shader*>  mShaderMap;
        std::map<std::string, BRDF*>    mBRDFMap;
        short       mBackgroundType;
        Color       mBackgroundColor;
        CubeMap*    mBackgroundCubeMap;


    }; // class Scene

    inline std::list<Camera*> & Scene::cameraList(void)
    {
        return mCameraList;
    }

    inline std::list<Light*> & Scene::lightList(void)
    {
        return mLightList;
    }

    inline std::list<Renderable*> & Scene::renderableList(void)
    {
        return mRenderableList;
    }

    inline void Scene::setBackgroundColor(const Color & pColor)
    {
        mBackgroundType = BACKGRD_COLOR;
        mBackgroundColor = pColor;
    }

    inline void Scene::setBackgroundCubeMap(CubeMap* pCubeMap)
    {
        mBackgroundType = BACKGRD_CUBEMAP;
        mBackgroundCubeMap = pCubeMap;
    }

    inline Color Scene::backgroundColor(const Ray & pRay) const
    {
        if(mBackgroundType == BACKGRD_COLOR)
            return mBackgroundColor;
        else
            return mBackgroundCubeMap->colorAt(pRay);
    }

} // namespace MatouMalin



#endif
