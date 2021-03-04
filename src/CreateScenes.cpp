//===============================================================================================//
/*!
 *  \file      CreateScenes.cpp
 *  \author    Loïc Corenthy
 *  \version   1.1
 *  \date      15/12/2012
 *  \copyright (c) 2012 Loïc Corenthy. All rights reserved.
 */
//===============================================================================================//

#include "CreateScenes.hpp"

#include <iostream>
#include <algorithm>
#include <memory>

using std::make_shared;
using std::make_unique;
using std::max;
using std::shared_ptr;
using std::static_pointer_cast;
using std::string;
using std::unique_ptr;

using namespace LCNS;

void createTestScene(shared_ptr<Scene> scene)
{
    Point                  centerSphere1(0.0, 0.0, 0.0);
    shared_ptr<Renderable> rSphere1 = make_shared<Sphere>(centerSphere1, 2.3);

    // Create a BRDF model for the sphere
    Color            diffusionSphere1(1.0, 0.0, 0.0);
    Color            specularSphere1(0.7, 0.3, 0.3);
    shared_ptr<BRDF> rBRDFSphere1 = make_shared<Phong>(diffusionSphere1, specularSphere1, 5);

    // Create a shader for the sphere
    auto rShaderSphere1 = make_shared<Shader>(rBRDFSphere1, 1.0, 1.0, scene, Shader::NONE);
    rShaderSphere1->setReflectionCountMax(2);
    rSphere1->shader(rShaderSphere1);

    scene->add(rSphere1);
    scene->add(rBRDFSphere1, string("brdf of sphere 1"));
    scene->add(rShaderSphere1, string("shader of sphere 1"));


    ////////////
    // LIGHTS //
    ////////////
    shared_ptr<Light> rLight1 = make_shared<DirectionalLight>(Vector(0.0, 0.0, -1.0), Color(22.0));
    scene->add(rLight1);


    ////////////
    // CAMERA //
    ////////////
    Point  centreCamera(0.0, 6.0, 10.0);
    Vector directionCamera(0.0, -0.5, -1.0);
    Vector cameraUp(0.0, 1.0, 0.0);
    double FOV = 60. * 3.141592 / 180.0;

    auto camera = make_unique<Camera>(centreCamera, directionCamera, cameraUp, FOV);
    scene->add(move(camera));


    ////////////////
    // BACKGROUND //
    ////////////////
    scene->setBackgroundColor(Color(0.3));
}

void createScene01(shared_ptr<Scene> scene)
{
    // Same reflection coefficient for all the spheres
    const double reflectionCoeff = 2.0;
    const double refractionCoeff = 1.0;

    ////////////////
    // RED SPHERE //
    ////////////////
    Point                  centerSphere1(0.0, 2.0, 2.1);
    shared_ptr<Renderable> rSphere1 = make_shared<Sphere>(centerSphere1, 0.3);

    // Create a BRDF model for the sphere
    Color            diffusionSphere1(1.0, 0.0, 0.0);
    Color            specularSphere1(0.7, 0.3, 0.3);
    shared_ptr<BRDF> rBRDFSphere1 = make_shared<Phong>(diffusionSphere1, specularSphere1, 5);

    // Create a shader for the sphere
    auto rShaderSphere1 = make_shared<Shader>(rBRDFSphere1, reflectionCoeff, refractionCoeff, scene, Shader::MARBLE);
    rShaderSphere1->setReflectionCountMax(2);
    rSphere1->shader(rShaderSphere1);

    scene->add(rSphere1);
    scene->add(rBRDFSphere1, string("brdf of sphere 1"));
    scene->add(rShaderSphere1, string("shader of sphere 1"));

    //////////////////
    // GREEN SPHERE //
    //////////////////
    Point                  centerSphere2(2.0, 0.5, 0.0);
    shared_ptr<Renderable> rSphere2 = make_shared<Sphere>(centerSphere2, 1.5);

    // Create a BRDF model for the sphere
    Color            diffusionSphere2(0.0, 1.0, 0.0);
    Color            specularSphere2(1.0);
    shared_ptr<BRDF> rBRDFSphere2 = make_shared<Phong>(diffusionSphere2, specularSphere2, 15);

    // Create a shader for the second sphere
    auto rShaderSphere2 = make_shared<Shader>(rBRDFSphere2, reflectionCoeff, refractionCoeff, scene, Shader::MARBLE);
    rShaderSphere2->setReflectionCountMax(2);
    rSphere2->shader(rShaderSphere2);

    scene->add(rSphere2);
    scene->add(rBRDFSphere2, string("brdf of sphere 2"));
    scene->add(rShaderSphere2, string("shader of sphere 2"));

    /////////////////
    // BLUE SPHERE //
    /////////////////
    Point                  centerSphere3(-1.8, 0.0, 0.0);
    shared_ptr<Renderable> rSphere3 = make_shared<Sphere>(centerSphere3, 1.0);

    // Create a BRDF model for the sphere
    Color            diffusionSphere3(0.0, 0.0, 1.0);
    Color            specularSphere3(0.8, 0.8, 1.0);
    shared_ptr<BRDF> rBRDFSphere3 = make_shared<Phong>(diffusionSphere3, specularSphere3, 25);

    // Create a shader for the third sphere
    auto rShaderSphere3 = make_shared<Shader>(rBRDFSphere3, reflectionCoeff, refractionCoeff, scene, Shader::MARBLE);
    rShaderSphere3->setReflectionCountMax(2);
    rSphere3->shader(rShaderSphere3);

    scene->add(rSphere3);
    scene->add(rBRDFSphere3, string("brdf of sphere 3"));
    scene->add(rShaderSphere3, string("shader of sphere 3"));

    ////////////
    // LIGHTS //
    ////////////
    Point             light1Position(0., 0.0, 5.0);
    Color             light1Color(9.0);
    shared_ptr<Light> rLight1 = make_shared<PunctualLight>(light1Position, light1Color);
    scene->add(rLight1);

    ////////////
    // CAMERA //
    ////////////
    Point  centreCamera(0.0, 2.5, 6.0);
    Vector directionCamera(0.05, -0.4, -1.0);
    Vector cameraUp(0., 1., 0.);
    double FOV = 60. * 3.141592 / 180.;

    auto camera = make_unique<Camera>(centreCamera, directionCamera, cameraUp, FOV);
    scene->add(move(camera));

    ////////////////
    // BACKGROUND //
    ////////////////
    scene->setBackgroundColor(Color(0));
}


void createScene02(shared_ptr<Scene> scene)
{
    // Same reflection coefficient for the spheres behind
    const double reflectionCoeff = 5.8;
    const double refractionCoeff = 1.0;

    ////////////////
    // RED SPHERE //
    ////////////////
    Point                  centerSphere1(-60.0, 0.0, 60.0);
    shared_ptr<Renderable> rSphere1 = make_shared<Sphere>(centerSphere1, 40.);

    // Create a BRDF model for the sphere
    Color            diffusionSphere1(1.0, 0.6, 0.6);
    Color            specularSphere1(0.9, 0.4, 0.4);
    shared_ptr<BRDF> rBRDFSphere1 = make_shared<Phong>(diffusionSphere1 * 2.0, specularSphere1, 3);

    // Create a shader for the sphere
    auto rShaderSphere1 = make_shared<Shader>(rBRDFSphere1, reflectionCoeff, refractionCoeff, scene);
    rShaderSphere1->setReflectionCountMax(3);
    rSphere1->shader(rShaderSphere1);

    scene->add(rSphere1);
    scene->add(rBRDFSphere1, string("brdf of sphere 1"));
    scene->add(rShaderSphere1, string("shader of sphere 1"));


    //////////////////
    // GREEN SPHERE //
    //////////////////
    Point                  centerSphere2(60.0, 0.0, 50.0);
    shared_ptr<Renderable> rSphere2 = make_shared<Sphere>(centerSphere2, 40.);

    // Create a BRDF model for the sphere
    Color            diffusionSphere2(0.6, 1.0, 0.6);
    Color            specularSphere2(0.4, 1.0, 0.4);
    shared_ptr<BRDF> rBRDFSphere2 = make_shared<Phong>(diffusionSphere2 * 2.0, specularSphere2, 3);

    // Create a shader for the second sphere
    auto rShaderSphere2 = make_shared<Shader>(rBRDFSphere2, reflectionCoeff, refractionCoeff, scene);
    rShaderSphere2->setReflectionCountMax(3);
    rSphere2->shader(rShaderSphere2);

    scene->add(rSphere2);
    scene->add(rBRDFSphere2, string("brdf of sphere 2"));
    scene->add(rShaderSphere2, string("shader of sphere 2"));


    /////////////////
    // BLUE SPHERE //
    /////////////////
    Point                  centerSphere3(0.0, -10.0, 110.0);
    shared_ptr<Renderable> rSphere3 = make_shared<Sphere>(centerSphere3, 20.0);

    // Create a BRDF model for the sphere
    Color            diffusionSphere3(0.6, 0.6, 1.0);
    Color            specularSphere3(0.4, 0.4, 0.9);
    shared_ptr<BRDF> rBRDFSphere3 = make_shared<Phong>(diffusionSphere3 * 2.0, specularSphere3, 3);

    // Create a shader for the third sphere
    auto rShaderSphere3 = make_shared<Shader>(rBRDFSphere3, reflectionCoeff, 1.0, scene);
    rShaderSphere3->setReflectionCountMax(3);
    rSphere3->shader(rShaderSphere3);

    scene->add(rSphere3);
    scene->add(rBRDFSphere3, string("brdf of sphere 3"));
    scene->add(rShaderSphere3, string("shader of sphere 3"));


    ///////////////////////////////
    // CYAN SPHERE IN BACKGROUND //
    ///////////////////////////////
    Point                  centerSphere4(-50.0, 0.0, -250.0);
    shared_ptr<Renderable> rSphere4 = make_shared<Sphere>(centerSphere4, 100.0);

    // Create a BRDF model for the sphere
    Color            diffusionSphere4(0, 255, 255);
    Color            specularSphere4(0.0);
    shared_ptr<BRDF> rBRDFSphere4 = make_shared<Phong>(diffusionSphere4 * 6, specularSphere4, 3);

    // Create a shader for the fourth sphere
    auto rShaderSphere4 = make_shared<Shader>(rBRDFSphere4, 0.0, 1.0, scene);
    rSphere4->shader(rShaderSphere4);

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
    Point             light1Position(50., 130., 150.0);
    Color             light1Color(18.0);
    shared_ptr<Light> rLight1 = make_shared<PunctualLight>(light1Position, light1Color);
    scene->add(rLight1);

    Point             light2Position(20., 150., 150.0);
    Color             light2Color(18.0);
    shared_ptr<Light> rLight2 = make_shared<PunctualLight>(light2Position, light2Color);
    scene->add(rLight2);

    Point             light3Position(-70., 50., 110.0);
    Color             light3Color(15.0);
    shared_ptr<Light> rLight3 = make_shared<PunctualLight>(light3Position, light3Color);
    scene->add(rLight3);

    Point             light4Position(-20., 50., 160.0);
    Color             light4Color(15.0);
    shared_ptr<Light> rLight4 = make_shared<PunctualLight>(light4Position, light4Color);
    scene->add(rLight4);


    ////////////
    // CAMERA //
    ////////////
    Point  centreCamera(0.0, 100.0, 250.0);
    Vector directionCamera(0.0, -0.6, -1.0);
    Vector cameraUp(0., 1., 0.);
    double FOV = 80. * 3.141592 / 180.;

    auto camera = make_unique<Camera>(centreCamera, directionCamera, cameraUp, FOV);
    camera->focalPoint(centerSphere3);
    camera->aperture(Camera::Aperture::F_SMALL, Camera::Precision::SUPER_AWESOME);

    scene->add(move(camera));


    ////////////////
    // BACKGROUND //
    ////////////////
    scene->setBackgroundColor(Color(2, 6, 13));
}

void createScene03(shared_ptr<Scene> scene)
{
    // Same reflection coefficient for the spheres
    const double reflection = 1.0;
    const double refraction = 1.0;

    //////////////////////////////////////
    // SPHERE WITH A TURBULANCE TEXTURE //
    //////////////////////////////////////
    Point                  center(-20.0, 0.0, 0.0);
    shared_ptr<Renderable> rSphere1 = make_shared<Sphere>(center, 3.0);

    Color            diffusion(245, 222, 179);
    Color            specular(255, 255, 255);
    shared_ptr<BRDF> rBRDF1 = make_shared<Phong>(diffusion * 2.0, specular, 15);

    // Create a shader for the turbulance sphere
    auto rShader1 = make_shared<Shader>(rBRDF1, reflection, refraction, scene, Shader::Material::TURBULANCE);
    rShader1->setReflectionCountMax(2);

    rSphere1->shader(rShader1);

    scene->add(rSphere1);
    scene->add(rBRDF1, string("brdf of sphere 1"));
    scene->add(rShader1, string("shader of sphere 1"));

    //////////////////////////////////
    // SPHERE WITH A MARBLE TEXTURE //
    //////////////////////////////////
    center.set(-10.0, 0.0, 0.0);
    shared_ptr<Renderable> rSphere2 = make_shared<Sphere>(center, 3.0);

    diffusion.set(0, 255, 255);
    shared_ptr<BRDF> rBRDF2 = make_shared<Phong>(diffusion, specular, 15);

    // Create a shader for the marble sphere
    auto rShader2 = make_shared<Shader>(rBRDF2, reflection, refraction, scene, Shader::Material::MARBLE);
    rShader2->setReflectionCountMax(2);

    rSphere2->shader(rShader2);

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
    shared_ptr<BRDF> rBRDFTorus = make_shared<Phong>(diffusion, specular, 3);

    // Create a shader for the torus
    auto rShaderTorus = make_shared<Shader>(rBRDFTorus, 0.8, 1.0, scene, Shader::NONE);

    // Get an iterator on the object of the scene and displace it until refers to the torus
    auto it = scene->renderableList().begin();
    it++;
    it++;

    (*it)->shader(rShaderTorus);

    scene->add(rBRDFTorus, string("brdf of the torus"));
    scene->add(rShaderTorus, string("shader of the torus"));

    ////////////////////////////////
    // SPHERE WITH A BUMP TEXTURE //
    ////////////////////////////////
    center.set(8.0, 0.0, 0.0);
    shared_ptr<Renderable> rSphere3 = make_shared<Sphere>(center, 3.0);

    diffusion.set(127, 255, 0);
    shared_ptr<BRDF> rBRDF3 = make_shared<Phong>(diffusion, specular, 15);

    // Create a shader for the marble sphere
    auto rShader3 = make_shared<Shader>(rBRDF3, reflection, refraction, scene, Shader::Material::BUMP);
    rShader3->setReflectionCountMax(2);

    rSphere3->shader(rShader3);

    scene->add(rSphere3);
    scene->add(rBRDF3, string("brdf of sphere 3"));
    scene->add(rShader3, string("shader of sphere 3"));

    ///////////////////////////
    // SPHERE WITH A TEXTURE //
    ///////////////////////////
    center.set(18.0, 0.0, 0.0);
    shared_ptr<Renderable> rSphere4 = make_shared<Sphere>(center, 3.0);

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
    shared_ptr<BRDF> rBRDF4 = make_shared<Phong>(diffusion * 2.0, specular, 15);
    rBRDF4->cubeMap(rCubeMapSphere);

    // Create a shader for the sphere
    auto rShader4 = make_shared<Shader>(rBRDF4, reflection, refraction, scene);
    rShader4->setReflectionCountMax(1);
    rSphere4->shader(rShader4);

    scene->add(rSphere4);
    scene->add(rBRDF4, string("brdf of sphere 4"));
    scene->add(rShader4, string("shader of sphere 4"));


    ////////////
    // LIGHTS //
    ////////////
    Point lightPos(0.0, 20.0, 15.0);
    Color lightCol(18.0);

    shared_ptr<Light> rLight = make_shared<PunctualLight>(lightPos, lightCol);
    scene->add(rLight);


    ////////////
    // CAMERA //
    ////////////
    Point  centreCamera(1.5, 10.0, 25.0);
    Vector directionCamera(-0.05, -0.4, -1.0);
    Vector cameraUp(0., 1.0, 0.);
    double FOV = 90. * 3.141592 / 180.;

    auto camera = make_unique<Camera>(centreCamera, directionCamera, cameraUp, FOV);
    camera->aperture(Camera::Aperture::ALL_SHARP);

    scene->add(move(camera));

    ///////////
    // FLOOR //
    ///////////
    FloorParameters floorParameters = { Color(0.0), Color(0.0), 1.0, 1.0, 2, 40.0, 3.0, string("no_texture") };
    createFloor(scene, floorParameters);


    ////////////////
    // BACKGROUND //
    ////////////////
    scene->setBackgroundColor(Color(0.0));
}


void createScene04(shared_ptr<Scene> scene)
{
    // Same reflection coefficient for the spheres behind
    double reflectionCoeff = 8.0;
    double refractionCoeff = 1.0;

    // Create a sphere
    Point                  centerSphere1(-180.0, 0.0, 0.0);
    shared_ptr<Renderable> rSphere1 = make_shared<Sphere>(centerSphere1, 50.);

    // Create a BRDF model for the sphere
    Color            diffusionSphere1(1.3, 0.0, 0.0);
    Color            specularSphere1(1.0);
    shared_ptr<BRDF> rBRDFSphere1 = make_shared<Phong>(diffusionSphere1, specularSphere1, 25);

    // Create a shader for the sphere
    auto rShaderSphere1 = make_shared<Shader>(rBRDFSphere1, reflectionCoeff, refractionCoeff, scene);
    rShaderSphere1->setReflectionCountMax(2);
    rSphere1->shader(rShaderSphere1);

    scene->add(rSphere1);
    scene->add(rBRDFSphere1, string("brdf of sphere 1"));
    scene->add(rShaderSphere1, string("shader of sphere 1"));

    // Create a second sphere
    Point                  centerSphere2(0.0, 0.0, 0.0);
    shared_ptr<Renderable> rSphere2 = make_shared<Sphere>(centerSphere2, 50.);

    // Create a BRDF model for the sphere
    Color            diffusionSphere2(0.0, 1.2, 0.0);
    Color            specularSphere2(0.8);
    shared_ptr<BRDF> rBRDFSphere2 = make_shared<Phong>(diffusionSphere2, specularSphere2, 25);

    // Create a shader for the second sphere
    auto rShaderSphere2 = make_shared<Shader>(rBRDFSphere2, reflectionCoeff, refractionCoeff, scene);
    rShaderSphere2->setReflectionCountMax(2);
    rSphere2->shader(rShaderSphere2);

    scene->add(rSphere2);
    scene->add(rBRDFSphere2, string("brdf of sphere 2"));
    scene->add(rShaderSphere2, string("shader of sphere 2"));

    // Create a purple sphere
    Point                  centerSphere3(180.0, 0.0, 0.0);
    shared_ptr<Renderable> rSphere3 = make_shared<Sphere>(centerSphere3, 50.0);

    // Create a BRDF model for the sphere
    Color            diffusionSphere3(0.24, 0.34, 1.97);
    Color            specularSphere3(0.8);
    shared_ptr<BRDF> rBRDFSphere3 = make_shared<Phong>(diffusionSphere3, specularSphere3, 25);

    // Create a shader for the third sphere
    auto rShaderSphere3 = make_shared<Shader>(rBRDFSphere3, reflectionCoeff, refractionCoeff, scene);
    rShaderSphere3->setReflectionCountMax(2);
    rSphere3->shader(rShaderSphere3);

    scene->add(rSphere3);
    scene->add(rBRDFSphere3, string("brdf of sphere 3"));
    scene->add(rShaderSphere3, string("shader of sphere 3"));


    ////////////
    // LIGHTS //
    ////////////
    Point             light1Position(0., 0.0, 100.0);
    Color             lowLightColor(20.0);
    shared_ptr<Light> rLight1 = make_shared<PunctualLight>(light1Position, lowLightColor);
    scene->add(rLight1);

    Point             light2Position(-200., 0.0, 100.0);
    shared_ptr<Light> rLight2 = make_shared<PunctualLight>(light2Position, lowLightColor);
    scene->add(rLight2);

    Point             light3Position(200., 0.0, 100.0);
    shared_ptr<Light> rLight3 = make_shared<PunctualLight>(light3Position, lowLightColor);
    scene->add(rLight3);

    Point             light4Position(90., 300., 200.0);
    Color             highLightColor(200.0);
    shared_ptr<Light> rLight4 = make_shared<PunctualLight>(light4Position, highLightColor);
    scene->add(rLight4);

    Point             light5Position(-90., 300., 200.0);
    shared_ptr<Light> rLight5 = make_shared<PunctualLight>(light5Position, highLightColor);
    scene->add(rLight5);

    ////////////
    // CAMERA //
    ////////////
    Point  centreCamera(-200.0, 150.0, 400.0);
    Vector directionCamera(0.2, -0.25, -0.5);
    Vector cameraUp(0., 1., 0.);
    double FOV = 80. * 3.141592 / 180.;

    auto camera = make_unique<Camera>(centreCamera, directionCamera, cameraUp, FOV);
    camera->aperture(Camera::Aperture::ALL_SHARP, Camera::Precision::LOW, 10.0);

    scene->add(move(camera));

    // FLOOR
    FloorParameters floorParameters = { Color(1.0), Color(0.3), 1.0, 1.0, 2, 2000.0, 100.0, string("./resources/rect5130.png") };

    createFloor(scene, floorParameters);

    ////////////////
    // BACKGROUND //
    ////////////////
    scene->setBackgroundColor(Color(0.0));
}

void createScene04bis(shared_ptr<Scene> scene)
{
    // Same reflection coefficient for the spheres
    const double reflectionCoeff = 8.0;
    const double refractionCoeff = 1.0;

    ////////////////
    // RED SPHERE //
    ////////////////
    Point                  centerSphere1(-2.50, 0.0, 0.0);
    shared_ptr<Renderable> rSphere1 = make_shared<Sphere>(centerSphere1, 1.0);

    // Create a BRDF model for the sphere
    Color            diffusionSphere1(1.3, 0.0, 0.0);
    Color            specularSphere1(1.0);
    shared_ptr<BRDF> rBRDFSphere1 = make_shared<Phong>(diffusionSphere1, specularSphere1, 25);

    // Create a shader for the sphere
    auto rShaderSphere1 = make_shared<Shader>(rBRDFSphere1, reflectionCoeff, refractionCoeff, scene);
    rShaderSphere1->setReflectionCountMax(4);
    rSphere1->shader(rShaderSphere1);

    scene->add(rSphere1);
    scene->add(rBRDFSphere1, string("brdf of sphere 1"));
    scene->add(rShaderSphere1, string("shader of sphere 1"));


    //////////////////
    // GREEN SPHERE //
    //////////////////
    Point                  centerSphere2(0.0, 0.0, 0.0);
    shared_ptr<Renderable> rSphere2 = make_shared<Sphere>(centerSphere2, 1.0);

    // Create a BRDF model for the sphere
    Color            diffusionSphere2(0.0, 1.2, 0.0);
    Color            specularSphere2(0.8);
    shared_ptr<BRDF> rBRDFSphere2 = make_shared<Phong>(diffusionSphere2, specularSphere2, 25);

    // Create a shader for the second sphere
    auto rShaderSphere2 = make_shared<Shader>(rBRDFSphere2, reflectionCoeff, refractionCoeff, scene);
    rShaderSphere2->setReflectionCountMax(4);
    rSphere2->shader(rShaderSphere2);

    scene->add(rSphere2);
    scene->add(rBRDFSphere2, string("brdf of sphere 2"));
    scene->add(rShaderSphere2, string("shader of sphere 2"));

    ///////////////////
    // PURPLE SPHERE //
    ///////////////////
    Point                  centerSphere3(2.50, 0.0, 0.0);
    shared_ptr<Renderable> rSphere3 = make_shared<Sphere>(centerSphere3, 1.0);

    // Create a BRDF model for the sphere
    Color            diffusionSphere3(0.24, 0.34, 1.97);
    Color            specularSphere3(0.8);
    shared_ptr<BRDF> rBRDFSphere3 = make_shared<Phong>(diffusionSphere3, specularSphere3, 25);

    // Create a shader for the third sphere
    auto rShaderSphere3 = make_shared<Shader>(rBRDFSphere3, reflectionCoeff, refractionCoeff, scene);
    rShaderSphere3->setReflectionCountMax(4);
    rSphere3->shader(rShaderSphere3);

    scene->add(rSphere3);
    scene->add(rBRDFSphere3, string("brdf of sphere 3"));
    scene->add(rShaderSphere3, string("shader of sphere 3"));


    ////////////
    // LIGHTS //
    ////////////
    Point             light4Position(1.15, 4., 4.0);
    Color             lightColor(16.0);
    shared_ptr<Light> rLight4 = make_shared<PunctualLight>(light4Position, lightColor);
    scene->add(rLight4);

    Point             light5Position(-1.15, 4., 4.0);
    shared_ptr<Light> rLight5 = make_shared<PunctualLight>(light5Position, lightColor);
    scene->add(rLight5);


    ////////////
    // CAMERA //
    ////////////
    Point  centreCamera(-3.5, 2.50, 11.0);
    Vector directionCamera(0.15, -0.20, -0.5);
    Vector cameraUp(0., 1., 0.);
    double FOV = 80. * 3.141592 / 180.;

    auto camera = make_unique<Camera>(centreCamera, directionCamera, cameraUp, FOV);
    scene->add(move(camera));

    ///////////
    // FLOOR //
    ///////////
    FloorParameters floorParameters = { Color(1.0), Color(0.3), 1.0, 1.0, 2, 20.0, 2.0, string("./resources/small_damier.png") };
    createFloor(scene, floorParameters);

    ////////////////
    // BACKGROUND //
    ////////////////
    scene->setBackgroundColor(Color(0.0));
}


void createScene05(shared_ptr<Scene> scene)
{
    // TORUS
    string path = "./resources/torus.obj";
    scene->createFromFile(path);

    // Create a BRDF model for the torus
    Color            diffusionTorus(0.76, 0.33, 0.12);
    Color            specularTorus(0.9, 0.8, 0.8);
    shared_ptr<BRDF> rBRDFTorus = make_shared<Phong>(diffusionTorus, specularTorus, 3);

    // Create a shader for the sphere
    auto rShaderTorus = make_shared<Shader>(rBRDFTorus, 0.8, 1.0, scene, Shader::BUMP);

    auto it = scene->renderableList().begin();
    (*it)->shader(rShaderTorus);

    scene->add(rBRDFTorus, string("brdf of the torus"));
    scene->add(rShaderTorus, string("shader of the torus"));


    ////////////
    // LIGHTS //
    ////////////
    Point             light1Position(0., 1.0, 10.0);
    Color             light1Color(10.0);
    shared_ptr<Light> rLight1 = make_shared<PunctualLight>(light1Position, light1Color);
    scene->add(rLight1);

    Point             light4Position(0., 10., 6.0);
    Color             light4Color(10.0);
    shared_ptr<Light> rLight4 = make_shared<PunctualLight>(light4Position, light4Color);
    scene->add(rLight4);


    ////////////
    // CAMERA //
    ////////////
    Point  centreCamera(0.0, 3.0, 12.0);
    Vector directionCamera(0.01, -0.3, -1.0);
    Vector cameraUp(0., 1., 0.);
    double FOV = 60. * 3.141592 / 180.;

    auto camera = make_unique<Camera>(centreCamera, directionCamera, cameraUp, FOV);
    camera->aperture(Camera::Aperture::ALL_SHARP);

    scene->add(move(camera));


    // FLOOR
    FloorParameters floorParameters = { Color(0.6), Color(0.7), 1.0, 1.0, 2, 200.0, 50.0, string("no_texture") };
    createFloor(scene, floorParameters);


    ////////////////
    // BACKGROUND //
    ////////////////
    scene->setBackgroundColor(Color(0.7, 0.72, 0.2));
}

void createScene06(shared_ptr<Scene> scene)
{
    // Same reflection coefficient for the spheres
    const double reflectionCoeff = 0.8;

    // SPHERE WITH REFRACTION
    Point                  center(0.0, 0.0, 0.0);
    shared_ptr<Renderable> rSphere1 = make_shared<Sphere>(center, 5.);

    // Create a BRDF model for the sphere
    Color            diffusionSphere1(1.0);
    Color            specularSphere1(0.1);
    shared_ptr<BRDF> rBRDFSphere1 = make_shared<Phong>(diffusionSphere1, specularSphere1, 3);

    // Create a shader for the sphere
    auto rShaderSphere1 = make_shared<Shader>(rBRDFSphere1, reflectionCoeff, 2.0, scene);
    rSphere1->shader(rShaderSphere1);

    scene->add(rSphere1);
    scene->add(rBRDFSphere1, string("brdf of sphere 1"));
    scene->add(rShaderSphere1, string("shader of sphere 1"));

    // SPHERES IN THE BACKGROUND
    // Nearest spheres
    double size = 4.0;
    center.z(-20);

    // BG 1, left
    center.x(-20.0);
    shared_ptr<Renderable> rSphereL1 = make_shared<Sphere>(center, size);

    shared_ptr<BRDF> rBRDF_L1  = make_shared<Phong>(Color(250, 240, 230) * 5.0, Color(1.0), 3);
    auto             rShaderL1 = make_shared<Shader>(rBRDF_L1, reflectionCoeff, 1.0, scene, Shader::BUMP);

    rSphereL1->shader(rShaderL1);

    scene->add(rSphereL1);
    scene->add(rBRDF_L1, string("brdf left 1"));
    scene->add(rShaderL1, string("shader left 1"));

    // BG 1, right
    center.x(20.0);
    shared_ptr<Renderable> rSphereR1 = make_shared<Sphere>(center, size);

    shared_ptr<BRDF> rBRDFR1   = make_shared<Phong>(Color(135, 206, 250) * 5.0, Color(1.0), 3);
    auto             rShaderR1 = make_shared<Shader>(rBRDFR1, reflectionCoeff, 1.0, scene, Shader::BUMP);

    rSphereR1->shader(rShaderR1);

    scene->add(rSphereR1);
    scene->add(rBRDFR1, string("brdf right 1"));
    scene->add(rShaderR1, string("shader right 1"));

    // BG 1, down
    center.x(0.0);
    center.y(-20.0);
    shared_ptr<Renderable> rSphereD1 = make_shared<Sphere>(center, size);

    shared_ptr<BRDF> rBRDFD1   = make_shared<Phong>(Color(250, 128, 114) * 5.0, Color(1.0), 3);
    auto             rShaderD1 = make_shared<Shader>(rBRDFD1, reflectionCoeff, 1.0, scene, Shader::BUMP);

    rSphereD1->shader(rShaderD1);

    scene->add(rSphereD1);
    scene->add(rBRDFD1, string("brdf down 1"));
    scene->add(rShaderD1, string("shader down 1"));

    // BG 1, up
    center.y(20.0);
    shared_ptr<Renderable> rSphereU1 = make_shared<Sphere>(center, size);

    shared_ptr<BRDF> rBRDFU1   = make_shared<Phong>(Color(255, 250, 205) * 5.0, Color(1.0), 3);
    auto             rShaderU1 = make_shared<Shader>(rBRDFU1, reflectionCoeff, 1.0, scene, Shader::BUMP);

    rSphereU1->shader(rShaderU1);

    scene->add(rSphereU1);
    scene->add(rBRDFU1, string("brdf up 1"));
    scene->add(rShaderU1, string("shader up 1"));

    // Furthest spheres
    size = 22.0;
    center.z(-220);

    // BG 2, left down
    center.x(-85.0);
    center.y(-85.0);
    shared_ptr<Renderable> rSphereLD2 = make_shared<Sphere>(center, size);

    shared_ptr<BRDF> rBRDFLD2   = make_shared<Phong>(Color(127, 255, 212) * 5.0, Color(1.0), 3);
    auto             rShaderLD2 = make_shared<Shader>(rBRDFLD2, reflectionCoeff, 1.0, scene);

    rSphereLD2->shader(rShaderLD2);

    scene->add(rSphereLD2);
    scene->add(rBRDFLD2, string("brdf left down 2"));
    scene->add(rShaderLD2, string("shader left down 2"));

    // BG 2, right down
    center.x(85.0);
    center.y(-85.0);
    shared_ptr<Renderable> rSphereRD2 = make_shared<Sphere>(center, size);

    shared_ptr<BRDF> rBRDFRD2   = make_shared<Phong>(Color(240, 248, 255) * 5.0, Color(1.0), 3);
    auto             rShaderRD2 = make_shared<Shader>(rBRDFRD2, reflectionCoeff, 1.0, scene);

    rSphereRD2->shader(rShaderRD2);

    scene->add(rSphereRD2);
    scene->add(rBRDFRD2, string("brdf right down 2"));
    scene->add(rShaderRD2, string("shader right down 2"));

    // BG 2, left up
    center.x(-85.0);
    center.y(85.0);
    shared_ptr<Renderable> rSphereLU2 = make_shared<Sphere>(center, size);

    shared_ptr<BRDF> rBRDFLU2   = make_shared<Phong>(Color(255, 99, 71) * 5.0, Color(1.0), 3);
    auto             rShaderLU2 = make_shared<Shader>(rBRDFLU2, reflectionCoeff, 1.0, scene);

    rSphereLU2->shader(rShaderLU2);

    scene->add(rSphereLU2);
    scene->add(rBRDFLU2, string("brdf left up 2"));
    scene->add(rShaderLU2, string("shader left up 2"));

    // BG2, right up
    center.x(85.0);
    center.y(85.0);
    shared_ptr<Renderable> rSphereRU2 = make_shared<Sphere>(center, size);

    shared_ptr<BRDF> rBRDFRU2   = make_shared<Phong>(Color(255, 255, 0) * 5.0, Color(1.0), 3);
    auto             rShaderRU2 = make_shared<Shader>(rBRDFRU2, reflectionCoeff, 1.0, scene);

    rSphereRU2->shader(rShaderRU2);

    scene->add(rSphereRU2);
    scene->add(rBRDFRU2, string("brdf right up 2"));
    scene->add(rShaderRU2, string("shader right up 2"));


    //    // SPHERE WITH TEXTURE
    //    Point centerSphere2(12.0,0.0,0.0);
    //	shared_ptr<Renderable> rSphere2 = make_shared<Sphere>(centerSphere2,5.);
    //
    //    // Create a BRDF model for the sphere
    //    Color diffusionSphere2(1.0);
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
    //	shared_ptr<BRDF> rBRDFSphere2 = make_shared<Phong>(diffusionSphere2,lSpecularSphere2,3);
    //    rBRDFSphere2->cubeMap(rCubeMapSphere);
    //
    //    // Create a shader for the second sphere
    //	auto rShaderSphere2 = make_shared<Shader>(rBRDFSphere2,lReflectionCoeff,1.0,scene);
    //    rSphere2->shader(rShaderSphere2);
    //
    //    scene->add(rSphere2);
    //    scene->add(rBRDFSphere2, string("brdf of sphere 2"));
    //    scene->add(rShaderSphere2, string("shader of sphere 2"));


    ////////////
    // LIGHTS //
    ////////////
    Point             lightPosition(0.0, 0.0, 20.0);
    Color             lightColor(6.0);
    shared_ptr<Light> rLight1 = make_shared<PunctualLight>(lightPosition, lightColor);
    scene->add(rLight1);


    ////////////
    // CAMERA //
    ////////////
    Point  centreCamera(0.0, 0.0, 15.0);
    Vector directionCamera(0.0, 0.0, -1.01);
    Vector cameraUp(0., 1., 0.);
    double FOV = 90. * 3.141592 / 180.;

    auto camera = make_unique<Camera>(centreCamera, directionCamera, cameraUp, FOV);
    camera->focalPoint(Point(4.0));
    camera->aperture(Camera::Aperture::F_SMALL, Camera::Precision::EXCELLENT);
    //    camera->aperture(Camera::Aperture::ALL_SHARP);

    scene->add(move(camera));

    // BACKGROUND
    auto rCubeMapBckGrd = make_shared<CubeMap>(Point(0.0), 260);  // 260

    rCubeMapBckGrd->addImage(CubeMap::Faces::BACK, "./resources/River_back.png");
    rCubeMapBckGrd->addImage(CubeMap::Faces::FRONT, "./resources/River_front.png");
    rCubeMapBckGrd->addImage(CubeMap::Faces::UP, "./resources/River_up.png");
    rCubeMapBckGrd->addImage(CubeMap::Faces::DOWN, "./resources/River_down.png");
    rCubeMapBckGrd->addImage(CubeMap::Faces::LEFT, "./resources/River_left.png");
    rCubeMapBckGrd->addImage(CubeMap::Faces::RIGHT, "./resources/River_right.png");

    rCubeMapBckGrd->interpolationMethod(Image::InterpolationMethod::LINEAR);

    scene->backgroundCubeMap(rCubeMapBckGrd);
}

void createScene07(shared_ptr<Scene> scene)
{
    // Create a sphere (1)
    Point                  centerSphere1(-30., 10.0, 20.0);
    shared_ptr<Renderable> rSphere1 = make_shared<Sphere>(centerSphere1, 13.);

    // Create a BRDF model for the sphere
    Color            diffusionSphere1(229.0 / 255.0, 51.0 / 255.0, 163.0 / 255.0);
    Color            specularSphere1(0.0);
    shared_ptr<BRDF> rBRDFSphere1 = make_shared<Phong>(diffusionSphere1, specularSphere1, 3);

    // Create a shader for the sphere
    auto rShaderSphere1 = make_shared<Shader>(rBRDFSphere1, 0.8, 1.0, scene, Shader::TURBULANCE);
    rSphere1->shader(rShaderSphere1);

    scene->add(rSphere1);
    scene->add(rBRDFSphere1, string("brdf of sphere 1"));
    scene->add(rShaderSphere1, string("shader of sphere 1"));

    // Create a sphere (2)
    Point                  centerSphere2(0.0, 10.0, 20.0);
    shared_ptr<Renderable> rSphere2 = make_shared<Sphere>(centerSphere2, 13.);

    // Create a BRDF model for the sphere
    Color            diffusionSphere2(220.0 / 255.0, 210.0 / 255.0, 120.0 / 255.0);
    Color            specularSphere2(0.0);
    shared_ptr<BRDF> rBRDFSphere2 = make_shared<Phong>(diffusionSphere2, specularSphere2, 3);

    // Create a shader for the sphere
    auto rShaderSphere2 = make_shared<Shader>(rBRDFSphere2, 0.8, 1.0, scene, Shader::MARBLE);
    rSphere2->shader(rShaderSphere2);

    scene->add(rSphere2);
    scene->add(rBRDFSphere2, string("brdf of sphere 2"));
    scene->add(rShaderSphere2, string("shader of sphere 2"));

    // Create a sphere (3)
    Point                  centerSphere3(30., 10.0, 20.0);
    shared_ptr<Renderable> rSphere3 = make_shared<Sphere>(centerSphere3, 13.);

    // Create a BRDF model for the sphere
    Color            diffusionSphere3(90.0 / 255.0, 160.0 / 255.0, 210.0 / 255.0);
    Color            specularSphere3(0.0);
    shared_ptr<BRDF> rBRDFSphere3 = make_shared<Phong>(diffusionSphere3, specularSphere3, 3);

    // Create a shader for the sphere
    auto rShaderSphere3 = make_shared<Shader>(rBRDFSphere3, 0.8, 1.0, scene, Shader::BUMP);
    rSphere3->shader(rShaderSphere3);

    scene->add(rSphere3);
    scene->add(rBRDFSphere3, string("brdf of sphere 3"));
    scene->add(rShaderSphere3, string("shader of sphere 3"));

    ////////////
    // LIGHTS //
    ////////////
    Point             lightPosition(0.0, 90.0, 0.0);
    Color             lightColor(5.0);
    shared_ptr<Light> rLight1 = make_shared<PunctualLight>(lightPosition, lightColor);
    scene->add(rLight1);

    //    lightPosition.setPoint(0.0,15.0,37.0);
    //	shared_ptr<Light> rLight2 = make_shared<PunctualLight>(lightPosition,lLightColor);
    //    scene->add(rLight2);

    lightPosition.set(10.0, 20.0, 37.0);
    shared_ptr<Light> rLight3 = make_shared<PunctualLight>(lightPosition, lightColor);
    scene->add(rLight3);

    lightPosition.set(-10.0, 20.0, 37.0);
    shared_ptr<Light> rLight4 = make_shared<PunctualLight>(lightPosition, lightColor);
    scene->add(rLight4);


    ////////////
    // CAMERA //
    ////////////
    Point  centreCamera(0.0, 25.0, 105.0);
    Vector directionCamera(0.0, -0.3, -1.0);
    Vector cameraUp(0., 1., 0.);
    double FOV = 80. * 3.141592 / 180.;

    auto camera = make_unique<Camera>(centreCamera, directionCamera, cameraUp, FOV);
    camera->aperture(Camera::Aperture::ALL_SHARP);


    scene->add(move(camera));

    // ROOM
    RoomParameters roomParameters = { Color(1.0, 0.18, 0.17),
                                      Color(0.0),
                                      1.0,
                                      1.0,
                                      2,
                                      Point(50.0),
                                      Vector(20.0),
                                      string("./resources/textureLeaves_750x750.png"),
                                      string("./resources/textureWall_400x400.png"),
                                      string("./resources/textureWall_400x400_Right.png"),
                                      string("./resources/textureWall_400x400.png"),
                                      string("no_texture") };

    createRoom(scene, roomParameters);

    ////////////////
    // BACKGROUND //
    ////////////////
    scene->setBackgroundColor(Color(0.2));
}

void createScene08(shared_ptr<Scene> scene)
{
    // Same reflection coefficient for the spheres behind
    const double reflectionCoeff = 0.8;
    const double refractionCoeff = 1.0;

    // Create a red sphere
    Point                  centerSphere1(00.0, 0.0, -5.0);
    shared_ptr<Renderable> rSphere1 = make_shared<Sphere>(centerSphere1, 2.);

    // Create a BRDF model for the sphere
    Color            diffusionSphere1(1.0, 0.6, 0.6);
    Color            specularSphere1(0.9, 0.4, 0.4);
    shared_ptr<BRDF> rBRDFSphere1 = make_shared<Phong>(diffusionSphere1, specularSphere1, 3);

    // Create a shader for the sphere
    auto rShaderSphere1 = make_shared<Shader>(rBRDFSphere1, reflectionCoeff, refractionCoeff, scene);
    rSphere1->shader(rShaderSphere1);

    scene->add(rSphere1);
    scene->add(rBRDFSphere1, string("brdf of sphere 1"));
    scene->add(rShaderSphere1, string("shader of sphere 1"));

    // Create a green sphere
    Point                  centerSphere2(10.0, 0.0, -100.0);
    shared_ptr<Renderable> rSphere2 = make_shared<Sphere>(centerSphere2, 30.);

    // Create a BRDF model for the sphere
    Color            diffusionSphere2(0.6, 1.0, 0.6);
    Color            specularSphere2(0.4, 1.0, 0.4);
    shared_ptr<BRDF> rBRDFSphere2 = make_shared<Phong>(diffusionSphere2, specularSphere2, 3);

    // Create a shader for the second sphere
    auto rShaderSphere2 = make_shared<Shader>(rBRDFSphere2, reflectionCoeff, refractionCoeff, scene);
    rSphere2->shader(rShaderSphere2);

    scene->add(rSphere2);
    scene->add(rBRDFSphere2, string("brdf of sphere 2"));
    scene->add(rShaderSphere2, string("shader of sphere 2"));

    ////////////
    // LIGHTS //
    ////////////
    Point             light1Position(0., 10., 0.0);
    Color             light1Color(3.0);
    shared_ptr<Light> rLight1 = make_shared<PunctualLight>(light1Position, light1Color);
    scene->add(rLight1);

    ////////////
    // CAMERA //
    ////////////
    Point  centreCamera(0.0, 0.0, 5.0);
    Vector directionCamera(0.0, -0.1, -1.0);
    Vector cameraUp(0., 1., 0.);
    double FOV = 80. * 3.141592 / 180.;

    auto camera = make_unique<Camera>(centreCamera, directionCamera, cameraUp, FOV);
    camera->aperture(Camera::Aperture::F_SMALL, Camera::Precision::SUPER_AWESOME, 1.0);
    camera->focalPoint(centerSphere1);
    scene->add(move(camera));


    ////////////////
    // BACKGROUND //
    ////////////////
    scene->setBackgroundColor(Color(188, 236, 253));
}

void createScene09(shared_ptr<Scene> scene)
{
    // Load the "torus"
    string path = "./resources/head_4.obj";
    scene->createFromFile(path);

    // Create a BRDF model for the sphere
    const auto       diffusionSphere = Color{ 0.76, 0.33, 0.12 };
    const auto       specularSphere  = Color{ 1.0 };
    shared_ptr<BRDF> rBRDFShpere     = make_shared<Phong>(diffusionSphere, specularSphere, 5);

    // Create a shader for the sphere
    auto rShaderSphere = make_shared<Shader>(rBRDFShpere, 0.8, 1.0, scene);

    scene->add(rBRDFShpere, string("brdf of the sphere"));
    scene->add(rShaderSphere, string("shader of the sphere"));

    auto it = scene->renderableList().begin();

    (*it)->shader(rShaderSphere);
    it++;


    // Create a BRDF model for the torus
    const auto       diffusionTorus = Color{ 0.96, 0.40, 0.40 };
    const auto       specularTorus  = Color{ 0.9, 0.8, 0.8 };
    shared_ptr<BRDF> rBRDFTorus     = make_shared<Phong>(diffusionTorus, specularTorus, 5);

    // Create a shader for the torus
    auto rShaderTorus = make_shared<Shader>(rBRDFTorus, 0.8, 1.0, scene, Shader::Material::MARBLE);

    scene->add(rBRDFTorus, string("brdf of the torus"));
    scene->add(rShaderTorus, string("shader of the torus"));

    (*it)->shader(rShaderTorus);
    it++;

    (*it)->shader(rShaderTorus);
    it++;


    // Create a BRDF model for the pipe
    const auto       diffusionPipe = Color{ 0.16, 0.89, 0.0 };
    const auto       specularPipe  = Color{ 0.4, 0.8, 0.4 };
    shared_ptr<BRDF> rBRDFPipe     = make_shared<Phong>(diffusionPipe, specularPipe, 5);

    // Create a shader for the torus
    auto rShaderPipe = make_shared<Shader>(rBRDFPipe, 0.8, 1.0, scene);

    scene->add(rBRDFPipe, string("brdf of the pipe"));
    scene->add(rShaderPipe, string("shader of the pipe"));

    (*it)->shader(rShaderPipe);
    it++;


    // Create a BRDF model for the cone
    const auto       diffusionCone = Color{ 0.06, 0.10, 0.90 };
    const auto       specularCone  = Color{ 0.3, 0.2, 0.8 };
    shared_ptr<BRDF> rBRDFCone     = make_shared<Phong>(diffusionCone, specularCone, 5);

    // Create a shader for the torus
    auto rShaderCone = make_shared<Shader>(rBRDFCone, 0.8, 1.0, scene, Shader::TURBULANCE);

    scene->add(rBRDFCone, string("brdf of the cone"));
    scene->add(rShaderCone, string("shader of the cone"));

    (*it)->shader(rShaderCone);


    ////////////
    // LIGHTS //
    ////////////
    const auto        light1Position = Point{ 0., 1.0, 10.0 };
    const auto        light1Color    = Color{ 10.0 };
    shared_ptr<Light> rLight1        = make_shared<PunctualLight>(light1Position, light1Color);
    scene->add(rLight1);

    const auto        light4Position = Point{ 0., 10., 6.0 };
    const auto        light4Color    = Color{ 10.0 };
    shared_ptr<Light> rLight4        = make_shared<PunctualLight>(light4Position, light4Color);
    scene->add(rLight4);


    ////////////
    // CAMERA //
    ////////////
    const auto centreCamera    = Point{ 0.0, 2.4, 10.0 };
    const auto directionCamera = Vector{ 0.01, -0.1, -1.0 };
    const auto cameraUp        = Vector{ 0.0, 1.0, 0.0 };
    double     FOV             = 60.0 * 3.141592 / 180.0;

    auto camera = make_unique<Camera>(centreCamera, directionCamera, cameraUp, FOV);
    camera->aperture(Camera::Aperture::ALL_SHARP);

    scene->add(move(camera));


    ////////////////
    // BACKGROUND //
    ////////////////
    scene->setBackgroundColor(Color(0.2, 0.32, 0.8));
}

void createScene10(shared_ptr<Scene> scene)
{
    // Same reflection coefficient for the spheres behind
    const double reflectionCoeff = 5.0;
    const double refractionCoeff = 1.0;

    ////////////////////////////////
    // Create a first blue sphere //
    ////////////////////////////////
    Point                  centerSphere1(0.0, 0.0, 0.0);
    shared_ptr<Renderable> rSphere1 = make_shared<Sphere>(centerSphere1, 100.);

    // Create a BRDF model for the sphere
    Color            diffusionSphere1(0., 0.0, 0.1);
    Color            specularSphere1(1.0);
    shared_ptr<BRDF> rBRDFSphere1 = make_shared<Phong>(diffusionSphere1, specularSphere1, 8);

    // Create a shader for the sphere
    auto rShaderSphere1 = make_shared<Shader>(rBRDFSphere1, reflectionCoeff, refractionCoeff, scene);
    rShaderSphere1->setReflectionCountMax(2);
    rSphere1->shader(rShaderSphere1);

    scene->add(rSphere1);
    scene->add(rBRDFSphere1, string("brdf of sphere 1"));
    scene->add(rShaderSphere1, string("shader of sphere 1"));


    /////////////////////////////////
    // Create a second blue sphere //
    /////////////////////////////////
    Point                  centerSphere2(50.0, -20.0, 230.0);
    shared_ptr<Renderable> rSphere2 = make_shared<Sphere>(centerSphere2, 60.);

    // Create a BRDF model for the sphere
    Color            diffusionSphere2(0.0, 0.0, 0.1);
    Color            specularSphere2(0, 250, 154);
    shared_ptr<BRDF> rBRDFSphere2 = make_shared<Phong>(diffusionSphere2, specularSphere2, 15);

    // Create a shader for the second sphere
    auto rShaderSphere2 = make_shared<Shader>(rBRDFSphere2, reflectionCoeff, refractionCoeff, scene);
    rShaderSphere2->setReflectionCountMax(2);
    rSphere2->shader(rShaderSphere2);

    scene->add(rSphere2);
    scene->add(rBRDFSphere2, string("brdf of sphere 2"));
    scene->add(rShaderSphere2, string("shader of sphere 2"));


    ////////////
    // LIGHTS //
    ////////////
    Point light1Position(-40., 150., 50.0);
    Color light1Color(212.0, 27.0, 218.0);
    light1Color *= 2.0;

    shared_ptr<Light> rLight1 = make_shared<PunctualLight>(light1Position, light1Color);
    scene->add(rLight1);


    Point light2Position(90., 150., 190.0);
    Color light2Color(189.0, 190.0, 53.0);

    light2Color *= 2.0;

    shared_ptr<Light> rLight2 = make_shared<PunctualLight>(light2Position, light2Color);
    scene->add(rLight2);

    Point light3Position(-190., 150., 90.0);
    Color light3Color(255, 140, 0);

    light3Color *= 200.0;

    shared_ptr<Light> rLight3 = make_shared<PunctualLight>(light3Position, light3Color);
    scene->add(rLight3);


    ////////////
    // CAMERA //
    ////////////
    Point  centreCamera(-280.0, 150.0, 350.0);
    Vector directionCamera(0.5, -0.35, -0.5);
    Vector cameraUp(0., 1., 0.);
    double FOV = 80. * 3.141592 / 180.;

    auto camera = make_unique<Camera>(centreCamera, directionCamera, cameraUp, FOV);
    camera->aperture(Camera::Aperture::ALL_SHARP, Camera::Precision::LOW, 10.0);

    scene->add(move(camera));


    ///////////
    // FLOOR //
    ///////////
    FloorParameters floorParameters = { Color(1.0), Color(0.3), 1.0, 1.0, 2, 2000.0, 100.0, string("./resources/rect5130.png") };
    createFloor(scene, floorParameters);


    ////////////////
    // BACKGROUND //
    ////////////////
    scene->setBackgroundColor(Color(0.0));
}

void createScene11(shared_ptr<Scene> scene)
{
    const double reflectionCoeff = 2.0;
    const double refractionCoeff = 1.0;

    //////////////////////////
    // Create a yellow sphere //
    //////////////////////////
    const auto             centerSphere1 = Point{ -1.1, 0.0, 0.0 };
    shared_ptr<Renderable> rSphere1      = make_shared<Sphere>(centerSphere1, 1.0);

    // Create a BRDF model for the sphere
    const auto       diffusionSphere1 = Color{ 255, 255, 0 };
    const auto       specularSphere1  = Color{ 230, 230, 250 };
    shared_ptr<BRDF> rBRDFSphere1     = make_shared<Phong>(diffusionSphere1, specularSphere1, 15);

    // Create a shader for the sphere
    auto rShaderSphere1 = make_shared<Shader>(rBRDFSphere1, reflectionCoeff, refractionCoeff, scene, Shader::TURBULANCE);

    // Set the max number of reflections to 4
    rShaderSphere1->setReflectionCountMax(4);
    rSphere1->shader(rShaderSphere1);

    scene->add(rSphere1);
    scene->add(rBRDFSphere1, string("brdf of sphere 1"));
    scene->add(rShaderSphere1, string("shader of sphere 1"));


    ///////////////////////////
    // Create a cyan sphere //
    ///////////////////////////
    const auto             centerSphere2 = Point{ 1.1, 0.0, 0.0 };
    shared_ptr<Renderable> rSphere2      = make_shared<Sphere>(centerSphere2, 1.0);

    // Create a BRDF model for the sphere
    const auto       diffusionSphere2 = Color{ 0, 255, 255 };
    const auto       specularSphere2  = Color{ 255, 160, 122 };
    shared_ptr<BRDF> rBRDFSphere2     = make_shared<Phong>(diffusionSphere2, specularSphere2, 15);

    // Create a shader for the second sphere
    auto rShaderSphere2 = make_shared<Shader>(rBRDFSphere2, reflectionCoeff, refractionCoeff, scene, Shader::TURBULANCE);

    // Set the max number of reflections to 3
    rShaderSphere2->setReflectionCountMax(3);
    rSphere2->shader(rShaderSphere2);

    scene->add(rSphere2);
    scene->add(rBRDFSphere2, string("brdf of sphere 2"));
    scene->add(rShaderSphere2, string("shader of sphere 2"));


    //////////////////////////
    // Create a pink sphere //
    //////////////////////////
    const auto             centerSphere3 = Point{ 0.0, 1.8, 0.0 };
    shared_ptr<Renderable> rSphere3      = make_shared<Sphere>(centerSphere3, 1.0);

    // Create a BRDF model for the sphere
    const auto       diffusionSphere3 = Color{ 255, 0, 255 };
    const auto       specularSphere3  = Color{ 127, 255, 212 };
    shared_ptr<BRDF> rBRDFSphere3     = make_shared<Phong>(diffusionSphere3, specularSphere3, 15);

    // Create a shader for the second sphere
    auto rShaderSphere3 = make_shared<Shader>(rBRDFSphere3, reflectionCoeff, refractionCoeff, scene, Shader::TURBULANCE);

    // Set the max number of reflections to 5
    rShaderSphere3->setReflectionCountMax(5);
    rSphere3->shader(rShaderSphere3);

    scene->add(rSphere3);
    scene->add(rBRDFSphere3, string("brdf of sphere 3"));
    scene->add(rShaderSphere3, string("shader of sphere 3"));


    ////////////
    // LIGHTS //
    ////////////
    const auto        light1Position = Point{ 0., 1.0, 10.0 };
    const auto        light1Color    = Color{ 8.0 };
    shared_ptr<Light> rLight1        = make_shared<PunctualLight>(light1Position, light1Color);
    scene->add(rLight1);

    const auto        light2Position = Point{ 0., 1.0, -10.0 };
    const auto        light2Color    = Color{ 5.0 };
    shared_ptr<Light> rLight2        = make_shared<PunctualLight>(light2Position, light2Color);
    scene->add(rLight2);


    ////////////
    // CAMERA //
    ////////////
    const auto centreCamera    = Point{ 0.0, 0.7, 2.0 };
    const auto directionCamera = Vector{ 0.0, 0.0, -1.0 };
    const auto cameraUp        = Vector{ 0.0, 1.0, 0.0 };
    double     FOV             = 60. * 3.141592 / 180.;

    auto camera = make_unique<Camera>(centreCamera, directionCamera, cameraUp, FOV);
    scene->add(move(camera));


    ////////////////
    // BACKGROUND //
    ////////////////
    scene->setBackgroundColor(Color(0.0));
}

void createScene12(shared_ptr<Scene> scene)
{
    // Same reflection coefficient for the spheres behind
    const double reflectionCoeff = 2.0;
    const double refractionCoeff = 1.0;

    // Create a sphere
    const auto             centerSphere1 = Point{ 0.0, 5.0, 5.0 };
    shared_ptr<Renderable> rSphere1      = make_shared<Sphere>(centerSphere1, 9.);

    // Create a BRDF model for the sphere
    const auto       diffusionSphere1 = Color{ 1.0, 0.8, 0.9 };
    const auto       specularSphere1  = Color{ 1.0 };
    shared_ptr<BRDF> rBRDFSphere1     = make_shared<Phong>(diffusionSphere1, specularSphere1, 3);

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
    auto rShaderSphere1 = make_shared<Shader>(rBRDFSphere1, reflectionCoeff, refractionCoeff, scene);
    rShaderSphere1->setReflectionCountMax(4);
    rSphere1->shader(rShaderSphere1);

    scene->add(rSphere1);
    scene->add(rBRDFSphere1, string("brdf of sphere 1"));
    scene->add(rShaderSphere1, string("shader of sphere 1"));

    // Create a second sphere
    const auto             centerSphere2 = Point{ -21.0, -5.0, 8.0 };
    shared_ptr<Renderable> rSphere2      = make_shared<Sphere>(centerSphere2, 9.);

    // Create a BRDF model for the sphere
    const auto       diffusionSphere2 = Color{ 0.9, 1.0, 0.8 };
    const auto       specularSphere2  = Color{ 1.0 };
    shared_ptr<BRDF> rBRDFSphere2     = make_shared<Phong>(diffusionSphere2, specularSphere2, 3);

    // Create a shader for the second sphere
    auto rShaderSphere2 = make_shared<Shader>(rBRDFSphere2, reflectionCoeff, refractionCoeff, scene);
    rShaderSphere2->setReflectionCountMax(4);
    rSphere2->shader(rShaderSphere2);

    scene->add(rSphere2);
    scene->add(rBRDFSphere2, string("brdf of sphere 2"));
    scene->add(rShaderSphere2, string("shader of sphere 2"));

    // Create a transparent sphere for refraction
    const auto             centerSphere3 = Point{ 21.0, -5.0, 8.0 };
    shared_ptr<Renderable> rSphere3      = make_shared<Sphere>(centerSphere3, 9.0);

    // Create a BRDF model for the sphere
    const auto       diffusionSphere3 = Color{ 0.95, 0.88, 0.60 };
    const auto       specularSphere3  = Color{ 1.0 };
    shared_ptr<BRDF> rBRDFSphere3     = make_shared<Phong>(diffusionSphere3, specularSphere3, 3);

    // Create a shader for the third sphere
    auto rShaderSphere3 = make_shared<Shader>(rBRDFSphere3, 0.6, 1.0, scene);
    rShaderSphere3->setReflectionCountMax(4);
    rSphere3->shader(rShaderSphere3);

    scene->add(rSphere3);
    scene->add(rBRDFSphere3, string("brdf of sphere 3"));
    scene->add(rShaderSphere3, string("shader of sphere 3"));

    ////////////
    // LIGHTS //
    ////////////
    const auto        light1Position = Point{ 0., 25.0, 50.0 };
    const auto        light1Color    = Color{ 30.0 };
    shared_ptr<Light> rLight1        = make_shared<PunctualLight>(light1Position, light1Color);
    scene->add(rLight1);

    ////////////
    // CAMERA //
    ////////////
    const auto centreCamera    = Point{ 0.0, 15.0, 80.0 };
    const auto directionCamera = Vector{ 0.0, -0.2, -1.0 };
    const auto cameraUp        = Vector{ 0.0, 1.0, 0.0 };
    double     FOV             = 60. * 3.141592 / 180.;

    auto camera = make_unique<Camera>(centreCamera, directionCamera, cameraUp, FOV);
    //    camera->aperture(Camera::Aperture::F_SMALL,45.0,Camera::LOW);
    camera->aperture(Camera::Aperture::ALL_SHARP);
    scene->add(move(camera));


    // ROOM
    RoomParameters parameters = { Color(0.8),
                                  Color(1.0),
                                  0.0,
                                  1.0,
                                  2,
                                  Point(35.0),
                                  Vector(15.0),
                                  string("no_texture"),
                                  string("no_texture"),
                                  string("no_texture"),
                                  string("no_texture"),
                                  string("no_texture") };
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

void createScene13(shared_ptr<Scene> scene)
{
    scene->createFromFile("./resources/tableAndStatue3_bis.obj");

    // Create BRDF model for the cones
    Color            diffusion(255, 105, 0);
    Color            specular(1.0);
    shared_ptr<BRDF> rBRDFCones = make_shared<Phong>(diffusion, specular, 3);

    // Create a shader for the cones
    auto rShaderCones = make_shared<Shader>(rBRDFCones, 0.8, 1.0, scene, Shader::NONE);

    scene->add(rBRDFCones, "BRDF cones ");
    scene->add(rShaderCones, "Shader cones ");

    auto it = scene->objectNamed("pCone1");
    if (it)
        it->shader(rShaderCones);

    it = scene->objectNamed("pCone2");
    if (it)
        it->shader(rShaderCones);

    it = scene->objectNamed("pCone3");
    if (it)
        it->shader(rShaderCones);

    it = scene->objectNamed("pCone4");
    if (it)
        it->shader(rShaderCones);

    // Create BRDF model for the torus
    shared_ptr<BRDF> rBRDFTorus = make_shared<Phong>(Color(255, 99, 71), Color(1.0), 3);

    // Create a shader for the torus
    auto rShaderTorus = make_shared<Shader>(rBRDFTorus, 1.8, 1.0, scene, Shader::NONE);

    scene->add(rBRDFTorus, "BRDF torus ");
    scene->add(rShaderTorus, "Shader torus ");

    it = scene->objectNamed("pTorus1");
    if (it)
        it->shader(rShaderTorus);

    it = scene->objectNamed("pTorus2");
    if (it)
        it->shader(rShaderTorus);

    // Create a BRDF model for the table
    shared_ptr<BRDF> rBRDFPyramid = make_shared<Phong>(Color(128, 128, 0), Color(1.0), 10);

    // Create a shader for the table
    auto rShaderPyramid = make_shared<Shader>(rBRDFPyramid, 1.0, 1.0, scene, Shader::Material::TURBULANCE);

    scene->add(rBRDFPyramid, "BRDF pyramid ");
    scene->add(rShaderPyramid, "Shader pyramid ");

    // Set shaders for the table
    it = scene->objectNamed("pPyramid1");
    if (it)
        it->shader(rShaderPyramid);

    it = scene->objectNamed("pPyramid2");
    if (it)
        it->shader(rShaderPyramid);


    // Create a BRDF model for the table
    shared_ptr<BRDF> rBRDFTable = make_shared<Phong>(Color(1.0), Color(1.0), 10);

    // Create a shader for the table
    auto rShaderTable = make_shared<Shader>(rBRDFTable, 1.0, 1.0, scene, Shader::Material::MARBLE);

    scene->add(rBRDFTable, "BRDF table ");
    scene->add(rShaderTable, "Shader table ");

    // Set shaders for the table
    it = scene->objectNamed("pCylinder1");
    if (it)
        it->shader(rShaderTable);

    it = scene->objectNamed("pCylinder2");
    if (it)
        it->shader(rShaderTable);

    it = scene->objectNamed("pCylinder3");
    if (it)
        it->shader(rShaderTable);

    it = scene->objectNamed("pCylinder4");
    if (it)
        it->shader(rShaderTable);

    it = scene->objectNamed("pCube1");
    if (it)
        it->shader(rShaderTable);


    // Sphere with texture
    Point                  centerSphere(0.0, 6.7, 0.0);
    shared_ptr<Renderable> rSphere1 = make_shared<Sphere>(centerSphere, 2.0);

    // Create a BRDF model for the sphere
    Color            diffusionSphere1(1.0);
    Color            specularSphere1(1.0);
    shared_ptr<BRDF> rBRDFSphere1 = make_shared<Phong>(diffusionSphere1, specularSphere1, 8);


    auto rCubeMapDesert = make_shared<CubeMap>(Point(0.0), 260);  // 260

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
    auto rShaderSphere1 = make_shared<Shader>(rBRDFSphere1, 1.0, 1.0, scene);
    rShaderSphere1->setReflectionCountMax(1);
    rSphere1->shader(rShaderSphere1);

    scene->add(rSphere1);
    scene->add(rBRDFSphere1, string("brdf of sphere 1"));
    scene->add(rShaderSphere1, string("shader of sphere 1"));

    // Mirror on the right wall
    double                 mirrorXPos = 10.0;
    shared_ptr<Renderable> rMirror1
    = make_shared<Triangle>(Point(mirrorXPos, 4.0, -10.0), Point(mirrorXPos, 12.0, -10.0), Point(mirrorXPos, 12.0, 18.0));
    shared_ptr<Renderable> rMirror2
    = make_shared<Triangle>(Point(mirrorXPos, 4.0, -10.0), Point(mirrorXPos, 12.0, 18.0), Point(mirrorXPos, 4.0, 18.0));

    const auto minusX = Vector(-1.0, 0.0, 0.0);

    static_pointer_cast<Triangle>(rMirror1)->vertexNormals()[0] = minusX;
    static_pointer_cast<Triangle>(rMirror1)->vertexNormals()[1] = minusX;
    static_pointer_cast<Triangle>(rMirror1)->vertexNormals()[2] = minusX;

    static_pointer_cast<Triangle>(rMirror2)->vertexNormals()[0] = minusX;
    static_pointer_cast<Triangle>(rMirror2)->vertexNormals()[1] = minusX;
    static_pointer_cast<Triangle>(rMirror2)->vertexNormals()[2] = minusX;

    // Create a BRDF model for the mirror
    shared_ptr<BRDF> rBRDFMirror = make_shared<Phong>(Color(0.4, 0.4, 0.6), Color(1.0), 8);

    // Create a shader for the mirror
    auto rShaderMirror = make_shared<Shader>(rBRDFMirror, 20.0, 1.0, scene);
    rShaderMirror->setReflectionCountMax(2);

    rMirror1->shader(rShaderMirror);
    rMirror2->shader(rShaderMirror);

    scene->add(rMirror1);
    scene->add(rMirror2);
    scene->add(rBRDFMirror, string("brdf of mirror"));
    scene->add(rShaderMirror, string("shader of mirror"));


    ////////////
    // LIGHTS //
    ////////////
    Point             light1Position(-3.0, 10.0, 20.0);
    Color             lightColor(20.0);
    shared_ptr<Light> rLight1 = make_shared<PunctualLight>(light1Position, lightColor);
    scene->add(rLight1);


    ////////////
    // CAMERA //
    ////////////
    Point  centreCamera(-5.0, 8.0, 21.0);
    Vector directionCamera(0.4, -0.20, -1.0);
    Vector cameraUp(0.0, 1.0, 0.0);
    double FOV = 80. * 3.141592 / 180.;

    auto camera = make_unique<Camera>(centreCamera, directionCamera, cameraUp, FOV);
    camera->focalPoint(centerSphere + directionCamera.normalize() * static_pointer_cast<Sphere>(rSphere1)->radius() * (-1.0));
    camera->aperture(Camera::Aperture::F_SMALL, Camera::Precision::SUPER_AWESOME);
    scene->add(move(camera));

    RoomParameters parameters = { Color(0.8),
                                  Color(0.8),
                                  0.0,
                                  1.0,
                                  1,
                                  Point(-28.0, 0.0, -20.0),
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
    scene->setBackgroundColor(Color(0.0));
}

void createScene14(shared_ptr<Scene> scene)
{
    scene->createFromFile("./resources/tableAndStatueAndPyramid3.obj");

    // Create BRDF model for the cones
    Color            diffusion(255, 105, 0);
    Color            specular(1.0);
    shared_ptr<BRDF> rBRDFCones = make_shared<Phong>(diffusion, specular, 3);

    // Create a shader for the cones
    auto rShaderCones = make_shared<Shader>(rBRDFCones, 0.8, 1.0, scene, Shader::NONE);

    scene->add(rBRDFCones, "BRDF cones ");
    scene->add(rShaderCones, "Shader cones ");

    auto it = scene->objectNamed("pCone1");
    if (it)
        it->shader(rShaderCones);

    it = scene->objectNamed("pCone2");
    if (it)
        it->shader(rShaderCones);

    it = scene->objectNamed("pCone3");
    if (it)
        it->shader(rShaderCones);

    it = scene->objectNamed("pCone4");
    if (it)
        it->shader(rShaderCones);

    // Create BRDF model for the torus
    shared_ptr<BRDF> rBRDFTorus = make_shared<Phong>(Color(255, 99, 71), Color(1.0), 3);

    // Create a shader for the torus
    auto rShaderTorus = make_shared<Shader>(rBRDFTorus, 1.8, 1.0, scene, Shader::NONE);

    scene->add(rBRDFTorus, "BRDF torus ");
    scene->add(rShaderTorus, "Shader torus ");

    it = scene->objectNamed("pTorus1");
    if (it)
        it->shader(rShaderTorus);

    it = scene->objectNamed("pTorus2");
    if (it)
        it->shader(rShaderTorus);

    // Create a BRDF model for the table
    shared_ptr<BRDF> rBRDFPyramid = make_shared<Phong>(Color(128, 128, 0), Color(1.0), 10);

    // Create a shader for the table
    auto rShaderPyramid = make_shared<Shader>(rBRDFPyramid, 1.0, 1.0, scene, Shader::Material::TURBULANCE);

    scene->add(rBRDFPyramid, "BRDF pyramid ");
    scene->add(rShaderPyramid, "Shader pyramid ");

    // Set shaders for the table
    it = scene->objectNamed("pPyramid1");
    if (it)
        it->shader(rShaderPyramid);

    it = scene->objectNamed("pPyramid2");
    if (it)
        it->shader(rShaderPyramid);


    shared_ptr<BRDF> rBRDFBackPyramid = make_shared<Phong>(Color(0, 255, 255), Color(1.0), 10);

    // Create a shader for the table
    auto rShaderBackPyramid = make_shared<Shader>(rBRDFBackPyramid, 1.0, 1.0, scene, Shader::Material::BUMP);

    scene->add(rBRDFBackPyramid, "BRDF pyramid in the background ");
    scene->add(rShaderBackPyramid, "Shader pyramid in the background ");

    it = scene->objectNamed("pPyramid3");
    if (it)
        it->shader(rShaderBackPyramid);


    // Create a BRDF model for the table
    shared_ptr<BRDF> rBRDFTable = make_shared<Phong>(Color(1.0), Color(1.0), 10);

    // Create a shader for the table
    auto rShaderTable = make_shared<Shader>(rBRDFTable, 1.0, 1.0, scene, Shader::Material::MARBLE);

    scene->add(rBRDFTable, "BRDF table ");
    scene->add(rShaderTable, "Shader table ");

    // Set shaders for the table
    it = scene->objectNamed("pCylinder1");
    if (it)
        it->shader(rShaderTable);

    it = scene->objectNamed("pCylinder2");
    if (it)
        it->shader(rShaderTable);

    it = scene->objectNamed("pCylinder3");
    if (it)
        it->shader(rShaderTable);

    it = scene->objectNamed("pCylinder4");
    if (it)
        it->shader(rShaderTable);

    it = scene->objectNamed("pCube1");
    if (it)
        it->shader(rShaderTable);


    // Sphere with texture
    Point                  centerSphere(.0, 6.7, 0.0);
    shared_ptr<Renderable> rSphere1 = make_shared<Sphere>(centerSphere, 2.0);

    // Create a BRDF model for the sphere
    Color            diffusionSphere1(0.1);
    Color            specularSphere1(0.1);
    shared_ptr<BRDF> rBRDFSphere1 = make_shared<Phong>(diffusionSphere1, specularSphere1, 8);

    // Create a shader for the sphere
    auto rShaderSphere1 = make_shared<Shader>(rBRDFSphere1, 1.0, 2.4, scene);
    rShaderSphere1->setReflectionCountMax(1);
    rSphere1->shader(rShaderSphere1);

    scene->add(rSphere1);
    scene->add(rBRDFSphere1, string("brdf of sphere 1"));
    scene->add(rShaderSphere1, string("shader of sphere 1"));


    ////////////
    // LIGHTS //
    ////////////
    Point             light1Position(0.0, 20.0, 10.0);
    Color             lightColor(20.0);
    shared_ptr<Light> rLight1 = make_shared<PunctualLight>(light1Position, lightColor);
    scene->add(rLight1);


    Point             light2Position(-5.0, 10.0, 10.0);
    shared_ptr<Light> rLight2 = make_shared<PunctualLight>(light2Position, lightColor);
    scene->add(rLight2);

    Point             light3Position(5.0, 10.0, 10.0);
    shared_ptr<Light> rLight3 = make_shared<PunctualLight>(light3Position, lightColor);
    scene->add(rLight3);


    ////////////
    // CAMERA //
    ////////////
    Point  centreCamera(-2.0, 8.0, 14.0);
    Vector directionCamera(0.05, -0.05, -1.0);
    Vector cameraUp(0.0, 1.0, 0.0);
    double FOV = 80. * 3.141592 / 180.;

    auto camera = make_unique<Camera>(centreCamera, directionCamera, cameraUp, FOV);
    camera->focalPoint(centerSphere + directionCamera.normalize() * static_pointer_cast<Sphere>(rSphere1)->radius() * (-1.0));
    camera->aperture(Camera::Aperture::F_MEDIUM, Camera::Precision::SUPER_AWESOME);
    scene->add(move(camera));


    auto rCubeMapBckGrd = make_shared<CubeMap>(Point(0.0), 260);  // 260

    rCubeMapBckGrd->addImage(CubeMap::Faces::BACK, "./resources/Desert_back.png");
    rCubeMapBckGrd->addImage(CubeMap::Faces::FRONT, "./resources/Desert_front.png");
    rCubeMapBckGrd->addImage(CubeMap::Faces::UP, "./resources/Desert_up.png");
    rCubeMapBckGrd->addImage(CubeMap::Faces::DOWN, "./resources/Desert_down.png");
    rCubeMapBckGrd->addImage(CubeMap::Faces::LEFT, "./resources/Desert_left.png");
    rCubeMapBckGrd->addImage(CubeMap::Faces::RIGHT, "./resources/Desert_right.png");

    rCubeMapBckGrd->interpolationMethod(Image::InterpolationMethod::LINEAR);

    scene->backgroundCubeMap(rCubeMapBckGrd);
}

void createFloor(shared_ptr<Scene> scene, const FloorParameters& param)
{
    double deep = -1.0 * param.deep;

    shared_ptr<Renderable> rTriangleZ1
    = make_shared<Triangle>(Point(-param.size, deep, -param.size), Point(-param.size, deep, param.size), Point(param.size, deep, param.size));
    shared_ptr<Renderable> rTriangleZ2
    = make_shared<Triangle>(Point(-param.size, deep, -param.size), Point(param.size, deep, param.size), Point(param.size, deep, -param.size));

    const auto up = Vector(0.0, 1.0, 0.0);

    static_pointer_cast<Triangle>(rTriangleZ1)->vertexNormals()[0] = up;
    static_pointer_cast<Triangle>(rTriangleZ1)->vertexNormals()[1] = up;
    static_pointer_cast<Triangle>(rTriangleZ1)->vertexNormals()[2] = up;

    static_pointer_cast<Triangle>(rTriangleZ2)->vertexNormals()[0] = up;
    static_pointer_cast<Triangle>(rTriangleZ2)->vertexNormals()[1] = up;
    static_pointer_cast<Triangle>(rTriangleZ2)->vertexNormals()[2] = up;

    // Create BRDF model for the triangle
    shared_ptr<BRDF> bRDFTriangle = make_shared<Phong>(param.diffusion, param.specular, 3);
    bRDFTriangle->ambient(Color(0.0));

    if (param.floorTexturePath.compare("no_texture"))
    {
        auto rCubeMapFloor = make_shared<CubeMap>(Point(0.0, -4.0, 0.0), param.size * 2.0);

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
    auto shaderTriangle = make_shared<Shader>(bRDFTriangle, param.reflectionCoeff, param.refractionCoeff, scene);
    shaderTriangle->setReflectionCountMax(param.maxReflection);

    rTriangleZ1->shader(shaderTriangle);
    rTriangleZ2->shader(shaderTriangle);

    scene->add(rTriangleZ1);
    scene->add(rTriangleZ2);
    scene->add(bRDFTriangle, string("brdf of the triangles of the floor"));
    scene->add(shaderTriangle, string("shader of the triangles of the floor"));
}

void createRoom(shared_ptr<Scene> scene, const RoomParameters& param)
{
    Point zero(param.lowCorner);
    Point one(zero.x(), zero.y(), zero.z() + param.dimensions.z());
    Point two(zero.x() + param.dimensions.x(), zero.y(), zero.z() + param.dimensions.z());
    Point three(zero.x() + param.dimensions.x(), zero.y(), zero.z());
    Point four(zero.x(), zero.y() + param.dimensions.y(), zero.z());
    Point five(zero.x(), zero.y() + param.dimensions.y(), zero.z() + param.dimensions.z());
    Point six = param.lowCorner + param.dimensions;
    Point seven(zero.x() + param.dimensions.x(), zero.y() + param.dimensions.y(), zero.z());

    // Create floor
    shared_ptr<Renderable> rTriFloor1 = make_shared<Triangle>(zero, one, two);
    shared_ptr<Renderable> rTriFloor2 = make_shared<Triangle>(zero, two, three);

    const auto up = Vector(0.0, 1.0, 0.0);

    static_pointer_cast<Triangle>(rTriFloor1)->vertexNormals()[0] = up;
    static_pointer_cast<Triangle>(rTriFloor1)->vertexNormals()[1] = up;
    static_pointer_cast<Triangle>(rTriFloor1)->vertexNormals()[2] = up;

    static_pointer_cast<Triangle>(rTriFloor2)->vertexNormals()[0] = up;
    static_pointer_cast<Triangle>(rTriFloor2)->vertexNormals()[1] = up;
    static_pointer_cast<Triangle>(rTriFloor2)->vertexNormals()[2] = up;

    Point middleOfFace((zero.x() + one.x() + two.x() + three.x()) * 0.25,
                       (zero.y() + one.y() + two.y() + three.y()) * 0.25,
                       (zero.z() + one.z() + two.z() + three.z()) * 0.25);

    shared_ptr<BRDF> rBRDF_Floor = make_shared<Phong>(param.diffusion, param.specular, 3);

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

    auto rShaderFloor = make_shared<Shader>(rBRDF_Floor, param.reflectionCoeff, param.refractionCoeff, scene);
    rShaderFloor->setReflectionCountMax(param.maxReflection);

    rTriFloor1->shader(rShaderFloor);
    rTriFloor2->shader(rShaderFloor);

    scene->add(rTriFloor1);
    scene->add(rTriFloor2);
    scene->add(rBRDF_Floor, string("brdf of the triangles of the floor"));
    scene->add(rShaderFloor, string("shader of the triangles of the floor"));


    // Create left wall
    shared_ptr<Renderable> rTriLeftWall1 = make_shared<Triangle>(zero, four, five);
    shared_ptr<Renderable> rTriLeftWall2 = make_shared<Triangle>(zero, five, one);

    const auto right = Vector(1.0, 0.0, 0.0);

    static_pointer_cast<Triangle>(rTriLeftWall1)->vertexNormals()[0] = right;
    static_pointer_cast<Triangle>(rTriLeftWall1)->vertexNormals()[1] = right;
    static_pointer_cast<Triangle>(rTriLeftWall1)->vertexNormals()[2] = right;

    static_pointer_cast<Triangle>(rTriLeftWall2)->vertexNormals()[0] = right;
    static_pointer_cast<Triangle>(rTriLeftWall2)->vertexNormals()[1] = right;
    static_pointer_cast<Triangle>(rTriLeftWall2)->vertexNormals()[2] = right;

    middleOfFace.x((zero.x() + one.x() + four.x() + five.x()) * 0.25);
    middleOfFace.y((zero.y() + one.y() + four.y() + five.y()) * 0.25);
    middleOfFace.z((zero.z() + one.z() + four.z() + five.z()) * 0.25);

    shared_ptr<BRDF> rBRDFLeftWall = make_shared<Phong>(param.diffusion, param.specular, 3);
    rBRDFLeftWall->ambient(Color(0.1));

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

    auto rShaderLeftWall = make_shared<Shader>(rBRDFLeftWall, param.reflectionCoeff, param.refractionCoeff, scene);
    rShaderLeftWall->setReflectionCountMax(param.maxReflection);

    rTriLeftWall1->shader(rShaderLeftWall);
    rTriLeftWall2->shader(rShaderLeftWall);

    scene->add(rTriLeftWall1);
    scene->add(rTriLeftWall2);
    scene->add(rBRDFLeftWall, string("brdf of the triangles of the left wall"));
    scene->add(rShaderLeftWall, string("shader of the triangles of the left wall"));

    // Create back wall
    shared_ptr<Renderable> rTriBackWall1 = make_shared<Triangle>(zero, three, four);
    shared_ptr<Renderable> rTriBackWall2 = make_shared<Triangle>(four, three, seven);

    const auto forward = Vector(0.0, 0.0, 1.0);

    static_pointer_cast<Triangle>(rTriBackWall1)->vertexNormals()[0] = forward;
    static_pointer_cast<Triangle>(rTriBackWall1)->vertexNormals()[1] = forward;
    static_pointer_cast<Triangle>(rTriBackWall1)->vertexNormals()[2] = forward;

    static_pointer_cast<Triangle>(rTriBackWall2)->vertexNormals()[0] = forward;
    static_pointer_cast<Triangle>(rTriBackWall2)->vertexNormals()[1] = forward;
    static_pointer_cast<Triangle>(rTriBackWall2)->vertexNormals()[2] = forward;

    middleOfFace.x((zero.x() + three.x() + four.x() + seven.x()) * 0.25);
    middleOfFace.y((zero.y() + three.y() + four.y() + seven.y()) * 0.25);
    middleOfFace.z((zero.z() + three.z() + four.z() + seven.z()) * 0.25);

    shared_ptr<BRDF> rBRDFBackWall = make_shared<Phong>(param.diffusion, param.specular, 3);
    rBRDFBackWall->ambient(Color(0.1));

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

    auto rShaderBackWall = make_shared<Shader>(rBRDFBackWall, param.reflectionCoeff, param.refractionCoeff, scene);
    rShaderBackWall->setReflectionCountMax(param.maxReflection);

    rTriBackWall1->shader(rShaderBackWall);
    rTriBackWall2->shader(rShaderBackWall);

    scene->add(rTriBackWall1);
    scene->add(rTriBackWall2);
    scene->add(rBRDFBackWall, string("brdf of the triangles of the back wall"));
    scene->add(rShaderBackWall, string("shader of the triangles of the back wall"));

    // Create right wall
    shared_ptr<Renderable> rTriRightWall1 = make_shared<Triangle>(three, two, six);
    shared_ptr<Renderable> rTriRightWall2 = make_shared<Triangle>(three, six, seven);

    const auto left = Vector(-1.0, 0.0, 0.0);

    static_pointer_cast<Triangle>(rTriRightWall1)->vertexNormals()[0] = left;
    static_pointer_cast<Triangle>(rTriRightWall1)->vertexNormals()[1] = left;
    static_pointer_cast<Triangle>(rTriRightWall1)->vertexNormals()[2] = left;

    static_pointer_cast<Triangle>(rTriRightWall2)->vertexNormals()[0] = left;
    static_pointer_cast<Triangle>(rTriRightWall2)->vertexNormals()[1] = left;
    static_pointer_cast<Triangle>(rTriRightWall2)->vertexNormals()[2] = left;

    middleOfFace.x((two.x() + three.x() + six.x() + seven.x()) * 0.25);
    middleOfFace.y((two.y() + three.y() + six.y() + seven.y()) * 0.25);
    middleOfFace.z((two.z() + three.z() + six.z() + seven.z()) * 0.25);

    shared_ptr<BRDF> rBRDFRightWall = make_shared<Phong>(param.diffusion, param.specular, 3);
    rBRDFRightWall->ambient(Color(0.1));

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

    auto rShaderRightWall = make_shared<Shader>(rBRDFRightWall, param.reflectionCoeff, param.refractionCoeff, scene);
    rShaderRightWall->setReflectionCountMax(param.maxReflection);

    rTriRightWall1->shader(rShaderRightWall);
    rTriRightWall2->shader(rShaderRightWall);

    scene->add(rTriRightWall1);
    scene->add(rTriRightWall2);
    scene->add(rBRDFRightWall, string("brdf of the triangles of the right wall"));
    scene->add(rShaderRightWall, string("shader of the triangles of the right wall"));

    // Create roof
    shared_ptr<Renderable> rTriCeiling1 = make_shared<Triangle>(four, five, six);
    shared_ptr<Renderable> rTriCeiling2 = make_shared<Triangle>(four, six, seven);

    const auto down = Vector(0.0, -1.0, 0.0);

    static_pointer_cast<Triangle>(rTriCeiling1)->vertexNormals()[0] = down;
    static_pointer_cast<Triangle>(rTriCeiling1)->vertexNormals()[1] = down;
    static_pointer_cast<Triangle>(rTriCeiling1)->vertexNormals()[2] = down;

    static_pointer_cast<Triangle>(rTriCeiling2)->vertexNormals()[0] = down;
    static_pointer_cast<Triangle>(rTriCeiling2)->vertexNormals()[1] = down;
    static_pointer_cast<Triangle>(rTriCeiling2)->vertexNormals()[2] = down;

    middleOfFace.x((four.x() + five.x() + six.x() + seven.x()) * 0.25);
    middleOfFace.y((four.y() + five.y() + six.y() + seven.y()) * 0.25);
    middleOfFace.z((four.z() + five.z() + six.z() + seven.z()) * 0.25);

    shared_ptr<BRDF> rBRDFCeiling = make_shared<Phong>(param.diffusion, param.specular, 13);
    rBRDFCeiling->ambient(Color(0.1));

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


    auto rShaderCeiling = make_shared<Shader>(rBRDFCeiling, param.reflectionCoeff, param.refractionCoeff, scene);
    rShaderCeiling->setReflectionCountMax(param.maxReflection);

    rTriCeiling1->shader(rShaderCeiling);
    rTriCeiling2->shader(rShaderCeiling);

    scene->add(rTriCeiling1);
    scene->add(rTriCeiling2);
    scene->add(rBRDFCeiling, string("brdf of the triangles of the roof"));
    scene->add(rShaderCeiling, string("shader of the triangles of the roof"));
}
