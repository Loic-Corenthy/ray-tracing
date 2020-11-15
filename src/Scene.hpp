//===============================================================================================//
/*!
 *  \file      Scene.hpp
 *  \author    Loïc Corenthy
 *  \version   1.0
 *  \date      14/10/2012
 *  \copyright (c) 2012 Loïc Corenthy. All rights reserved.
 */
//===============================================================================================//

#pragma once

#include <list>
#include <map>
#include <string>

#include "Color.hpp"
#include "OBJParameters.hpp"
#include "Ray.hpp"
#include "CubeMap.hpp"

namespace LCNS
{
    // Forward declaration
    class Renderable;
    class Camera;
    class Light;
    class Shader;
    class BRDF;

    struct DeleteObject
    {
        template <typename T>
        void operator()(const T* object) const
        {
            delete object;
            object = nullptr;
        }
    };  // struct DeleteObject


    class Scene
    {
    private:
        enum BackgroundType : short
        {
            BACKGRD_UNDEFINED,
            BACKGRD_COLOR,
            BACKGRD_CUBEMAP
        };

    public:
        /// Default constructor
        Scene(void);

        /// Destructor, the scene is responsable to free ALL the memory allocated to create the scene
        ~Scene(void);

        /// Get the list of camera in the scene
        std::list<Camera*>& cameraList(void);

        /// Get the list of lights in the scene
        std::list<Light*>& lightList(void);

        /// Get the list of object in the scene
        std::list<Renderable*>& renderableList(void);

        /// Get an object of the list of renderables with its name
        Renderable* objectNamed(const std::string& name);

        /// Add a pointer on a camera to the scene
        void add(Camera* camera);

        /// Add a pointer on a light to the scene
        void add(Light* light);

        /// Add a pointer on an object to render to the scene
        void add(Renderable* renderable);

        /// Add a pointer on a shader, must also provide a name for the shader
        void add(Shader* shader, const std::string& name);

        /// Add a pointer on a BRDF, must also provide a name for the shader
        void add(BRDF* bRDF, const std::string& name);

        /// Add a pointer on a CubeMap used as texture for an object
        void add(CubeMap* cubeMap);

        /// Check if a ray intersect one of the object of the scene
        bool intersect(Ray& ray) const;

        /// Create a scene from a .obj file
        void createFromFile(const std::string& objFilePath);

        /// Set the color of the background in the scene
        void setBackgroundColor(const Color& color);

        /// Set a cubemap all around the scene
        void setBackgroundCubeMap(CubeMap* cubeMap);

        /// Get the color of the background
        Color backgroundColor(const Ray& ray) const;

        /// Calculate the mean of the light intensity in the entire scene
        Color meanAmbiantLight(void) const;

    private:
        /// Copy constructor (copy is not allowed)
        Scene(const Scene& scene);

        /// Copy constructor (copy is not allowed)
        Scene operator=(const Scene& scene);

        /// Utility function to count the number of vertices and faces in a .obj file
        void _countVerticesAndFaces(const std::string& objFilePath, OBJParameters& parameters) const;

    private:
        std::list<Camera*>             _cameraList;
        std::list<Light*>              _lightList;
        std::list<Renderable*>         _renderableList;
        std::list<CubeMap*>            _cubeMapList;
        std::map<std::string, Shader*> _shaderMap;
        std::map<std::string, BRDF*>   _bRDFMap;
        short                          _backgroundType;
        Color                          _backgroundColor;
        CubeMap*                       _backgroundCubeMap;


    };  // class Scene

    inline std::list<Camera*>& Scene::cameraList(void)
    {
        return _cameraList;
    }

    inline std::list<Light*>& Scene::lightList(void)
    {
        return _lightList;
    }

    inline std::list<Renderable*>& Scene::renderableList(void)
    {
        return _renderableList;
    }

    inline void Scene::setBackgroundColor(const Color& color)
    {
        _backgroundType  = BACKGRD_COLOR;
        _backgroundColor = color;
    }

    inline void Scene::setBackgroundCubeMap(CubeMap* cubeMap)
    {
        _backgroundType    = BACKGRD_CUBEMAP;
        _backgroundCubeMap = cubeMap;
    }

    inline Color Scene::backgroundColor(const Ray& ray) const
    {
        if (_backgroundType == BACKGRD_COLOR)
            return _backgroundColor;
        else
            return _backgroundCubeMap->colorAt(ray);
    }

}  // namespace LCNS
