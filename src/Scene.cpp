//===============================================================================================//
/*!
 *  \file      Scene.cpp
 *  \author    Loïc Corenthy
 *  \version   1.0
 *  \date      14/10/2012
 *  \copyright (c) 2012 Loïc Corenthy. All rights reserved.
 */
//===============================================================================================//

#include "Scene.hpp"

#include <iostream>
#include <fstream>
#include <limits>
#include <memory>
#include <stdexcept>
#include <string>
#include <sstream>
#include <cassert>
#include <vector>
#include <algorithm>

#include "Color.hpp"
#include "Renderable.hpp"
#include "Camera.hpp"
#include "Shader.hpp"
#include "BRDF.hpp"
#include "Ray.hpp"
#include "Triangle.hpp"
#include "Light.hpp"
#include "Mesh.hpp"
#include "Light.hpp"
#include "CubeMap.hpp"

using std::cerr;
using std::cout;
using std::end;
using std::endl;
using std::find_if;
using std::ifstream;
using std::iterator;
using std::list;
using std::make_shared;
using std::numeric_limits;
using std::pair;
using std::runtime_error;
using std::shared_ptr;
using std::static_pointer_cast;
using std::stoi;
using std::string;
using std::stringstream;
using std::vector;

using LCNS::BRDF;
using LCNS::Camera;
using LCNS::Color;
using LCNS::CubeMap;
using LCNS::Light;
using LCNS::Mesh;
using LCNS::Ray;
using LCNS::Renderable;
using LCNS::Scene;
using LCNS::Shader;
using LCNS::Triangle;

Scene::~Scene(void)
{
    for_each(_cameraList.begin(), _cameraList.end(), DeleteObject());
    for_each(_lightList.begin(), _lightList.end(), DeleteObject());
}

list<Camera*>& Scene::cameraList(void)
{
    return _cameraList;
}

list<Light*>& Scene::lightList(void)
{
    return _lightList;
}

list<shared_ptr<Renderable>>& Scene::renderableList(void)
{
    return _renderableList;
}

void Scene::setBackgroundColor(const Color& color)
{
    _backgroundType  = BackgroundType::COLOR;
    _backgroundColor = color;
}

void Scene::backgroundCubeMap(shared_ptr<CubeMap> cubeMap)
{
    _backgroundType    = BackgroundType::CUBEMAP;
    _backgroundCubeMap = cubeMap;
}

Color Scene::backgroundColor(const Ray& ray) const
{
    if (_backgroundType == BackgroundType::COLOR)
        return _backgroundColor;
    else
        return _backgroundCubeMap->colorAt(ray);
}

shared_ptr<Renderable> Scene::objectNamed(const string& name)
{
    auto result = find_if(_renderableList.begin(), _renderableList.end(), [&name](shared_ptr<Renderable> object) { return object->name() == name; });

    if (result == end(_renderableList))
    {
        return nullptr;
    }
    else
    {
        return *result;
    }
}

void Scene::add(Camera* camera)
{
    assert(camera && "camera added to the scene is not valid");
    _cameraList.push_back(camera);
}

void Scene::add(Light* light)
{
    assert(light && "light added to the scene is not valid");
    _lightList.push_back(light);
}

void Scene::add(shared_ptr<Renderable> renderable)
{
    assert(renderable && "object added to the scene is not valid");
    _renderableList.push_back(renderable);
}

void Scene::add(shared_ptr<Shader> shader, const string& name)
{
    assert(shader && "shader added to the scene is not valid");
    auto success = _shaderMap.try_emplace(name, move(shader));

    if (!success.second)
    {
        auto errorMessage = string("Count not save ");
        errorMessage.append(name);
        errorMessage.append(" shader");

        throw runtime_error(move(errorMessage));
    }
}

void Scene::add(shared_ptr<BRDF> bRDF, const string& name)
{
    assert(bRDF && "brdf added to the scene is not valid");

    auto success = _bRDFMap.try_emplace(name, move(bRDF));

    if (!success.second)
    {
        auto errorMessage = string("Count not save ");
        errorMessage.append(name);
        errorMessage.append(" BRDF");

        throw runtime_error(move(errorMessage));
    }
}

void Scene::add(shared_ptr<CubeMap> cubeMap)
{
    assert(cubeMap && "cubeMap added to the scene is not valid");
    _cubeMapList.push_back(cubeMap);
}

bool Scene::intersect(Ray& ray) const
{
    float       closestDist    = numeric_limits<float>::max();
    Renderable* rClosestObject = nullptr;
    Renderable* objectFromRay  = ray.intersected();

    int i = 0;

    bool hasIntersection(false);

    if (!(_renderableList.empty()))
    {
        auto iterator = _renderableList.begin();  //(c++11)
        auto end      = _renderableList.end();

        while (iterator != end)
        {
            hasIntersection = (*iterator)->intersect(ray);
            if (hasIntersection && ray.length() < closestDist && objectFromRay != ray.intersected())
            {
                closestDist    = ray.length();
                rClosestObject = ray.intersected();
                i++;
            }

            iterator++;
        }
    }

    if (i > 0)
    {
        ray.setLength(closestDist);
        ray.setIntersected(rClosestObject);
        return true;
    }
    else
    {
        ray.setLength(numeric_limits<float>::max());
        ray.setIntersected(nullptr);
        return false;
    }
}

void Scene::createFromFile(const string& objFilePath)
{
    // Count the different parameters (vertices, normals, faces, ...) in the file
    OBJParameters parameters;
    _countVerticesAndFaces(objFilePath, parameters);

    // Create containers for the vertices and normals
    vector<Point> vertices;
    vertices.reserve(parameters.vertexCount);

    vector<Vector> normals;
    if (parameters.normalCount > 0)
        normals.reserve(parameters.normalCount);

    // Create a mesh containing all the triangle of a group
    unsigned int           currentObjectIdx = 0;
    shared_ptr<Renderable> rCurrentObject;

    Point minPoint(1000000.0, 1000000.0, 1000000.0);
    Point maxPoint(-1000000.0, -1000000.0, -1000000.0);


    Point  tmpPoint(0.0, 0.0, 0.0);
    Vector tmpNormal(0.0, 0.0, 0.0);
    double tmpDoubleValue(0.0);

    unsigned int vertexIdx        = 0;
    unsigned int textureIdx       = 0;
    unsigned int normalIdx        = 0;
    bool         lineNotProcessed = true;
    bool         firstGDefault    = true;

    // Create the triangles
    ifstream objFile(objFilePath.c_str(), ifstream::in);

    if (objFile)
    {
        string line;
        while (getline(objFile, line))
        {
            stringstream stringStream(line);
            string       word;
            lineNotProcessed = true;


            switch (line[0])
            {
                case 'g':
                    if (line == "g default")
                    {
                        if (firstGDefault)
                            firstGDefault = false;
                        else
                        {
                            throw std::runtime_error("This is suspicious code");
                            static_pointer_cast<Mesh>(rCurrentObject)->boundingBoxLimits(minPoint, maxPoint);
                            rCurrentObject = nullptr;
                            minPoint.set(1000000.0, 1000000.0, 1000000.0);
                            maxPoint.set(-1000000.0, -1000000.0, -1000000.0);

                            currentObjectIdx++;
                        }
                    }
                    else
                    {
                        rCurrentObject = make_shared<Mesh>(parameters.faceCount.at(currentObjectIdx));

                        // Read the "g"
                        stringStream >> word;

                        // Read the name of the object
                        stringStream >> word;

                        rCurrentObject->name(word);

                        _renderableList.push_back(rCurrentObject);
                    }
                    break;


                case 'v':
                    if (line[1] == ' ')
                    {
                        while (stringStream.good() && lineNotProcessed)
                        {
                            // Read the "v"
                            stringStream >> word;

                            // Read the x coordinate of the vertex
                            stringStream >> tmpDoubleValue;
                            tmpPoint.x(tmpDoubleValue);

                            stringStream >> tmpDoubleValue;
                            tmpPoint.y(tmpDoubleValue);

                            stringStream >> tmpDoubleValue;
                            tmpPoint.z(tmpDoubleValue);

                            vertices.push_back(tmpPoint);

                            lineNotProcessed = false;
                        }
                    }
                    else if (line[1] == 'n')
                    {
                        while (stringStream.good() && lineNotProcessed)
                        {
                            // Read the "vn"
                            stringStream >> word;

                            // Read the x coordinate of the vertex
                            stringStream >> tmpDoubleValue;
                            tmpNormal.setX(tmpDoubleValue);

                            stringStream >> tmpDoubleValue;
                            tmpNormal.setY(tmpDoubleValue);

                            stringStream >> tmpDoubleValue;
                            tmpNormal.setZ(tmpDoubleValue);

                            normals.push_back(tmpNormal);

                            lineNotProcessed = false;
                        }
                    }
                    break;

                case 'f':
                    if (parameters.textureCount == 0 && parameters.normalCount == 0)
                    {
                        while (stringStream.good() && lineNotProcessed)
                        {
                            shared_ptr<Renderable> triangle = make_shared<Triangle>();

                            // Read the "f"
                            stringStream >> word;

                            // Read the first vertex index
                            stringStream >> vertexIdx;
                            static_pointer_cast<Triangle>(triangle)->vertexPositions()[0] = vertices[vertexIdx - 1];

                            // Read the second vertex index
                            stringStream >> vertexIdx;
                            static_pointer_cast<Triangle>(triangle)->vertexPositions()[1] = vertices[vertexIdx - 1];

                            // Read the third vertex index
                            stringStream >> vertexIdx;
                            static_pointer_cast<Triangle>(triangle)->vertexPositions()[2] = vertices[vertexIdx - 1];


                            // Calculate the normal
                            if (parameters.normalCount > 0)
                                static_pointer_cast<Triangle>(triangle)->normal(normals[vertexIdx - 1]);
                            else
                                static_pointer_cast<Triangle>(triangle)->updateNormal();

                            _renderableList.push_back(triangle);

                            lineNotProcessed = false;
                        }
                    }
                    else
                    {
                        while (stringStream.good() && lineNotProcessed)
                        {
                            Triangle triangle;

                            // Read the "f"
                            stringStream >> word;

                            Vector localNormals[3] = { Vector(0.0, 0.0, 0.0), Vector(0.0, 0.0, 0.0), Vector(0.0, 0.0, 0.0) };

                            for (unsigned int i = 0; i < 3; ++i)
                            {
                                // Read the first combination of vertex/texture/normal indices
                                stringStream >> word;

                                char* str = new char[word.size() + 1];
                                strcpy(str, word.c_str());

                                char* subStr = strtok(str, "/");
                                vertexIdx    = static_cast<unsigned int>(stoi(subStr));

                                subStr     = strtok(NULL, "/");
                                textureIdx = static_cast<unsigned int>(stoi(subStr));

                                subStr    = strtok(NULL, "/");
                                normalIdx = static_cast<unsigned int>(stoi(subStr));

                                delete[] str;

                                triangle.vertexPositions()[i] = vertices[vertexIdx - 1];

                                // Update bounding box
                                if (vertices[vertexIdx - 1].x() < minPoint.x())
                                    minPoint.x(vertices[vertexIdx - 1].x());

                                if (vertices[vertexIdx - 1].y() < minPoint.y())
                                    minPoint.y(vertices[vertexIdx - 1].y());

                                if (vertices[vertexIdx - 1].z() < minPoint.z())
                                    minPoint.z(vertices[vertexIdx - 1].z());

                                if (vertices[vertexIdx - 1].x() > maxPoint.x())
                                    maxPoint.x(vertices[vertexIdx - 1].x());

                                if (vertices[vertexIdx - 1].y() > maxPoint.y())
                                    maxPoint.y(vertices[vertexIdx - 1].y());

                                if (vertices[vertexIdx - 1].z() > maxPoint.z())
                                    maxPoint.z(vertices[vertexIdx - 1].z());

                                triangle.vertexNormals()[i] = normals[normalIdx - 1];
                                localNormals[i]             = normals[normalIdx - 1];
                            }

                            // Calculate the normal
                            triangle.updateNormal();

                            static_pointer_cast<Mesh>(rCurrentObject)->addTriangle(triangle);

                            lineNotProcessed = false;
                        }
                    }
                    break;

                default:
                    break;
            }
        }

        // Set the bouning box of the last object
        static_pointer_cast<Mesh>(rCurrentObject)->boundingBoxLimits(minPoint, maxPoint);

        objFile.close();
    }
    else
    {
        cerr << "ERROR: Impossible to open file" << endl;
    }
}

Color Scene::meanAmbiantLight(void) const
{
    Color meanLight(0.0f);

    // Calculate mean light value: sum all the light sources intensities
    for (list<Light*>::const_iterator iterator = _lightList.begin(), end = _lightList.end(); iterator != end; iterator++)
        meanLight += (*iterator)->intensity();

    // Divide by the number of light sources
    meanLight *= 1.0f / static_cast<float>(_lightList.size());

    return meanLight;
}

void Scene::_countVerticesAndFaces(const string& objFilePath, OBJParameters& parameters) const
{
    // Open file
    ifstream objFile(objFilePath.c_str(), ifstream::in);

    if (objFile)
    {
        string line;

        // Read all the lines
        while (getline(objFile, line))
        {
            // Check the first character
            switch (line[0])
            {
                // If it's a "v", increase the vertex count
                case 'v':
                    if (line[1] == ' ')
                        ++parameters.vertexCount;
                    else if (line[1] == 't')
                        ++parameters.textureCount;
                    else if (line[1] == 'n')
                        ++parameters.normalCount;
                    break;

                // If it's a "f", increase the face count
                case 'f':
                    ++parameters.currentFaceCount;
                    break;

                case 'g':
                    if (line == "g default" && parameters.currentFaceCount != 0)
                    {
                        parameters.faceCount.push_back(parameters.currentFaceCount);
                        parameters.currentFaceCount = 0u;
                    }
                    break;

                default:
                    break;
            }
        }

        // Save the number of faces of the last object
        parameters.faceCount.push_back(parameters.currentFaceCount);
        parameters.currentFaceCount = 0u;

        // Close file
        objFile.close();
    }
    else
    {
        cout << "ERROR: Impossible to open file" << endl;
    }
}
