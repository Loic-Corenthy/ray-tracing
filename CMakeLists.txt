cmake_minimum_required( VERSION 3.15 )

# set the project name, version and language
project( ray-tracing VERSION 1.1 LANGUAGES CXX )

set( CMAKE_CXX_STANDARD 17 )
set( CMAKE_CXX_STANDARD_REQUIRED ON )
set( CMAKE_CXX_EXTENSIONS OFF )


file( GLOB LOCAL_HEADER_FILES ${CMAKE_SOURCE_DIR}/src/*.hpp )
file( GLOB LOCAL_SOURCE_FILES ${CMAKE_SOURCE_DIR}/src/*.cpp )

add_executable( ray-tracing ${LOCAL_SOURCE_FILES} )
