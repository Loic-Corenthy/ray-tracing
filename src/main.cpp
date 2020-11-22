//===============================================================================================//
/*!
 *  \file      main.cpp
 *  \author    Loïc Corenthy
 *  \version   1.0
 *  \date      06/05/2012
 *  \copyright (c) 2012 Loïc Corenthy. All rights reserved.
 */
//===============================================================================================//

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
#include "Renderer.hpp"

using LCNS::Buffer;
using LCNS::Renderer;
using LCNS::Scene;
using std::cerr;
using std::cout;
using std::endl;

int main(int argc, char* argv[])
{
    if (argc < 2)
    {
        cerr << "ERROR: Please call the executable with a number between 0 and 15 as scene parameter. \nFor example: " << argv[0] << " --scene 3\n\n";
        cerr << "Supersampling is optional. \nFor example: " << argv[0] << " --scene 5 --supersampling\n\n";
        cerr << "Window dimensions parameters are optional. \nFor example: " << argv[0] << " --scene 5 --width 800 --height 600\n\n";
        cerr << "Window initial position parameters are optional. \nFor example: " << argv[0] << " --scene 5 --xpos 200 --ypos 100" << endl;
        return EXIT_FAILURE;
    }

    // Parameters to the executable
    unsigned int sceneIndex   = 0;
    unsigned int windowWidth  = 800u;
    unsigned int windowHeight = 600u;
    unsigned int windowXPos   = 0u;
    unsigned int windowYPos   = 0u;

    for (unsigned int i = 1; i < argc; ++i)
    {
        if (strcmp(argv[i], "--scene") == 0)
        {
            sceneIndex = atoi(argv[i + 1]);
        }
        else if (strcmp(argv[i], "--supersampling") == 0)
        {
            cout << "Super sampling on" << '\n';
            Renderer::setSuperSampling(true);
        }
        else if (strcmp(argv[i], "--width ") == 0)
        {
            windowWidth = atoi(argv[i + 1]);
        }
        else if (strcmp(argv[i], "--height") == 0)
        {
            windowHeight = atoi(argv[i + 1]);
        }
        else if (strcmp(argv[i], "--xpos") == 0)
        {
            windowXPos = atoi(argv[i + 1]);
        }
        else if (strcmp(argv[i], "--ypos") == 0)
        {
            windowYPos = atoi(argv[i + 1]);
        }
    }


    if (sceneIndex < 0 || 15 < sceneIndex)
    {
        cerr << "Error: the parameter to select the scene must be between 0 and 15" << endl;
        return EXIT_FAILURE;
    }


    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

    // Init window position and size,
    glutInitWindowPosition(windowXPos, windowYPos);
    glutInitWindowSize(windowWidth, windowHeight);

    glutCreateWindow("Ray tracing window");

    Scene* scene = new Scene;

    // Setup the scene
    switch (sceneIndex)
    {
        case 0:
            createTestScene(scene);
            break;
        case 1:
            createScene01(scene);
            break;
        case 2:
            createScene02(scene);
            break;
        case 3:
            createScene03(scene);
            break;
        case 4:
            createScene04(scene);
            break;
        case 5:
            createScene04bis(scene);
            break;
        case 6:
            createScene05(scene);
            break;
        case 7:
            createScene06(scene);
            break;
        case 8:
            createScene07(scene);
            break;
        case 9:
            createScene08(scene);
            break;
        case 10:
            createScene09(scene);
            break;
        case 11:
            createScene10(scene);
            break;
        case 12:
            createScene11(scene);
            break;
        case 13:
            createScene12(scene);
            break;
        case 14:
            createScene13(scene);
            break;
        case 15:
            createScene14(scene);
            break;
        default:
            assert(false && "We should never reach here");
            break;
    }

    // Send the scene to the renderer
    Renderer::setScene(scene, windowWidth, windowHeight);

    // Render the scene
    Renderer::render();

    auto display = []() {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glMatrixMode(GL_MODELVIEW);
        glClear(GL_COLOR_BUFFER_BIT);

        const Buffer& buffer = Renderer::getBuffer();
        glDrawPixels(buffer.width(), buffer.height(), GL_RGB, GL_UNSIGNED_BYTE, buffer.allPixels());

        glutSwapBuffers();
    };

    // Display loop
    glutDisplayFunc(display);

    delete scene;

    glutMainLoop();

    cout << "Application exited succesfully" << endl;
    return EXIT_SUCCESS;
}
