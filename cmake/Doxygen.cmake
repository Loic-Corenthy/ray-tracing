function (enable_doxygen)

    message ("")
    message (STATUS "Doxygen")
    message (STATUS "-------")

    option (ENABLE_DOXYGEN "Enable doxygen doc builds of source" OFF)

    if (ENABLE_DOXYGEN)

        find_package (Doxygen REQUIRED dot)

        # Configure Doxyfile
        set (DOXYGEN_CALLER_GRAPH ON)
        set (DOXYGEN_CALL_GRAPH ON)
        set (DOXYGEN_EXTRACT_ALL ON)

        set (DOXYGEN_PROJECT_NUMBER "1.0")
        set (DOXYGEN_PROJECT_BRIEF "A better way to teach the art of dancing")
        set (DOXYGEN_PROJECT_LOGO ./documentation/images/logo.png)
        # set (DOXYGEN_IMAGE_PATH ./images)
        set (DOXYGEN_OUTPUT_DIRECTORY documentation)
        set (DOXYGEN_HTML_EXTRA_STYLESHEET ./documentation/css/doxygenHtmlStyle.css)
        set (DOXYGEN_HTML_COLORSTYLE_HUE 52)
        set (DOXYGEN_HTML_COLORSTYLE_SAT 65)
        set (DOXYGEN_HTML_COLORSTYLE_GAMMA 65)

        # note the option ALL which allows to build the docs together with the application
        doxygen_add_docs (doxygen-docs ALL)

        # Copy resources for the documentation
        add_custom_command (TARGET doxygen-docs POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/documentation/images
                                                                   "${CMAKE_CURRENT_BINARY_DIR}/images")

        add_custom_command (TARGET doxygen-docs POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_SOURCE_DIR}/documentation/mainpage.md
                                                                   ${CMAKE_CURRENT_BINARY_DIR}/mainpage.md)
    endif ()

endfunction ()
