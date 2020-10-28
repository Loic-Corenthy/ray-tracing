//
//  CreateScenes.h
//  RayTracing
//
//  Created by Loïc CORENTHY on 12/15/12.
//
//

#ifndef RAYTRACING_CREATE_SCENES_H
#define RAYTRACING_CREATE_SCENES_H

#include <vector>
#include <string>

#include <cmath>

#include "Buffer.hpp"
#include "Camera.hpp"
#include "Color.hpp"
#include "Light.hpp"
#include "DirectionalLight.hpp"
#include "PunctualLight.hpp"
#include "BRDF.hpp"
#include "Shader.hpp"
#include "Phong.hpp"
#include "Ray.hpp"
#include "Renderable.hpp"
#include "Renderer.hpp"
#include "Scene.hpp"
#include "Point.hpp"
#include "Vector.hpp"
#include "Triangle.hpp"
#include "Sphere.hpp"
#include "Image.hpp"
#include "CubeMap.hpp"

struct FloorParameters
{
    MatouMalin::Color diffusion;
    MatouMalin::Color specular;
    double reflectionCoeff;
    double refractionCoeff;
    unsigned short maxReflection;
    double size;
    double deep;
    std::string floorTexturePath;
};

struct RoomParameters
{
    MatouMalin::Color diffusion;
    MatouMalin::Color specular;
    double reflectionCoeff;
    double refractionCoeff;
    unsigned short maxReflection;
    MatouMalin::Point lowCorner;
    MatouMalin::Vector dimensions;
    std::string floorTexturePath;
    std::string wallLeftTexturePath;
    std::string wallRightTexturePath;
    std::string wallBackTexturePath;
    std::string ceilingTexturePath;
};

/// Create a test scene
void createTestScene(MatouMalin::Scene* pScene);

// Create a basic scene with 3 spheres (reflection coeff: 2)
void createScene01(MatouMalin::Scene* pScene);

// Create a scene with: red, green and blue sphere + damier floor. Pink sphere in the back to illustrate the blur (reflection coeff: 3)
void createScene02(MatouMalin::Scene* pScene);

// Create a scene with: a room and 3 spheres
void createScene03(MatouMalin::Scene* pScene);

// Create a scene with: a red, green and blue sphere + damier floor. All sharp scene, illustrate multiple reflections
void createScene04(MatouMalin::Scene* pScene);

// Create a scene with: a red, green and blue sphere + small damier floor. All sharp scene
void createScene04bis(MatouMalin::Scene* pScene);

// Create a scene with: an object loaded from a .obj file (the torus)
void createScene05(MatouMalin::Scene* pScene);

// Create a scene with: a transparent sphere with refraction and a background using a cubemap
void createScene06(MatouMalin::Scene* pScene);

// Create a scene with: a room containing sphere with the different noise effects
void createScene07(MatouMalin::Scene* pScene);

// Create a scene with: a sphere close and a sphere far from the camera (test the aperture efects)
void createScene08(MatouMalin::Scene* pScene);

/// Create a scene with: several objects loaded from an .obj file (the head)
void createScene09(MatouMalin::Scene* pScene);

/// Create a scene with: 2 spheres + a floor and lights of different colors
void createScene10(MatouMalin::Scene* pScene);

/// Create a scene with: 3 spheres with different max reflection counts
void createScene11(MatouMalin::Scene* pScene);

/// Create a scene with: a room and 3 spheres
void createScene12(MatouMalin::Scene* pScene);

/// Create a scene with: a table in a room, mirrors and a sphere with a texture 
void createScene13(MatouMalin::Scene* pScene);

/// Create a scene with: a table with a refractive sphere on top of it, use a cubemap as the background
void createScene14(MatouMalin::Scene* pScene);

// Create a square (2 triangles) to symbolise a floor
void createFloor(MatouMalin::Scene* pScene, const FloorParameters & pParam);

// Create a "room" with a floor and 3 walls
void createRoom(MatouMalin::Scene* pScene, const RoomParameters & pParam);


#endif