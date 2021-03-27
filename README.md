# Ray Tracing

![Render scene 14 - inside a room with a sphere refracting the outside above a table and other 3D objects around. There a "mirror" on the right wall](https://github.com/Loic-Corenthy/ray-tracing/blob/main/rendered%20test%20scenes/scene%2014%20-%20single%20thread%20-%202773_3%20seconds.png)

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
To build the code on Windows for Visual Studio, simply use
```
mkdir build
cd build
cmake -G "Visual Studio 16 2019" -DCMAKE_BUILD_TYPE=Release ..
```

When building the project from Visual Studio, select "Release" as build configuration to match the above mentioned build type. This is necessary to have the resource directory copied in the correct folder to the executable to have access to it.

# Scenes and speed comparision
