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
#include <memory>

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

    class Scene
    {
    private:
        enum class BackgroundType
        {
            UNDEFINED,
            COLOR,
            CUBEMAP
        };

    public:
        /// Default constructor
        Scene(void) = default;

        /// Copy constructor (copy is not allowed)
        Scene(const Scene& scene) = delete;

        /// Copy constructor (copy is not allowed)
        Scene operator=(const Scene& scene) = delete;

        /// Destructor, the scene is responsable to free ALL the memory allocated to create the scene
        ~Scene(void) = default;

        /// Get the list of camera in the scene
        std::list<std::unique_ptr<Camera>>& cameraList(void);

        /// Get the list of lights in the scene
        std::list<std::shared_ptr<Light>>& lightList(void);

        /// Get the list of object in the scene
        std::list<std::shared_ptr<Renderable>>& renderableList(void);

        /// Get an object of the list of renderables with its name
        std::shared_ptr<Renderable> objectNamed(const std::string& name);

        /// Add a pointer on a camera to the scene
        void add(std::unique_ptr<Camera>&& camera);

        /// Add a pointer on a light to the scene
        void add(std::shared_ptr<Light> light);

        /// Add a pointer on an object to render to the scene
        void add(std::shared_ptr<Renderable> renderable);

        /// Add a pointer on a shader, must also provide a name for the shader
        void add(std::shared_ptr<Shader> shader, const std::string& name);

        /// Add a pointer on a BRDF, must also provide a name for the shader
        void add(std::shared_ptr<BRDF> bRDF, const std::string& name);

        /// Add a pointer on a CubeMap used as texture for an object
        void add(std::shared_ptr<CubeMap> cubeMap);

        /// Check if a ray intersect one of the object of the scene
        bool intersect(Ray& ray) const;

        /// Create a scene from a .obj file
        void createFromFile(const std::string& objFilePath);

        /// Set the color of the background in the scene
        void setBackgroundColor(const Color& color);

        /// Set a cubemap all around the scene
        void backgroundCubeMap(std::shared_ptr<CubeMap> cubeMap);

        /// Get the color of the background
        Color backgroundColor(const Ray& ray) const;

        /// Calculate the mean of the light intensity in the entire scene
        Color meanAmbiantLight(void) const;

    private:
        /// Utility function to count the number of vertices and faces in a .obj file
        void _countVerticesAndFaces(const std::string& objFilePath, OBJParameters& parameters) const;

    private:
        std::list<std::unique_ptr<Camera>>             _cameraList;
        std::list<std::shared_ptr<Light>>              _lightList;
        std::list<std::shared_ptr<Renderable>>         _renderableList;
        std::list<std::shared_ptr<CubeMap>>            _cubeMapList;
        std::map<std::string, std::shared_ptr<Shader>> _shaderMap;
        std::map<std::string, std::shared_ptr<BRDF>>   _bRDFMap;
        std::shared_ptr<CubeMap>                       _backgroundCubeMap;
        BackgroundType                                 _backgroundType = BackgroundType::UNDEFINED;
        Color                                          _backgroundColor;

    };  // class Scene

}  // namespace LCNS
