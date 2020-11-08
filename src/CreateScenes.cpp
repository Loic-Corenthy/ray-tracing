//
//  CreateScenes.cpp
//  RayTracing
//
//  Created by Loïc CORENTHY on 12/15/12.
//
//

#include "CreateScenes.hpp"

#include <iostream>
#include <algorithm>

using namespace MatouMalin;
using namespace std;




void createTestScene(MatouMalin::Scene* pScene)
{

    MatouMalin::Point lCenterSphere1(0.0,0.0,0.0);
	Renderable* rSphere1 = new Sphere(lCenterSphere1,2.3);

	// Create a BRDF model for the sphere
    Color lDiffusionSphere1(1.0f,0.0f,0.0f);
	Color lSpecularSphere1(0.7f,0.3f,0.3f);
	BRDF* rBRDFSphere1 = new Phong(lDiffusionSphere1,lSpecularSphere1,5);

	// Create a shader for the sphere
	Shader* rShaderSphere1 = new Shader(rBRDFSphere1,1.0,1.0,pScene,Shader::NONE);
    rShaderSphere1->setReflectionCountMax(2);
	rSphere1->setShader(rShaderSphere1);

    pScene->add(rSphere1);
    pScene->add(rBRDFSphere1, string("brdf of sphere 1"));
    pScene->add(rShaderSphere1, string("shader of sphere 1"));


    ////////////
    // LIGHTS //
    ////////////
	Light* rLight1 = new DirectionalLight(Vector(0.0, 0.0, -1.0), Color(22.0));
    pScene->add(rLight1);


//    MatouMalin::Point lLight2Position(0.f,1.0f,0.0f);
//	Light* rLight2 = new PunctualLight(lLight2Position,lLight1Color);
//    pScene->add(rLight2);

    ////////////
    // CAMERA //
    ////////////
    MatouMalin::Point lCentreCamera(0.0f,7.0f,10.0f);
    Vector lDirectionCamera(0.00f,-0.4f,-1.0f);
	Vector lCameraUp(0.f,1.f,0.f);
	float FOV = 60.f*3.141592/180.f;

	Camera* rCamera = new Camera(lCentreCamera,lDirectionCamera,lCameraUp,FOV);
    pScene->add(rCamera);


    ////////////////
    // BACKGROUND //
    ////////////////
    pScene->setBackgroundColor(Color(0.3f));

}

void createScene01(Scene* pScene)
{
    // Same reflection coefficient for all the spheres
    double lReflectionCoeff(2.0);
    double lRefractionCoeff(1.0);

    ////////////////
    // RED SPHERE //
    ////////////////
    MatouMalin::Point lCenterSphere1(0.0,2.0,2.1);
	Renderable* rSphere1 = new Sphere(lCenterSphere1,0.3);

	// Create a BRDF model for the sphere
    Color lDiffusionSphere1(1.0f,0.0f,0.0f);
	Color lSpecularSphere1(0.7f,0.3f,0.3f);
	BRDF* rBRDFSphere1 = new Phong(lDiffusionSphere1,lSpecularSphere1,5);

	// Create a shader for the sphere
	Shader* rShaderSphere1 = new Shader(rBRDFSphere1,lReflectionCoeff,lRefractionCoeff,pScene,Shader::MARBLE);
    rShaderSphere1->setReflectionCountMax(2);
	rSphere1->setShader(rShaderSphere1);

    pScene->add(rSphere1);
    pScene->add(rBRDFSphere1, string("brdf of sphere 1"));
    pScene->add(rShaderSphere1, string("shader of sphere 1"));

    //////////////////
    // GREEN SPHERE //
    //////////////////
    MatouMalin::Point lCenterSphere2(2.0,0.5,0.0);
	Renderable* rSphere2 = new Sphere(lCenterSphere2,1.5);

    // Create a BRDF model for the sphere
    Color lDiffusionSphere2(0.0f,1.0f,0.0f);
	Color lSpecularSphere2(1.0f);
	BRDF* rBRDFSphere2 = new Phong(lDiffusionSphere2,lSpecularSphere2,15);

    // Create a shader for the second sphere
	Shader* rShaderSphere2 = new Shader(rBRDFSphere2,lReflectionCoeff,lRefractionCoeff,pScene,Shader::MARBLE);
    rShaderSphere2->setReflectionCountMax(2);
    rSphere2->setShader(rShaderSphere2);

    pScene->add(rSphere2);
    pScene->add(rBRDFSphere2, string("brdf of sphere 2"));
    pScene->add(rShaderSphere2, string("shader of sphere 2"));

    /////////////////
    // BLUE SPHERE //
    /////////////////
    MatouMalin::Point lCenterSphere3(-1.8,0.0,0.0);
	Renderable* rSphere3 = new Sphere(lCenterSphere3,1.0);

    // Create a BRDF model for the sphere
	Color lDiffusionSphere3(0.0f,0.0f,1.0f);
	Color lSpecularSphere3(0.8f,0.8f,1.0f);
    BRDF* rBRDFSphere3 = new Phong(lDiffusionSphere3,lSpecularSphere3,25);

    // Create a shader for the third sphere
	Shader* rShaderSphere3 = new Shader(rBRDFSphere3,lReflectionCoeff,lRefractionCoeff,pScene,Shader::MARBLE);
    rShaderSphere3->setReflectionCountMax(2);
    rSphere3->setShader(rShaderSphere3);

    pScene->add(rSphere3);
    pScene->add(rBRDFSphere3, string("brdf of sphere 3"));
    pScene->add(rShaderSphere3, string("shader of sphere 3"));

    ////////////
    // LIGHTS //
    ////////////
    MatouMalin::Point lLight1Position(0.f,0.0f,5.0f);
	Color lLight1Color(9.0f);
	Light* rLight1 = new PunctualLight(lLight1Position,lLight1Color);
    pScene->add(rLight1);

    ////////////
    // CAMERA //
    ////////////
    MatouMalin::Point lCentreCamera(0.0f,2.5f,6.0f);
    Vector lDirectionCamera(0.05f,-0.4f,-1.0f);
	Vector lCameraUp(0.f,1.f,0.f);
	float FOV = 60.f*3.141592/180.f;

	Camera* rCamera = new Camera(lCentreCamera,lDirectionCamera,lCameraUp,FOV);
    pScene->add(rCamera);

    ////////////////
    // BACKGROUND //
    ////////////////
    pScene->setBackgroundColor(Color(0));

}


void createScene02(Scene* pScene)
{
    // Same reflection coefficient for the spheres behind
    double lReflectionCoeff(5.8);
    double lRefractionCoeff(1.0);

    ////////////////
    // RED SPHERE //
    ////////////////
	MatouMalin::Point lCenterSphere1(-60.0,0.0,60.0);
	Sphere* rSphere1 = new Sphere(lCenterSphere1,40.f);

	// Create a BRDF model for the sphere
    Color lDiffusionSphere1(1.0f,0.6f,0.6f);
	Color lSpecularSphere1(0.9f,0.4f,0.4f);
	Phong* rBRDFSphere1 = new Phong(lDiffusionSphere1*2.0,lSpecularSphere1,3);

	// Create a shader for the sphere
	Shader* rShaderSphere1 = new Shader(rBRDFSphere1,lReflectionCoeff,lRefractionCoeff,pScene);
    rShaderSphere1->setReflectionCountMax(3);
	rSphere1->setShader(rShaderSphere1);

    pScene->add(rSphere1);
    pScene->add(rBRDFSphere1, string("brdf of sphere 1"));
    pScene->add(rShaderSphere1, string("shader of sphere 1"));


    //////////////////
    // GREEN SPHERE //
    //////////////////
    MatouMalin::Point lCenterSphere2(60.0,0.0,50.0);
	Sphere* rSphere2 = new Sphere(lCenterSphere2,40.f);

    // Create a BRDF model for the sphere
    Color lDiffusionSphere2(0.6f,1.0f,0.6f);
	Color lSpecularSphere2(0.4,1.0f,0.4f);
	Phong* rBRDFSphere2 = new Phong(lDiffusionSphere2*2.0,lSpecularSphere2,3);

    // Create a shader for the second sphere
	Shader* rShaderSphere2 = new Shader(rBRDFSphere2,lReflectionCoeff,lRefractionCoeff,pScene);
    rShaderSphere2->setReflectionCountMax(3);
    rSphere2->setShader(rShaderSphere2);

    pScene->add(rSphere2);
    pScene->add(rBRDFSphere2, string("brdf of sphere 2"));
    pScene->add(rShaderSphere2, string("shader of sphere 2"));


    /////////////////
    // BLUE SPHERE //
    /////////////////
    MatouMalin::Point lCenterSphere3(0.0,-10.0,110.0);
	Sphere* rSphere3 = new Sphere(lCenterSphere3,20.0f);

    // Create a BRDF model for the sphere
	Color lDiffusionSphere3(0.6f,0.6f,1.0f);
	Color lSpecularSphere3(0.4f,0.4f,0.9f);
    Phong* rBRDFSphere3 = new Phong(lDiffusionSphere3*2.0,lSpecularSphere3,3);

    // Create a shader for the third sphere
	Shader* rShaderSphere3 = new Shader(rBRDFSphere3,lReflectionCoeff,1.0,pScene);
    rShaderSphere3->setReflectionCountMax(3);
    rSphere3->setShader(rShaderSphere3);

    pScene->add(rSphere3);
    pScene->add(rBRDFSphere3, string("brdf of sphere 3"));
    pScene->add(rShaderSphere3, string("shader of sphere 3"));


    ///////////////////////////////
    // CYAN SPHERE IN BACKGROUND //
    ///////////////////////////////
    MatouMalin::Point lCenterSphere4(-50.0,0.0,-250.0);
	Sphere* rSphere4 = new Sphere(lCenterSphere4,100.0f);

    // Create a BRDF model for the sphere
	Color lDiffusionSphere4(0,255,255);
	Color lSpecularSphere4(0.0f);
    Phong* rBRDFSphere4 = new Phong(lDiffusionSphere4*6,lSpecularSphere4,3);

    // Create a shader for the fourth sphere
	Shader* rShaderSphere4 = new Shader(rBRDFSphere4,0.0,1.0,pScene);
    rSphere4->setShader(rShaderSphere4);

    pScene->add(rSphere4);
    pScene->add(rBRDFSphere4, string("brdf of sphere 4"));
    pScene->add(rShaderSphere4, string("shader of sphere 4"));


    ///////////
    // FLOOR //
    ///////////
    FloorParameters lFloorParameters = {Color(1.0), Color(0.8), 2.0,1.0, 2, 400.0, 80.0, string("./resources/damierBlueYellow.png")};
    createFloor(pScene, lFloorParameters);


    ////////////
    // LIGHTS //
    ////////////
    MatouMalin::Point lLight1Position(50.f,130.f,150.0f);
	Color lLight1Color(18.0f);
	Light* rLight1 = new PunctualLight(lLight1Position,lLight1Color);
    pScene->add(rLight1);

    MatouMalin::Point lLight2Position(20.f,150.f,150.0f);
	Color lLight2Color(18.0f);
	Light* rLight2 = new PunctualLight(lLight2Position,lLight2Color);
    pScene->add(rLight2);

    MatouMalin::Point lLight3Position(-70.f,50.f,110.0f);
	Color lLight3Color(15.0f);
	Light* rLight3 = new PunctualLight(lLight3Position,lLight3Color);
    pScene->add(rLight3);

    MatouMalin::Point lLight4Position(-20.f,50.f,160.0f);
	Color lLight4Color(15.0f);
	Light* rLight4 = new PunctualLight(lLight4Position,lLight4Color);
    pScene->add(rLight4);


    ////////////
    // CAMERA //
    ////////////
    MatouMalin::Point lCentreCamera(0.0f,100.0f,250.0f);
    Vector lDirectionCamera(0.0f,-0.6f,-1.0f);
	Vector lCameraUp(0.f,1.f,0.f);
	float FOV = 80.f*3.141592/180.f;

	Camera* rCamera = new Camera(lCentreCamera,lDirectionCamera,lCameraUp,FOV);
    rCamera->setFocalPoint(lCenterSphere3);
    rCamera->setAperture(Camera::F_SMALL,Camera::SUPER_AWESOME);

    pScene->add(rCamera);


    ////////////////
    // BACKGROUND //
    ////////////////
    pScene->setBackgroundColor(Color(2,6,13));

}

void createScene03(Scene* pScene)
{
    // Same reflection coefficient for the spheres
    double lReflection(1.0);
    double lRefraction(1.0);

    //////////////////////////////////////
    // SPHERE WITH A TURBULANCE TEXTURE //
    //////////////////////////////////////
    MatouMalin::Point lCenter(-20.0,0.0,0.0);
    Sphere* rSphere1 = new Sphere(lCenter, 3.0f);

    Color lDiffusion(245, 222, 179);
    Color lSpecular(255, 255, 255);
    Phong* rBRDF1 = new Phong(lDiffusion*2.0,lSpecular,15);

	// Create a shader for the turbulance sphere
	Shader* rShader1 = new Shader(rBRDF1,lReflection,lRefraction,pScene,Shader::Material::TURBULANCE);
    rShader1->setReflectionCountMax(2);

	rSphere1->setShader(rShader1);

    pScene->add(rSphere1);
    pScene->add(rBRDF1, string("brdf of sphere 1"));
    pScene->add(rShader1, string("shader of sphere 1"));

    //////////////////////////////////
    // SPHERE WITH A MARBLE TEXTURE //
    //////////////////////////////////
    lCenter.setPoint(-10.0, 0.0, 0.0);
    Sphere* rSphere2 = new Sphere(lCenter, 3.0f);

    lDiffusion.setColor(0, 255, 255);
    Phong* rBRDF2 = new Phong(lDiffusion,lSpecular,15);

    // Create a shader for the marble sphere
	Shader* rShader2 = new Shader(rBRDF2,lReflection,lRefraction,pScene,Shader::Material::MARBLE);
    rShader2->setReflectionCountMax(2);

	rSphere2->setShader(rShader2);

    pScene->add(rSphere2);
    pScene->add(rBRDF2, string("brdf of sphere 2"));
    pScene->add(rShader2, string("shader of sphere 2"));

    ///////////
    // TORUS //
    ///////////
    string lPath = "./resources/torus.obj";
    pScene->createFromFile(lPath);

    // Create a BRDF model for the torus
    lDiffusion.setColor(255, 105, 0);
	Phong* rBRDFTorus = new Phong(lDiffusion,lSpecular,3);

	// Create a shader for the torus
	Shader* rShaderTorus = new Shader(rBRDFTorus,0.8,1.0,pScene,Shader::NONE);

    // Get an iterator on the object of the scene and displace it until refers to the torus
    auto lIt = pScene->renderableList().begin();
    lIt++;lIt++;

    (*lIt)->setShader(rShaderTorus);

    pScene->add(rBRDFTorus, string("brdf of the torus"));
    pScene->add(rShaderTorus, string("shader of the torus"));

    ////////////////////////////////
    // SPHERE WITH A BUMP TEXTURE //
    ////////////////////////////////
    lCenter.setPoint(8.0, 0.0, 0.0);
    Sphere* rSphere3 = new Sphere(lCenter, 3.0f);

    lDiffusion.setColor(127, 255, 0);
    Phong* rBRDF3 = new Phong(lDiffusion,lSpecular,15);

    // Create a shader for the marble sphere
	Shader* rShader3 = new Shader(rBRDF3,lReflection,lRefraction,pScene,Shader::Material::BUMP);
    rShader3->setReflectionCountMax(2);

	rSphere3->setShader(rShader3);

    pScene->add(rSphere3);
    pScene->add(rBRDF3, string("brdf of sphere 2"));
    pScene->add(rShader3, string("shader of sphere 2"));

    ///////////////////////////
    // SPHERE WITH A TEXTURE //
    ///////////////////////////
    lCenter.setPoint(18.0, 0.0, 0.0);
	Renderable* rSphere4 = new Sphere(lCenter,3.0);

	// Create a BRDF model for the sphere
    CubeMap* rCubeMapSphere = new CubeMap(lCenter, 104);
    rCubeMapSphere->addImage(CubeMap::BACK, "./resources/earth_back.png");
    rCubeMapSphere->addImage(CubeMap::FRONT,"./resources/earth_front.png");
    rCubeMapSphere->addImage(CubeMap::UP, "./resources/earth_up.png");
    rCubeMapSphere->addImage(CubeMap::DOWN,"./resources/earth_down.png");
    rCubeMapSphere->addImage(CubeMap::LEFT, "./resources/earth_left.png");
    rCubeMapSphere->addImage(CubeMap::RIGHT,"./resources/earth_right.png");
    rCubeMapSphere->setInterpolationMethod(Image::Interpolation::LINEAR);

    pScene->add(rCubeMapSphere);

    lDiffusion.setColor(255, 255, 255);
	BRDF* rBRDF4 = new Phong(lDiffusion*2.0,lSpecular,15);
    rBRDF4->setCubeMap(rCubeMapSphere);

	// Create a shader for the sphere
	Shader* rShader4 = new Shader(rBRDF4,lReflection,lRefraction,pScene);
    rShader4->setReflectionCountMax(1);
	rSphere4->setShader(rShader4);

    pScene->add(rSphere4);
    pScene->add(rBRDF4, string("brdf of sphere 4"));
    pScene->add(rShader4, string("shader of sphere 4"));


    ////////////
    // LIGHTS //
    ////////////
    MatouMalin::Point lLightPos(0.0,20.0,15.0);
    Color lLightCol(18.0f);

	Light* rLight = new PunctualLight(lLightPos,lLightCol);
    pScene->add(rLight);


    ////////////
    // CAMERA //
    ////////////
    MatouMalin::Point lCentreCamera(1.5f,10.0f,25.0f);
    Vector lDirectionCamera(-0.05f,-0.4f,-1.0f);
	Vector lCameraUp(0.f,1.0f,0.f);
	float FOV = 90.f*3.141592/180.f;

	Camera* rCamera = new Camera(lCentreCamera,lDirectionCamera,lCameraUp,FOV);
    rCamera->setAperture(Camera::ALL_SHARP);

    pScene->add(rCamera);

    ///////////
    // FLOOR //
    ///////////
    FloorParameters lFloorParameters = {Color(0.0f), Color(0.0f), 1.0f, 1.0f, 2, 40.0,3.0, string("no_texture")};
    createFloor(pScene, lFloorParameters);


    ////////////////
    // BACKGROUND //
    ////////////////
    pScene->setBackgroundColor(Color(0.0f));


}


void createScene04(Scene* pScene)
{

    // Same reflection coefficient for the spheres behind
    double lReflectionCoeff(8.0);
    double lRefractionCoeff(1.0);

    // Create a sphere
	MatouMalin::Point lCenterSphere1(-180.0,0.0,0.0);
	Sphere* rSphere1 = new Sphere(lCenterSphere1,50.f);

	// Create a BRDF model for the sphere
    Color lDiffusionSphere1(1.3f,0.0f,0.0f);
	Color lSpecularSphere1(1.0f);
	Phong* rBRDFSphere1 = new Phong(lDiffusionSphere1,lSpecularSphere1,25);

	// Create a shader for the sphere
	Shader* rShaderSphere1 = new Shader(rBRDFSphere1,lReflectionCoeff,lRefractionCoeff,pScene);
    rShaderSphere1->setReflectionCountMax(2);
	rSphere1->setShader(rShaderSphere1);

    pScene->add(rSphere1);
    pScene->add(rBRDFSphere1, string("brdf of sphere 1"));
    pScene->add(rShaderSphere1, string("shader of sphere 1"));

    // Create a second sphere
    MatouMalin::Point lCenterSphere2(0.0,0.0,0.0);
	Sphere* rSphere2 = new Sphere(lCenterSphere2,50.f);

    // Create a BRDF model for the sphere
    Color lDiffusionSphere2(0.0f,1.2f,0.0f);
	Color lSpecularSphere2(0.8f);
	Phong* rBRDFSphere2 = new Phong(lDiffusionSphere2,lSpecularSphere2,25);

    // Create a shader for the second sphere
	Shader* rShaderSphere2 = new Shader(rBRDFSphere2,lReflectionCoeff,lRefractionCoeff,pScene);
    rShaderSphere2->setReflectionCountMax(2);
    rSphere2->setShader(rShaderSphere2);

    pScene->add(rSphere2);
    pScene->add(rBRDFSphere2, string("brdf of sphere 2"));
    pScene->add(rShaderSphere2, string("shader of sphere 2"));

    // Create a purple sphere
    MatouMalin::Point lCenterSphere3(180.0,0.0,0.0);
	Sphere* rSphere3 = new Sphere(lCenterSphere3,50.0f);

    // Create a BRDF model for the sphere
	Color lDiffusionSphere3(0.24f,0.34f,1.97f);
	Color lSpecularSphere3(0.8);
    Phong* rBRDFSphere3 = new Phong(lDiffusionSphere3,lSpecularSphere3,25);

    // Create a shader for the third sphere
	Shader* rShaderSphere3 = new Shader(rBRDFSphere3,lReflectionCoeff,lRefractionCoeff,pScene);
    rShaderSphere3->setReflectionCountMax(2);
    rSphere3->setShader(rShaderSphere3);

    pScene->add(rSphere3);
    pScene->add(rBRDFSphere3, string("brdf of sphere 3"));
    pScene->add(rShaderSphere3, string("shader of sphere 3"));


    ////////////
    // LIGHTS //
    ////////////
    MatouMalin::Point lLight1Position(0.f,0.0f,100.0f);
	Color lLowLightColor(20.0f);
	Light* rLight1 = new PunctualLight(lLight1Position,lLowLightColor);
    pScene->add(rLight1);

    MatouMalin::Point lLight2Position(-200.f,0.0f,100.0f);
	Light* rLight2 = new PunctualLight(lLight2Position,lLowLightColor);
    pScene->add(rLight2);

    MatouMalin::Point lLight3Position(200.f,0.0f,100.0f);
	Light* rLight3 = new PunctualLight(lLight3Position,lLowLightColor);
    pScene->add(rLight3);

    MatouMalin::Point lLight4Position(90.f,300.f,200.0f);
	Color lHighLightColor(200.0f);
	Light* rLight4 = new PunctualLight(lLight4Position,lHighLightColor);
    pScene->add(rLight4);

    MatouMalin::Point lLight5Position(-90.f,300.f,200.0f);
	Light* rLight5 = new PunctualLight(lLight5Position,lHighLightColor);
    pScene->add(rLight5);

    ////////////
    // CAMERA //
    ////////////
    MatouMalin::Point lCentreCamera(-200.0f,150.0f,400.0f);
    Vector lDirectionCamera(0.2f,-0.25f,-0.5f);
	Vector lCameraUp(0.f,1.f,0.f);
	float FOV = 80.f*3.141592/180.f;

	Camera* rCamera = new Camera(lCentreCamera,lDirectionCamera,lCameraUp,FOV);
    rCamera->setAperture(Camera::ALL_SHARP,10.0);

    pScene->add(rCamera);

    // FLOOR
    FloorParameters lFloorParameters = {Color(1.0f), Color(0.3f),1.0f,1.0f,2,2000.0,100.0, string("./resources/rect5130.png")};

    createFloor(pScene, lFloorParameters);

    ////////////////
    // BACKGROUND //
    ////////////////
    pScene->setBackgroundColor(Color(0.0f));
}

void createScene04bis(MatouMalin::Scene* pScene)
{
    // Same reflection coefficient for the spheres
    double lReflectionCoeff(8.0);
    double lRefractionCoeff(1.0);

    ////////////////
    // RED SPHERE //
    ////////////////
	MatouMalin::Point lCenterSphere1(-2.50,0.0,0.0);
	Sphere* rSphere1 = new Sphere(lCenterSphere1,1.0f);

	// Create a BRDF model for the sphere
    Color lDiffusionSphere1(1.3f,0.0f,0.0f);
	Color lSpecularSphere1(1.0f);
	Phong* rBRDFSphere1 = new Phong(lDiffusionSphere1,lSpecularSphere1,25);

	// Create a shader for the sphere
	Shader* rShaderSphere1 = new Shader(rBRDFSphere1,lReflectionCoeff,lRefractionCoeff,pScene);
    rShaderSphere1->setReflectionCountMax(4);
	rSphere1->setShader(rShaderSphere1);

    pScene->add(rSphere1);
    pScene->add(rBRDFSphere1, string("brdf of sphere 1"));
    pScene->add(rShaderSphere1, string("shader of sphere 1"));


    //////////////////
    // GREEN SPHERE //
    //////////////////
    MatouMalin::Point lCenterSphere2(0.0,0.0,0.0);
	Sphere* rSphere2 = new Sphere(lCenterSphere2,1.0f);

    // Create a BRDF model for the sphere
    Color lDiffusionSphere2(0.0f,1.2f,0.0f);
	Color lSpecularSphere2(0.8f);
	Phong* rBRDFSphere2 = new Phong(lDiffusionSphere2,lSpecularSphere2,25);

    // Create a shader for the second sphere
	Shader* rShaderSphere2 = new Shader(rBRDFSphere2,lReflectionCoeff,lRefractionCoeff,pScene);
    rShaderSphere2->setReflectionCountMax(4);
    rSphere2->setShader(rShaderSphere2);

    pScene->add(rSphere2);
    pScene->add(rBRDFSphere2, string("brdf of sphere 2"));
    pScene->add(rShaderSphere2, string("shader of sphere 2"));

    ///////////////////
    // PURPLE SPHERE //
    ///////////////////
    MatouMalin::Point lCenterSphere3(2.50,0.0,0.0);
	Sphere* rSphere3 = new Sphere(lCenterSphere3,1.0f);

    // Create a BRDF model for the sphere
	Color lDiffusionSphere3(0.24f,0.34f,1.97f);
	Color lSpecularSphere3(0.8);
    Phong* rBRDFSphere3 = new Phong(lDiffusionSphere3,lSpecularSphere3,25);

    // Create a shader for the third sphere
	Shader* rShaderSphere3 = new Shader(rBRDFSphere3,lReflectionCoeff,lRefractionCoeff,pScene);
    rShaderSphere3->setReflectionCountMax(4);
    rSphere3->setShader(rShaderSphere3);

    pScene->add(rSphere3);
    pScene->add(rBRDFSphere3, string("brdf of sphere 3"));
    pScene->add(rShaderSphere3, string("shader of sphere 3"));


    ////////////
    // LIGHTS //
    ////////////
    MatouMalin::Point lLight4Position(1.15f,4.f,4.0f);
	Color lLightColor(16.0f);
	Light* rLight4 = new PunctualLight(lLight4Position,lLightColor);
    pScene->add(rLight4);

    MatouMalin::Point lLight5Position(-1.15f,4.f,4.0f);
	Light* rLight5 = new PunctualLight(lLight5Position,lLightColor);
    pScene->add(rLight5);


    ////////////
    // CAMERA //
    ////////////
    MatouMalin::Point lCentreCamera(-3.5f,2.50f,7.0f);
    Vector lDirectionCamera(0.15f,-0.25f,-0.5f);
	Vector lCameraUp(0.f,1.f,0.f);
	float FOV = 80.f*3.141592/180.f;

	Camera* rCamera = new Camera(lCentreCamera,lDirectionCamera,lCameraUp,FOV);
    pScene->add(rCamera);

    ///////////
    // FLOOR //
    ///////////
    FloorParameters lFloorParameters = {Color(1.0f), Color(0.3f), 1.0f, 1.0f, 2, 20.0, 2.0, string("./resources/small_damier.png")};
    createFloor(pScene, lFloorParameters);

    ////////////////
    // BACKGROUND //
    ////////////////
    pScene->setBackgroundColor(Color(0.0f));

}


void createScene05(Scene* pScene)
{
    // TORUS
    string lPath = "./resources/torus.obj";
    pScene->createFromFile(lPath);

    // Create a BRDF model for the torus
    Color lDiffusionTorus(0.76f,0.33f,0.12f);
	Color lSpecularTorus(0.9f,0.8f,0.8f);
	Phong* rBRDFTorus = new Phong(lDiffusionTorus,lSpecularTorus,3);

	// Create a shader for the sphere
	Shader* rShaderTorus = new Shader(rBRDFTorus,0.8,1.0,pScene,Shader::BUMP);

    auto lIt = pScene->renderableList().begin();
    (*lIt)->setShader(rShaderTorus);

    pScene->add(rBRDFTorus, string("brdf of the torus"));
    pScene->add(rShaderTorus, string("shader of the torus"));


    ////////////
    // LIGHTS //
    ////////////
    MatouMalin::Point lLight1Position(0.f,1.0f,10.0f);
	Color lLight1Color(10.0f);
	Light* rLight1 = new PunctualLight(lLight1Position,lLight1Color);
    pScene->add(rLight1);

    MatouMalin::Point lLight4Position(0.f,10.f,6.0f);
	Color lLight4Color(10.0f);
	Light* rLight4 = new PunctualLight(lLight4Position,lLight4Color);
    pScene->add(rLight4);


    ////////////
    // CAMERA //
    ////////////
    MatouMalin::Point lCentreCamera(0.0f,3.0f,12.0f);
    Vector lDirectionCamera(0.01f,-0.3f,-1.0f);
	Vector lCameraUp(0.f,1.f,0.f);
	float FOV = 60.f*3.141592/180.f;

	Camera* rCamera = new Camera(lCentreCamera,lDirectionCamera,lCameraUp,FOV);
    rCamera->setAperture(Camera::ALL_SHARP);

    pScene->add(rCamera);


    // FLOOR
    FloorParameters lFloorParameters = {Color(0.6f), Color(0.7f),1.0,1.0, 2,200.0,50.0, string("no_texture")};
    createFloor(pScene, lFloorParameters);


    ////////////////
    // BACKGROUND //
    ////////////////
    pScene->setBackgroundColor(Color(0.7f,0.72f,0.2f));

}

void createScene06(Scene* pScene)
{

    // Same reflection coefficient for the spheres
    double lReflectionCoeff(0.8);

    // SPHERE WITH REFRACTION
	MatouMalin::Point lCenter(0.0,0.0,0.0);
	Sphere* rSphere1 = new Sphere(lCenter,5.f);

	// Create a BRDF model for the sphere
    Color lDiffusionSphere1(1.0f);
	Color lSpecularSphere1(0.1f);
	Phong* rBRDFSphere1 = new Phong(lDiffusionSphere1,lSpecularSphere1,3);

	// Create a shader for the sphere
	Shader* rShaderSphere1 = new Shader(rBRDFSphere1,lReflectionCoeff,2.0,pScene);
	rSphere1->setShader(rShaderSphere1);

    pScene->add(rSphere1);
    pScene->add(rBRDFSphere1, string("brdf of sphere 1"));
    pScene->add(rShaderSphere1, string("shader of sphere 1"));

    // SPHERES IN THE BACKGROUND
    // Nearest spheres
    double lSize = 4.0;
    lCenter.setZ(-20);

    // BG 1, left
    lCenter.setX(-20.0);
	Sphere* rSphereL1 = new Sphere(lCenter,lSize);

    Phong* rBRDF_L1 = new Phong(Color(250, 240, 230)*5.0,Color(1.0),3);
	Shader* rShaderL1 = new Shader(rBRDF_L1,lReflectionCoeff,1.0,pScene,Shader::BUMP);

    rSphereL1->setShader(rShaderL1);

    pScene->add(rSphereL1);
    pScene->add(rBRDF_L1, string("brdf left 1"));
    pScene->add(rShaderL1, string("shader left 1"));

    // BG 1, right
    lCenter.setX(20.0);
	Sphere* rSphereR1 = new Sphere(lCenter,lSize);

    Phong* rBRDFR1 = new Phong(Color(135, 206, 250)*5.0,Color(1.0),3);
	Shader* rShaderR1 = new Shader(rBRDFR1,lReflectionCoeff,1.0,pScene,Shader::BUMP);

    rSphereR1->setShader(rShaderR1);

    pScene->add(rSphereR1);
    pScene->add(rBRDFR1, string("brdf right 1"));
    pScene->add(rShaderR1, string("shader right 1"));

    // BG 1, down
    lCenter.setX(0.0);
    lCenter.setY(-20.0);
	Sphere* rSphereD1 = new Sphere(lCenter,lSize);

    Phong* rBRDFD1 = new Phong(Color(250, 128, 114)*5.0,Color(1.0),3);
	Shader* rShaderD1 = new Shader(rBRDFD1,lReflectionCoeff,1.0,pScene,Shader::BUMP);

    rSphereD1->setShader(rShaderD1);

    pScene->add(rSphereD1);
    pScene->add(rBRDFD1, string("brdf down 1"));
    pScene->add(rShaderD1, string("shader down 1"));

    // BG 1, up
    lCenter.setY(20.0);
	Sphere* rSphereU1 = new Sphere(lCenter,lSize);

    Phong* rBRDFU1 = new Phong(Color(255, 250, 205)*5.0,Color(1.0),3);
	Shader* rShaderU1 = new Shader(rBRDFU1,lReflectionCoeff,1.0,pScene,Shader::BUMP);

    rSphereU1->setShader(rShaderU1);

    pScene->add(rSphereU1);
    pScene->add(rBRDFU1, string("brdf up 1"));
    pScene->add(rShaderU1, string("shader up 1"));

    // Furthest spheres
    lSize = 22.0;
    lCenter.setZ(-220);

    // BG 2, left down
    lCenter.setX(-85.0);
    lCenter.setY(-85.0);
	Sphere* rSphereLD2 = new Sphere(lCenter,lSize);

    Phong* rBRDFLD2 = new Phong(Color(127, 255, 212)*5.0,Color(1.0),3);
	Shader* rShaderLD2 = new Shader(rBRDFLD2,lReflectionCoeff,1.0,pScene);

    rSphereLD2->setShader(rShaderLD2);

    pScene->add(rSphereLD2);
    pScene->add(rBRDFLD2, string("brdf left down 2"));
    pScene->add(rShaderLD2, string("shader left down 2"));

    // BG 2, right down
    lCenter.setX(85.0);
    lCenter.setY(-85.0);
	Sphere* rSphereRD2 = new Sphere(lCenter,lSize);

    Phong* rBRDFRD2 = new Phong(Color(240, 248, 255)*5.0,Color(1.0),3);
	Shader* rShaderRD2 = new Shader(rBRDFRD2,lReflectionCoeff,1.0,pScene);

    rSphereRD2->setShader(rShaderRD2);

    pScene->add(rSphereRD2);
    pScene->add(rBRDFRD2, string("brdf right down 2"));
    pScene->add(rShaderRD2, string("shader right down 2"));

    // BG 2, left up
    lCenter.setX(-85.0);
    lCenter.setY(85.0);
	Sphere* rSphereLU2 = new Sphere(lCenter,lSize);

    Phong* rBRDFLU2 = new Phong(Color(255, 99, 71)*5.0,Color(1.0),3);
	Shader* rShaderLU2 = new Shader(rBRDFLU2,lReflectionCoeff,1.0,pScene);

    rSphereLU2->setShader(rShaderLU2);

    pScene->add(rSphereLU2);
    pScene->add(rBRDFLU2, string("brdf left up 2"));
    pScene->add(rShaderLU2, string("shader left up 2"));

    // BG2, right up
    lCenter.setX(85.0);
    lCenter.setY(85.0);
	Sphere* rSphereRU2 = new Sphere(lCenter,lSize);

    Phong* rBRDFRU2 = new Phong(Color(255, 255, 0)*5.0,Color(1.0),3);
	Shader* rShaderRU2 = new Shader(rBRDFRU2,lReflectionCoeff,1.0,pScene);

    rSphereRU2->setShader(rShaderRU2);

    pScene->add(rSphereRU2);
    pScene->add(rBRDFRU2, string("brdf right up 2"));
    pScene->add(rShaderRU2, string("shader right up 2"));


//    // SPHERE WITH TEXTURE
//    MatouMalin::Point lCenterSphere2(12.0,0.0,0.0);
//	Sphere* rSphere2 = new Sphere(lCenterSphere2,5.f);
//
//    // Create a BRDF model for the sphere
//    Color lDiffusionSphere2(1.0f);
//	Color lSpecularSphere2(0.1);
//    CubeMap* rCubeMapSphere = new CubeMap(lCenterSphere2, 520);
//    rCubeMapSphere->addImage(CubeMap::BACK, "./resources/Desert_back.png");
//    rCubeMapSphere->addImage(CubeMap::FRONT,"./resources/Desert_front.png");
//    rCubeMapSphere->addImage(CubeMap::UP, "./resources/Desert_up.png");
//    rCubeMapSphere->addImage(CubeMap::DOWN,"./resources/Desert_down.png");
//    rCubeMapSphere->addImage(CubeMap::LEFT, "./resources/Desert_left.png");
//    rCubeMapSphere->addImage(CubeMap::RIGHT,"./resources/Desert_right.png");
//
//    pScene->add(rCubeMapSphere);
//
//	Phong* rBRDFSphere2 = new Phong(lDiffusionSphere2,lSpecularSphere2,3);
//    rBRDFSphere2->setCubeMap(rCubeMapSphere);
//
//    // Create a shader for the second sphere
//	Shader* rShaderSphere2 = new Shader(rBRDFSphere2,lReflectionCoeff,1.0,pScene);
//    rSphere2->setShader(rShaderSphere2);
//
//    pScene->add(rSphere2);
//    pScene->add(rBRDFSphere2, string("brdf of sphere 2"));
//    pScene->add(rShaderSphere2, string("shader of sphere 2"));


    ////////////
    // LIGHTS //
    ////////////
    MatouMalin::Point lLightPosition(0.0f,0.0f,20.0f);
	Color lLightColor(6.0f);
	Light* rLight1 = new PunctualLight(lLightPosition,lLightColor);
    pScene->add(rLight1);


    ////////////
    // CAMERA //
    ////////////
    MatouMalin::Point lCentreCamera(0.0f,0.0f,15.0f);
    Vector lDirectionCamera(0.0f,0.0f,-1.01f);
	Vector lCameraUp(0.f,1.f,0.f);
	float FOV = 90.f*3.141592/180.f;

	Camera* rCamera = new Camera(lCentreCamera,lDirectionCamera,lCameraUp,FOV);
    rCamera->setFocalPoint(MatouMalin::Point(4.0));
    rCamera->setAperture(Camera::F_SMALL,Camera::Precision::EXCELLENT);
//    rCamera->setAperture(Camera::ALL_SHARP);

    pScene->add(rCamera);

    // BACKGROUND
    CubeMap* rCubeMapBckGrd = new CubeMap(MatouMalin::Point(0.0), 260); // 260

    rCubeMapBckGrd->addImage(CubeMap::BACK, "./resources/River_back.png");
    rCubeMapBckGrd->addImage(CubeMap::FRONT,"./resources/River_front.png");
    rCubeMapBckGrd->addImage(CubeMap::UP, "./resources/River_up.png");
    rCubeMapBckGrd->addImage(CubeMap::DOWN,"./resources/River_down.png");
    rCubeMapBckGrd->addImage(CubeMap::LEFT, "./resources/River_left.png");
    rCubeMapBckGrd->addImage(CubeMap::RIGHT,"./resources/River_right.png");

    rCubeMapBckGrd->setInterpolationMethod(Image::Interpolation::LINEAR);

    pScene->setBackgroundCubeMap(rCubeMapBckGrd);


}

void createScene07(Scene* pScene)
{
    // Create a sphere (1)
	MatouMalin::Point lCenterSphere1(-30.f,10.0f,20.0f);
	Sphere* rSphere1 = new Sphere(lCenterSphere1,13.f);

	// Create a BRDF model for the sphere
    Color lDiffusionSphere1(229.0f/255.0f,51.0f/255.0f,163.0f/255.0f);
	Color lSpecularSphere1(0.0f);
	Phong* rBRDFSphere1 = new Phong(lDiffusionSphere1,lSpecularSphere1,3);

	// Create a shader for the sphere
	Shader* rShaderSphere1 = new Shader(rBRDFSphere1,0.8,1.0,pScene,Shader::TURBULANCE);
	rSphere1->setShader(rShaderSphere1);

    pScene->add(rSphere1);
    pScene->add(rBRDFSphere1, string("brdf of sphere 1"));
    pScene->add(rShaderSphere1, string("shader of sphere 1"));

    // Create a sphere (2)
	MatouMalin::Point lCenterSphere2(0.0f,10.0f,20.0f);
	Sphere* rSphere2 = new Sphere(lCenterSphere2,13.f);

	// Create a BRDF model for the sphere
    Color lDiffusionSphere2(220.0f/255.0f,210.0f/255.0f,120.0f/255.0f);
	Color lSpecularSphere2(0.0f);
	Phong* rBRDFSphere2 = new Phong(lDiffusionSphere2,lSpecularSphere2,3);

	// Create a shader for the sphere
	Shader* rShaderSphere2 = new Shader(rBRDFSphere2,0.8,1.0,pScene,Shader::MARBLE);
	rSphere2->setShader(rShaderSphere2);

    pScene->add(rSphere2);
    pScene->add(rBRDFSphere2, string("brdf of sphere 2"));
    pScene->add(rShaderSphere2, string("shader of sphere 2"));

    // Create a sphere (3)
	MatouMalin::Point lCenterSphere3(30.f,10.0f,20.0f);
	Sphere* rSphere3 = new Sphere(lCenterSphere3,13.f);

	// Create a BRDF model for the sphere
    Color lDiffusionSphere3(90.0f/255.0f,160.0f/255.0f,210.0f/255.0f);
	Color lSpecularSphere3(0.0f);
	Phong* rBRDFSphere3 = new Phong(lDiffusionSphere3,lSpecularSphere3,3);

	// Create a shader for the sphere
	Shader* rShaderSphere3 = new Shader(rBRDFSphere3,0.8,1.0,pScene,Shader::BUMP);
	rSphere3->setShader(rShaderSphere3);

    pScene->add(rSphere3);
    pScene->add(rBRDFSphere3, string("brdf of sphere 3"));
    pScene->add(rShaderSphere3, string("shader of sphere 3"));

    ////////////
    // LIGHTS //
    ////////////
    MatouMalin::Point lLightPosition(0.0f,90.0f,0.0f);
	Color lLightColor(5.0f);
	Light* rLight1 = new PunctualLight(lLightPosition,lLightColor);
    pScene->add(rLight1);

    //    lLightPosition.setPoint(0.0f,15.0f,37.0f);
    //	Light* rLight2 = new PunctualLight(lLightPosition,lLightColor);
    //    pScene->add(rLight2);

    lLightPosition.setPoint(10.0f,20.0f,37.0f);
	Light* rLight3 = new PunctualLight(lLightPosition,lLightColor);
    pScene->add(rLight3);

    lLightPosition.setPoint(-10.0f,20.0f,37.0f);
	Light* rLight4 = new PunctualLight(lLightPosition,lLightColor);
    pScene->add(rLight4);


    ////////////
    // CAMERA //
    ////////////
    MatouMalin::Point lCentreCamera(0.0f,25.0f,105.0f);
    Vector lDirectionCamera(0.0f,-0.3f,-1.0f);
	Vector lCameraUp(0.f,1.f,0.f);
	float FOV = 80.f*3.141592/180.f;

	Camera* rCamera = new Camera(lCentreCamera,lDirectionCamera,lCameraUp,FOV);
//    rCamera->setAperture(Camera::F_SMALL,85.0,Camera::PRECISION::LOW);
//    rCamera->setFocalPoint(lCenterSphere2);
    rCamera->setAperture(Camera::Aperture::ALL_SHARP);


    pScene->add(rCamera);

    // ROOM
    RoomParameters lRoomParameters = {Color(1.0f,0.18f,0.17f), Color(0.0f), 1.0,1.0, 2,50.0, 20.0,string("./resources/textureLeaves_750x750.png"),string("./resources/textureWall_400x400.png"),string("./resources/textureWall_400x400_Right.png"),string("./resources/textureWall_400x400.png")};

//    RoomParameters lRoomParameters = {Color(1.0f,0.78f,0.17f), Color(0.0f,0.0f,0.79), 50.0, 20.0,string("no_texture"),string("no_texture"),string("no_texture"),string("no_texture")};

    createRoom(pScene, lRoomParameters);

    ////////////////
    // BACKGROUND //
    ////////////////
    pScene->setBackgroundColor(Color(0.2f));


}

void createScene08(MatouMalin::Scene* pScene)
{
    // Same reflection coefficient for the spheres behind
    double lReflectionCoeff(0.8);
    double lRefractionCoeff(1.0);

    // Create a red sphere
	MatouMalin::Point lCenterSphere1(00.0,0.0,-5.0);
	Sphere* rSphere1 = new Sphere(lCenterSphere1,2.f);

	// Create a BRDF model for the sphere
    Color lDiffusionSphere1(1.0f,0.6f,0.6f);
	Color lSpecularSphere1(0.9f,0.4f,0.4f);
	Phong* rBRDFSphere1 = new Phong(lDiffusionSphere1,lSpecularSphere1,3);

	// Create a shader for the sphere
	Shader* rShaderSphere1 = new Shader(rBRDFSphere1,lReflectionCoeff,lRefractionCoeff,pScene);
	rSphere1->setShader(rShaderSphere1);

    pScene->add(rSphere1);
    pScene->add(rBRDFSphere1, string("brdf of sphere 1"));
    pScene->add(rShaderSphere1, string("shader of sphere 1"));

    // Create a green sphere
    MatouMalin::Point lCenterSphere2(10.0,0.0,-100.0);
	Sphere* rSphere2 = new Sphere(lCenterSphere2,30.f);

    // Create a BRDF model for the sphere
    Color lDiffusionSphere2(0.6f,1.0f,0.6f);
	Color lSpecularSphere2(0.4,1.0f,0.4f);
	Phong* rBRDFSphere2 = new Phong(lDiffusionSphere2,lSpecularSphere2,3);

    // Create a shader for the second sphere
	Shader* rShaderSphere2 = new Shader(rBRDFSphere2,lReflectionCoeff,lRefractionCoeff,pScene);
    rSphere2->setShader(rShaderSphere2);

    pScene->add(rSphere2);
    pScene->add(rBRDFSphere2, string("brdf of sphere 2"));
    pScene->add(rShaderSphere2, string("shader of sphere 2"));

    ////////////
    // LIGHTS //
    ////////////
    MatouMalin::Point lLight1Position(0.f,10.f,0.0f);
	Color lLight1Color(3.0f);
	Light* rLight1 = new PunctualLight(lLight1Position,lLight1Color);
    pScene->add(rLight1);

    ////////////
    // CAMERA //
    ////////////
    MatouMalin::Point lCentreCamera(0.0f,0.0f,5.0f);
    Vector lDirectionCamera(0.0f,-0.1f,-1.0f);
	Vector lCameraUp(0.f,1.f,0.f);
	float FOV = 80.f*3.141592/180.f;

	Camera* rCamera = new Camera(lCentreCamera,lDirectionCamera,lCameraUp,FOV);
    rCamera->setAperture(Camera::F_SMALL,1.0,Camera::Precision::SUPER_AWESOME);
    rCamera->setFocalPoint(lCenterSphere1);
    pScene->add(rCamera);


    ////////////////
    // BACKGROUND //
    ////////////////
    pScene->setBackgroundColor(Color(188,236,253));


}

void createScene09(MatouMalin::Scene* pScene)
{
    // Load the "torus"
    string lPath = "./resources/head_4.obj";
    pScene->createFromFile(lPath);

    // Create a BRDF model for the sphere
    Color lDiffusionSphere(0.76f,0.33f,0.12f);
	Color lSpecularSphere(1.0f);
	Phong* rBRDFShpere = new Phong(lDiffusionSphere,lSpecularSphere,5);

	// Create a shader for the sphere
	Shader* rShaderSphere = new Shader(rBRDFShpere,0.8,1.0,pScene);

    pScene->add(rBRDFShpere, string("brdf of the sphere"));
    pScene->add(rShaderSphere, string("shader of the sphere"));

    auto lIt = pScene->renderableList().begin();

    (*lIt)->setShader(rShaderSphere);
    lIt++;


    // Create a BRDF model for the torus
    Color lDiffusionTorus(0.96f,0.40f,0.40f);
	Color lSpecularTorus(0.9f,0.8f,0.8f);
	Phong* rBRDFTorus = new Phong(lDiffusionTorus,lSpecularTorus,5);

	// Create a shader for the torus
	Shader* rShaderTorus = new Shader(rBRDFTorus,0.8,1.0,pScene,Shader::Material::MARBLE);

    pScene->add(rBRDFTorus, string("brdf of the torus"));
    pScene->add(rShaderTorus, string("shader of the torus"));

    (*lIt)->setShader(rShaderTorus);
    lIt++;

    (*lIt)->setShader(rShaderTorus);
    lIt++;


    // Create a BRDF model for the pipe
    Color lDiffusionPipe(0.16f,0.89f,0.0f);
	Color lSpecularPipe(0.4f,0.8f,0.4f);
	Phong* rBRDFPipe = new Phong(lDiffusionPipe,lSpecularPipe,5);

	// Create a shader for the torus
	Shader* rShaderPipe = new Shader(rBRDFPipe,0.8,1.0,pScene);

    pScene->add(rBRDFPipe, string("brdf of the pipe"));
    pScene->add(rShaderPipe, string("shader of the pipe"));

    (*lIt)->setShader(rShaderPipe);
    lIt++;


    // Create a BRDF model for the cone
    Color lDiffusionCone(0.06f,0.10f,0.90f);
	Color lSpecularCone(0.3f,0.2f,0.8f);
	Phong* rBRDFCone = new Phong(lDiffusionCone,lSpecularCone,5);

	// Create a shader for the torus
	Shader* rShaderCone = new Shader(rBRDFCone,0.8,1.0,pScene,Shader::TURBULANCE);

    pScene->add(rBRDFCone, string("brdf of the cone"));
    pScene->add(rShaderCone, string("shader of the cone"));

    (*lIt)->setShader(rShaderCone);


    ////////////
    // LIGHTS //
    ////////////
    MatouMalin::Point lLight1Position(0.f,1.0f,10.0f);
	Color lLight1Color(10.0f);
	Light* rLight1 = new PunctualLight(lLight1Position,lLight1Color);
    pScene->add(rLight1);

    MatouMalin::Point lLight4Position(0.f,10.f,6.0f);
	Color lLight4Color(10.0f);
	Light* rLight4 = new PunctualLight(lLight4Position,lLight4Color);
    pScene->add(rLight4);


    ////////////
    // CAMERA //
    ////////////
    MatouMalin::Point lCentreCamera(0.0f,2.4f,8.0f);
    Vector lDirectionCamera(0.01f,-0.1f,-1.0f);
	Vector lCameraUp(0.f,1.f,0.f);
	float FOV = 60.f*3.141592/180.f;

	Camera* rCamera = new Camera(lCentreCamera,lDirectionCamera,lCameraUp,FOV);
    rCamera->setAperture(Camera::ALL_SHARP);

    pScene->add(rCamera);

    // FLOOR
//    FloorParameters lFloorParameters = {Color(0.6f), Color(0.7f),200.0,50.0, string("no_texture")};
//    createFloor(pScene, lFloorParameters);

    ////////////////
    // BACKGROUND //
    ////////////////
    pScene->setBackgroundColor(Color(0.2f,0.32f,0.8f));


}

void createScene10(MatouMalin::Scene* pScene)
{

    // Same reflection coefficient for the spheres behind
    double lReflectionCoeff(5.0);
    double lRefractionCoeff(1.0);

    ////////////////////////////////
    // Create a first blue sphere //
    ////////////////////////////////
	MatouMalin::Point lCenterSphere1(0.0,0.0,0.0);
	Sphere* rSphere1 = new Sphere(lCenterSphere1,100.f);

	// Create a BRDF model for the sphere
    Color lDiffusionSphere1(0.f,0.0f,0.1f);
	Color lSpecularSphere1(1.0f);
	Phong* rBRDFSphere1 = new Phong(lDiffusionSphere1,lSpecularSphere1,8);

	// Create a shader for the sphere
	Shader* rShaderSphere1 = new Shader(rBRDFSphere1,lReflectionCoeff,lRefractionCoeff,pScene);
    rShaderSphere1->setReflectionCountMax(2);
	rSphere1->setShader(rShaderSphere1);

    pScene->add(rSphere1);
    pScene->add(rBRDFSphere1, string("brdf of sphere 1"));
    pScene->add(rShaderSphere1, string("shader of sphere 1"));


    /////////////////////////////////
    // Create a second blue sphere //
    /////////////////////////////////
    MatouMalin::Point lCenterSphere2(50.0,-20.0,230.0);
	Sphere* rSphere2 = new Sphere(lCenterSphere2,60.f);

    // Create a BRDF model for the sphere
    Color lDiffusionSphere2(0.0f,0.0f,0.1f);
	Color lSpecularSphere2(0,250,154);
	Phong* rBRDFSphere2 = new Phong(lDiffusionSphere2,lSpecularSphere2,15);

    // Create a shader for the second sphere
	Shader* rShaderSphere2 = new Shader(rBRDFSphere2,lReflectionCoeff,lRefractionCoeff,pScene);
    rShaderSphere2->setReflectionCountMax(2);
    rSphere2->setShader(rShaderSphere2);

    pScene->add(rSphere2);
    pScene->add(rBRDFSphere2, string("brdf of sphere 2"));
    pScene->add(rShaderSphere2, string("shader of sphere 2"));


    ////////////
    // LIGHTS //
    ////////////
    MatouMalin::Point lLight1Position(-40.f,150.f,50.0f);
	Color lLight1Color(212.0f,27.0f,218.0f);
    lLight1Color *= 2.0;

	Light* rLight1 = new PunctualLight(lLight1Position,lLight1Color);
    pScene->add(rLight1);


    MatouMalin::Point lLight2Position(90.f,150.f,190.0f);
	Color lLight2Color(189.0f,190.0f,53.0f);

    lLight2Color *= 2.0f;

	Light* rLight2 = new PunctualLight(lLight2Position,lLight2Color);
    pScene->add(rLight2);

    MatouMalin::Point lLight3Position(-190.f,150.f,90.0f);
	Color lLight3Color(255,140,0);

    lLight3Color *= 200.0f;

	Light* rLight3 = new PunctualLight(lLight3Position,lLight3Color);
    pScene->add(rLight3);


    ////////////
    // CAMERA //
    ////////////
    MatouMalin::Point lCentreCamera(-280.0f,150.0f,350.0f);
    Vector lDirectionCamera(0.5f,-0.35f,-0.5f);
	Vector lCameraUp(0.f,1.f,0.f);
	float FOV = 80.f*3.141592/180.f;

	Camera* rCamera = new Camera(lCentreCamera,lDirectionCamera,lCameraUp,FOV);
    rCamera->setAperture(Camera::ALL_SHARP,10.0);

    pScene->add(rCamera);


    ///////////
    // FLOOR //
    ///////////
    FloorParameters lFloorParameters = {Color(1.0f), Color(0.3f),1.0,1.0, 2, 2000.0,100.0, string("./resources/rect5130.png")};
    createFloor(pScene, lFloorParameters);


    ////////////////
    // BACKGROUND //
    ////////////////
    pScene->setBackgroundColor(Color(0.0f));
}

void createScene11(MatouMalin::Scene* pScene)
{
    double lReflectionCoeff(2.0);
    double lRefractionCoeff(1.0);

    //////////////////////////
    // Create a yellow sphere //
    //////////////////////////
    MatouMalin::Point lCenterSphere1(-1.1,0.0,0.0);
	Renderable* rSphere1 = new Sphere(lCenterSphere1,1.0);

	// Create a BRDF model for the sphere
    Color lDiffusionSphere1(255,255,0);
	Color lSpecularSphere1(230,230,250);
	BRDF* rBRDFSphere1 = new Phong(lDiffusionSphere1,lSpecularSphere1,15);

	// Create a shader for the sphere
	Shader* rShaderSphere1 = new Shader(rBRDFSphere1,lReflectionCoeff,lRefractionCoeff,pScene,Shader::TURBULANCE);

    // Set the max number of reflections to 4
    rShaderSphere1->setReflectionCountMax(4);
	rSphere1->setShader(rShaderSphere1);

    pScene->add(rSphere1);
    pScene->add(rBRDFSphere1, string("brdf of sphere 1"));
    pScene->add(rShaderSphere1, string("shader of sphere 1"));


    ///////////////////////////
    // Create a cyan sphere //
    ///////////////////////////
    MatouMalin::Point lCenterSphere2(1.1,0.0,0.0);
	Renderable* rSphere2 = new Sphere(lCenterSphere2,1.0);

    // Create a BRDF model for the sphere
    Color lDiffusionSphere2(0,255,255);
	Color lSpecularSphere2(255,160,122);
	BRDF* rBRDFSphere2 = new Phong(lDiffusionSphere2,lSpecularSphere2,15);

    // Create a shader for the second sphere
	Shader* rShaderSphere2 = new Shader(rBRDFSphere2,lReflectionCoeff,lRefractionCoeff,pScene,Shader::TURBULANCE);

    // Set the max number of reflections to 3
    rShaderSphere2->setReflectionCountMax(3);
    rSphere2->setShader(rShaderSphere2);

    pScene->add(rSphere2);
    pScene->add(rBRDFSphere2, string("brdf of sphere 2"));
    pScene->add(rShaderSphere2, string("shader of sphere 2"));


    //////////////////////////
    // Create a pink sphere //
    //////////////////////////
    MatouMalin::Point lCenterSphere3(0.0,1.8,0.0);
	Renderable* rSphere3 = new Sphere(lCenterSphere3,1.0);

    // Create a BRDF model for the sphere
    Color lDiffusionSphere3(255,0,255);
	Color lSpecularSphere3(127,255,212);
	BRDF* rBRDFSphere3 = new Phong(lDiffusionSphere3,lSpecularSphere3,15);

    // Create a shader for the second sphere
	Shader* rShaderSphere3 = new Shader(rBRDFSphere3,lReflectionCoeff,lRefractionCoeff,pScene,Shader::TURBULANCE);

    // Set the max number of reflections to 5
    rShaderSphere3->setReflectionCountMax(5);
    rSphere3->setShader(rShaderSphere3);

    pScene->add(rSphere3);
    pScene->add(rBRDFSphere3, string("brdf of sphere 3"));
    pScene->add(rShaderSphere3, string("shader of sphere 3"));


    ////////////
    // LIGHTS //
    ////////////
    MatouMalin::Point lLight1Position(0.f,1.0f,10.0f);
	Color lLight1Color(8.0f);
	Light* rLight1 = new PunctualLight(lLight1Position,lLight1Color);
    pScene->add(rLight1);

    MatouMalin::Point lLight2Position(0.f,1.0f,-10.0f);
	Color lLight2Color(5.0f);
	Light* rLight2 = new PunctualLight(lLight2Position,lLight2Color);
    pScene->add(rLight2);


    ////////////
    // CAMERA //
    ////////////
    MatouMalin::Point lCentreCamera(0.0f,0.7f,2.0f);
    Vector lDirectionCamera(0.0f,0.0f,-1.0f);
	Vector lCameraUp(0.f,1.f,0.f);
	float FOV = 60.f*3.141592/180.f;

	Camera* rCamera = new Camera(lCentreCamera,lDirectionCamera,lCameraUp,FOV);
    pScene->add(rCamera);


    ////////////////
    // BACKGROUND //
    ////////////////
    pScene->setBackgroundColor(Color(0.0f));

}

void createScene12(MatouMalin::Scene* pScene)
{
    // Same reflection coefficient for the spheres behind
    double lReflectionCoeff(2.0);
    double lRefractionCoeff(1.0);

    // Create a sphere
	MatouMalin::Point lCenterSphere1(0.0,5.0,5.0);
	Sphere* rSphere1 = new Sphere(lCenterSphere1,9.f);

	// Create a BRDF model for the sphere
    Color lDiffusionSphere1(1.0f,0.8f,0.9f);
	Color lSpecularSphere1(1.0);
	Phong* rBRDFSphere1 = new Phong(lDiffusionSphere1,lSpecularSphere1,3);

    // Create a BRDF model for the sphere
    //    CubeMap* rCubeMapSphere = new CubeMap(lCenterSphere1, 720);
    //    rCubeMapSphere->addImage(CubeMap::BACK, "./resources/nightSky2.png");
    //    rCubeMapSphere->setLink(CubeMap::FRONT, 0);
    //    rCubeMapSphere->setLink(CubeMap::UP, 0);
    //    rCubeMapSphere->setLink(CubeMap::DOWN, 0);
    //    rCubeMapSphere->setLink(CubeMap::LEFT, 0);
    //    rCubeMapSphere->setLink(CubeMap::RIGHT, 0);
    //
    //    pScene->add(rCubeMapSphere);
    //
    //    rBRDFSphere1->setCubeMap(rCubeMapSphere);

	// Create a shader for the sphere
	Shader* rShaderSphere1 = new Shader(rBRDFSphere1,lReflectionCoeff,lRefractionCoeff,pScene);
    rShaderSphere1->setReflectionCountMax(4);
	rSphere1->setShader(rShaderSphere1);

    pScene->add(rSphere1);
    pScene->add(rBRDFSphere1, string("brdf of sphere 1"));
    pScene->add(rShaderSphere1, string("shader of sphere 1"));

    // Create a second sphere
    MatouMalin::Point lCenterSphere2(-21.0,-5.0,8.0);
	Sphere* rSphere2 = new Sphere(lCenterSphere2,9.f);

    // Create a BRDF model for the sphere
    Color lDiffusionSphere2(0.9f,1.0f,0.8f);
	Color lSpecularSphere2(1.0f);
	Phong* rBRDFSphere2 = new Phong(lDiffusionSphere2,lSpecularSphere2,3);

    // Create a shader for the second sphere
	Shader* rShaderSphere2 = new Shader(rBRDFSphere2,lReflectionCoeff,lRefractionCoeff,pScene);
    rShaderSphere2->setReflectionCountMax(4);
    rSphere2->setShader(rShaderSphere2);

    pScene->add(rSphere2);
    pScene->add(rBRDFSphere2, string("brdf of sphere 2"));
    pScene->add(rShaderSphere2, string("shader of sphere 2"));

    // Create a transparent sphere for refraction
    MatouMalin::Point lCenterSphere3(21.0,-5.0,8.0);
	Sphere* rSphere3 = new Sphere(lCenterSphere3,9.0f);

    // Create a BRDF model for the sphere
	Color lDiffusionSphere3(0.95f,0.88f,0.60f);
	Color lSpecularSphere3(1.0f);
    Phong* rBRDFSphere3 = new Phong(lDiffusionSphere3,lSpecularSphere3,3);

    // Create a shader for the third sphere
	Shader* rShaderSphere3 = new Shader(rBRDFSphere3,0.6,1.0,pScene);
    rShaderSphere3->setReflectionCountMax(4);
    rSphere3->setShader(rShaderSphere3);

    pScene->add(rSphere3);
    pScene->add(rBRDFSphere3, string("brdf of sphere 3"));
    pScene->add(rShaderSphere3, string("shader of sphere 3"));

    ////////////
    // LIGHTS //
    ////////////
    MatouMalin::Point lLight1Position(0.f,25.0f,50.0f);
	Color lLight1Color(30.0f);
	Light* rLight1 = new PunctualLight(lLight1Position,lLight1Color);
    pScene->add(rLight1);

    //    MatouMalin::Point lLight4Position(0.f,20.f,6.0f);
    //	Color lLight4Color(10.0f);
    //	Light* rLight4 = new PunctualLight(lLight4Position,lLight4Color);
    //    pScene->add(rLight4);


    ////////////
    // CAMERA //
    ////////////
    MatouMalin::Point lCentreCamera(0.0f,15.0f,40.0f);
    Vector lDirectionCamera(0.0f,-0.1f,-1.0f);
	Vector lCameraUp(0.f,1.f,0.f);
	float FOV = 60.f*3.141592/180.f;

	Camera* rCamera = new Camera(lCentreCamera,lDirectionCamera,lCameraUp,FOV);
    //    rCamera->setAperture(Camera::F_SMALL,45.0,Camera::LOW);
    rCamera->setAperture(Camera::ALL_SHARP);
    pScene->add(rCamera);


    // ROOM
    RoomParameters lParameters = {Color(0.8f),Color(1.0f), 0.0,1.0, 2,35.0,15.0,string("no_texture"),string("no_texture"),string("no_texture"),string("no_texture")};
    createRoom(pScene, lParameters);




    ////////////////
    // BACKGROUND //
    ////////////////
    //    CubeMap* rCubeMap = new CubeMap(lCenterSphere1, 750);
    //
    //    rCubeMap->addImage(CubeMap::BACK, "./resources/nightSky2.png");
    //    rCubeMap->setLink(CubeMap::FRONT, 0);
    //    rCubeMap->setLink(CubeMap::UP, 0);
    //    rCubeMap->setLink(CubeMap::DOWN, 0);
    //    rCubeMap->setLink(CubeMap::LEFT, 0);
    //    rCubeMap->setLink(CubeMap::RIGHT, 0);
    //
    //    pScene->setBackgroundCubeMap(rCubeMap);

    pScene->setBackgroundColor(Color(220, 240, 250));


}

void createScene13(MatouMalin::Scene* pScene)
{
    pScene->createFromFile("./resources/tableAndStatue3_bis.obj");

    // Create BRDF model for the cones
    Color lDiffusion(255, 105, 0);
    Color lSpecular(1.0f);
	Phong* rBRDFCones = new Phong(lDiffusion,lSpecular,3);

	// Create a shader for the cones
	Shader* rShaderCones = new Shader(rBRDFCones,0.8,1.0,pScene,Shader::NONE);

    pScene->add(rBRDFCones, "BRDF cones ");
    pScene->add(rShaderCones, "Shader cones ");

    auto lIt = pScene->objectNamed("pCone1");
    if (lIt)
        lIt->setShader(rShaderCones);

    lIt = pScene->objectNamed("pCone2");
    if (lIt)
        lIt->setShader(rShaderCones);

    lIt = pScene->objectNamed("pCone3");
    if (lIt)
        lIt->setShader(rShaderCones);

    lIt = pScene->objectNamed("pCone4");
    if (lIt)
        lIt->setShader(rShaderCones);

    // Create BRDF model for the torus
	Phong* rBRDFTorus = new Phong(Color(255,99,71),Color(1.0),3);

	// Create a shader for the torus
	Shader* rShaderTorus = new Shader(rBRDFTorus,1.8,1.0,pScene,Shader::NONE);

    pScene->add(rBRDFTorus, "BRDF torus ");
    pScene->add(rShaderTorus, "Shader torus ");

    lIt = pScene->objectNamed("pTorus1");
    if (lIt)
        lIt->setShader(rShaderTorus);

    lIt = pScene->objectNamed("pTorus2");
    if (lIt)
        lIt->setShader(rShaderTorus);

    // Create a BRDF model for the table
    Phong* rBRDFPyramid = new Phong(Color(128,128,0), Color(1.0f), 10);

    // Create a shader for the table
    Shader* rShaderPyramid = new Shader(rBRDFPyramid, 1.0f, 1.0f, pScene,Shader::Material::TURBULANCE);

    pScene->add(rBRDFPyramid, "BRDF pyramid ");
    pScene->add(rShaderPyramid, "Shader pyramid ");

    // Set shaders for the table
    lIt = pScene->objectNamed("pPyramid1");
    if (lIt)
        lIt->setShader(rShaderPyramid);

    lIt = pScene->objectNamed("pPyramid2");
    if (lIt)
        lIt->setShader(rShaderPyramid);




    // Create a BRDF model for the table
    Phong* rBRDFTable = new Phong(Color(1.0f), Color(1.0f), 10);

    // Create a shader for the table
    Shader* rShaderTable = new Shader(rBRDFTable, 1.0f, 1.0f, pScene,Shader::Material::MARBLE);

    pScene->add(rBRDFTable, "BRDF table ");
    pScene->add(rShaderTable, "Shader table ");

    // Set shaders for the table
    lIt = pScene->objectNamed("pCylinder1");
    if (lIt)
        lIt->setShader(rShaderTable);

    lIt = pScene->objectNamed("pCylinder2");
    if (lIt)
        lIt->setShader(rShaderTable);

    lIt = pScene->objectNamed("pCylinder3");
    if (lIt)
        lIt->setShader(rShaderTable);

    lIt = pScene->objectNamed("pCylinder4");
    if (lIt)
        lIt->setShader(rShaderTable);

    lIt = pScene->objectNamed("pCube1");
    if (lIt)
        lIt->setShader(rShaderTable);



    // Sphere with texture
    MatouMalin::Point lCenterSphere(0.0,6.7,0.0);
	Sphere* rSphere1 = new Sphere(lCenterSphere,2.0f);

	// Create a BRDF model for the sphere
    Color lDiffusionSphere1(1.0f);
	Color lSpecularSphere1(1.0f);
	Phong* rBRDFSphere1 = new Phong(lDiffusionSphere1,lSpecularSphere1,8);


    CubeMap* rCubeMapDesert = new CubeMap(MatouMalin::Point(0.0), 260); // 260

    rCubeMapDesert->addImage(CubeMap::BACK, "./resources/Desert_back.png");
    rCubeMapDesert->addImage(CubeMap::FRONT,"./resources/Desert_front.png");
    rCubeMapDesert->addImage(CubeMap::UP, "./resources/Desert_up.png");
    rCubeMapDesert->addImage(CubeMap::DOWN,"./resources/Desert_down.png");
    rCubeMapDesert->addImage(CubeMap::LEFT, "./resources/Desert_left.png");
    rCubeMapDesert->addImage(CubeMap::RIGHT,"./resources/Desert_right.png");

    rCubeMapDesert->setInterpolationMethod(Image::Interpolation::LINEAR);

    pScene->add(rCubeMapDesert);

    rBRDFSphere1->setCubeMap(rCubeMapDesert);

	// Create a shader for the sphere
	Shader* rShaderSphere1 = new Shader(rBRDFSphere1,1.0,1.0,pScene);
    rShaderSphere1->setReflectionCountMax(1);
	rSphere1->setShader(rShaderSphere1);

    pScene->add(rSphere1);
    pScene->add(rBRDFSphere1, string("brdf of sphere 1"));
    pScene->add(rShaderSphere1, string("shader of sphere 1"));

    // Mirror on the right wall
    double lMirrorXPos = 10.0;
    Triangle* rMirror1 = new Triangle(MatouMalin::Point(lMirrorXPos, 4.0,-10.0),MatouMalin::Point(lMirrorXPos, 12.0,-10.0),MatouMalin::Point(lMirrorXPos, 12.0,18.0));
    Triangle* rMirror2 = new Triangle(MatouMalin::Point(lMirrorXPos, 4.0,-10.0),MatouMalin::Point(lMirrorXPos, 12.0, 18.0),MatouMalin::Point(lMirrorXPos, 4.0, 18.0));

    Vector lMinusX(-1.0, 0.0, 0.0);

    rMirror1->setVertexNormal(0, lMinusX);
    rMirror1->setVertexNormal(1, lMinusX);
    rMirror1->setVertexNormal(2, lMinusX);

    rMirror2->setVertexNormal(0, lMinusX);
    rMirror2->setVertexNormal(1, lMinusX);
    rMirror2->setVertexNormal(2, lMinusX);

    // Create a BRDF model for the mirror
	Phong* rBRDFMirror = new Phong(Color(0.4f,0.4f,0.6f),Color(1.0f),8);

	// Create a shader for the mirror
	Shader* rShaderMirror = new Shader(rBRDFMirror,20.0,1.0,pScene);
    rShaderMirror->setReflectionCountMax(2);

	rMirror1->setShader(rShaderMirror);
	rMirror2->setShader(rShaderMirror);

    pScene->add(rMirror1);
    pScene->add(rMirror2);
    pScene->add(rBRDFMirror, string("brdf of sphere 1"));
    pScene->add(rShaderMirror, string("shader of sphere 1"));


    ////////////
    // LIGHTS //
    ////////////
    MatouMalin::Point lLight1Position(-3.0,10.0,20.0);
	Color lLightColor(20.0f);
	Light* rLight1 = new PunctualLight(lLight1Position,lLightColor);
    pScene->add(rLight1);


//    MatouMalin::Point lLight2Position(-5.0,10.0,10.0);
//	Light* rLight2 = new PunctualLight(lLight2Position,lLightColor);
//    pScene->add(rLight2);

//    MatouMalin::Point lLight3Position(-4.0,7.0,-9.0);
//	Light* rLight3 = new PunctualLight(lLight3Position,lLightColor);
//    pScene->add(rLight3);


    ////////////
    // CAMERA //
    ////////////
    MatouMalin::Point lCentreCamera(-5.0,8.0,21.0);
    Vector lDirectionCamera(0.4,-0.20,-1.0);
	Vector lCameraUp(0.0,1.0,0.0);
	float FOV = 80.f*3.141592/180.f;

	Camera* rCamera = new Camera(lCentreCamera,lDirectionCamera,lCameraUp,FOV);
    rCamera->setFocalPoint(lCenterSphere+lDirectionCamera.normalize()*rSphere1->radius()*(-1.0));
    rCamera->setAperture(Camera::Aperture::F_SMALL,Camera::Precision::SUPER_AWESOME);
    pScene->add(rCamera);

    RoomParameters lParameters = {Color(0.8f),Color(0.8f), 0.0,1.0, 1, MatouMalin::Point(-28.0,0.0,-20.0),Vector(40.0,15.0,40.0),string("./resources/floor.png"),string("./resources/textureWall_400x400.png"),string("./resources/textureWall_400x400_Right.png"),string("./resources/textureWall_400x400.png"),string("./resources/ceiling.png")};

    createRoom(pScene, lParameters);


    ////////////////
    // BACKGROUND //
    ////////////////
    pScene->setBackgroundColor(Color(0.0f));
}

void createScene14(MatouMalin::Scene* pScene)
{
    pScene->createFromFile("./resources/tableAndStatueAndPyramid3.obj");

    // Create BRDF model for the cones
    Color lDiffusion(255, 105, 0);
    Color lSpecular(1.0f);
	Phong* rBRDFCones = new Phong(lDiffusion,lSpecular,3);

	// Create a shader for the cones
	Shader* rShaderCones = new Shader(rBRDFCones,0.8,1.0,pScene,Shader::NONE);

    pScene->add(rBRDFCones, "BRDF cones ");
    pScene->add(rShaderCones, "Shader cones ");

    auto lIt = pScene->objectNamed("pCone1");
    if (lIt)
        lIt->setShader(rShaderCones);

    lIt = pScene->objectNamed("pCone2");
    if (lIt)
        lIt->setShader(rShaderCones);

    lIt = pScene->objectNamed("pCone3");
    if (lIt)
        lIt->setShader(rShaderCones);

    lIt = pScene->objectNamed("pCone4");
    if (lIt)
        lIt->setShader(rShaderCones);

    // Create BRDF model for the torus
	Phong* rBRDFTorus = new Phong(Color(255,99,71),Color(1.0),3);

	// Create a shader for the torus
	Shader* rShaderTorus = new Shader(rBRDFTorus,1.8,1.0,pScene,Shader::NONE);

    pScene->add(rBRDFTorus, "BRDF torus ");
    pScene->add(rShaderTorus, "Shader torus ");

    lIt = pScene->objectNamed("pTorus1");
    if (lIt)
        lIt->setShader(rShaderTorus);

    lIt = pScene->objectNamed("pTorus2");
    if (lIt)
        lIt->setShader(rShaderTorus);

    // Create a BRDF model for the table
    Phong* rBRDFPyramid = new Phong(Color(128,128,0), Color(1.0f), 10);

    // Create a shader for the table
    Shader* rShaderPyramid = new Shader(rBRDFPyramid, 1.0f, 1.0f, pScene,Shader::Material::TURBULANCE);

    pScene->add(rBRDFPyramid, "BRDF pyramid ");
    pScene->add(rShaderPyramid, "Shader pyramid ");

    // Set shaders for the table
    lIt = pScene->objectNamed("pPyramid1");
    if (lIt)
        lIt->setShader(rShaderPyramid);

    lIt = pScene->objectNamed("pPyramid2");
    if (lIt)
        lIt->setShader(rShaderPyramid);


    Phong* rBRDFBackPyramid = new Phong(Color(0, 255, 255), Color(1.0f), 10);

    // Create a shader for the table
    Shader* rShaderBackPyramid = new Shader(rBRDFBackPyramid, 1.0f, 1.0f, pScene,Shader::Material::BUMP);

    pScene->add(rBRDFBackPyramid, "BRDF pyramid in the background ");
    pScene->add(rShaderBackPyramid, "Shader pyramid in the background ");

    lIt = pScene->objectNamed("pPyramid3");
    if (lIt)
        lIt->setShader(rShaderBackPyramid);


    // Create a BRDF model for the table
    Phong* rBRDFTable = new Phong(Color(1.0f), Color(1.0f), 10);

    // Create a shader for the table
    Shader* rShaderTable = new Shader(rBRDFTable, 1.0f, 1.0f, pScene,Shader::Material::MARBLE);

    pScene->add(rBRDFTable, "BRDF table ");
    pScene->add(rShaderTable, "Shader table ");

    // Set shaders for the table
    lIt = pScene->objectNamed("pCylinder1");
    if (lIt)
        lIt->setShader(rShaderTable);

    lIt = pScene->objectNamed("pCylinder2");
    if (lIt)
        lIt->setShader(rShaderTable);

    lIt = pScene->objectNamed("pCylinder3");
    if (lIt)
        lIt->setShader(rShaderTable);

    lIt = pScene->objectNamed("pCylinder4");
    if (lIt)
        lIt->setShader(rShaderTable);

    lIt = pScene->objectNamed("pCube1");
    if (lIt)
        lIt->setShader(rShaderTable);




    // Sphere with texture
    MatouMalin::Point lCenterSphere(.0,6.7,0.0);
	Sphere* rSphere1 = new Sphere(lCenterSphere,2.0f);

	// Create a BRDF model for the sphere
    Color lDiffusionSphere1(0.1f);
	Color lSpecularSphere1(0.1f);
	Phong* rBRDFSphere1 = new Phong(lDiffusionSphere1,lSpecularSphere1,8);

  	// Create a shader for the sphere
	Shader* rShaderSphere1 = new Shader(rBRDFSphere1,1.0,2.4,pScene);
    rShaderSphere1->setReflectionCountMax(1);
	rSphere1->setShader(rShaderSphere1);

    pScene->add(rSphere1);
    pScene->add(rBRDFSphere1, string("brdf of sphere 1"));
    pScene->add(rShaderSphere1, string("shader of sphere 1"));


    ////////////
    // LIGHTS //
    ////////////
    MatouMalin::Point lLight1Position(0.0,20.0,10.0);
	Color lLightColor(20.0f);
	Light* rLight1 = new PunctualLight(lLight1Position,lLightColor);
    pScene->add(rLight1);


    MatouMalin::Point lLight2Position(-5.0,10.0,10.0);
	Light* rLight2 = new PunctualLight(lLight2Position,lLightColor);
    pScene->add(rLight2);

    MatouMalin::Point lLight3Position(5.0,10.0,10.0);
	Light* rLight3 = new PunctualLight(lLight3Position,lLightColor);
    pScene->add(rLight3);


    ////////////
    // CAMERA //
    ////////////
    MatouMalin::Point lCentreCamera(-2.0,8.0,14.0);
    Vector lDirectionCamera(0.05,-0.05,-1.0);
	Vector lCameraUp(0.0,1.0,0.0);
	float FOV = 80.f*3.141592/180.f;

	Camera* rCamera = new Camera(lCentreCamera,lDirectionCamera,lCameraUp,FOV);
    rCamera->setFocalPoint(lCenterSphere+lDirectionCamera.normalize()*rSphere1->radius()*(-1.0));
    rCamera->setAperture(Camera::Aperture::F_MEDIUM,Camera::Precision::SUPER_AWESOME);
    pScene->add(rCamera);


    CubeMap* rCubeMapBckGrd = new CubeMap(MatouMalin::Point(0.0), 260); // 260

    rCubeMapBckGrd->addImage(CubeMap::BACK, "./resources/Desert_back.png");
    rCubeMapBckGrd->addImage(CubeMap::FRONT,"./resources/Desert_front.png");
    rCubeMapBckGrd->addImage(CubeMap::UP, "./resources/Desert_up.png");
    rCubeMapBckGrd->addImage(CubeMap::DOWN,"./resources/Desert_down.png");
    rCubeMapBckGrd->addImage(CubeMap::LEFT, "./resources/Desert_left.png");
    rCubeMapBckGrd->addImage(CubeMap::RIGHT,"./resources/Desert_right.png");

    rCubeMapBckGrd->setInterpolationMethod(Image::Interpolation::LINEAR);

    pScene->setBackgroundCubeMap(rCubeMapBckGrd);
}

void createFloor(Scene* pScene, const FloorParameters & pParam)
{
    double lDeep = -1.0*pParam.deep;

    Triangle* rTriangleZ1 = new Triangle(MatouMalin::Point(-pParam.size,lDeep,-pParam.size),MatouMalin::Point(-pParam.size,lDeep,pParam.size),MatouMalin::Point(pParam.size,lDeep,pParam.size));
    Triangle* rTriangleZ2 = new Triangle(MatouMalin::Point(-pParam.size,lDeep,-pParam.size),MatouMalin::Point(pParam.size,lDeep,pParam.size),MatouMalin::Point(pParam.size,lDeep,-pParam.size));

    rTriangleZ1->setVertexNormal(0, Vector(0.0,1.0,0.0));
    rTriangleZ1->setVertexNormal(1, Vector(0.0,1.0,0.0));
    rTriangleZ1->setVertexNormal(2, Vector(0.0,1.0,0.0));

    rTriangleZ2->setVertexNormal(0, Vector(0.0,1.0,0.0));
    rTriangleZ2->setVertexNormal(1, Vector(0.0,1.0,0.0));
    rTriangleZ2->setVertexNormal(2, Vector(0.0,1.0,0.0));

	// Create BRDF model for the triangle
	Phong* lBRDFTriangle = new Phong(pParam.diffusion,pParam.specular,3);
    lBRDFTriangle->setAmbient(Color(0.0f));

    if (pParam.floorTexturePath.compare("no_texture"))
    {
        CubeMap* rCubeMapFloor = new CubeMap(MatouMalin::Point(0.0,-4.0,0.0), pParam.size*2.0);

        rCubeMapFloor->addImage(CubeMap::BACK, pParam.floorTexturePath);
        rCubeMapFloor->setLink(CubeMap::FRONT, 0);
        rCubeMapFloor->setLink(CubeMap::UP, 0);
        rCubeMapFloor->setLink(CubeMap::DOWN, 0);
        rCubeMapFloor->setLink(CubeMap::LEFT, 0);
        rCubeMapFloor->setLink(CubeMap::RIGHT, 0);

        rCubeMapFloor->setInterpolationMethod(Image::Interpolation::NEAREST);

        pScene->add(rCubeMapFloor);

        lBRDFTriangle->setCubeMap(rCubeMapFloor);
    }


	// Create a shader for the triangle
	Shader* lShaderTriangle = new Shader(lBRDFTriangle,pParam.reflectionCoeff,pParam.refractionCoeff,pScene);
    lShaderTriangle->setReflectionCountMax(pParam.maxReflection);

    rTriangleZ1->setShader(lShaderTriangle);
    rTriangleZ2->setShader(lShaderTriangle);

    pScene->add(rTriangleZ1);
    pScene->add(rTriangleZ2);
    pScene->add(lBRDFTriangle, string("brdf of the triangles of the floor"));
    pScene->add(lShaderTriangle, string("shader of the triangles of the floor"));

}

void createRoom(Scene* pScene, const RoomParameters & pParam)
{

    MatouMalin::Point lZero(pParam.lowCorner);
    MatouMalin::Point lOne(lZero.x(),lZero.y(), lZero.z()+pParam.dimensions.z());
    MatouMalin::Point lTwo(lZero.x()+pParam.dimensions.x(),lZero.y(), lZero.z()+pParam.dimensions.z());
    MatouMalin::Point lThree(lZero.x()+pParam.dimensions.x(),lZero.y(), lZero.z());
    MatouMalin::Point lFour(lZero.x(),lZero.y()+pParam.dimensions.y(), lZero.z());
    MatouMalin::Point lFive(lZero.x(),lZero.y()+pParam.dimensions.y(), lZero.z()+pParam.dimensions.z());
    MatouMalin::Point lSix = pParam.lowCorner + pParam.dimensions;
    MatouMalin::Point lSeven(lZero.x()+pParam.dimensions.x(),lZero.y()+pParam.dimensions.y(), lZero.z());

    // Create floor
    Triangle* rTriFloor1 = new Triangle(lZero,lOne,lTwo);
    Triangle* rTriFloor2 = new Triangle(lZero,lTwo,lThree);

    rTriFloor1->setVertexNormal(0, Vector(0.0,1.0,0.0));
    rTriFloor1->setVertexNormal(1, Vector(0.0,1.0,0.0));
    rTriFloor1->setVertexNormal(2, Vector(0.0,1.0,0.0));

    rTriFloor2->setVertexNormal(0, Vector(0.0,1.0,0.0));
    rTriFloor2->setVertexNormal(1, Vector(0.0,1.0,0.0));
    rTriFloor2->setVertexNormal(2, Vector(0.0,1.0,0.0));

    MatouMalin::Point lMiddleOfFace((lZero.x()+lOne.x()+lTwo.x()+lThree.x())*0.25,(lZero.y()+lOne.y()+lTwo.y()+lThree.y())*0.25,(lZero.z()+lOne.z()+lTwo.z()+lThree.z())*0.25);

    Phong* rBRDF_Floor = new Phong(pParam.diffusion,pParam.specular,3);
//    rBRDF_Floor->setAmbient(Color(0.0f));

    if (pParam.floorTexturePath.compare("no_texture"))
    {
        CubeMap* rCubeMapFloor = new CubeMap(lMiddleOfFace, max(pParam.dimensions.x(), pParam.dimensions.z()));

        rCubeMapFloor->addImage(CubeMap::BACK, pParam.floorTexturePath);
        rCubeMapFloor->setLink(CubeMap::FRONT, 0);
        rCubeMapFloor->setLink(CubeMap::UP, 0);
        rCubeMapFloor->setLink(CubeMap::DOWN, 0);
        rCubeMapFloor->setLink(CubeMap::LEFT, 0);
        rCubeMapFloor->setLink(CubeMap::RIGHT, 0);

        rCubeMapFloor->setInterpolationMethod(Image::Interpolation::LINEAR);

        pScene->add(rCubeMapFloor);

        rBRDF_Floor->setCubeMap(rCubeMapFloor);
    }

    Shader* rShaderFloor = new Shader(rBRDF_Floor,pParam.reflectionCoeff,pParam.refractionCoeff,pScene);
    rShaderFloor->setReflectionCountMax(pParam.maxReflection);

    rTriFloor1->setShader(rShaderFloor);
    rTriFloor2->setShader(rShaderFloor);

    pScene->add(rTriFloor1);
    pScene->add(rTriFloor2);
    pScene->add(rBRDF_Floor, string("brdf of the triangles of the floor"));
    pScene->add(rShaderFloor, string("shader of the triangles of the floor"));


    // Create left wall
    Triangle* rTriLeftWall1 = new Triangle(lZero,lFour,lFive);
    Triangle* rTriLeftWall2 = new Triangle(lZero,lFive,lOne);

    rTriLeftWall1->setVertexNormal(0, Vector(1.0,0.0,0.0));
    rTriLeftWall1->setVertexNormal(1, Vector(1.0,0.0,0.0));
    rTriLeftWall1->setVertexNormal(2, Vector(1.0,0.0,0.0));

    rTriLeftWall2->setVertexNormal(0, Vector(1.0,0.0,0.0));
    rTriLeftWall2->setVertexNormal(1, Vector(1.0,0.0,0.0));
    rTriLeftWall2->setVertexNormal(2, Vector(1.0,0.0,0.0));

    lMiddleOfFace.setX((lZero.x()+lOne.x()+lFour.x()+lFive.x())*0.25);
    lMiddleOfFace.setY((lZero.y()+lOne.y()+lFour.y()+lFive.y())*0.25);
    lMiddleOfFace.setZ((lZero.z()+lOne.z()+lFour.z()+lFive.z())*0.25);

    Phong* rBRDFLeftWall = new Phong(pParam.diffusion,pParam.specular,3);
    rBRDFLeftWall->setAmbient(Color(0.1f));

    if (pParam.wallLeftTexturePath.compare("no_texture"))
    {
        CubeMap* rCubeMapLeftWall = new CubeMap(lMiddleOfFace, max(pParam.dimensions.y(), pParam.dimensions.z()));

        rCubeMapLeftWall->addImage(CubeMap::BACK, pParam.wallLeftTexturePath);
        rCubeMapLeftWall->setLink(CubeMap::FRONT, 0);
        rCubeMapLeftWall->setLink(CubeMap::UP, 0);
        rCubeMapLeftWall->setLink(CubeMap::DOWN, 0);
        rCubeMapLeftWall->setLink(CubeMap::LEFT, 0);
        rCubeMapLeftWall->setLink(CubeMap::RIGHT, 0);

        rCubeMapLeftWall->setInterpolationMethod(Image::Interpolation::LINEAR);

        pScene->add(rCubeMapLeftWall);

        rBRDFLeftWall->setCubeMap(rCubeMapLeftWall);
    }

    Shader* rShaderLeftWall = new Shader(rBRDFLeftWall,pParam.reflectionCoeff,pParam.refractionCoeff,pScene);
    rShaderLeftWall->setReflectionCountMax(pParam.maxReflection);

    rTriLeftWall1->setShader(rShaderLeftWall);
    rTriLeftWall2->setShader(rShaderLeftWall);

    pScene->add(rTriLeftWall1);
    pScene->add(rTriLeftWall2);
    pScene->add(rBRDFLeftWall, string("brdf of the triangles of the left wall"));
    pScene->add(rShaderLeftWall, string("shader of the triangles of the left wall"));


    // Create back wall
    Triangle* rTriBackWall1 = new Triangle(lZero, lThree, lFour);
    Triangle* rTriBackWall2 = new Triangle(lFour, lThree, lSeven);

    rTriBackWall1->setVertexNormal(0, Vector(0.0,0.0,1.0));
    rTriBackWall1->setVertexNormal(1, Vector(0.0,0.0,1.0));
    rTriBackWall1->setVertexNormal(2, Vector(0.0,0.0,1.0));

    rTriBackWall2->setVertexNormal(0, Vector(0.0,0.0,1.0));
    rTriBackWall2->setVertexNormal(1, Vector(0.0,0.0,1.0));
    rTriBackWall2->setVertexNormal(2, Vector(0.0,0.0,1.0));

    lMiddleOfFace.setX((lZero.x()+lThree.x()+lFour.x()+lSeven.x())*0.25);
    lMiddleOfFace.setY((lZero.y()+lThree.y()+lFour.y()+lSeven.y())*0.25);
    lMiddleOfFace.setZ((lZero.z()+lThree.z()+lFour.z()+lSeven.z())*0.25);

    Phong* rBRDFBackWall = new Phong(pParam.diffusion,pParam.specular,3);
    rBRDFBackWall->setAmbient(Color(0.1f));

    if (pParam.wallBackTexturePath.compare("no_texture"))
    {
        CubeMap* rCubeMapBackWall = new CubeMap(lMiddleOfFace, max(pParam.dimensions.x(), pParam.dimensions.y()));

        rCubeMapBackWall->addImage(CubeMap::BACK, pParam.wallBackTexturePath);
        rCubeMapBackWall->setLink(CubeMap::FRONT, 0);
        rCubeMapBackWall->setLink(CubeMap::UP, 0);
        rCubeMapBackWall->setLink(CubeMap::DOWN, 0);
        rCubeMapBackWall->setLink(CubeMap::LEFT, 0);
        rCubeMapBackWall->setLink(CubeMap::RIGHT, 0);

        rCubeMapBackWall->setInterpolationMethod(Image::Interpolation::LINEAR);

        pScene->add(rCubeMapBackWall);

        rBRDFBackWall->setCubeMap(rCubeMapBackWall);
    }

    Shader* rShaderBackWall = new Shader(rBRDFBackWall,pParam.reflectionCoeff,pParam.refractionCoeff,pScene);
    rShaderBackWall->setReflectionCountMax(pParam.maxReflection);

    rTriBackWall1->setShader(rShaderBackWall);
    rTriBackWall2->setShader(rShaderBackWall);

    pScene->add(rTriBackWall1);
    pScene->add(rTriBackWall2);
    pScene->add(rBRDFBackWall, string("brdf of the triangles of the back wall"));
    pScene->add(rShaderBackWall, string("shader of the triangles of the back wall"));

    // Create right wall
    Triangle* rTriRightWall1 = new Triangle(lThree, lTwo, lSix);
    Triangle* rTriRightWall2 = new Triangle(lThree, lSix, lSeven);

    rTriRightWall1->setVertexNormal(0, Vector(-1.0,0.0,0.0));
    rTriRightWall1->setVertexNormal(1, Vector(-1.0,0.0,0.0));
    rTriRightWall1->setVertexNormal(2, Vector(-1.0,0.0,0.0));

    rTriRightWall2->setVertexNormal(0, Vector(-1.0,0.0,0.0));
    rTriRightWall2->setVertexNormal(1, Vector(-1.0,0.0,0.0));
    rTriRightWall2->setVertexNormal(2, Vector(-1.0,0.0,0.0));

    lMiddleOfFace.setX((lTwo.x()+lThree.x()+lSix.x()+lSeven.x())*0.25);
    lMiddleOfFace.setY((lTwo.y()+lThree.y()+lSix.y()+lSeven.y())*0.25);
    lMiddleOfFace.setZ((lTwo.z()+lThree.z()+lSix.z()+lSeven.z())*0.25);

    Phong* rBRDFRightWall = new Phong(pParam.diffusion,pParam.specular,3);
    rBRDFRightWall->setAmbient(Color(0.1f));

    if (pParam.wallRightTexturePath.compare("no_texture"))
    {
        CubeMap* rCubeMapRightWall = new CubeMap(lMiddleOfFace, max(pParam.dimensions.y(), pParam.dimensions.z()));

        rCubeMapRightWall->addImage(CubeMap::BACK, pParam.wallRightTexturePath);
        rCubeMapRightWall->setLink(CubeMap::FRONT, 0);
        rCubeMapRightWall->setLink(CubeMap::UP, 0);
        rCubeMapRightWall->setLink(CubeMap::DOWN, 0);
        rCubeMapRightWall->setLink(CubeMap::LEFT, 0);
        rCubeMapRightWall->setLink(CubeMap::RIGHT, 0);

        rCubeMapRightWall->setInterpolationMethod(Image::Interpolation::LINEAR);

        pScene->add(rCubeMapRightWall);

        rBRDFRightWall->setCubeMap(rCubeMapRightWall);
    }

    Shader* rShaderRightWall = new Shader(rBRDFRightWall,pParam.reflectionCoeff,pParam.refractionCoeff,pScene);
    rShaderRightWall->setReflectionCountMax(pParam.maxReflection);

    rTriRightWall1->setShader(rShaderRightWall);
    rTriRightWall2->setShader(rShaderRightWall);

    pScene->add(rTriRightWall1);
    pScene->add(rTriRightWall2);
    pScene->add(rBRDFRightWall, string("brdf of the triangles of the right wall"));
    pScene->add(rShaderRightWall, string("shader of the triangles of the right wall"));

    // Create roof
    Triangle* rTriCeiling1 = new Triangle(lFour, lFive, lSix);
    Triangle* rTriCeiling2 = new Triangle(lFour, lSix, lSeven);

    rTriCeiling1->setVertexNormal(0, Vector(0.0,-1.0,0.0));
    rTriCeiling1->setVertexNormal(1, Vector(0.0,-1.0,0.0));
    rTriCeiling1->setVertexNormal(2, Vector(0.0,-1.0,0.0));

    rTriCeiling2->setVertexNormal(0, Vector(0.0,-1.0,0.0));
    rTriCeiling2->setVertexNormal(1, Vector(0.0,-1.0,0.0));
    rTriCeiling2->setVertexNormal(2, Vector(0.0,-1.0,0.0));

    lMiddleOfFace.setX((lFour.x()+lFive.x()+lSix.x()+lSeven.x())*0.25);
    lMiddleOfFace.setY((lFour.y()+lFive.y()+lSix.y()+lSeven.y())*0.25);
    lMiddleOfFace.setZ((lFour.z()+lFive.z()+lSix.z()+lSeven.z())*0.25);

    Phong* rBRDFCeiling = new Phong(pParam.diffusion,pParam.specular,13);
    rBRDFCeiling->setAmbient(Color(0.1f));

    if (pParam.ceilingTexturePath.compare("no_texture"))
    {
        CubeMap* rCubeMapCeiling = new CubeMap(lMiddleOfFace, max(pParam.dimensions.x(), pParam.dimensions.z()));

        rCubeMapCeiling->addImage(CubeMap::DOWN, pParam.ceilingTexturePath);
        rCubeMapCeiling->setLink(CubeMap::FRONT, 0);
        rCubeMapCeiling->setLink(CubeMap::UP, 0);
        rCubeMapCeiling->setLink(CubeMap::BACK, 0);
        rCubeMapCeiling->setLink(CubeMap::LEFT, 0);
        rCubeMapCeiling->setLink(CubeMap::RIGHT, 0);

        rCubeMapCeiling->setInterpolationMethod(Image::Interpolation::LINEAR);

        pScene->add(rCubeMapCeiling);

        rBRDFCeiling->setCubeMap(rCubeMapCeiling);
    }


    Shader* rShaderCeiling = new Shader(rBRDFCeiling,pParam.reflectionCoeff,pParam.refractionCoeff,pScene);
    rShaderCeiling->setReflectionCountMax(pParam.maxReflection);

    rTriCeiling1->setShader(rShaderCeiling);
    rTriCeiling2->setShader(rShaderCeiling);

    pScene->add(rTriCeiling1);
    pScene->add(rTriCeiling2);
    pScene->add(rBRDFCeiling, string("brdf of the triangles of the roof"));
    pScene->add(rShaderCeiling, string("shader of the triangles of the roof"));

}

