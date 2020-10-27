//
//  main.cpp
//  RayTracing
//
//  Created by Loïc CORENTHY on 6/5/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include <OpenGL/gl.hpp>
#include <OpenGL/glu.hpp>
#include <GLUT/glut.hpp>

#include "CreateScenes.hpp"

#define WIDTH  600
#define HEIGHT 600


using namespace MatouMalin;
using namespace std;

// Create renderer with scene and size of window parameters
Renderer myRenderer(nullptr, WIDTH, HEIGHT);

// GLUT callbacks: Pass the buffer to glut to be displayed
void display(void);

int main(int argc,char* argv[])
{
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    
	// Init window position and size,
	glutInitWindowPosition(0,0);
	glutInitWindowSize(WIDTH,HEIGHT);
    
    glutCreateWindow("Ray tracing window");
    
    Scene* lScene = new Scene;
    
    
    createTestScene(lScene);
//    createScene01(lScene);
//    createScene02(lScene);
//    createScene03(lScene);
//    createScene04(lScene);
//    createScene04bis(lScene);
//    createScene05(lScene);
//    createScene06(lScene);
//    createScene07(lScene);
//    createScene08(lScene);
//    createScene09(lScene);
//    createScene10(lScene);
//    createScene11(lScene);
//    createScene12(lScene);
//    createScene13(lScene);
//    createScene14(lScene);
    
	myRenderer.setScene(lScene);
//    myRenderer.setSuperSampling(true);
	myRenderer.render();
    
	// Display loop
	glutDisplayFunc(display);
  
    delete lScene;
    
	glutMainLoop();
    
    return 0;
}

void display(void)
{
	const Buffer & lBuffer = myRenderer.getBuffer();
	const unsigned char* lPixels = lBuffer.allPixels();
    
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
	glMatrixMode(GL_MODELVIEW);
	glClear(GL_COLOR_BUFFER_BIT);
    
	glDrawPixels(WIDTH,HEIGHT,GL_RGB,GL_UNSIGNED_BYTE,lPixels);
    
	glutSwapBuffers();
}




