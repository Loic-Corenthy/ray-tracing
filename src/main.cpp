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
    #include <windows.h>
    #include <GL\gl.h>
    #include <GL\glu.h>
    #include <GL\glut.h>
    #include <regex>
    #include <string>
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

struct SceneParameters
{
    unsigned int sceneIndex   = 0;
    unsigned int windowWidth  = 800u;
    unsigned int windowHeight = 600u;
    unsigned int windowXPos   = 0u;
    unsigned int windowYPos   = 0u;
};

SceneParameters processArguments(int argc, char** argv);

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
    const auto sceneParemeters = processArguments(argc, argv);

    if (15 < sceneParemeters.sceneIndex)
    {
        cerr << "Error: the parameter to select the scene must be between 0 and 15" << endl;
        return EXIT_FAILURE;
    }

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

    // Init window position and size,
    glutInitWindowPosition(static_cast<int>(sceneParemeters.windowXPos), static_cast<int>(sceneParemeters.windowYPos));
    glutInitWindowSize(static_cast<int>(sceneParemeters.windowWidth), static_cast<int>(sceneParemeters.windowHeight));

    glutCreateWindow("Ray tracing window");

    shared_ptr<Scene> scene = make_shared<Scene>();

    // Setup the scene
    switch (sceneParemeters.sceneIndex)
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
    Renderer::setScene(scene, sceneParemeters.windowWidth, sceneParemeters.windowHeight);

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

#ifdef WIN32
SceneParameters processArguments(int argc, char** argv)
{
    SceneParameters parameters;

    if (argc != 2)
    {
        cerr << "This version of processArguments expect all the arguments provided to the executable to be held in argv[1]" << '\n';
        return parameters;
    }

    auto allArguments = std::string(argv[1]);

    const unsigned int parameterCount                    = 5u;
    const std::regex   allParameterRegex[parameterCount] = { std::regex(R"(\s*--scene\s+([0-9]+))"),
                                                           std::regex(R"(\s*--width\s+([0-9]+))"),
                                                           std::regex(R"(\s*--height\s+([0-9]+))"),
                                                           std::regex(R"(\s*--xpos\s+([0-9]+))"),
                                                           std::regex(R"(\s*--ypos\s+([0-9]+))") };

    for (unsigned int i = 0; i < parameterCount; ++i)
    {
        std::smatch baseMatch;
        if (std::regex_search(allArguments, baseMatch, allParameterRegex[i]))
        {
            // The first sub_match is the whole string; the next sub_match is the first parenthesized expression.
            if (baseMatch.size() == 2)
            {
                switch (i)
                {
                    case 0:
                        parameters.sceneIndex = static_cast<unsigned int>(stoi(baseMatch[1].str()));
                        break;

                    case 1:
                        parameters.windowWidth = static_cast<unsigned int>(stoi(baseMatch[1].str()));
                        break;

                    case 2:
                        parameters.windowHeight = static_cast<unsigned int>(stoi(baseMatch[1].str()));
                        break;

                    case 3:
                        parameters.windowXPos = static_cast<unsigned int>(stoi(baseMatch[1].str()));
                        break;

                    case 4:
                        parameters.windowYPos = static_cast<unsigned int>(stoi(baseMatch[1].str()));
                        break;
                }
            }
        }
    }

    if (allArguments.find("--supersampling") != std::string::npos)
    {
        cout << "Super sampling on" << '\n';
        Renderer::setSuperSampling(true);
    }

    return parameters;
}
#else
SceneParameters processArguments(int argc, char** argv)
{
    SceneParameters parameters;

    for (int i = 1; i < argc; ++i)
    {
        if (strcmp(argv[i], "--scene") == 0)
        {
            parameters.sceneIndex = static_cast<unsigned int>(atoi(argv[i + 1]));
            cout << "Scene index " << parameters.sceneIndex << "\n";
        }
        else if (strcmp(argv[i], "--supersampling") == 0)
        {
            cout << "Super sampling on" << '\n';
            Renderer::setSuperSampling(true);
        }
        else if (strcmp(argv[i], "--width ") == 0)
        {
            parameters.windowWidth = static_cast<unsigned int>(atoi(argv[i + 1]));
        }
        else if (strcmp(argv[i], "--height") == 0)
        {
            parameters.windowHeight = static_cast<unsigned int>(atoi(argv[i + 1]));
        }
        else if (strcmp(argv[i], "--xpos") == 0)
        {
            parameters.windowXPos = static_cast<unsigned int>(atoi(argv[i + 1]));
        }
        else if (strcmp(argv[i], "--ypos") == 0)
        {
            parameters.windowYPos = static_cast<unsigned int>(atoi(argv[i + 1]));
        }
    }

    return parameters;
}
#endif
