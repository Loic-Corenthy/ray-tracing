macro (run_conan)

    message ("")
    message (STATUS "Get external packages")
    message (STATUS "---------------------")

    # Download automatically, you can also just copy the conan.cmake file
    if (NOT EXISTS "${CMAKE_BINARY_DIR}/conan.cmake")
        message (STATUS "Downloading conan.cmake from https://github.com/conan-io/cmake-conan")
        file (DOWNLOAD "https://github.com/conan-io/cmake-conan/raw/v0.15/conan.cmake" "${CMAKE_BINARY_DIR}/conan.cmake")
    endif ()

    include (${CMAKE_BINARY_DIR}/conan.cmake)

    conan_add_remote (NAME bincrafters URL https://api.bintray.com/conan/bincrafters/public-conan)

    # Copy the parameters of the function to a variable for conan_cmake_run (add space between items)
    foreach (package_to_get ${ARGV})
        list (APPEND CONAN_EXTRA_REQUIRES ${package_to_get} " ")
    endforeach ()

    conan_cmake_run (REQUIRES
                     ${CONAN_EXTRA_REQUIRES}
                     OPTIONS
                     ${CONAN_EXTRA_OPTIONS}
                     BASIC_SETUP
                     CMAKE_TARGETS # individual targets to link to
                     BUILD
                     missing)
endmacro ()
