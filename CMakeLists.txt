cmake_minimum_required(VERSION 3.15)

# ==================================
# Project name, version and language
# ==================================
project(ray-tracing VERSION 1.1 LANGUAGES CXX)


# ===========
# C++ version
# ===========
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)


# ======================
# Project extra settings
# ======================
include(cmake/StandardProjectSettings.cmake)


# ==========================
# Configure project warnings
# ==========================
include(cmake/CompilerWarnings.cmake)
add_library(project_warnings INTERFACE)
set_project_warnings(project_warnings)


# =======
# Doxygen
# =======
include(cmake/Doxygen.cmake)
enable_doxygen()


# ================================
# Third party libraries with Conan
# ================================
include(cmake/Conan.cmake)
run_conan("fmt/6.1.2")


# ===========================
# Other third party libraries
# ===========================
find_package(OpenImageIO REQUIRED)
if(OpenImageIO_FOUND)
    message(STATUS "Found Open Image IO " ${OpenImageIO_VERSION})
    # For some reason, the following variables are not defined properly: ${OPENIMAGEIO_LIBRARY} ${OPENIMAGEIO_LIBRARIES}
    # You have to use OpenImageIO::OpenImageIO to link
endif()

find_package(OpenGL REQUIRED)
if(OpenGL_FOUND)
    message(STATUS "Found OpenGL: " ${OPENGL_opengl_LIBRARY})
endif()

find_package(GLUT REQUIRED)
if(GLUT_FOUND)
    message(STATUS "Found GLUT: " ${GLUT_LIBRARY})
endif()

# =======================
# Header and source files
# =======================
file(GLOB LOCAL_HEADER_FILES ${CMAKE_SOURCE_DIR}/src/*.hpp)
file(GLOB LOCAL_SOURCE_FILES ${CMAKE_SOURCE_DIR}/src/*.cpp)


# ====================
# Configuration per OS
# ====================
if(UNIX AND NOT APPLE)
    add_executable(${CMAKE_PROJECT_NAME} ${LOCAL_SOURCE_FILES})

    # Set include directories for source code and external libraries
    target_include_directories (${CMAKE_PROJECT_NAME} PUBLIC "/usr/include/" ${CMAKE_SOURCE_DIR}/src  ${CMAKE_BINARY_DIR}/conanbuildinfo.cmake ${OpenImageIO_INCLUDE_DIR} ${OPENGL_INCLUDE_DIR} ${GLUT_INCLUDE_DIR})
    conan_basic_setup(${CMAKE_PROJECT_NAME})

    # Specify external libraries needed for this project
    target_link_libraries (${CMAKE_PROJECT_NAME} PRIVATE project_warnings CONAN_PKG::fmt OpenImageIO::OpenImageIO ${OPENGL_opengl_LIBRARY} ${OPENGL_glx_LIBRARY} ${OPENGL_glu_LIBRARY} ${OPENGL_glx_LIBRARY} ${GLUT_LIBRARY})

	# Copy resources directory
	ADD_CUSTOM_COMMAND (TARGET ${CMAKE_PROJECT_NAME} POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/resources "${CMAKE_CURRENT_BINARY_DIR}/resources/")
	message (STATUS "Copied resources from " ${CMAKE_SOURCE_DIR}/resources " to " ${CMAKE_CURRENT_BINARY_DIR}/resources/)
endif()
