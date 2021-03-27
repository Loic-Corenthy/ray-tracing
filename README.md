# Ray Tracing

![Render scene 11 - 2 spheres and a floor with multiple point lights, of different colours](https://github.com/Loic-Corenthy/ray-tracing/blob/main/rendered%20test%20scenes/scene%2011%20-%20single%20thread%20-%206_78263%20seconds.png)

# Overview

This repository contains the code for a ray-tracing project that I worked on during my master degree in 2012. Since uploading it to github, the idea is to
1. Modernize the C++ used in the source code moving from early C++11 to C++17
2. Integrate a package manager to make it easier to handle third party libraries.
3. Have a play with multi-threading to make the render faster

# Cloning the repo
The project is setup to use vcpkg as a submodule to manage external dependecies. To have access to vcpkg directly, clone the repository with the recursive option
```
git clone --recursive https://github.com/Loic-Corenthy/ray-tracing.git
```

# Build

## Linux
To build the code on a Unix system, simply use
```
mkdir build
cd build
cmake ..
make
```

## macOS
To build the code on macOS for Xcode, simply use
```
mkdir build
cd build
cmake -G "Xcode" -DCMAKE_BUILD_TYPE=Release ..
```

When building the project from Xcode, select "Release" as build configuration to match the above mentioned build type. This is necessary to have the resource directory copied in the correct folder to the executable to have access to it.

## Windows
To build the code on Windows for Visual Studio (2019 in this case), simply use
```
mkdir build
cd build
cmake -G "Visual Studio 16 2019" -DCMAKE_BUILD_TYPE=Release ..
```

When building the project from Visual Studio, select "Release" as build configuration to match the above mentioned build type. This is necessary to have the resource directory copied in the correct folder to the executable to have access to it.

# Executable
The executable is expecting some parameters to be able to run. The only **mandatory** parameter is the scene number, between 0 and 15.\
For example: ```./RayTracing --scene 3```

The other **optional** parameters are:
- *Supersampling*\
For example: ```./RayTracing --scene 5 --supersampling```

- *Multi-threading*\
For example: ```./RayTracing --scene 5 --multithreading```

- *Window dimensions*\
For example: .```/RayTracing --scene 5 --width 800 --height 600```

- *Window initial position*\
For example: ```./RayTracing --scene 5 --xpos 200 --ypos 100```


# Scenes and speed comparision
This code is **not** intented to production ready. There are 15 test scenes defined in CreateScenes.cpp to illustrate what the engine can do. Ideally, it should be possible to load a scene from a file, I might add this functionality one day if I have time :)

I took advantage of uploading this code to github and "modernizing it" to also have a play with multithreading. Please see the wiki pages for more details. 
