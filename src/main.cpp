//
//  main.cpp
//  RayTracing
//
//  Created by Loïc CORENTHY on 6/5/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifdef __linux__
    #include <GL/gl.h>
    #include <GL/glu.h>
    #include <GL/glut.h>
#elif __APPLE__
    #include <OpenGL/gl.hpp>
    #include <OpenGL/glu.hpp>
    #include <GLUT/glut.hpp>
#elif _WIN32
    // /*! \todo Add includes for Windows */
#endif

#include "CreateScenes.hpp"

using namespace MatouMalin;
using namespace std;

constexpr const auto width  = 600u;
constexpr const auto height = 600u;

// Create renderer with scene and size of window parameters
Renderer myRenderer(nullptr, width, height);

// GLUT callbacks: Pass the buffer to glut to be displayed
void display(void)
{
	const Buffer & lBuffer = myRenderer.getBuffer();
	const unsigned char* lPixels = lBuffer.allPixels();

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glClear(GL_COLOR_BUFFER_BIT);

	glDrawPixels(width,height,GL_RGB,GL_UNSIGNED_BYTE,lPixels);

	glutSwapBuffers();
}

int main(int argc,char* argv[])
{
    if (argc < 2)
    {
        cerr << "ERROR: Please call the executable with a number between 0 and 15 as parameter" << '\n';
        cerr << "For example: " << argv[0] << " 3" << '\n';
        cerr << "Supersampling is optional. For example: " << argv[0] << " 5 --supersampling" << endl;
        return EXIT_FAILURE;
    }

    const auto sceneIndex = atoi(argv[1]);

    if (sceneIndex < 0 || 15 < sceneIndex)
    {
        cerr << "Error: the parameter to select the scene must be between 0 and 15" << endl;
        return EXIT_FAILURE;
    }

	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

	// Init window position and size,
	glutInitWindowPosition(0,0);
	glutInitWindowSize(width,height);

    glutCreateWindow("Ray tracing window");

    Scene* lScene = new Scene;

    // Setup the scene
    switch (sceneIndex)
    {
        case  0: createTestScene(lScene);   break;
        case  1: createScene01(lScene);     break;
        case  2: createScene02(lScene);     break;
        case  3: createScene03(lScene);     break;
        case  4: createScene04(lScene);     break;
        case  5: createScene04bis(lScene);  break;
        case  6: createScene05(lScene);     break;
        case  7: createScene06(lScene);     break;
        case  8: createScene07(lScene);     break;
        case  9: createScene08(lScene);     break;
        case 10: createScene09(lScene);     break;
        case 11: createScene10(lScene);     break;
        case 12: createScene11(lScene);     break;
        case 13: createScene12(lScene);     break;
        case 14: createScene13(lScene);     break;
        case 15: createScene14(lScene);     break;
        default: assert(false && "We should never reach here"); break;
    }

    // Send the scene to the renderer
	myRenderer.setScene(lScene);

    if (argc == 3 && strcmp(argv[2], "--supersampling") == 0)
    {
        cout << "Super sampling on" << '\n';
        myRenderer.setSuperSampling(true);
    }

    // Render the scene
	myRenderer.render();

	// Display loop
	glutDisplayFunc(display);

    delete lScene;

	glutMainLoop();

    cout << "Application exited succesfully" << endl;
    return EXIT_SUCCESS;
}

