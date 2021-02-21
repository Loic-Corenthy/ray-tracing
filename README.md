# Ray Tracing

Code for a project that I worked on during my master degree in 2012.

# Cloning the repo
The project is setup to use vcpkg as a submodule to manage external dependecies. To have access to vcpkg directly, clone the repository with the recursive option
git clone --recursive https://github.com/Loic-Corenthy/ray-tracing.git

## macOS
To build the code on macOS for Xcode, simply use
mkdir build
cd build
cmake -G "Xcode" -DCMAKE_BUILD_TYPE=Release ..

When building the project from Xcode, select "Release" as build configuration to match the above mentioned build type. This is necessary to have the resource directory copied in the correct folder to the executable to have access to it.
