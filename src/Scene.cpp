#include "Scene.hpp"

// Standard includes
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <cassert>
#include <vector>

// Local includes
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
using namespace MatouMalin;

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

    for (auto lIt = _shaderMap.begin(), lEnd = _shaderMap.end(); lIt != lEnd; lIt++)
        delete lIt->second;

    for (auto lIt = _bRDFMap.begin(), lEnd = _bRDFMap.end(); lIt != lEnd; lIt++)
        delete lIt->second;

    if (_backgroundCubeMap)
        delete _backgroundCubeMap;
}

Renderable* Scene::objectNamed(const std::string& name)
{
    for (auto lIt = _renderableList.begin(), lEnd = _renderableList.end(); lIt != lEnd; lIt++)
    {
        if ((*lIt)->name() == name)
        {
            return (*lIt);
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
    float       lClosestDist   = std::numeric_limits<float>::max();
    Renderable* rClosestObject = nullptr;
    Renderable* lObjectFromRay = ray.intersected();

    int lI = 0;

    bool lHasIntersection(false);

    if (!(_renderableList.empty()))
    {
        auto lIterator = _renderableList.begin();  //(c++11)
        auto lEnd      = _renderableList.end();

        while (lIterator != lEnd)
        {
            lHasIntersection = (*lIterator)->intersect(ray);
            if (lHasIntersection && ray.length() < lClosestDist && lObjectFromRay != ray.intersected())
            {
                lClosestDist   = ray.length();
                rClosestObject = ray.intersected();
                lI++;
            }

            lIterator++;
        }
    }

    if (lI > 0)
    {
        ray.setLength(lClosestDist);
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
    OBJParameters lParameters;
    _countVerticesAndFaces(objFilePath, lParameters);

    // Create containers for the vertices and normals
    vector<Point> lVertices;
    lVertices.reserve(lParameters.vertexCount());

    vector<Vector> lNormals;
    if (lParameters.normalCount() > 0)
        lNormals.reserve(lParameters.normalCount());

    // Create a mesh containing all the triangle of a group
    unsigned int lCurrentObjectIdx = 0;
    Mesh*        rCurrentObject    = nullptr;

    Point lMinPoint(1000000.0, 1000000.0, 1000000.0);
    Point lMaxPoint(-1000000.0, -1000000.0, -1000000.0);


    Point  lTmpPoint(0.0, 0.0, 0.0);
    Vector lTmpNormal(0.0, 0.0, 0.0);
    double lTmpDoubleValue(0.0);

    unsigned int lVertexIdx(0);
    unsigned int lTextureIdx(0);
    unsigned int lNormalIdx(0);
    bool         lLineNotProcessed(true);
    bool         lFirstGDefault(true);

    // Create the triangles
    ifstream lObjFile(objFilePath.c_str(), ifstream::in);

    if (lObjFile)
    {
        string lLine;
        while (getline(lObjFile, lLine))
        {
            stringstream lStringStream(lLine);
            string       lWord;
            lLineNotProcessed = true;


            switch (lLine[0])
            {
                case 'g':
                    if (lLine == "g default")
                    {
                        if (lFirstGDefault)
                            lFirstGDefault = false;
                        else
                        {
                            rCurrentObject->setBBLimits(lMinPoint, lMaxPoint);
                            rCurrentObject = nullptr;
                            lMinPoint.setPoint(1000000.0, 1000000.0, 1000000.0);
                            lMaxPoint.setPoint(-1000000.0, -1000000.0, -1000000.0);

                            lCurrentObjectIdx++;
                        }
                    }
                    else
                    {
                        rCurrentObject = new Mesh(lParameters.faceCount(lCurrentObjectIdx));

                        // Read the "g"
                        lStringStream >> lWord;

                        // Read the name of the object
                        lStringStream >> lWord;

                        rCurrentObject->setName(lWord);

                        _renderableList.push_back(rCurrentObject);
                    }
                    break;


                case 'v':
                    if (lLine[1] == ' ')
                    {
                        while (lStringStream.good() && lLineNotProcessed)
                        {
                            // Read the "v"
                            lStringStream >> lWord;

                            // Read the x coordinate of the vertex
                            lStringStream >> lTmpDoubleValue;
                            lTmpPoint.setX(lTmpDoubleValue);

                            lStringStream >> lTmpDoubleValue;
                            lTmpPoint.setY(lTmpDoubleValue);

                            lStringStream >> lTmpDoubleValue;
                            lTmpPoint.setZ(lTmpDoubleValue);

                            lVertices.push_back(lTmpPoint);

                            lLineNotProcessed = false;
                        }
                    }
                    else if (lLine[1] == 'n')
                    {
                        while (lStringStream.good() && lLineNotProcessed)
                        {
                            // Read the "vn"
                            lStringStream >> lWord;

                            // Read the x coordinate of the vertex
                            lStringStream >> lTmpDoubleValue;
                            lTmpNormal.setX(lTmpDoubleValue);

                            lStringStream >> lTmpDoubleValue;
                            lTmpNormal.setY(lTmpDoubleValue);

                            lStringStream >> lTmpDoubleValue;
                            lTmpNormal.setZ(lTmpDoubleValue);

                            lNormals.push_back(lTmpNormal);

                            lLineNotProcessed = false;
                        }
                    }
                    break;

                case 'f':
                    if (lParameters.textureCoordinatesCount() == 0 && lParameters.normalCount() == 0)
                    {
                        while (lStringStream.good() && lLineNotProcessed)
                        {
                            Triangle* lTriangle = new Triangle;

                            // Read the "f"
                            lStringStream >> lWord;

                            // Read the first vertex index
                            lStringStream >> lVertexIdx;
                            lTriangle->setV0(lVertices[lVertexIdx - 1]);

                            // Read the second vertex index
                            lStringStream >> lVertexIdx;
                            lTriangle->setV1(lVertices[lVertexIdx - 1]);

                            // Read the third vertex index
                            lStringStream >> lVertexIdx;
                            lTriangle->setV2(lVertices[lVertexIdx - 1]);


                            // Calculate the normal
                            if (lParameters.normalCount() > 0)
                                lTriangle->setNormal(lNormals[lVertexIdx - 1]);
                            else
                                lTriangle->updateNormal();

                            _renderableList.push_back(lTriangle);

                            lLineNotProcessed = false;
                        }
                    }
                    else
                    {
                        while (lStringStream.good() && lLineNotProcessed)
                        {
                            Triangle lTriangle;

                            // Read the "f"
                            lStringStream >> lWord;

                            Vector lLocalNormals[3] = { Vector(0.0, 0.0, 0.0), Vector(0.0, 0.0, 0.0), Vector(0.0, 0.0, 0.0) };

                            for (unsigned int i = 0; i < 3; ++i)
                            {
                                // Read the first combination of vertex/texture/normal indices
                                lStringStream >> lWord;

                                char* lStr = new char[lWord.size() + 1];
                                strcpy(lStr, lWord.c_str());

                                char* lSubStr = strtok(lStr, "/");
                                lVertexIdx    = stoi(lSubStr);

                                lSubStr     = strtok(NULL, "/");
                                lTextureIdx = stoi(lSubStr);

                                lSubStr    = strtok(NULL, "/");
                                lNormalIdx = stoi(lSubStr);

                                delete[] lStr;

                                lTriangle.setVI(i, lVertices[lVertexIdx - 1]);

                                // Update bounding box
                                if (lVertices[lVertexIdx - 1].x() < lMinPoint.x())
                                    lMinPoint.setX(lVertices[lVertexIdx - 1].x());

                                if (lVertices[lVertexIdx - 1].y() < lMinPoint.y())
                                    lMinPoint.setY(lVertices[lVertexIdx - 1].y());

                                if (lVertices[lVertexIdx - 1].z() < lMinPoint.z())
                                    lMinPoint.setZ(lVertices[lVertexIdx - 1].z());

                                if (lVertices[lVertexIdx - 1].x() > lMaxPoint.x())
                                    lMaxPoint.setX(lVertices[lVertexIdx - 1].x());

                                if (lVertices[lVertexIdx - 1].y() > lMaxPoint.y())
                                    lMaxPoint.setY(lVertices[lVertexIdx - 1].y());

                                if (lVertices[lVertexIdx - 1].z() > lMaxPoint.z())
                                    lMaxPoint.setZ(lVertices[lVertexIdx - 1].z());

                                lTriangle.setVertexNormal(i, lNormals[lNormalIdx - 1]);
                                lLocalNormals[i] = lNormals[lNormalIdx - 1];
                            }

                            // Calculate the normal
                            lTriangle.updateNormal();

                            rCurrentObject->addTriangle(lTriangle);

                            lLineNotProcessed = false;
                        }
                    }
                    break;

                default:
                    break;
            }
        }

        // Set the bouning box of the last object
        rCurrentObject->setBBLimits(lMinPoint, lMaxPoint);

        lObjFile.close();
    }
    else
    {
        cerr << "ERROR: Impossible to open file" << endl;
    }
}

Color Scene::meanAmbiantLight(void) const
{
    Color lMeanLight(0.0f);

    // Calculate mean light value: sum all the light sources intensities
    for (list<Light*>::const_iterator lIterator = _lightList.begin(), lEnd = _lightList.end(); lIterator != lEnd; lIterator++)
        lMeanLight += (*lIterator)->intensity();

    // Divide by the number of light sources
    lMeanLight *= 1.0f / static_cast<float>(_lightList.size());

    return lMeanLight;
}

void Scene::_countVerticesAndFaces(const std::string& objFilePath, OBJParameters& parameters) const
{
    // Open file
    ifstream lObjFile(objFilePath.c_str(), ifstream::in);

    if (lObjFile)
    {
        string lLine;

        // Read all the lines
        while (getline(lObjFile, lLine))
        {
            // Check the first character
            switch (lLine[0])
            {
                // If it's a "v", increase the vertex count
                case 'v':
                    if (lLine[1] == ' ')
                        parameters.vpp();
                    else if (lLine[1] == 't')
                        parameters.vtpp();
                    else if (lLine[1] == 'n')
                        parameters.npp();
                    break;

                // If it's a "f", increase the face count
                case 'f':
                    parameters.fpp();
                    break;

                case 'g':
                    if (lLine == "g default" && parameters.currentFaceCount() != 0)
                        parameters.opp();

                default:
                    break;
            }
        }

        // Save the number of faces of the last object
        parameters.opp();

        // Close file
        lObjFile.close();
    }
    else
    {
        cout << "ERROR: Impossible to open file" << endl;
    }
}
