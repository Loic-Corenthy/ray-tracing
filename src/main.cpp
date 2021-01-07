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
    #include <gl.h>
    #include <glu.h>
    #include <glut.h>
#elif _WIN32
// /*! \todo Add includes for Windows */
#endif

#include <memory>

#include "CreateScenes.hpp"
#include "Renderer.hpp"
#include "Scene.hpp"

using std::cerr;
using std::cout;
using std::endl;
using std::make_shared;
using std::shared_ptr;

using LCNS::Buffer;
using LCNS::Renderer;
using LCNS::Scene;

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

    for (int i = 1; i < argc; ++i)
    {
        if (strcmp(argv[i], "--scene") == 0)
        {
            sceneIndex = static_cast<unsigned int>(atoi(argv[i + 1]));
        }
        else if (strcmp(argv[i], "--supersampling") == 0)
        {
            cout << "Super sampling on" << '\n';
            Renderer::setSuperSampling(true);
        }
        else if (strcmp(argv[i], "--width ") == 0)
        {
            windowWidth = static_cast<unsigned int>(atoi(argv[i + 1]));
        }
        else if (strcmp(argv[i], "--height") == 0)
        {
            windowHeight = static_cast<unsigned int>(atoi(argv[i + 1]));
        }
        else if (strcmp(argv[i], "--xpos") == 0)
        {
            windowXPos = static_cast<unsigned int>(atoi(argv[i + 1]));
        }
        else if (strcmp(argv[i], "--ypos") == 0)
        {
            windowYPos = static_cast<unsigned int>(atoi(argv[i + 1]));
        }
    }


    if (15 < sceneIndex)
    {
        cerr << "Error: the parameter to select the scene must be between 0 and 15" << endl;
        return EXIT_FAILURE;
    }


    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

    // Init window position and size,
    glutInitWindowPosition(static_cast<int>(windowXPos), static_cast<int>(windowYPos));
    glutInitWindowSize(static_cast<int>(windowWidth), static_cast<int>(windowHeight));

    glutCreateWindow("Ray tracing window");

    shared_ptr<Scene> scene = make_shared<Scene>();

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
        glDrawPixels(static_cast<GLsizei>(buffer.width()), static_cast<GLsizei>(buffer.height()), GL_RGB, GL_UNSIGNED_BYTE, buffer.allPixels().get());

        glutSwapBuffers();
    };

    // Display loop
    glutDisplayFunc(display);

    glutMainLoop();

    cout << "Application exited successfully" << endl;
    return EXIT_SUCCESS;
}
