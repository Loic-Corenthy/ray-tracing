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
#include <string>
#include <sstream>
#include <cassert>
#include <vector>

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

using namespace std;
using namespace LCNS;

Scene::Scene(void)
: _backgroundType(BACKGRD_UNDEFINED)
, _backgroundColor(Color(0.0))
, _backgroundCubeMap(nullptr)
{
}

Scene::Scene(const Scene& scene)
: _cameraList(scene._cameraList)
, _lightList(scene._lightList)
, _renderableList(scene._renderableList)
, _shaderMap(scene._shaderMap)
, _bRDFMap(scene._bRDFMap)
, _backgroundType(scene._backgroundType)
, _backgroundColor(scene._backgroundColor)
, _backgroundCubeMap(scene._backgroundCubeMap)
{
}

Scene Scene::operator=(const Scene& scene)
{
    if (this == &scene)
        return *this;

    _cameraList        = scene._cameraList;
    _lightList         = scene._lightList;
    _renderableList    = scene._renderableList;
    _shaderMap         = scene._shaderMap;
    _bRDFMap           = scene._bRDFMap;
    _backgroundType    = scene._backgroundType;
    _backgroundColor   = scene._backgroundColor;
    _backgroundCubeMap = scene._backgroundCubeMap;

    return *this;
}

Scene::~Scene(void)
{
    for_each(_cameraList.begin(), _cameraList.end(), DeleteObject());
    for_each(_lightList.begin(), _lightList.end(), DeleteObject());
    for_each(_renderableList.begin(), _renderableList.end(), DeleteObject());
    for_each(_cubeMapList.begin(), _cubeMapList.end(), DeleteObject());

    for (auto it = _shaderMap.begin(), end = _shaderMap.end(); it != end; it++)
        delete it->second;

    for (auto it = _bRDFMap.begin(), end = _bRDFMap.end(); it != end; it++)
        delete it->second;

    if (_backgroundCubeMap)
        delete _backgroundCubeMap;
}

Renderable* Scene::objectNamed(const std::string& name)
{
    for (auto it = _renderableList.begin(), end = _renderableList.end(); it != end; it++)
    {
        if ((*it)->name() == name)
        {
            return (*it);
        }
    }

    return nullptr;
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

void Scene::add(Renderable* renderable)
{
    assert(renderable && "object added to the scene is not valid");
    _renderableList.push_back(renderable);
}

void Scene::add(Shader* shader, const std::string& name)
{
    assert(shader && "shader added to the scene is not valid");
    _shaderMap.insert(std::pair<std::string, Shader*>(name, shader));
}

void Scene::add(BRDF* bRDF, const std::string& name)
{
    assert(bRDF && "brdf added to the scene is not valid");
    _bRDFMap.insert(std::pair<std::string, BRDF*>(name, bRDF));
}

void Scene::add(CubeMap* cubeMap)
{
    assert(cubeMap && "cubeMap added to the scene is not valid");
    _cubeMapList.push_back(cubeMap);
}

bool Scene::intersect(Ray& ray) const
{
    float       closestDist    = std::numeric_limits<float>::max();
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
        ray.setLength(std::numeric_limits<float>::max());
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
    vertices.reserve(parameters.vertexCount());

    vector<Vector> normals;
    if (parameters.normalCount() > 0)
        normals.reserve(parameters.normalCount());

    // Create a mesh containing all the triangle of a group
    unsigned int currentObjectIdx = 0;
    Mesh*        rCurrentObject   = nullptr;

    Point minPoint(1000000.0, 1000000.0, 1000000.0);
    Point maxPoint(-1000000.0, -1000000.0, -1000000.0);


    Point  tmpPoint(0.0, 0.0, 0.0);
    Vector tmpNormal(0.0, 0.0, 0.0);
    double tmpDoubleValue(0.0);

    unsigned int vertexIdx(0);
    unsigned int textureIdx(0);
    unsigned int normalIdx(0);
    bool         lineNotProcessed(true);
    bool         firstGDefault(true);

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
                            rCurrentObject->setBBLimits(minPoint, maxPoint);
                            rCurrentObject = nullptr;
                            minPoint.set(1000000.0, 1000000.0, 1000000.0);
                            maxPoint.set(-1000000.0, -1000000.0, -1000000.0);

                            currentObjectIdx++;
                        }
                    }
                    else
                    {
                        rCurrentObject = new Mesh(parameters.faceCount(currentObjectIdx));

                        // Read the "g"
                        stringStream >> word;

                        // Read the name of the object
                        stringStream >> word;

                        rCurrentObject->setName(word);

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
                    if (parameters.textureCoordinatesCount() == 0 && parameters.normalCount() == 0)
                    {
                        while (stringStream.good() && lineNotProcessed)
                        {
                            Triangle* triangle = new Triangle;

                            // Read the "f"
                            stringStream >> word;

                            // Read the first vertex index
                            stringStream >> vertexIdx;
                            triangle->setV0(vertices[vertexIdx - 1]);

                            // Read the second vertex index
                            stringStream >> vertexIdx;
                            triangle->setV1(vertices[vertexIdx - 1]);

                            // Read the third vertex index
                            stringStream >> vertexIdx;
                            triangle->setV2(vertices[vertexIdx - 1]);


                            // Calculate the normal
                            if (parameters.normalCount() > 0)
                                triangle->setNormal(normals[vertexIdx - 1]);
                            else
                                triangle->updateNormal();

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
                                vertexIdx    = stoi(subStr);

                                subStr     = strtok(NULL, "/");
                                textureIdx = stoi(subStr);

                                subStr    = strtok(NULL, "/");
                                normalIdx = stoi(subStr);

                                delete[] str;

                                triangle.setVI(i, vertices[vertexIdx - 1]);

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

                                triangle.setVertexNormal(i, normals[normalIdx - 1]);
                                localNormals[i] = normals[normalIdx - 1];
                            }

                            // Calculate the normal
                            triangle.updateNormal();

                            rCurrentObject->addTriangle(triangle);

                            lineNotProcessed = false;
                        }
                    }
                    break;

                default:
                    break;
            }
        }

        // Set the bouning box of the last object
        rCurrentObject->setBBLimits(minPoint, maxPoint);

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

void Scene::_countVerticesAndFaces(const std::string& objFilePath, OBJParameters& parameters) const
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
                        parameters.vpp();
                    else if (line[1] == 't')
                        parameters.vtpp();
                    else if (line[1] == 'n')
                        parameters.npp();
                    break;

                // If it's a "f", increase the face count
                case 'f':
                    parameters.fpp();
                    break;

                case 'g':
                    if (line == "g default" && parameters.currentFaceCount() != 0)
                        parameters.opp();

                default:
                    break;
            }
        }

        // Save the number of faces of the last object
        parameters.opp();

        // Close file
        objFile.close();
    }
    else
    {
        cout << "ERROR: Impossible to open file" << endl;
    }
}
