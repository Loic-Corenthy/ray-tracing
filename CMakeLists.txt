cmake_minimum_required(VERSION 3.15)


# ===========================
# Setup vcpkg
# ===========================
message(STATUS "Setting up vcpkg")

set(VCPKG_INSTALLED OFF CACHE BOOL "Define if vcpkg is already installed")

if(NOT ${VCPKG_INSTALLED})
    if(UNIX)
        execute_process(COMMAND ./bootstrap-vcpkg.sh -disableMetrics
                        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/vcpkg/
                        RESULT_VARIABLE GIT_SUBMOD_RESULT)
    else(WIN32)
        execute_process(COMMAND cmd /c "bootstrap-vcpkg.bat -disableMetrics"
                        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/vcpkg/
                        RESULT_VARIABLE GIT_SUBMOD_RESULT)
    endif()

    if(NOT GIT_SUBMOD_RESULT EQUAL "0")
        message(FATAL_ERROR "Unable to set up vcpkg")
    else()
        message(STATUS "VCPKG configured. Toolchain file set to script in build system.")
        set(VCPKG_INSTALLED ON CACHE BOOL "Define if vcpkg is already installed" FORCE)
        set(CMAKE_TOOLCHAIN_FILE ${CMAKE_SOURCE_DIR}/vcpkg/scripts/buildsystems/vcpkg.cmake)
    endif()  
endif()


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


# ===========================
# Other third party libraries
# ===========================
if(UNIX)
    find_package(OpenImageIO)
    if(OpenImageIO_FOUND)
        message(STATUS "Found Open Image IO " ${OpenImageIO_VERSION})
        # For some reason, the following variables are not defined properly: ${OPENIMAGEIO_LIBRARY} ${OPENIMAGEIO_LIBRARIES}
        # You have to use OpenImageIO::OpenImageIO to link
    else()
        execute_process(COMMAND ./vcpkg install openimageio
                        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/vcpkg/
                        RESULT_VARIABLE OPEN_IMAGE_IO_FROM_VCPKG)

        if(NOT OPEN_IMAGE_IO_FROM_VCPKG EQUAL "0")
            message(FATAL_ERROR "Unable to download OpenImageIO")
        endif()

        find_package(OpenImageIOConfig REQUIRED)
    endif()

    find_package(OpenGL REQUIRED)
    if(OpenGL_FOUND)
        message(STATUS "Found OpenGL: " ${OPENGL_opengl_LIBRARY})
    endif()

    find_package(GLUT REQUIRED)
    if(GLUT_FOUND)
        message(STATUS "Found GLUT: " ${GLUT_LIBRARY})
    endif()
else(WIN32)
    # Configure openimageio
    execute_process(COMMAND cmd /c "vcpkg.exe install openimageio openimageio:x64-windows"
                    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/vcpkg/
                    RESULT_VARIABLE OPEN_IMAGE_IO_FROM_VCPKG)

    if(NOT OPEN_IMAGE_IO_FROM_VCPKG EQUAL "0")
        message(FATAL_ERROR "Unable to download OpenImageIO")
    endif()

    find_package(OpenImageIO REQUIRED)

    # Configure OpenGL
    find_package(OpenGL REQUIRED)
    if(OpenGL_FOUND)
        message(STATUS "Found OpenGL: " ${OPENGL_opengl_LIBRARY})
    endif()

    # Configure freeglut
    execute_process(COMMAND cmd /c "vcpkg.exe install freeglut freeglut:x64-windows"
                    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/vcpkg/
                    RESULT_VARIABLE FREEGLUT_FROM_VCPKG)

    if(NOT FREEGLUT_FROM_VCPKG EQUAL "0")
        message(FATAL_ERROR "Unable to download freeglut")
    endif()

    find_package(GLUT REQUIRED)
    if(GLUT_FOUND)
        message(STATUS "Found GLUT: " ${GLUT_LIBRARY})
    endif()
endif()


# =======================
# Header and source files
# =======================
file(GLOB LOCAL_HEADER_FILES ${CMAKE_SOURCE_DIR}/src/*.hpp)
file(GLOB LOCAL_SOURCE_FILES ${CMAKE_SOURCE_DIR}/src/*.cpp)


# ====================
# Configuration per OS
# ====================
set(OUTPUT_NAME "RayTracing")

if(UNIX AND NOT APPLE)
    add_executable(${OUTPUT_NAME} ${LOCAL_SOURCE_FILES})

    # Set include directories for source code and external libraries
    target_include_directories(${OUTPUT_NAME} PUBLIC "/usr/include/" ${CMAKE_SOURCE_DIR}/src  ${CMAKE_BINARY_DIR}/conanbuildinfo.cmake ${OpenImageIO_INCLUDE_DIR} ${OPENGL_INCLUDE_DIR} ${GLUT_INCLUDE_DIR})

    # Specify external libraries needed for this project
    target_link_libraries(${OUTPUT_NAME} PRIVATE project_warnings OpenImageIO::OpenImageIO ${OPENGL_opengl_LIBRARY} ${OPENGL_glx_LIBRARY} ${OPENGL_glu_LIBRARY} ${OPENGL_glx_LIBRARY} ${GLUT_LIBRARY})

	# Copy resources directory
	add_custom_command (TARGET ${OUTPUT_NAME} POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/resources "${CMAKE_CURRENT_BINARY_DIR}/resources/")
	message (STATUS "Post build, resources will be copied from " ${CMAKE_SOURCE_DIR}/resources " to " ${CMAKE_CURRENT_BINARY_DIR}/resources/)

elseif(APPLE)
    add_executable(${OUTPUT_NAME} ${LOCAL_SOURCE_FILES})

    # Set include directories for source code and external libraries
	target_include_directories(${OUTPUT_NAME} PUBLIC "/usr/include/" ${CMAKE_SOURCE_DIR}/src  ${CMAKE_BINARY_DIR}/conanbuildinfo.cmake ${OpenImageIO_INCLUDE_DIR} ${OPENGL_INCLUDE_DIR}/Headers ${GLUT_INCLUDE_DIR})

    # Specify external libraries needed for this project
    target_link_libraries(${OUTPUT_NAME} PRIVATE project_warnings OpenImageIO::OpenImageIO ${OPENGL_opengl_LIBRARY} ${OPENGL_glx_LIBRARY} ${OPENGL_glu_LIBRARY} ${OPENGL_glx_LIBRARY} ${GLUT_LIBRARY})

	# Copy resources directory
	add_custom_command(TARGET ${OUTPUT_NAME} POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/resources "${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_BUILD_TYPE}/resources/")
	message(STATUS "Post build, resources will be copied from " ${CMAKE_SOURCE_DIR}/resources " to " ${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_BUILD_TYPE}/resources/)

elseif(WIN32)
    add_executable(${OUTPUT_NAME} ${LOCAL_SOURCE_FILES})

    # Define NOMINMAX to be able to use max function in std::numeric_limits
    target_compile_definitions(${OUTPUT_NAME} PUBLIC NOMINMAX)

    # Set include directories for source code and external libraries
    target_include_directories(${OUTPUT_NAME} PUBLIC "/usr/include/" ${CMAKE_SOURCE_DIR}/src  ${CMAKE_BINARY_DIR}/conanbuildinfo.cmake ${OpenImageIO_INCLUDE_DIR} ${OPENGL_INCLUDE_DIR} ${GLUT_INCLUDE_DIR})

    # Specify external libraries needed for this project
    target_link_libraries(${OUTPUT_NAME} PRIVATE project_warnings OpenImageIO::OpenImageIO ${OPENGL_opengl_LIBRARY} ${OPENGL_glx_LIBRARY} ${OPENGL_glu_LIBRARY} ${OPENGL_glx_LIBRARY} GLUT::GLUT)

    # Copy resources directory
    add_custom_command (TARGET ${OUTPUT_NAME} POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/resources "${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_BUILD_TYPE}/resources/")
    message (STATUS "Post build, resources will be copied from " ${CMAKE_SOURCE_DIR}/resources " to " ${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_BUILD_TYPE}/resources/)
endif()
