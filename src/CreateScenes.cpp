//===============================================================================================//
/*!
 *  \file      CreateScenes.cpp
 *  \author    Loïc Corenthy
 *  \version   1.0
 *  \date      15/12/2012
 *  \copyright (c) 2012 Loïc Corenthy. All rights reserved.
 */
//===============================================================================================//

#include "CreateScenes.hpp"

#include <iostream>
#include <algorithm>
#include <memory>

using namespace LCNS;

using std::make_shared;
using std::max;
using std::string;

void createTestScene(LCNS::Scene* scene)
{
    LCNS::Point centerSphere1(0.0, 0.0, 0.0);
    Renderable* rSphere1 = new Sphere(centerSphere1, 2.3);

    // Create a BRDF model for the sphere
    Color diffusionSphere1(1.0f, 0.0f, 0.0f);
    Color specularSphere1(0.7f, 0.3f, 0.3f);
    BRDF* rBRDFSphere1 = new Phong(diffusionSphere1, specularSphere1, 5);

    // Create a shader for the sphere
    Shader* rShaderSphere1 = new Shader(rBRDFSphere1, 1.0, 1.0, scene, Shader::NONE);
    rShaderSphere1->setReflectionCountMax(2);
    rSphere1->setShader(rShaderSphere1);

    scene->add(rSphere1);
    scene->add(rBRDFSphere1, string("brdf of sphere 1"));
    scene->add(rShaderSphere1, string("shader of sphere 1"));


    ////////////
    // LIGHTS //
    ////////////
    Light* rLight1 = new DirectionalLight(Vector(0.0, 0.0, -1.0), Color(22.0));
    scene->add(rLight1);


    //    LCNS::Point light2Position(0.f,1.0f,0.0f);
    //	Light* rLight2 = new PunctualLight(light2Position,lLight1Color);
    //    scene->add(rLight2);

    ////////////
    // CAMERA //
    ////////////
    LCNS::Point centreCamera(0.0f, 7.0f, 10.0f);
    Vector      directionCamera(0.00f, -0.4f, -1.0f);
    Vector      cameraUp(0.f, 1.f, 0.f);
    float       FOV = 60.f * 3.141592 / 180.f;

    Camera* rCamera = new Camera(centreCamera, directionCamera, cameraUp, FOV);
    scene->add(rCamera);


    ////////////////
    // BACKGROUND //
    ////////////////
    scene->setBackgroundColor(Color(0.3f));
}

void createScene01(Scene* scene)
{
    // Same reflection coefficient for all the spheres
    double reflectionCoeff(2.0);
    double refractionCoeff(1.0);

    ////////////////
    // RED SPHERE //
    ////////////////
    LCNS::Point centerSphere1(0.0, 2.0, 2.1);
    Renderable* rSphere1 = new Sphere(centerSphere1, 0.3);

    // Create a BRDF model for the sphere
    Color diffusionSphere1(1.0f, 0.0f, 0.0f);
    Color specularSphere1(0.7f, 0.3f, 0.3f);
    BRDF* rBRDFSphere1 = new Phong(diffusionSphere1, specularSphere1, 5);

    // Create a shader for the sphere
    Shader* rShaderSphere1 = new Shader(rBRDFSphere1, reflectionCoeff, refractionCoeff, scene, Shader::MARBLE);
    rShaderSphere1->setReflectionCountMax(2);
    rSphere1->setShader(rShaderSphere1);

    scene->add(rSphere1);
    scene->add(rBRDFSphere1, string("brdf of sphere 1"));
    scene->add(rShaderSphere1, string("shader of sphere 1"));

    //////////////////
    // GREEN SPHERE //
    //////////////////
    LCNS::Point centerSphere2(2.0, 0.5, 0.0);
    Renderable* rSphere2 = new Sphere(centerSphere2, 1.5);

    // Create a BRDF model for the sphere
    Color diffusionSphere2(0.0f, 1.0f, 0.0f);
    Color specularSphere2(1.0f);
    BRDF* rBRDFSphere2 = new Phong(diffusionSphere2, specularSphere2, 15);

    // Create a shader for the second sphere
    Shader* rShaderSphere2 = new Shader(rBRDFSphere2, reflectionCoeff, refractionCoeff, scene, Shader::MARBLE);
    rShaderSphere2->setReflectionCountMax(2);
    rSphere2->setShader(rShaderSphere2);

    scene->add(rSphere2);
    scene->add(rBRDFSphere2, string("brdf of sphere 2"));
    scene->add(rShaderSphere2, string("shader of sphere 2"));

    /////////////////
    // BLUE SPHERE //
    /////////////////
    LCNS::Point centerSphere3(-1.8, 0.0, 0.0);
    Renderable* rSphere3 = new Sphere(centerSphere3, 1.0);

    // Create a BRDF model for the sphere
    Color diffusionSphere3(0.0f, 0.0f, 1.0f);
    Color specularSphere3(0.8f, 0.8f, 1.0f);
    BRDF* rBRDFSphere3 = new Phong(diffusionSphere3, specularSphere3, 25);

    // Create a shader for the third sphere
    Shader* rShaderSphere3 = new Shader(rBRDFSphere3, reflectionCoeff, refractionCoeff, scene, Shader::MARBLE);
    rShaderSphere3->setReflectionCountMax(2);
    rSphere3->setShader(rShaderSphere3);

    scene->add(rSphere3);
    scene->add(rBRDFSphere3, string("brdf of sphere 3"));
    scene->add(rShaderSphere3, string("shader of sphere 3"));

    ////////////
    // LIGHTS //
    ////////////
    LCNS::Point light1Position(0.f, 0.0f, 5.0f);
    Color       light1Color(9.0f);
    Light*      rLight1 = new PunctualLight(light1Position, light1Color);
    scene->add(rLight1);

    ////////////
    // CAMERA //
    ////////////
    LCNS::Point centreCamera(0.0f, 2.5f, 6.0f);
    Vector      directionCamera(0.05f, -0.4f, -1.0f);
    Vector      cameraUp(0.f, 1.f, 0.f);
    float       FOV = 60.f * 3.141592 / 180.f;

    Camera* rCamera = new Camera(centreCamera, directionCamera, cameraUp, FOV);
    scene->add(rCamera);

    ////////////////
    // BACKGROUND //
    ////////////////
    scene->setBackgroundColor(Color(0));
}


void createScene02(Scene* scene)
{
    // Same reflection coefficient for the spheres behind
    double reflectionCoeff(5.8);
    double refractionCoeff(1.0);

    ////////////////
    // RED SPHERE //
    ////////////////
    LCNS::Point centerSphere1(-60.0, 0.0, 60.0);
    Sphere*     rSphere1 = new Sphere(centerSphere1, 40.f);

    // Create a BRDF model for the sphere
    Color  diffusionSphere1(1.0f, 0.6f, 0.6f);
    Color  specularSphere1(0.9f, 0.4f, 0.4f);
    Phong* rBRDFSphere1 = new Phong(diffusionSphere1 * 2.0, specularSphere1, 3);

    // Create a shader for the sphere
    Shader* rShaderSphere1 = new Shader(rBRDFSphere1, reflectionCoeff, refractionCoeff, scene);
    rShaderSphere1->setReflectionCountMax(3);
    rSphere1->setShader(rShaderSphere1);

    scene->add(rSphere1);
    scene->add(rBRDFSphere1, string("brdf of sphere 1"));
    scene->add(rShaderSphere1, string("shader of sphere 1"));


    //////////////////
    // GREEN SPHERE //
    //////////////////
    LCNS::Point centerSphere2(60.0, 0.0, 50.0);
    Sphere*     rSphere2 = new Sphere(centerSphere2, 40.f);

    // Create a BRDF model for the sphere
    Color  diffusionSphere2(0.6f, 1.0f, 0.6f);
    Color  specularSphere2(0.4, 1.0f, 0.4f);
    Phong* rBRDFSphere2 = new Phong(diffusionSphere2 * 2.0, specularSphere2, 3);

    // Create a shader for the second sphere
    Shader* rShaderSphere2 = new Shader(rBRDFSphere2, reflectionCoeff, refractionCoeff, scene);
    rShaderSphere2->setReflectionCountMax(3);
    rSphere2->setShader(rShaderSphere2);

    scene->add(rSphere2);
    scene->add(rBRDFSphere2, string("brdf of sphere 2"));
    scene->add(rShaderSphere2, string("shader of sphere 2"));


    /////////////////
    // BLUE SPHERE //
    /////////////////
    LCNS::Point centerSphere3(0.0, -10.0, 110.0);
    Sphere*     rSphere3 = new Sphere(centerSphere3, 20.0f);

    // Create a BRDF model for the sphere
    Color  diffusionSphere3(0.6f, 0.6f, 1.0f);
    Color  specularSphere3(0.4f, 0.4f, 0.9f);
    Phong* rBRDFSphere3 = new Phong(diffusionSphere3 * 2.0, specularSphere3, 3);

    // Create a shader for the third sphere
    Shader* rShaderSphere3 = new Shader(rBRDFSphere3, reflectionCoeff, 1.0, scene);
    rShaderSphere3->setReflectionCountMax(3);
    rSphere3->setShader(rShaderSphere3);

    scene->add(rSphere3);
    scene->add(rBRDFSphere3, string("brdf of sphere 3"));
    scene->add(rShaderSphere3, string("shader of sphere 3"));


    ///////////////////////////////
    // CYAN SPHERE IN BACKGROUND //
    ///////////////////////////////
    LCNS::Point centerSphere4(-50.0, 0.0, -250.0);
    Sphere*     rSphere4 = new Sphere(centerSphere4, 100.0f);

    // Create a BRDF model for the sphere
    Color  diffusionSphere4(0, 255, 255);
    Color  specularSphere4(0.0f);
    Phong* rBRDFSphere4 = new Phong(diffusionSphere4 * 6, specularSphere4, 3);

    // Create a shader for the fourth sphere
    Shader* rShaderSphere4 = new Shader(rBRDFSphere4, 0.0, 1.0, scene);
    rSphere4->setShader(rShaderSphere4);

    scene->add(rSphere4);
    scene->add(rBRDFSphere4, string("brdf of sphere 4"));
    scene->add(rShaderSphere4, string("shader of sphere 4"));


    ///////////
    // FLOOR //
    ///////////
    FloorParameters floorParameters = { Color(1.0), Color(0.8), 2.0, 1.0, 2, 400.0, 80.0, string("./resources/damierBlueYellow.png") };
    createFloor(scene, floorParameters);


    ////////////
    // LIGHTS //
    ////////////
    LCNS::Point light1Position(50.f, 130.f, 150.0f);
    Color       light1Color(18.0f);
    Light*      rLight1 = new PunctualLight(light1Position, light1Color);
    scene->add(rLight1);

    LCNS::Point light2Position(20.f, 150.f, 150.0f);
    Color       light2Color(18.0f);
    Light*      rLight2 = new PunctualLight(light2Position, light2Color);
    scene->add(rLight2);

    LCNS::Point light3Position(-70.f, 50.f, 110.0f);
    Color       light3Color(15.0f);
    Light*      rLight3 = new PunctualLight(light3Position, light3Color);
    scene->add(rLight3);

    LCNS::Point light4Position(-20.f, 50.f, 160.0f);
    Color       light4Color(15.0f);
    Light*      rLight4 = new PunctualLight(light4Position, light4Color);
    scene->add(rLight4);


    ////////////
    // CAMERA //
    ////////////
    LCNS::Point centreCamera(0.0f, 100.0f, 250.0f);
    Vector      directionCamera(0.0f, -0.6f, -1.0f);
    Vector      cameraUp(0.f, 1.f, 0.f);
    float       FOV = 80.f * 3.141592 / 180.f;

    Camera* rCamera = new Camera(centreCamera, directionCamera, cameraUp, FOV);
    rCamera->focalPoint(centerSphere3);
    rCamera->aperture(Camera::Aperture::F_SMALL, Camera::Precision::SUPER_AWESOME);

    scene->add(rCamera);


    ////////////////
    // BACKGROUND //
    ////////////////
    scene->setBackgroundColor(Color(2, 6, 13));
}

void createScene03(Scene* scene)
{
    // Same reflection coefficient for the spheres
    double reflection(1.0);
    double refraction(1.0);

    //////////////////////////////////////
    // SPHERE WITH A TURBULANCE TEXTURE //
    //////////////////////////////////////
    LCNS::Point center(-20.0, 0.0, 0.0);
    Sphere*     rSphere1 = new Sphere(center, 3.0f);

    Color  diffusion(245, 222, 179);
    Color  specular(255, 255, 255);
    Phong* rBRDF1 = new Phong(diffusion * 2.0, specular, 15);

    // Create a shader for the turbulance sphere
    Shader* rShader1 = new Shader(rBRDF1, reflection, refraction, scene, Shader::Material::TURBULANCE);
    rShader1->setReflectionCountMax(2);

    rSphere1->setShader(rShader1);

    scene->add(rSphere1);
    scene->add(rBRDF1, string("brdf of sphere 1"));
    scene->add(rShader1, string("shader of sphere 1"));

    //////////////////////////////////
    // SPHERE WITH A MARBLE TEXTURE //
    //////////////////////////////////
    center.set(-10.0, 0.0, 0.0);
    Sphere* rSphere2 = new Sphere(center, 3.0f);

    diffusion.set(0, 255, 255);
    Phong* rBRDF2 = new Phong(diffusion, specular, 15);

    // Create a shader for the marble sphere
    Shader* rShader2 = new Shader(rBRDF2, reflection, refraction, scene, Shader::Material::MARBLE);
    rShader2->setReflectionCountMax(2);

    rSphere2->setShader(rShader2);

    scene->add(rSphere2);
    scene->add(rBRDF2, string("brdf of sphere 2"));
    scene->add(rShader2, string("shader of sphere 2"));

    ///////////
    // TORUS //
    ///////////
    string path = "./resources/torus.obj";
    scene->createFromFile(path);

    // Create a BRDF model for the torus
    diffusion.set(255, 105, 0);
    Phong* rBRDFTorus = new Phong(diffusion, specular, 3);

    // Create a shader for the torus
    Shader* rShaderTorus = new Shader(rBRDFTorus, 0.8, 1.0, scene, Shader::NONE);

    // Get an iterator on the object of the scene and displace it until refers to the torus
    auto it = scene->renderableList().begin();
    it++;
    it++;

    (*it)->setShader(rShaderTorus);

    scene->add(rBRDFTorus, string("brdf of the torus"));
    scene->add(rShaderTorus, string("shader of the torus"));

    ////////////////////////////////
    // SPHERE WITH A BUMP TEXTURE //
    ////////////////////////////////
    center.set(8.0, 0.0, 0.0);
    Sphere* rSphere3 = new Sphere(center, 3.0f);

    diffusion.set(127, 255, 0);
    Phong* rBRDF3 = new Phong(diffusion, specular, 15);

    // Create a shader for the marble sphere
    Shader* rShader3 = new Shader(rBRDF3, reflection, refraction, scene, Shader::Material::BUMP);
    rShader3->setReflectionCountMax(2);

    rSphere3->setShader(rShader3);

    scene->add(rSphere3);
    scene->add(rBRDF3, string("brdf of sphere 2"));
    scene->add(rShader3, string("shader of sphere 2"));

    ///////////////////////////
    // SPHERE WITH A TEXTURE //
    ///////////////////////////
    center.set(18.0, 0.0, 0.0);
    Renderable* rSphere4 = new Sphere(center, 3.0);

    // Create a BRDF model for the sphere
    auto rCubeMapSphere = make_shared<CubeMap>(center, 104);
    rCubeMapSphere->addImage(CubeMap::Faces::BACK, "./resources/earth_back.png");
    rCubeMapSphere->addImage(CubeMap::Faces::FRONT, "./resources/earth_front.png");
    rCubeMapSphere->addImage(CubeMap::Faces::UP, "./resources/earth_up.png");
    rCubeMapSphere->addImage(CubeMap::Faces::DOWN, "./resources/earth_down.png");
    rCubeMapSphere->addImage(CubeMap::Faces::LEFT, "./resources/earth_left.png");
    rCubeMapSphere->addImage(CubeMap::Faces::RIGHT, "./resources/earth_right.png");
    rCubeMapSphere->interpolationMethod(Image::InterpolationMethod::LINEAR);

    scene->add(rCubeMapSphere);

    diffusion.set(255, 255, 255);
    BRDF* rBRDF4 = new Phong(diffusion * 2.0, specular, 15);
    rBRDF4->cubeMap(rCubeMapSphere);

    // Create a shader for the sphere
    Shader* rShader4 = new Shader(rBRDF4, reflection, refraction, scene);
    rShader4->setReflectionCountMax(1);
    rSphere4->setShader(rShader4);

    scene->add(rSphere4);
    scene->add(rBRDF4, string("brdf of sphere 4"));
    scene->add(rShader4, string("shader of sphere 4"));


    ////////////
    // LIGHTS //
    ////////////
    LCNS::Point lightPos(0.0, 20.0, 15.0);
    Color       lightCol(18.0f);

    Light* rLight = new PunctualLight(lightPos, lightCol);
    scene->add(rLight);


    ////////////
    // CAMERA //
    ////////////
    LCNS::Point centreCamera(1.5f, 10.0f, 25.0f);
    Vector      directionCamera(-0.05f, -0.4f, -1.0f);
    Vector      cameraUp(0.f, 1.0f, 0.f);
    float       FOV = 90.f * 3.141592 / 180.f;

    Camera* rCamera = new Camera(centreCamera, directionCamera, cameraUp, FOV);
    rCamera->aperture(Camera::Aperture::ALL_SHARP);

    scene->add(rCamera);

    ///////////
    // FLOOR //
    ///////////
    FloorParameters floorParameters = { Color(0.0f), Color(0.0f), 1.0f, 1.0f, 2, 40.0, 3.0, string("no_texture") };
    createFloor(scene, floorParameters);


    ////////////////
    // BACKGROUND //
    ////////////////
    scene->setBackgroundColor(Color(0.0f));
}


void createScene04(Scene* scene)
{
    // Same reflection coefficient for the spheres behind
    double reflectionCoeff(8.0);
    double refractionCoeff(1.0);

    // Create a sphere
    LCNS::Point centerSphere1(-180.0, 0.0, 0.0);
    Sphere*     rSphere1 = new Sphere(centerSphere1, 50.f);

    // Create a BRDF model for the sphere
    Color  diffusionSphere1(1.3f, 0.0f, 0.0f);
    Color  specularSphere1(1.0f);
    Phong* rBRDFSphere1 = new Phong(diffusionSphere1, specularSphere1, 25);

    // Create a shader for the sphere
    Shader* rShaderSphere1 = new Shader(rBRDFSphere1, reflectionCoeff, refractionCoeff, scene);
    rShaderSphere1->setReflectionCountMax(2);
    rSphere1->setShader(rShaderSphere1);

    scene->add(rSphere1);
    scene->add(rBRDFSphere1, string("brdf of sphere 1"));
    scene->add(rShaderSphere1, string("shader of sphere 1"));

    // Create a second sphere
    LCNS::Point centerSphere2(0.0, 0.0, 0.0);
    Sphere*     rSphere2 = new Sphere(centerSphere2, 50.f);

    // Create a BRDF model for the sphere
    Color  diffusionSphere2(0.0f, 1.2f, 0.0f);
    Color  specularSphere2(0.8f);
    Phong* rBRDFSphere2 = new Phong(diffusionSphere2, specularSphere2, 25);

    // Create a shader for the second sphere
    Shader* rShaderSphere2 = new Shader(rBRDFSphere2, reflectionCoeff, refractionCoeff, scene);
    rShaderSphere2->setReflectionCountMax(2);
    rSphere2->setShader(rShaderSphere2);

    scene->add(rSphere2);
    scene->add(rBRDFSphere2, string("brdf of sphere 2"));
    scene->add(rShaderSphere2, string("shader of sphere 2"));

    // Create a purple sphere
    LCNS::Point centerSphere3(180.0, 0.0, 0.0);
    Sphere*     rSphere3 = new Sphere(centerSphere3, 50.0f);

    // Create a BRDF model for the sphere
    Color  diffusionSphere3(0.24f, 0.34f, 1.97f);
    Color  specularSphere3(0.8);
    Phong* rBRDFSphere3 = new Phong(diffusionSphere3, specularSphere3, 25);

    // Create a shader for the third sphere
    Shader* rShaderSphere3 = new Shader(rBRDFSphere3, reflectionCoeff, refractionCoeff, scene);
    rShaderSphere3->setReflectionCountMax(2);
    rSphere3->setShader(rShaderSphere3);

    scene->add(rSphere3);
    scene->add(rBRDFSphere3, string("brdf of sphere 3"));
    scene->add(rShaderSphere3, string("shader of sphere 3"));


    ////////////
    // LIGHTS //
    ////////////
    LCNS::Point light1Position(0.f, 0.0f, 100.0f);
    Color       lowLightColor(20.0f);
    Light*      rLight1 = new PunctualLight(light1Position, lowLightColor);
    scene->add(rLight1);

    LCNS::Point light2Position(-200.f, 0.0f, 100.0f);
    Light*      rLight2 = new PunctualLight(light2Position, lowLightColor);
    scene->add(rLight2);

    LCNS::Point light3Position(200.f, 0.0f, 100.0f);
    Light*      rLight3 = new PunctualLight(light3Position, lowLightColor);
    scene->add(rLight3);

    LCNS::Point light4Position(90.f, 300.f, 200.0f);
    Color       highLightColor(200.0f);
    Light*      rLight4 = new PunctualLight(light4Position, highLightColor);
    scene->add(rLight4);

    LCNS::Point light5Position(-90.f, 300.f, 200.0f);
    Light*      rLight5 = new PunctualLight(light5Position, highLightColor);
    scene->add(rLight5);

    ////////////
    // CAMERA //
    ////////////
    LCNS::Point centreCamera(-200.0f, 150.0f, 400.0f);
    Vector      directionCamera(0.2f, -0.25f, -0.5f);
    Vector      cameraUp(0.f, 1.f, 0.f);
    float       FOV = 80.f * 3.141592 / 180.f;

    Camera* rCamera = new Camera(centreCamera, directionCamera, cameraUp, FOV);
    rCamera->aperture(Camera::Aperture::ALL_SHARP, Camera::Precision::LOW, 10.0);

    scene->add(rCamera);

    // FLOOR
    FloorParameters floorParameters = { Color(1.0f), Color(0.3f), 1.0f, 1.0f, 2, 2000.0, 100.0, string("./resources/rect5130.png") };

    createFloor(scene, floorParameters);

    ////////////////
    // BACKGROUND //
    ////////////////
    scene->setBackgroundColor(Color(0.0f));
}

void createScene04bis(LCNS::Scene* scene)
{
    // Same reflection coefficient for the spheres
    double reflectionCoeff(8.0);
    double refractionCoeff(1.0);

    ////////////////
    // RED SPHERE //
    ////////////////
    LCNS::Point centerSphere1(-2.50, 0.0, 0.0);
    Sphere*     rSphere1 = new Sphere(centerSphere1, 1.0f);

    // Create a BRDF model for the sphere
    Color  diffusionSphere1(1.3f, 0.0f, 0.0f);
    Color  specularSphere1(1.0f);
    Phong* rBRDFSphere1 = new Phong(diffusionSphere1, specularSphere1, 25);

    // Create a shader for the sphere
    Shader* rShaderSphere1 = new Shader(rBRDFSphere1, reflectionCoeff, refractionCoeff, scene);
    rShaderSphere1->setReflectionCountMax(4);
    rSphere1->setShader(rShaderSphere1);

    scene->add(rSphere1);
    scene->add(rBRDFSphere1, string("brdf of sphere 1"));
    scene->add(rShaderSphere1, string("shader of sphere 1"));


    //////////////////
    // GREEN SPHERE //
    //////////////////
    LCNS::Point centerSphere2(0.0, 0.0, 0.0);
    Sphere*     rSphere2 = new Sphere(centerSphere2, 1.0f);

    // Create a BRDF model for the sphere
    Color  diffusionSphere2(0.0f, 1.2f, 0.0f);
    Color  specularSphere2(0.8f);
    Phong* rBRDFSphere2 = new Phong(diffusionSphere2, specularSphere2, 25);

    // Create a shader for the second sphere
    Shader* rShaderSphere2 = new Shader(rBRDFSphere2, reflectionCoeff, refractionCoeff, scene);
    rShaderSphere2->setReflectionCountMax(4);
    rSphere2->setShader(rShaderSphere2);

    scene->add(rSphere2);
    scene->add(rBRDFSphere2, string("brdf of sphere 2"));
    scene->add(rShaderSphere2, string("shader of sphere 2"));

    ///////////////////
    // PURPLE SPHERE //
    ///////////////////
    LCNS::Point centerSphere3(2.50, 0.0, 0.0);
    Sphere*     rSphere3 = new Sphere(centerSphere3, 1.0f);

    // Create a BRDF model for the sphere
    Color  diffusionSphere3(0.24f, 0.34f, 1.97f);
    Color  specularSphere3(0.8);
    Phong* rBRDFSphere3 = new Phong(diffusionSphere3, specularSphere3, 25);

    // Create a shader for the third sphere
    Shader* rShaderSphere3 = new Shader(rBRDFSphere3, reflectionCoeff, refractionCoeff, scene);
    rShaderSphere3->setReflectionCountMax(4);
    rSphere3->setShader(rShaderSphere3);

    scene->add(rSphere3);
    scene->add(rBRDFSphere3, string("brdf of sphere 3"));
    scene->add(rShaderSphere3, string("shader of sphere 3"));


    ////////////
    // LIGHTS //
    ////////////
    LCNS::Point light4Position(1.15f, 4.f, 4.0f);
    Color       lightColor(16.0f);
    Light*      rLight4 = new PunctualLight(light4Position, lightColor);
    scene->add(rLight4);

    LCNS::Point light5Position(-1.15f, 4.f, 4.0f);
    Light*      rLight5 = new PunctualLight(light5Position, lightColor);
    scene->add(rLight5);


    ////////////
    // CAMERA //
    ////////////
    LCNS::Point centreCamera(-3.5f, 2.50f, 7.0f);
    Vector      directionCamera(0.15f, -0.25f, -0.5f);
    Vector      cameraUp(0.f, 1.f, 0.f);
    float       FOV = 80.f * 3.141592 / 180.f;

    Camera* rCamera = new Camera(centreCamera, directionCamera, cameraUp, FOV);
    scene->add(rCamera);

    ///////////
    // FLOOR //
    ///////////
    FloorParameters floorParameters = { Color(1.0f), Color(0.3f), 1.0f, 1.0f, 2, 20.0, 2.0, string("./resources/small_damier.png") };
    createFloor(scene, floorParameters);

    ////////////////
    // BACKGROUND //
    ////////////////
    scene->setBackgroundColor(Color(0.0f));
}


void createScene05(Scene* scene)
{
    // TORUS
    string path = "./resources/torus.obj";
    scene->createFromFile(path);

    // Create a BRDF model for the torus
    Color  diffusionTorus(0.76f, 0.33f, 0.12f);
    Color  specularTorus(0.9f, 0.8f, 0.8f);
    Phong* rBRDFTorus = new Phong(diffusionTorus, specularTorus, 3);

    // Create a shader for the sphere
    Shader* rShaderTorus = new Shader(rBRDFTorus, 0.8, 1.0, scene, Shader::BUMP);

    auto it = scene->renderableList().begin();
    (*it)->setShader(rShaderTorus);

    scene->add(rBRDFTorus, string("brdf of the torus"));
    scene->add(rShaderTorus, string("shader of the torus"));


    ////////////
    // LIGHTS //
    ////////////
    LCNS::Point light1Position(0.f, 1.0f, 10.0f);
    Color       light1Color(10.0f);
    Light*      rLight1 = new PunctualLight(light1Position, light1Color);
    scene->add(rLight1);

    LCNS::Point light4Position(0.f, 10.f, 6.0f);
    Color       light4Color(10.0f);
    Light*      rLight4 = new PunctualLight(light4Position, light4Color);
    scene->add(rLight4);


    ////////////
    // CAMERA //
    ////////////
    LCNS::Point centreCamera(0.0f, 3.0f, 12.0f);
    Vector      directionCamera(0.01f, -0.3f, -1.0f);
    Vector      cameraUp(0.f, 1.f, 0.f);
    float       FOV = 60.f * 3.141592 / 180.f;

    Camera* rCamera = new Camera(centreCamera, directionCamera, cameraUp, FOV);
    rCamera->aperture(Camera::Aperture::ALL_SHARP);

    scene->add(rCamera);


    // FLOOR
    FloorParameters floorParameters = { Color(0.6f), Color(0.7f), 1.0, 1.0, 2, 200.0, 50.0, string("no_texture") };
    createFloor(scene, floorParameters);


    ////////////////
    // BACKGROUND //
    ////////////////
    scene->setBackgroundColor(Color(0.7f, 0.72f, 0.2f));
}

void createScene06(Scene* scene)
{
    // Same reflection coefficient for the spheres
    double reflectionCoeff(0.8);

    // SPHERE WITH REFRACTION
    LCNS::Point center(0.0, 0.0, 0.0);
    Sphere*     rSphere1 = new Sphere(center, 5.f);

    // Create a BRDF model for the sphere
    Color  diffusionSphere1(1.0f);
    Color  specularSphere1(0.1f);
    Phong* rBRDFSphere1 = new Phong(diffusionSphere1, specularSphere1, 3);

    // Create a shader for the sphere
    Shader* rShaderSphere1 = new Shader(rBRDFSphere1, reflectionCoeff, 2.0, scene);
    rSphere1->setShader(rShaderSphere1);

    scene->add(rSphere1);
    scene->add(rBRDFSphere1, string("brdf of sphere 1"));
    scene->add(rShaderSphere1, string("shader of sphere 1"));

    // SPHERES IN THE BACKGROUND
    // Nearest spheres
    double size = 4.0;
    center.z(-20);

    // BG 1, left
    center.x(-20.0);
    Sphere* rSphereL1 = new Sphere(center, size);

    Phong*  rBRDF_L1  = new Phong(Color(250, 240, 230) * 5.0, Color(1.0), 3);
    Shader* rShaderL1 = new Shader(rBRDF_L1, reflectionCoeff, 1.0, scene, Shader::BUMP);

    rSphereL1->setShader(rShaderL1);

    scene->add(rSphereL1);
    scene->add(rBRDF_L1, string("brdf left 1"));
    scene->add(rShaderL1, string("shader left 1"));

    // BG 1, right
    center.x(20.0);
    Sphere* rSphereR1 = new Sphere(center, size);

    Phong*  rBRDFR1   = new Phong(Color(135, 206, 250) * 5.0, Color(1.0), 3);
    Shader* rShaderR1 = new Shader(rBRDFR1, reflectionCoeff, 1.0, scene, Shader::BUMP);

    rSphereR1->setShader(rShaderR1);

    scene->add(rSphereR1);
    scene->add(rBRDFR1, string("brdf right 1"));
    scene->add(rShaderR1, string("shader right 1"));

    // BG 1, down
    center.x(0.0);
    center.y(-20.0);
    Sphere* rSphereD1 = new Sphere(center, size);

    Phong*  rBRDFD1   = new Phong(Color(250, 128, 114) * 5.0, Color(1.0), 3);
    Shader* rShaderD1 = new Shader(rBRDFD1, reflectionCoeff, 1.0, scene, Shader::BUMP);

    rSphereD1->setShader(rShaderD1);

    scene->add(rSphereD1);
    scene->add(rBRDFD1, string("brdf down 1"));
    scene->add(rShaderD1, string("shader down 1"));

    // BG 1, up
    center.y(20.0);
    Sphere* rSphereU1 = new Sphere(center, size);

    Phong*  rBRDFU1   = new Phong(Color(255, 250, 205) * 5.0, Color(1.0), 3);
    Shader* rShaderU1 = new Shader(rBRDFU1, reflectionCoeff, 1.0, scene, Shader::BUMP);

    rSphereU1->setShader(rShaderU1);

    scene->add(rSphereU1);
    scene->add(rBRDFU1, string("brdf up 1"));
    scene->add(rShaderU1, string("shader up 1"));

    // Furthest spheres
    size = 22.0;
    center.z(-220);

    // BG 2, left down
    center.x(-85.0);
    center.y(-85.0);
    Sphere* rSphereLD2 = new Sphere(center, size);

    Phong*  rBRDFLD2   = new Phong(Color(127, 255, 212) * 5.0, Color(1.0), 3);
    Shader* rShaderLD2 = new Shader(rBRDFLD2, reflectionCoeff, 1.0, scene);

    rSphereLD2->setShader(rShaderLD2);

    scene->add(rSphereLD2);
    scene->add(rBRDFLD2, string("brdf left down 2"));
    scene->add(rShaderLD2, string("shader left down 2"));

    // BG 2, right down
    center.x(85.0);
    center.y(-85.0);
    Sphere* rSphereRD2 = new Sphere(center, size);

    Phong*  rBRDFRD2   = new Phong(Color(240, 248, 255) * 5.0, Color(1.0), 3);
    Shader* rShaderRD2 = new Shader(rBRDFRD2, reflectionCoeff, 1.0, scene);

    rSphereRD2->setShader(rShaderRD2);

    scene->add(rSphereRD2);
    scene->add(rBRDFRD2, string("brdf right down 2"));
    scene->add(rShaderRD2, string("shader right down 2"));

    // BG 2, left up
    center.x(-85.0);
    center.y(85.0);
    Sphere* rSphereLU2 = new Sphere(center, size);

    Phong*  rBRDFLU2   = new Phong(Color(255, 99, 71) * 5.0, Color(1.0), 3);
    Shader* rShaderLU2 = new Shader(rBRDFLU2, reflectionCoeff, 1.0, scene);

    rSphereLU2->setShader(rShaderLU2);

    scene->add(rSphereLU2);
    scene->add(rBRDFLU2, string("brdf left up 2"));
    scene->add(rShaderLU2, string("shader left up 2"));

    // BG2, right up
    center.x(85.0);
    center.y(85.0);
    Sphere* rSphereRU2 = new Sphere(center, size);

    Phong*  rBRDFRU2   = new Phong(Color(255, 255, 0) * 5.0, Color(1.0), 3);
    Shader* rShaderRU2 = new Shader(rBRDFRU2, reflectionCoeff, 1.0, scene);

    rSphereRU2->setShader(rShaderRU2);

    scene->add(rSphereRU2);
    scene->add(rBRDFRU2, string("brdf right up 2"));
    scene->add(rShaderRU2, string("shader right up 2"));


    //    // SPHERE WITH TEXTURE
    //    LCNS::Point centerSphere2(12.0,0.0,0.0);
    //	Sphere* rSphere2 = new Sphere(centerSphere2,5.f);
    //
    //    // Create a BRDF model for the sphere
    //    Color diffusionSphere2(1.0f);
    //	Color specularSphere2(0.1);
    //    auto rCubeMapSphere = make_shared<CubeMap>(centerSphere2, 520);
    //    rCubeMapSphere->addImage(CubeMap::Faces::BACK, "./resources/Desert_back.png");
    //    rCubeMapSphere->addImage(CubeMap::Faces::FRONT,"./resources/Desert_front.png");
    //    rCubeMapSphere->addImage(CubeMap::Faces::UP, "./resources/Desert_up.png");
    //    rCubeMapSphere->addImage(CubeMap::Faces::DOWN,"./resources/Desert_down.png");
    //    rCubeMapSphere->addImage(CubeMap::Faces::LEFT, "./resources/Desert_left.png");
    //    rCubeMapSphere->addImage(CubeMap::Faces::RIGHT,"./resources/Desert_right.png");
    //
    //    scene->add(rCubeMapSphere);
    //
    //	Phong* rBRDFSphere2 = new Phong(diffusionSphere2,lSpecularSphere2,3);
    //    rBRDFSphere2->cubeMap(rCubeMapSphere);
    //
    //    // Create a shader for the second sphere
    //	Shader* rShaderSphere2 = new Shader(rBRDFSphere2,lReflectionCoeff,1.0,scene);
    //    rSphere2->setShader(rShaderSphere2);
    //
    //    scene->add(rSphere2);
    //    scene->add(rBRDFSphere2, string("brdf of sphere 2"));
    //    scene->add(rShaderSphere2, string("shader of sphere 2"));


    ////////////
    // LIGHTS //
    ////////////
    LCNS::Point lightPosition(0.0f, 0.0f, 20.0f);
    Color       lightColor(6.0f);
    Light*      rLight1 = new PunctualLight(lightPosition, lightColor);
    scene->add(rLight1);


    ////////////
    // CAMERA //
    ////////////
    LCNS::Point centreCamera(0.0f, 0.0f, 15.0f);
    Vector      directionCamera(0.0f, 0.0f, -1.01f);
    Vector      cameraUp(0.f, 1.f, 0.f);
    float       FOV = 90.f * 3.141592 / 180.f;

    Camera* rCamera = new Camera(centreCamera, directionCamera, cameraUp, FOV);
    rCamera->focalPoint(LCNS::Point(4.0));
    rCamera->aperture(Camera::Aperture::F_SMALL, Camera::Precision::EXCELLENT);
    //    rCamera->aperture(Camera::Aperture::ALL_SHARP);

    scene->add(rCamera);

    // BACKGROUND
    auto rCubeMapBckGrd = make_shared<CubeMap>(LCNS::Point(0.0), 260);  // 260

    rCubeMapBckGrd->addImage(CubeMap::Faces::BACK, "./resources/River_back.png");
    rCubeMapBckGrd->addImage(CubeMap::Faces::FRONT, "./resources/River_front.png");
    rCubeMapBckGrd->addImage(CubeMap::Faces::UP, "./resources/River_up.png");
    rCubeMapBckGrd->addImage(CubeMap::Faces::DOWN, "./resources/River_down.png");
    rCubeMapBckGrd->addImage(CubeMap::Faces::LEFT, "./resources/River_left.png");
    rCubeMapBckGrd->addImage(CubeMap::Faces::RIGHT, "./resources/River_right.png");

    rCubeMapBckGrd->interpolationMethod(Image::InterpolationMethod::LINEAR);

    scene->backgroundCubeMap(rCubeMapBckGrd);
}

void createScene07(Scene* scene)
{
    // Create a sphere (1)
    LCNS::Point centerSphere1(-30.f, 10.0f, 20.0f);
    Sphere*     rSphere1 = new Sphere(centerSphere1, 13.f);

    // Create a BRDF model for the sphere
    Color  diffusionSphere1(229.0f / 255.0f, 51.0f / 255.0f, 163.0f / 255.0f);
    Color  specularSphere1(0.0f);
    Phong* rBRDFSphere1 = new Phong(diffusionSphere1, specularSphere1, 3);

    // Create a shader for the sphere
    Shader* rShaderSphere1 = new Shader(rBRDFSphere1, 0.8, 1.0, scene, Shader::TURBULANCE);
    rSphere1->setShader(rShaderSphere1);

    scene->add(rSphere1);
    scene->add(rBRDFSphere1, string("brdf of sphere 1"));
    scene->add(rShaderSphere1, string("shader of sphere 1"));

    // Create a sphere (2)
    LCNS::Point centerSphere2(0.0f, 10.0f, 20.0f);
    Sphere*     rSphere2 = new Sphere(centerSphere2, 13.f);

    // Create a BRDF model for the sphere
    Color  diffusionSphere2(220.0f / 255.0f, 210.0f / 255.0f, 120.0f / 255.0f);
    Color  specularSphere2(0.0f);
    Phong* rBRDFSphere2 = new Phong(diffusionSphere2, specularSphere2, 3);

    // Create a shader for the sphere
    Shader* rShaderSphere2 = new Shader(rBRDFSphere2, 0.8, 1.0, scene, Shader::MARBLE);
    rSphere2->setShader(rShaderSphere2);

    scene->add(rSphere2);
    scene->add(rBRDFSphere2, string("brdf of sphere 2"));
    scene->add(rShaderSphere2, string("shader of sphere 2"));

    // Create a sphere (3)
    LCNS::Point centerSphere3(30.f, 10.0f, 20.0f);
    Sphere*     rSphere3 = new Sphere(centerSphere3, 13.f);

    // Create a BRDF model for the sphere
    Color  diffusionSphere3(90.0f / 255.0f, 160.0f / 255.0f, 210.0f / 255.0f);
    Color  specularSphere3(0.0f);
    Phong* rBRDFSphere3 = new Phong(diffusionSphere3, specularSphere3, 3);

    // Create a shader for the sphere
    Shader* rShaderSphere3 = new Shader(rBRDFSphere3, 0.8, 1.0, scene, Shader::BUMP);
    rSphere3->setShader(rShaderSphere3);

    scene->add(rSphere3);
    scene->add(rBRDFSphere3, string("brdf of sphere 3"));
    scene->add(rShaderSphere3, string("shader of sphere 3"));

    ////////////
    // LIGHTS //
    ////////////
    LCNS::Point lightPosition(0.0f, 90.0f, 0.0f);
    Color       lightColor(5.0f);
    Light*      rLight1 = new PunctualLight(lightPosition, lightColor);
    scene->add(rLight1);

    //    lightPosition.setPoint(0.0f,15.0f,37.0f);
    //	Light* rLight2 = new PunctualLight(lightPosition,lLightColor);
    //    scene->add(rLight2);

    lightPosition.set(10.0f, 20.0f, 37.0f);
    Light* rLight3 = new PunctualLight(lightPosition, lightColor);
    scene->add(rLight3);

    lightPosition.set(-10.0f, 20.0f, 37.0f);
    Light* rLight4 = new PunctualLight(lightPosition, lightColor);
    scene->add(rLight4);


    ////////////
    // CAMERA //
    ////////////
    LCNS::Point centreCamera(0.0f, 25.0f, 105.0f);
    Vector      directionCamera(0.0f, -0.3f, -1.0f);
    Vector      cameraUp(0.f, 1.f, 0.f);
    float       FOV = 80.f * 3.141592 / 180.f;

    Camera* rCamera = new Camera(centreCamera, directionCamera, cameraUp, FOV);
    rCamera->aperture(Camera::Aperture::ALL_SHARP);


    scene->add(rCamera);

    // ROOM
    RoomParameters roomParameters = { Color(1.0f, 0.18f, 0.17f),
                                      Color(0.0f),
                                      1.0,
                                      1.0,
                                      2,
                                      Point(50.0),
                                      20.0,
                                      string("./resources/textureLeaves_750x750.png"),
                                      string("./resources/textureWall_400x400.png"),
                                      string("./resources/textureWall_400x400_Right.png"),
                                      string("./resources/textureWall_400x400.png") };

    createRoom(scene, roomParameters);

    ////////////////
    // BACKGROUND //
    ////////////////
    scene->setBackgroundColor(Color(0.2f));
}

void createScene08(LCNS::Scene* scene)
{
    // Same reflection coefficient for the spheres behind
    double reflectionCoeff(0.8);
    double refractionCoeff(1.0);

    // Create a red sphere
    LCNS::Point centerSphere1(00.0, 0.0, -5.0);
    Sphere*     rSphere1 = new Sphere(centerSphere1, 2.f);

    // Create a BRDF model for the sphere
    Color  diffusionSphere1(1.0f, 0.6f, 0.6f);
    Color  specularSphere1(0.9f, 0.4f, 0.4f);
    Phong* rBRDFSphere1 = new Phong(diffusionSphere1, specularSphere1, 3);

    // Create a shader for the sphere
    Shader* rShaderSphere1 = new Shader(rBRDFSphere1, reflectionCoeff, refractionCoeff, scene);
    rSphere1->setShader(rShaderSphere1);

    scene->add(rSphere1);
    scene->add(rBRDFSphere1, string("brdf of sphere 1"));
    scene->add(rShaderSphere1, string("shader of sphere 1"));

    // Create a green sphere
    LCNS::Point centerSphere2(10.0, 0.0, -100.0);
    Sphere*     rSphere2 = new Sphere(centerSphere2, 30.f);

    // Create a BRDF model for the sphere
    Color  diffusionSphere2(0.6f, 1.0f, 0.6f);
    Color  specularSphere2(0.4, 1.0f, 0.4f);
    Phong* rBRDFSphere2 = new Phong(diffusionSphere2, specularSphere2, 3);

    // Create a shader for the second sphere
    Shader* rShaderSphere2 = new Shader(rBRDFSphere2, reflectionCoeff, refractionCoeff, scene);
    rSphere2->setShader(rShaderSphere2);

    scene->add(rSphere2);
    scene->add(rBRDFSphere2, string("brdf of sphere 2"));
    scene->add(rShaderSphere2, string("shader of sphere 2"));

    ////////////
    // LIGHTS //
    ////////////
    LCNS::Point light1Position(0.f, 10.f, 0.0f);
    Color       light1Color(3.0f);
    Light*      rLight1 = new PunctualLight(light1Position, light1Color);
    scene->add(rLight1);

    ////////////
    // CAMERA //
    ////////////
    LCNS::Point centreCamera(0.0f, 0.0f, 5.0f);
    Vector      directionCamera(0.0f, -0.1f, -1.0f);
    Vector      cameraUp(0.f, 1.f, 0.f);
    float       FOV = 80.f * 3.141592 / 180.f;

    Camera* rCamera = new Camera(centreCamera, directionCamera, cameraUp, FOV);
    rCamera->aperture(Camera::Aperture::F_SMALL, Camera::Precision::SUPER_AWESOME, 1.0);
    rCamera->focalPoint(centerSphere1);
    scene->add(rCamera);


    ////////////////
    // BACKGROUND //
    ////////////////
    scene->setBackgroundColor(Color(188, 236, 253));
}

void createScene09(LCNS::Scene* scene)
{
    // Load the "torus"
    string path = "./resources/head_4.obj";
    scene->createFromFile(path);

    // Create a BRDF model for the sphere
    Color  diffusionSphere(0.76f, 0.33f, 0.12f);
    Color  specularSphere(1.0f);
    Phong* rBRDFShpere = new Phong(diffusionSphere, specularSphere, 5);

    // Create a shader for the sphere
    Shader* rShaderSphere = new Shader(rBRDFShpere, 0.8, 1.0, scene);

    scene->add(rBRDFShpere, string("brdf of the sphere"));
    scene->add(rShaderSphere, string("shader of the sphere"));

    auto it = scene->renderableList().begin();

    (*it)->setShader(rShaderSphere);
    it++;


    // Create a BRDF model for the torus
    Color  diffusionTorus(0.96f, 0.40f, 0.40f);
    Color  specularTorus(0.9f, 0.8f, 0.8f);
    Phong* rBRDFTorus = new Phong(diffusionTorus, specularTorus, 5);

    // Create a shader for the torus
    Shader* rShaderTorus = new Shader(rBRDFTorus, 0.8, 1.0, scene, Shader::Material::MARBLE);

    scene->add(rBRDFTorus, string("brdf of the torus"));
    scene->add(rShaderTorus, string("shader of the torus"));

    (*it)->setShader(rShaderTorus);
    it++;

    (*it)->setShader(rShaderTorus);
    it++;


    // Create a BRDF model for the pipe
    Color  diffusionPipe(0.16f, 0.89f, 0.0f);
    Color  specularPipe(0.4f, 0.8f, 0.4f);
    Phong* rBRDFPipe = new Phong(diffusionPipe, specularPipe, 5);

    // Create a shader for the torus
    Shader* rShaderPipe = new Shader(rBRDFPipe, 0.8, 1.0, scene);

    scene->add(rBRDFPipe, string("brdf of the pipe"));
    scene->add(rShaderPipe, string("shader of the pipe"));

    (*it)->setShader(rShaderPipe);
    it++;


    // Create a BRDF model for the cone
    Color  diffusionCone(0.06f, 0.10f, 0.90f);
    Color  specularCone(0.3f, 0.2f, 0.8f);
    Phong* rBRDFCone = new Phong(diffusionCone, specularCone, 5);

    // Create a shader for the torus
    Shader* rShaderCone = new Shader(rBRDFCone, 0.8, 1.0, scene, Shader::TURBULANCE);

    scene->add(rBRDFCone, string("brdf of the cone"));
    scene->add(rShaderCone, string("shader of the cone"));

    (*it)->setShader(rShaderCone);


    ////////////
    // LIGHTS //
    ////////////
    LCNS::Point light1Position(0.f, 1.0f, 10.0f);
    Color       light1Color(10.0f);
    Light*      rLight1 = new PunctualLight(light1Position, light1Color);
    scene->add(rLight1);

    LCNS::Point light4Position(0.f, 10.f, 6.0f);
    Color       light4Color(10.0f);
    Light*      rLight4 = new PunctualLight(light4Position, light4Color);
    scene->add(rLight4);


    ////////////
    // CAMERA //
    ////////////
    LCNS::Point centreCamera(0.0f, 2.4f, 8.0f);
    Vector      directionCamera(0.01f, -0.1f, -1.0f);
    Vector      cameraUp(0.f, 1.f, 0.f);
    float       FOV = 60.f * 3.141592 / 180.f;

    Camera* rCamera = new Camera(centreCamera, directionCamera, cameraUp, FOV);
    rCamera->aperture(Camera::Aperture::ALL_SHARP);

    scene->add(rCamera);

    // FLOOR
    //    FloorParameters floorParameters = {Color(0.6f), Color(0.7f),200.0,50.0, string("no_texture")};
    //    createFloor(scene, floorParameters);

    ////////////////
    // BACKGROUND //
    ////////////////
    scene->setBackgroundColor(Color(0.2f, 0.32f, 0.8f));
}

void createScene10(LCNS::Scene* scene)
{
    // Same reflection coefficient for the spheres behind
    double reflectionCoeff(5.0);
    double refractionCoeff(1.0);

    ////////////////////////////////
    // Create a first blue sphere //
    ////////////////////////////////
    LCNS::Point centerSphere1(0.0, 0.0, 0.0);
    Sphere*     rSphere1 = new Sphere(centerSphere1, 100.f);

    // Create a BRDF model for the sphere
    Color  diffusionSphere1(0.f, 0.0f, 0.1f);
    Color  specularSphere1(1.0f);
    Phong* rBRDFSphere1 = new Phong(diffusionSphere1, specularSphere1, 8);

    // Create a shader for the sphere
    Shader* rShaderSphere1 = new Shader(rBRDFSphere1, reflectionCoeff, refractionCoeff, scene);
    rShaderSphere1->setReflectionCountMax(2);
    rSphere1->setShader(rShaderSphere1);

    scene->add(rSphere1);
    scene->add(rBRDFSphere1, string("brdf of sphere 1"));
    scene->add(rShaderSphere1, string("shader of sphere 1"));


    /////////////////////////////////
    // Create a second blue sphere //
    /////////////////////////////////
    LCNS::Point centerSphere2(50.0, -20.0, 230.0);
    Sphere*     rSphere2 = new Sphere(centerSphere2, 60.f);

    // Create a BRDF model for the sphere
    Color  diffusionSphere2(0.0f, 0.0f, 0.1f);
    Color  specularSphere2(0, 250, 154);
    Phong* rBRDFSphere2 = new Phong(diffusionSphere2, specularSphere2, 15);

    // Create a shader for the second sphere
    Shader* rShaderSphere2 = new Shader(rBRDFSphere2, reflectionCoeff, refractionCoeff, scene);
    rShaderSphere2->setReflectionCountMax(2);
    rSphere2->setShader(rShaderSphere2);

    scene->add(rSphere2);
    scene->add(rBRDFSphere2, string("brdf of sphere 2"));
    scene->add(rShaderSphere2, string("shader of sphere 2"));


    ////////////
    // LIGHTS //
    ////////////
    LCNS::Point light1Position(-40.f, 150.f, 50.0f);
    Color       light1Color(212.0f, 27.0f, 218.0f);
    light1Color *= 2.0;

    Light* rLight1 = new PunctualLight(light1Position, light1Color);
    scene->add(rLight1);


    LCNS::Point light2Position(90.f, 150.f, 190.0f);
    Color       light2Color(189.0f, 190.0f, 53.0f);

    light2Color *= 2.0f;

    Light* rLight2 = new PunctualLight(light2Position, light2Color);
    scene->add(rLight2);

    LCNS::Point light3Position(-190.f, 150.f, 90.0f);
    Color       light3Color(255, 140, 0);

    light3Color *= 200.0f;

    Light* rLight3 = new PunctualLight(light3Position, light3Color);
    scene->add(rLight3);


    ////////////
    // CAMERA //
    ////////////
    LCNS::Point centreCamera(-280.0f, 150.0f, 350.0f);
    Vector      directionCamera(0.5f, -0.35f, -0.5f);
    Vector      cameraUp(0.f, 1.f, 0.f);
    float       FOV = 80.f * 3.141592 / 180.f;

    Camera* rCamera = new Camera(centreCamera, directionCamera, cameraUp, FOV);
    rCamera->aperture(Camera::Aperture::ALL_SHARP, Camera::Precision::LOW, 10.0);

    scene->add(rCamera);


    ///////////
    // FLOOR //
    ///////////
    FloorParameters floorParameters = { Color(1.0f), Color(0.3f), 1.0, 1.0, 2, 2000.0, 100.0, string("./resources/rect5130.png") };
    createFloor(scene, floorParameters);


    ////////////////
    // BACKGROUND //
    ////////////////
    scene->setBackgroundColor(Color(0.0f));
}

void createScene11(LCNS::Scene* scene)
{
    double reflectionCoeff(2.0);
    double refractionCoeff(1.0);

    //////////////////////////
    // Create a yellow sphere //
    //////////////////////////
    LCNS::Point centerSphere1(-1.1, 0.0, 0.0);
    Renderable* rSphere1 = new Sphere(centerSphere1, 1.0);

    // Create a BRDF model for the sphere
    Color diffusionSphere1(255, 255, 0);
    Color specularSphere1(230, 230, 250);
    BRDF* rBRDFSphere1 = new Phong(diffusionSphere1, specularSphere1, 15);

    // Create a shader for the sphere
    Shader* rShaderSphere1 = new Shader(rBRDFSphere1, reflectionCoeff, refractionCoeff, scene, Shader::TURBULANCE);

    // Set the max number of reflections to 4
    rShaderSphere1->setReflectionCountMax(4);
    rSphere1->setShader(rShaderSphere1);

    scene->add(rSphere1);
    scene->add(rBRDFSphere1, string("brdf of sphere 1"));
    scene->add(rShaderSphere1, string("shader of sphere 1"));


    ///////////////////////////
    // Create a cyan sphere //
    ///////////////////////////
    LCNS::Point centerSphere2(1.1, 0.0, 0.0);
    Renderable* rSphere2 = new Sphere(centerSphere2, 1.0);

    // Create a BRDF model for the sphere
    Color diffusionSphere2(0, 255, 255);
    Color specularSphere2(255, 160, 122);
    BRDF* rBRDFSphere2 = new Phong(diffusionSphere2, specularSphere2, 15);

    // Create a shader for the second sphere
    Shader* rShaderSphere2 = new Shader(rBRDFSphere2, reflectionCoeff, refractionCoeff, scene, Shader::TURBULANCE);

    // Set the max number of reflections to 3
    rShaderSphere2->setReflectionCountMax(3);
    rSphere2->setShader(rShaderSphere2);

    scene->add(rSphere2);
    scene->add(rBRDFSphere2, string("brdf of sphere 2"));
    scene->add(rShaderSphere2, string("shader of sphere 2"));


    //////////////////////////
    // Create a pink sphere //
    //////////////////////////
    LCNS::Point centerSphere3(0.0, 1.8, 0.0);
    Renderable* rSphere3 = new Sphere(centerSphere3, 1.0);

    // Create a BRDF model for the sphere
    Color diffusionSphere3(255, 0, 255);
    Color specularSphere3(127, 255, 212);
    BRDF* rBRDFSphere3 = new Phong(diffusionSphere3, specularSphere3, 15);

    // Create a shader for the second sphere
    Shader* rShaderSphere3 = new Shader(rBRDFSphere3, reflectionCoeff, refractionCoeff, scene, Shader::TURBULANCE);

    // Set the max number of reflections to 5
    rShaderSphere3->setReflectionCountMax(5);
    rSphere3->setShader(rShaderSphere3);

    scene->add(rSphere3);
    scene->add(rBRDFSphere3, string("brdf of sphere 3"));
    scene->add(rShaderSphere3, string("shader of sphere 3"));


    ////////////
    // LIGHTS //
    ////////////
    LCNS::Point light1Position(0.f, 1.0f, 10.0f);
    Color       light1Color(8.0f);
    Light*      rLight1 = new PunctualLight(light1Position, light1Color);
    scene->add(rLight1);

    LCNS::Point light2Position(0.f, 1.0f, -10.0f);
    Color       light2Color(5.0f);
    Light*      rLight2 = new PunctualLight(light2Position, light2Color);
    scene->add(rLight2);


    ////////////
    // CAMERA //
    ////////////
    LCNS::Point centreCamera(0.0f, 0.7f, 2.0f);
    Vector      directionCamera(0.0f, 0.0f, -1.0f);
    Vector      cameraUp(0.f, 1.f, 0.f);
    float       FOV = 60.f * 3.141592 / 180.f;

    Camera* rCamera = new Camera(centreCamera, directionCamera, cameraUp, FOV);
    scene->add(rCamera);


    ////////////////
    // BACKGROUND //
    ////////////////
    scene->setBackgroundColor(Color(0.0f));
}

void createScene12(LCNS::Scene* scene)
{
    // Same reflection coefficient for the spheres behind
    double reflectionCoeff(2.0);
    double refractionCoeff(1.0);

    // Create a sphere
    LCNS::Point centerSphere1(0.0, 5.0, 5.0);
    Sphere*     rSphere1 = new Sphere(centerSphere1, 9.f);

    // Create a BRDF model for the sphere
    Color  diffusionSphere1(1.0f, 0.8f, 0.9f);
    Color  specularSphere1(1.0);
    Phong* rBRDFSphere1 = new Phong(diffusionSphere1, specularSphere1, 3);

    // Create a BRDF model for the sphere
    //    auto rCubeMapSphere = make_shared<CubeMap>(centerSphere1, 720);
    //    rCubeMapSphere->addImage(CubeMap::Faces::BACK, "./resources/nightSky2.png");
    //    rCubeMapSphere->setLink(CubeMap::Faces::FRONT, 0);
    //    rCubeMapSphere->setLink(CubeMap::Faces::UP, 0);
    //    rCubeMapSphere->setLink(CubeMap::Faces::DOWN, 0);
    //    rCubeMapSphere->setLink(CubeMap::Faces::LEFT, 0);
    //    rCubeMapSphere->setLink(CubeMap::Faces::RIGHT, 0);
    //
    //    scene->add(rCubeMapSphere);
    //
    //    rBRDFSphere1->cubeMap(rCubeMapSphere);

    // Create a shader for the sphere
    Shader* rShaderSphere1 = new Shader(rBRDFSphere1, reflectionCoeff, refractionCoeff, scene);
    rShaderSphere1->setReflectionCountMax(4);
    rSphere1->setShader(rShaderSphere1);

    scene->add(rSphere1);
    scene->add(rBRDFSphere1, string("brdf of sphere 1"));
    scene->add(rShaderSphere1, string("shader of sphere 1"));

    // Create a second sphere
    LCNS::Point centerSphere2(-21.0, -5.0, 8.0);
    Sphere*     rSphere2 = new Sphere(centerSphere2, 9.f);

    // Create a BRDF model for the sphere
    Color  diffusionSphere2(0.9f, 1.0f, 0.8f);
    Color  specularSphere2(1.0f);
    Phong* rBRDFSphere2 = new Phong(diffusionSphere2, specularSphere2, 3);

    // Create a shader for the second sphere
    Shader* rShaderSphere2 = new Shader(rBRDFSphere2, reflectionCoeff, refractionCoeff, scene);
    rShaderSphere2->setReflectionCountMax(4);
    rSphere2->setShader(rShaderSphere2);

    scene->add(rSphere2);
    scene->add(rBRDFSphere2, string("brdf of sphere 2"));
    scene->add(rShaderSphere2, string("shader of sphere 2"));

    // Create a transparent sphere for refraction
    LCNS::Point centerSphere3(21.0, -5.0, 8.0);
    Sphere*     rSphere3 = new Sphere(centerSphere3, 9.0f);

    // Create a BRDF model for the sphere
    Color  diffusionSphere3(0.95f, 0.88f, 0.60f);
    Color  specularSphere3(1.0f);
    Phong* rBRDFSphere3 = new Phong(diffusionSphere3, specularSphere3, 3);

    // Create a shader for the third sphere
    Shader* rShaderSphere3 = new Shader(rBRDFSphere3, 0.6, 1.0, scene);
    rShaderSphere3->setReflectionCountMax(4);
    rSphere3->setShader(rShaderSphere3);

    scene->add(rSphere3);
    scene->add(rBRDFSphere3, string("brdf of sphere 3"));
    scene->add(rShaderSphere3, string("shader of sphere 3"));

    ////////////
    // LIGHTS //
    ////////////
    LCNS::Point light1Position(0.f, 25.0f, 50.0f);
    Color       light1Color(30.0f);
    Light*      rLight1 = new PunctualLight(light1Position, light1Color);
    scene->add(rLight1);

    //    LCNS::Point light4Position(0.f,20.f,6.0f);
    //	Color light4Color(10.0f);
    //	Light* rLight4 = new PunctualLight(light4Position,lLight4Color);
    //    scene->add(rLight4);


    ////////////
    // CAMERA //
    ////////////
    LCNS::Point centreCamera(0.0f, 15.0f, 40.0f);
    Vector      directionCamera(0.0f, -0.1f, -1.0f);
    Vector      cameraUp(0.f, 1.f, 0.f);
    float       FOV = 60.f * 3.141592 / 180.f;

    Camera* rCamera = new Camera(centreCamera, directionCamera, cameraUp, FOV);
    //    rCamera->aperture(Camera::Aperture::F_SMALL,45.0,Camera::LOW);
    rCamera->aperture(Camera::Aperture::ALL_SHARP);
    scene->add(rCamera);


    // ROOM
    RoomParameters parameters
    = { Color(0.8f),          Color(1.0f),         0.0, 1.0, 2, Point(35.0), 15.0, string("no_texture"), string("no_texture"),
        string("no_texture"), string("no_texture") };
    createRoom(scene, parameters);


    ////////////////
    // BACKGROUND //
    ////////////////
    //    auto rCubeMap = make_shared<CubeMap>(centerSphere1, 750);
    //
    //    rCubeMap->addImage(CubeMap::Faces::BACK, "./resources/nightSky2.png");
    //    rCubeMap->setLink(CubeMap::Faces::FRONT, 0);
    //    rCubeMap->setLink(CubeMap::Faces::UP, 0);
    //    rCubeMap->setLink(CubeMap::Faces::DOWN, 0);
    //    rCubeMap->setLink(CubeMap::Faces::LEFT, 0);
    //    rCubeMap->setLink(CubeMap::Faces::RIGHT, 0);
    //
    //    scene->backgroundCubeMap(rCubeMap);

    scene->setBackgroundColor(Color(220, 240, 250));
}

void createScene13(LCNS::Scene* scene)
{
    scene->createFromFile("./resources/tableAndStatue3_bis.obj");

    // Create BRDF model for the cones
    Color  diffusion(255, 105, 0);
    Color  specular(1.0f);
    Phong* rBRDFCones = new Phong(diffusion, specular, 3);

    // Create a shader for the cones
    Shader* rShaderCones = new Shader(rBRDFCones, 0.8, 1.0, scene, Shader::NONE);

    scene->add(rBRDFCones, "BRDF cones ");
    scene->add(rShaderCones, "Shader cones ");

    auto it = scene->objectNamed("pCone1");
    if (it)
        it->setShader(rShaderCones);

    it = scene->objectNamed("pCone2");
    if (it)
        it->setShader(rShaderCones);

    it = scene->objectNamed("pCone3");
    if (it)
        it->setShader(rShaderCones);

    it = scene->objectNamed("pCone4");
    if (it)
        it->setShader(rShaderCones);

    // Create BRDF model for the torus
    Phong* rBRDFTorus = new Phong(Color(255, 99, 71), Color(1.0), 3);

    // Create a shader for the torus
    Shader* rShaderTorus = new Shader(rBRDFTorus, 1.8, 1.0, scene, Shader::NONE);

    scene->add(rBRDFTorus, "BRDF torus ");
    scene->add(rShaderTorus, "Shader torus ");

    it = scene->objectNamed("pTorus1");
    if (it)
        it->setShader(rShaderTorus);

    it = scene->objectNamed("pTorus2");
    if (it)
        it->setShader(rShaderTorus);

    // Create a BRDF model for the table
    Phong* rBRDFPyramid = new Phong(Color(128, 128, 0), Color(1.0f), 10);

    // Create a shader for the table
    Shader* rShaderPyramid = new Shader(rBRDFPyramid, 1.0f, 1.0f, scene, Shader::Material::TURBULANCE);

    scene->add(rBRDFPyramid, "BRDF pyramid ");
    scene->add(rShaderPyramid, "Shader pyramid ");

    // Set shaders for the table
    it = scene->objectNamed("pPyramid1");
    if (it)
        it->setShader(rShaderPyramid);

    it = scene->objectNamed("pPyramid2");
    if (it)
        it->setShader(rShaderPyramid);


    // Create a BRDF model for the table
    Phong* rBRDFTable = new Phong(Color(1.0f), Color(1.0f), 10);

    // Create a shader for the table
    Shader* rShaderTable = new Shader(rBRDFTable, 1.0f, 1.0f, scene, Shader::Material::MARBLE);

    scene->add(rBRDFTable, "BRDF table ");
    scene->add(rShaderTable, "Shader table ");

    // Set shaders for the table
    it = scene->objectNamed("pCylinder1");
    if (it)
        it->setShader(rShaderTable);

    it = scene->objectNamed("pCylinder2");
    if (it)
        it->setShader(rShaderTable);

    it = scene->objectNamed("pCylinder3");
    if (it)
        it->setShader(rShaderTable);

    it = scene->objectNamed("pCylinder4");
    if (it)
        it->setShader(rShaderTable);

    it = scene->objectNamed("pCube1");
    if (it)
        it->setShader(rShaderTable);


    // Sphere with texture
    LCNS::Point centerSphere(0.0, 6.7, 0.0);
    Sphere*     rSphere1 = new Sphere(centerSphere, 2.0f);

    // Create a BRDF model for the sphere
    Color  diffusionSphere1(1.0f);
    Color  specularSphere1(1.0f);
    Phong* rBRDFSphere1 = new Phong(diffusionSphere1, specularSphere1, 8);


    auto rCubeMapDesert = make_shared<CubeMap>(LCNS::Point(0.0), 260);  // 260

    rCubeMapDesert->addImage(CubeMap::Faces::BACK, "./resources/Desert_back.png");
    rCubeMapDesert->addImage(CubeMap::Faces::FRONT, "./resources/Desert_front.png");
    rCubeMapDesert->addImage(CubeMap::Faces::UP, "./resources/Desert_up.png");
    rCubeMapDesert->addImage(CubeMap::Faces::DOWN, "./resources/Desert_down.png");
    rCubeMapDesert->addImage(CubeMap::Faces::LEFT, "./resources/Desert_left.png");
    rCubeMapDesert->addImage(CubeMap::Faces::RIGHT, "./resources/Desert_right.png");

    rCubeMapDesert->interpolationMethod(Image::InterpolationMethod::LINEAR);

    scene->add(rCubeMapDesert);

    rBRDFSphere1->cubeMap(rCubeMapDesert);

    // Create a shader for the sphere
    Shader* rShaderSphere1 = new Shader(rBRDFSphere1, 1.0, 1.0, scene);
    rShaderSphere1->setReflectionCountMax(1);
    rSphere1->setShader(rShaderSphere1);

    scene->add(rSphere1);
    scene->add(rBRDFSphere1, string("brdf of sphere 1"));
    scene->add(rShaderSphere1, string("shader of sphere 1"));

    // Mirror on the right wall
    double    mirrorXPos = 10.0;
    Triangle* rMirror1 = new Triangle(LCNS::Point(mirrorXPos, 4.0, -10.0), LCNS::Point(mirrorXPos, 12.0, -10.0), LCNS::Point(mirrorXPos, 12.0, 18.0));
    Triangle* rMirror2 = new Triangle(LCNS::Point(mirrorXPos, 4.0, -10.0), LCNS::Point(mirrorXPos, 12.0, 18.0), LCNS::Point(mirrorXPos, 4.0, 18.0));

    Vector minusX(-1.0, 0.0, 0.0);

    rMirror1->setVertexNormal(0, minusX);
    rMirror1->setVertexNormal(1, minusX);
    rMirror1->setVertexNormal(2, minusX);

    rMirror2->setVertexNormal(0, minusX);
    rMirror2->setVertexNormal(1, minusX);
    rMirror2->setVertexNormal(2, minusX);

    // Create a BRDF model for the mirror
    Phong* rBRDFMirror = new Phong(Color(0.4f, 0.4f, 0.6f), Color(1.0f), 8);

    // Create a shader for the mirror
    Shader* rShaderMirror = new Shader(rBRDFMirror, 20.0, 1.0, scene);
    rShaderMirror->setReflectionCountMax(2);

    rMirror1->setShader(rShaderMirror);
    rMirror2->setShader(rShaderMirror);

    scene->add(rMirror1);
    scene->add(rMirror2);
    scene->add(rBRDFMirror, string("brdf of sphere 1"));
    scene->add(rShaderMirror, string("shader of sphere 1"));


    ////////////
    // LIGHTS //
    ////////////
    LCNS::Point light1Position(-3.0, 10.0, 20.0);
    Color       lightColor(20.0f);
    Light*      rLight1 = new PunctualLight(light1Position, lightColor);
    scene->add(rLight1);


    //    LCNS::Point light2Position(-5.0,10.0,10.0);
    //	Light* rLight2 = new PunctualLight(light2Position,lLightColor);
    //    scene->add(rLight2);

    //    LCNS::Point light3Position(-4.0,7.0,-9.0);
    //	Light* rLight3 = new PunctualLight(light3Position,lLightColor);
    //    scene->add(rLight3);


    ////////////
    // CAMERA //
    ////////////
    LCNS::Point centreCamera(-5.0, 8.0, 21.0);
    Vector      directionCamera(0.4, -0.20, -1.0);
    Vector      cameraUp(0.0, 1.0, 0.0);
    float       FOV = 80.f * 3.141592 / 180.f;

    Camera* rCamera = new Camera(centreCamera, directionCamera, cameraUp, FOV);
    rCamera->focalPoint(centerSphere + directionCamera.normalize() * rSphere1->radius() * (-1.0));
    rCamera->aperture(Camera::Aperture::F_SMALL, Camera::Precision::SUPER_AWESOME);
    scene->add(rCamera);

    RoomParameters parameters = { Color(0.8f),
                                  Color(0.8f),
                                  0.0,
                                  1.0,
                                  1,
                                  LCNS::Point(-28.0, 0.0, -20.0),
                                  Vector(40.0, 15.0, 40.0),
                                  string("./resources/floor.png"),
                                  string("./resources/textureWall_400x400.png"),
                                  string("./resources/textureWall_400x400_Right.png"),
                                  string("./resources/textureWall_400x400.png"),
                                  string("./resources/ceiling.png") };

    createRoom(scene, parameters);


    ////////////////
    // BACKGROUND //
    ////////////////
    scene->setBackgroundColor(Color(0.0f));
}

void createScene14(LCNS::Scene* scene)
{
    scene->createFromFile("./resources/tableAndStatueAndPyramid3.obj");

    // Create BRDF model for the cones
    Color  diffusion(255, 105, 0);
    Color  specular(1.0f);
    Phong* rBRDFCones = new Phong(diffusion, specular, 3);

    // Create a shader for the cones
    Shader* rShaderCones = new Shader(rBRDFCones, 0.8, 1.0, scene, Shader::NONE);

    scene->add(rBRDFCones, "BRDF cones ");
    scene->add(rShaderCones, "Shader cones ");

    auto it = scene->objectNamed("pCone1");
    if (it)
        it->setShader(rShaderCones);

    it = scene->objectNamed("pCone2");
    if (it)
        it->setShader(rShaderCones);

    it = scene->objectNamed("pCone3");
    if (it)
        it->setShader(rShaderCones);

    it = scene->objectNamed("pCone4");
    if (it)
        it->setShader(rShaderCones);

    // Create BRDF model for the torus
    Phong* rBRDFTorus = new Phong(Color(255, 99, 71), Color(1.0), 3);

    // Create a shader for the torus
    Shader* rShaderTorus = new Shader(rBRDFTorus, 1.8, 1.0, scene, Shader::NONE);

    scene->add(rBRDFTorus, "BRDF torus ");
    scene->add(rShaderTorus, "Shader torus ");

    it = scene->objectNamed("pTorus1");
    if (it)
        it->setShader(rShaderTorus);

    it = scene->objectNamed("pTorus2");
    if (it)
        it->setShader(rShaderTorus);

    // Create a BRDF model for the table
    Phong* rBRDFPyramid = new Phong(Color(128, 128, 0), Color(1.0f), 10);

    // Create a shader for the table
    Shader* rShaderPyramid = new Shader(rBRDFPyramid, 1.0f, 1.0f, scene, Shader::Material::TURBULANCE);

    scene->add(rBRDFPyramid, "BRDF pyramid ");
    scene->add(rShaderPyramid, "Shader pyramid ");

    // Set shaders for the table
    it = scene->objectNamed("pPyramid1");
    if (it)
        it->setShader(rShaderPyramid);

    it = scene->objectNamed("pPyramid2");
    if (it)
        it->setShader(rShaderPyramid);


    Phong* rBRDFBackPyramid = new Phong(Color(0, 255, 255), Color(1.0f), 10);

    // Create a shader for the table
    Shader* rShaderBackPyramid = new Shader(rBRDFBackPyramid, 1.0f, 1.0f, scene, Shader::Material::BUMP);

    scene->add(rBRDFBackPyramid, "BRDF pyramid in the background ");
    scene->add(rShaderBackPyramid, "Shader pyramid in the background ");

    it = scene->objectNamed("pPyramid3");
    if (it)
        it->setShader(rShaderBackPyramid);


    // Create a BRDF model for the table
    Phong* rBRDFTable = new Phong(Color(1.0f), Color(1.0f), 10);

    // Create a shader for the table
    Shader* rShaderTable = new Shader(rBRDFTable, 1.0f, 1.0f, scene, Shader::Material::MARBLE);

    scene->add(rBRDFTable, "BRDF table ");
    scene->add(rShaderTable, "Shader table ");

    // Set shaders for the table
    it = scene->objectNamed("pCylinder1");
    if (it)
        it->setShader(rShaderTable);

    it = scene->objectNamed("pCylinder2");
    if (it)
        it->setShader(rShaderTable);

    it = scene->objectNamed("pCylinder3");
    if (it)
        it->setShader(rShaderTable);

    it = scene->objectNamed("pCylinder4");
    if (it)
        it->setShader(rShaderTable);

    it = scene->objectNamed("pCube1");
    if (it)
        it->setShader(rShaderTable);


    // Sphere with texture
    LCNS::Point centerSphere(.0, 6.7, 0.0);
    Sphere*     rSphere1 = new Sphere(centerSphere, 2.0f);

    // Create a BRDF model for the sphere
    Color  diffusionSphere1(0.1f);
    Color  specularSphere1(0.1f);
    Phong* rBRDFSphere1 = new Phong(diffusionSphere1, specularSphere1, 8);

    // Create a shader for the sphere
    Shader* rShaderSphere1 = new Shader(rBRDFSphere1, 1.0, 2.4, scene);
    rShaderSphere1->setReflectionCountMax(1);
    rSphere1->setShader(rShaderSphere1);

    scene->add(rSphere1);
    scene->add(rBRDFSphere1, string("brdf of sphere 1"));
    scene->add(rShaderSphere1, string("shader of sphere 1"));


    ////////////
    // LIGHTS //
    ////////////
    LCNS::Point light1Position(0.0, 20.0, 10.0);
    Color       lightColor(20.0f);
    Light*      rLight1 = new PunctualLight(light1Position, lightColor);
    scene->add(rLight1);


    LCNS::Point light2Position(-5.0, 10.0, 10.0);
    Light*      rLight2 = new PunctualLight(light2Position, lightColor);
    scene->add(rLight2);

    LCNS::Point light3Position(5.0, 10.0, 10.0);
    Light*      rLight3 = new PunctualLight(light3Position, lightColor);
    scene->add(rLight3);


    ////////////
    // CAMERA //
    ////////////
    LCNS::Point centreCamera(-2.0, 8.0, 14.0);
    Vector      directionCamera(0.05, -0.05, -1.0);
    Vector      cameraUp(0.0, 1.0, 0.0);
    float       FOV = 80.f * 3.141592 / 180.f;

    Camera* rCamera = new Camera(centreCamera, directionCamera, cameraUp, FOV);
    rCamera->focalPoint(centerSphere + directionCamera.normalize() * rSphere1->radius() * (-1.0));
    rCamera->aperture(Camera::Aperture::F_MEDIUM, Camera::Precision::SUPER_AWESOME);
    scene->add(rCamera);


    auto rCubeMapBckGrd = make_shared<CubeMap>(LCNS::Point(0.0), 260);  // 260

    rCubeMapBckGrd->addImage(CubeMap::Faces::BACK, "./resources/Desert_back.png");
    rCubeMapBckGrd->addImage(CubeMap::Faces::FRONT, "./resources/Desert_front.png");
    rCubeMapBckGrd->addImage(CubeMap::Faces::UP, "./resources/Desert_up.png");
    rCubeMapBckGrd->addImage(CubeMap::Faces::DOWN, "./resources/Desert_down.png");
    rCubeMapBckGrd->addImage(CubeMap::Faces::LEFT, "./resources/Desert_left.png");
    rCubeMapBckGrd->addImage(CubeMap::Faces::RIGHT, "./resources/Desert_right.png");

    rCubeMapBckGrd->interpolationMethod(Image::InterpolationMethod::LINEAR);

    scene->backgroundCubeMap(rCubeMapBckGrd);
}

void createFloor(Scene* scene, const FloorParameters& param)
{
    double deep = -1.0 * param.deep;

    Triangle* rTriangleZ1 = new Triangle(
    LCNS::Point(-param.size, deep, -param.size), LCNS::Point(-param.size, deep, param.size), LCNS::Point(param.size, deep, param.size));
    Triangle* rTriangleZ2 = new Triangle(
    LCNS::Point(-param.size, deep, -param.size), LCNS::Point(param.size, deep, param.size), LCNS::Point(param.size, deep, -param.size));

    rTriangleZ1->setVertexNormal(0, Vector(0.0, 1.0, 0.0));
    rTriangleZ1->setVertexNormal(1, Vector(0.0, 1.0, 0.0));
    rTriangleZ1->setVertexNormal(2, Vector(0.0, 1.0, 0.0));

    rTriangleZ2->setVertexNormal(0, Vector(0.0, 1.0, 0.0));
    rTriangleZ2->setVertexNormal(1, Vector(0.0, 1.0, 0.0));
    rTriangleZ2->setVertexNormal(2, Vector(0.0, 1.0, 0.0));

    // Create BRDF model for the triangle
    Phong* bRDFTriangle = new Phong(param.diffusion, param.specular, 3);
    bRDFTriangle->ambient(Color(0.0f));

    if (param.floorTexturePath.compare("no_texture"))
    {
        auto rCubeMapFloor = make_shared<CubeMap>(LCNS::Point(0.0, -4.0, 0.0), param.size * 2.0);

        rCubeMapFloor->addImage(CubeMap::Faces::BACK, param.floorTexturePath);
        rCubeMapFloor->setLink(CubeMap::Faces::FRONT, 0);
        rCubeMapFloor->setLink(CubeMap::Faces::UP, 0);
        rCubeMapFloor->setLink(CubeMap::Faces::DOWN, 0);
        rCubeMapFloor->setLink(CubeMap::Faces::LEFT, 0);
        rCubeMapFloor->setLink(CubeMap::Faces::RIGHT, 0);

        rCubeMapFloor->interpolationMethod(Image::InterpolationMethod::NEAREST);

        scene->add(rCubeMapFloor);

        bRDFTriangle->cubeMap(rCubeMapFloor);
    }


    // Create a shader for the triangle
    Shader* shaderTriangle = new Shader(bRDFTriangle, param.reflectionCoeff, param.refractionCoeff, scene);
    shaderTriangle->setReflectionCountMax(param.maxReflection);

    rTriangleZ1->setShader(shaderTriangle);
    rTriangleZ2->setShader(shaderTriangle);

    scene->add(rTriangleZ1);
    scene->add(rTriangleZ2);
    scene->add(bRDFTriangle, string("brdf of the triangles of the floor"));
    scene->add(shaderTriangle, string("shader of the triangles of the floor"));
}

void createRoom(Scene* scene, const RoomParameters& param)
{
    LCNS::Point zero(param.lowCorner);
    LCNS::Point one(zero.x(), zero.y(), zero.z() + param.dimensions.z());
    LCNS::Point two(zero.x() + param.dimensions.x(), zero.y(), zero.z() + param.dimensions.z());
    LCNS::Point three(zero.x() + param.dimensions.x(), zero.y(), zero.z());
    LCNS::Point four(zero.x(), zero.y() + param.dimensions.y(), zero.z());
    LCNS::Point five(zero.x(), zero.y() + param.dimensions.y(), zero.z() + param.dimensions.z());
    LCNS::Point six = param.lowCorner + param.dimensions;
    LCNS::Point seven(zero.x() + param.dimensions.x(), zero.y() + param.dimensions.y(), zero.z());

    // Create floor
    Triangle* rTriFloor1 = new Triangle(zero, one, two);
    Triangle* rTriFloor2 = new Triangle(zero, two, three);

    rTriFloor1->setVertexNormal(0, Vector(0.0, 1.0, 0.0));
    rTriFloor1->setVertexNormal(1, Vector(0.0, 1.0, 0.0));
    rTriFloor1->setVertexNormal(2, Vector(0.0, 1.0, 0.0));

    rTriFloor2->setVertexNormal(0, Vector(0.0, 1.0, 0.0));
    rTriFloor2->setVertexNormal(1, Vector(0.0, 1.0, 0.0));
    rTriFloor2->setVertexNormal(2, Vector(0.0, 1.0, 0.0));

    LCNS::Point middleOfFace((zero.x() + one.x() + two.x() + three.x()) * 0.25,
                             (zero.y() + one.y() + two.y() + three.y()) * 0.25,
                             (zero.z() + one.z() + two.z() + three.z()) * 0.25);

    Phong* rBRDF_Floor = new Phong(param.diffusion, param.specular, 3);
    //    rBRDF_Floor->ambient(Color(0.0f));

    if (param.floorTexturePath.compare("no_texture"))
    {
        auto rCubeMapFloor = make_shared<CubeMap>(middleOfFace, max(param.dimensions.x(), param.dimensions.z()));

        rCubeMapFloor->addImage(CubeMap::Faces::BACK, param.floorTexturePath);
        rCubeMapFloor->setLink(CubeMap::Faces::FRONT, 0);
        rCubeMapFloor->setLink(CubeMap::Faces::UP, 0);
        rCubeMapFloor->setLink(CubeMap::Faces::DOWN, 0);
        rCubeMapFloor->setLink(CubeMap::Faces::LEFT, 0);
        rCubeMapFloor->setLink(CubeMap::Faces::RIGHT, 0);

        rCubeMapFloor->interpolationMethod(Image::InterpolationMethod::LINEAR);

        scene->add(rCubeMapFloor);

        rBRDF_Floor->cubeMap(rCubeMapFloor);
    }

    Shader* rShaderFloor = new Shader(rBRDF_Floor, param.reflectionCoeff, param.refractionCoeff, scene);
    rShaderFloor->setReflectionCountMax(param.maxReflection);

    rTriFloor1->setShader(rShaderFloor);
    rTriFloor2->setShader(rShaderFloor);

    scene->add(rTriFloor1);
    scene->add(rTriFloor2);
    scene->add(rBRDF_Floor, string("brdf of the triangles of the floor"));
    scene->add(rShaderFloor, string("shader of the triangles of the floor"));


    // Create left wall
    Triangle* rTriLeftWall1 = new Triangle(zero, four, five);
    Triangle* rTriLeftWall2 = new Triangle(zero, five, one);

    rTriLeftWall1->setVertexNormal(0, Vector(1.0, 0.0, 0.0));
    rTriLeftWall1->setVertexNormal(1, Vector(1.0, 0.0, 0.0));
    rTriLeftWall1->setVertexNormal(2, Vector(1.0, 0.0, 0.0));

    rTriLeftWall2->setVertexNormal(0, Vector(1.0, 0.0, 0.0));
    rTriLeftWall2->setVertexNormal(1, Vector(1.0, 0.0, 0.0));
    rTriLeftWall2->setVertexNormal(2, Vector(1.0, 0.0, 0.0));

    middleOfFace.x((zero.x() + one.x() + four.x() + five.x()) * 0.25);
    middleOfFace.y((zero.y() + one.y() + four.y() + five.y()) * 0.25);
    middleOfFace.z((zero.z() + one.z() + four.z() + five.z()) * 0.25);

    Phong* rBRDFLeftWall = new Phong(param.diffusion, param.specular, 3);
    rBRDFLeftWall->ambient(Color(0.1f));

    if (param.wallLeftTexturePath.compare("no_texture"))
    {
        auto rCubeMapLeftWall = make_shared<CubeMap>(middleOfFace, max(param.dimensions.y(), param.dimensions.z()));

        rCubeMapLeftWall->addImage(CubeMap::Faces::BACK, param.wallLeftTexturePath);
        rCubeMapLeftWall->setLink(CubeMap::Faces::FRONT, 0);
        rCubeMapLeftWall->setLink(CubeMap::Faces::UP, 0);
        rCubeMapLeftWall->setLink(CubeMap::Faces::DOWN, 0);
        rCubeMapLeftWall->setLink(CubeMap::Faces::LEFT, 0);
        rCubeMapLeftWall->setLink(CubeMap::Faces::RIGHT, 0);

        rCubeMapLeftWall->interpolationMethod(Image::InterpolationMethod::LINEAR);

        scene->add(rCubeMapLeftWall);

        rBRDFLeftWall->cubeMap(rCubeMapLeftWall);
    }

    Shader* rShaderLeftWall = new Shader(rBRDFLeftWall, param.reflectionCoeff, param.refractionCoeff, scene);
    rShaderLeftWall->setReflectionCountMax(param.maxReflection);

    rTriLeftWall1->setShader(rShaderLeftWall);
    rTriLeftWall2->setShader(rShaderLeftWall);

    scene->add(rTriLeftWall1);
    scene->add(rTriLeftWall2);
    scene->add(rBRDFLeftWall, string("brdf of the triangles of the left wall"));
    scene->add(rShaderLeftWall, string("shader of the triangles of the left wall"));


    // Create back wall
    Triangle* rTriBackWall1 = new Triangle(zero, three, four);
    Triangle* rTriBackWall2 = new Triangle(four, three, seven);

    rTriBackWall1->setVertexNormal(0, Vector(0.0, 0.0, 1.0));
    rTriBackWall1->setVertexNormal(1, Vector(0.0, 0.0, 1.0));
    rTriBackWall1->setVertexNormal(2, Vector(0.0, 0.0, 1.0));

    rTriBackWall2->setVertexNormal(0, Vector(0.0, 0.0, 1.0));
    rTriBackWall2->setVertexNormal(1, Vector(0.0, 0.0, 1.0));
    rTriBackWall2->setVertexNormal(2, Vector(0.0, 0.0, 1.0));

    middleOfFace.x((zero.x() + three.x() + four.x() + seven.x()) * 0.25);
    middleOfFace.y((zero.y() + three.y() + four.y() + seven.y()) * 0.25);
    middleOfFace.z((zero.z() + three.z() + four.z() + seven.z()) * 0.25);

    Phong* rBRDFBackWall = new Phong(param.diffusion, param.specular, 3);
    rBRDFBackWall->ambient(Color(0.1f));

    if (param.wallBackTexturePath.compare("no_texture"))
    {
        auto rCubeMapBackWall = make_shared<CubeMap>(middleOfFace, max(param.dimensions.x(), param.dimensions.y()));

        rCubeMapBackWall->addImage(CubeMap::Faces::BACK, param.wallBackTexturePath);
        rCubeMapBackWall->setLink(CubeMap::Faces::FRONT, 0);
        rCubeMapBackWall->setLink(CubeMap::Faces::UP, 0);
        rCubeMapBackWall->setLink(CubeMap::Faces::DOWN, 0);
        rCubeMapBackWall->setLink(CubeMap::Faces::LEFT, 0);
        rCubeMapBackWall->setLink(CubeMap::Faces::RIGHT, 0);

        rCubeMapBackWall->interpolationMethod(Image::InterpolationMethod::LINEAR);

        scene->add(rCubeMapBackWall);

        rBRDFBackWall->cubeMap(rCubeMapBackWall);
    }

    Shader* rShaderBackWall = new Shader(rBRDFBackWall, param.reflectionCoeff, param.refractionCoeff, scene);
    rShaderBackWall->setReflectionCountMax(param.maxReflection);

    rTriBackWall1->setShader(rShaderBackWall);
    rTriBackWall2->setShader(rShaderBackWall);

    scene->add(rTriBackWall1);
    scene->add(rTriBackWall2);
    scene->add(rBRDFBackWall, string("brdf of the triangles of the back wall"));
    scene->add(rShaderBackWall, string("shader of the triangles of the back wall"));

    // Create right wall
    Triangle* rTriRightWall1 = new Triangle(three, two, six);
    Triangle* rTriRightWall2 = new Triangle(three, six, seven);

    rTriRightWall1->setVertexNormal(0, Vector(-1.0, 0.0, 0.0));
    rTriRightWall1->setVertexNormal(1, Vector(-1.0, 0.0, 0.0));
    rTriRightWall1->setVertexNormal(2, Vector(-1.0, 0.0, 0.0));

    rTriRightWall2->setVertexNormal(0, Vector(-1.0, 0.0, 0.0));
    rTriRightWall2->setVertexNormal(1, Vector(-1.0, 0.0, 0.0));
    rTriRightWall2->setVertexNormal(2, Vector(-1.0, 0.0, 0.0));

    middleOfFace.x((two.x() + three.x() + six.x() + seven.x()) * 0.25);
    middleOfFace.y((two.y() + three.y() + six.y() + seven.y()) * 0.25);
    middleOfFace.z((two.z() + three.z() + six.z() + seven.z()) * 0.25);

    Phong* rBRDFRightWall = new Phong(param.diffusion, param.specular, 3);
    rBRDFRightWall->ambient(Color(0.1f));

    if (param.wallRightTexturePath.compare("no_texture"))
    {
        auto rCubeMapRightWall = make_shared<CubeMap>(middleOfFace, max(param.dimensions.y(), param.dimensions.z()));

        rCubeMapRightWall->addImage(CubeMap::Faces::BACK, param.wallRightTexturePath);
        rCubeMapRightWall->setLink(CubeMap::Faces::FRONT, 0);
        rCubeMapRightWall->setLink(CubeMap::Faces::UP, 0);
        rCubeMapRightWall->setLink(CubeMap::Faces::DOWN, 0);
        rCubeMapRightWall->setLink(CubeMap::Faces::LEFT, 0);
        rCubeMapRightWall->setLink(CubeMap::Faces::RIGHT, 0);

        rCubeMapRightWall->interpolationMethod(Image::InterpolationMethod::LINEAR);

        scene->add(rCubeMapRightWall);

        rBRDFRightWall->cubeMap(rCubeMapRightWall);
    }

    Shader* rShaderRightWall = new Shader(rBRDFRightWall, param.reflectionCoeff, param.refractionCoeff, scene);
    rShaderRightWall->setReflectionCountMax(param.maxReflection);

    rTriRightWall1->setShader(rShaderRightWall);
    rTriRightWall2->setShader(rShaderRightWall);

    scene->add(rTriRightWall1);
    scene->add(rTriRightWall2);
    scene->add(rBRDFRightWall, string("brdf of the triangles of the right wall"));
    scene->add(rShaderRightWall, string("shader of the triangles of the right wall"));

    // Create roof
    Triangle* rTriCeiling1 = new Triangle(four, five, six);
    Triangle* rTriCeiling2 = new Triangle(four, six, seven);

    rTriCeiling1->setVertexNormal(0, Vector(0.0, -1.0, 0.0));
    rTriCeiling1->setVertexNormal(1, Vector(0.0, -1.0, 0.0));
    rTriCeiling1->setVertexNormal(2, Vector(0.0, -1.0, 0.0));

    rTriCeiling2->setVertexNormal(0, Vector(0.0, -1.0, 0.0));
    rTriCeiling2->setVertexNormal(1, Vector(0.0, -1.0, 0.0));
    rTriCeiling2->setVertexNormal(2, Vector(0.0, -1.0, 0.0));

    middleOfFace.x((four.x() + five.x() + six.x() + seven.x()) * 0.25);
    middleOfFace.y((four.y() + five.y() + six.y() + seven.y()) * 0.25);
    middleOfFace.z((four.z() + five.z() + six.z() + seven.z()) * 0.25);

    Phong* rBRDFCeiling = new Phong(param.diffusion, param.specular, 13);
    rBRDFCeiling->ambient(Color(0.1f));

    if (param.ceilingTexturePath.compare("no_texture"))
    {
        auto rCubeMapCeiling = make_shared<CubeMap>(middleOfFace, max(param.dimensions.x(), param.dimensions.z()));

        rCubeMapCeiling->addImage(CubeMap::Faces::DOWN, param.ceilingTexturePath);
        rCubeMapCeiling->setLink(CubeMap::Faces::FRONT, 0);
        rCubeMapCeiling->setLink(CubeMap::Faces::UP, 0);
        rCubeMapCeiling->setLink(CubeMap::Faces::BACK, 0);
        rCubeMapCeiling->setLink(CubeMap::Faces::LEFT, 0);
        rCubeMapCeiling->setLink(CubeMap::Faces::RIGHT, 0);

        rCubeMapCeiling->interpolationMethod(Image::InterpolationMethod::LINEAR);

        scene->add(rCubeMapCeiling);

        rBRDFCeiling->cubeMap(rCubeMapCeiling);
    }


    Shader* rShaderCeiling = new Shader(rBRDFCeiling, param.reflectionCoeff, param.refractionCoeff, scene);
    rShaderCeiling->setReflectionCountMax(param.maxReflection);

    rTriCeiling1->setShader(rShaderCeiling);
    rTriCeiling2->setShader(rShaderCeiling);

    scene->add(rTriCeiling1);
    scene->add(rTriCeiling2);
    scene->add(rBRDFCeiling, string("brdf of the triangles of the roof"));
    scene->add(rShaderCeiling, string("shader of the triangles of the roof"));
}
