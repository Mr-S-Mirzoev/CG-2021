cmake_minimum_required(VERSION 3.5)
project(main)

set(CMAKE_CXX_STANDARD 14)

set(SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(INC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/inc)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin)

set(SOURCE_FILES
        ${SRC_DIR}/gameplay/input_processing.cpp
        ${SRC_DIR}/gameplay/inventory.cpp
        ${SRC_DIR}/gameplay/game.cpp
        ${SRC_DIR}/gameplay/Player.cpp
        ${SRC_DIR}/graphics/Image.cpp
        ${SRC_DIR}/graphics/screen.cpp
        ${SRC_DIR}/graphics/tile.cpp
        ${SRC_DIR}/utilities/game_object.cpp
        ${SRC_DIR}/utilities/room.cpp
        ${SRC_DIR}/utilities/labirinth.cpp
        ${SRC_DIR}/utilities/matrix.cpp
        ${SRC_DIR}/glad.c
        ${SRC_DIR}/main.cpp)

set(ADDITIONAL_INCLUDE_DIRS
        deps/include/GLAD)
set(ADDITIONAL_LIBRARY_DIRS
        deps/lib)   
set(ADDITIONAL_RUNTIME_LIBRARY_DIRS
        deps/bin)   

set (CMAKE_CXX_FLAGS_DEBUG  "${CMAKE_CXX_FLAGS_DEBUG}")

if(WIN32)
        set(ADDITIONAL_INCLUDE_DIRS 
                ${ADDITIONAL_INCLUDE_DIRS}
                deps/include)
        link_directories(${ADDITIONAL_LIBRARY_DIRS})
else()
        find_package(glfw3 REQUIRED)
endif()

include_directories(${ADDITIONAL_INCLUDE_DIRS} ${INC_DIR})

find_package(OpenGL REQUIRED)

add_executable(main ${SOURCE_FILES})

target_include_directories(main PRIVATE ${OPENGL_INCLUDE_DIR})

if(WIN32)
        add_custom_command(TARGET main POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_directory "${PROJECT_SOURCE_DIR}/deps/bin" $<TARGET_FILE_DIR:main>)
        set_target_properties(main PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}")
        target_compile_options(main PRIVATE)
        target_link_libraries(main LINK_PUBLIC ${OPENGL_gl_LIBRARY} glfw3dll)
else()
        target_compile_options(main PRIVATE -Wnarrowing)
        target_link_libraries(main LINK_PUBLIC ${OPENGL_gl_LIBRARY} glfw rt dl)
endif()

# first we can indicate the documentation build as an option and set it to ON by default
option(BUILD_DOC "Build documentation" OFF)

if(BUILD_DOC)
        # check if Doxygen is installed
        find_package(Doxygen)
        if (DOXYGEN_FOUND)
        # set input and output files
        set(DOXYGEN_IN ${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile.in)
        set(DOXYGEN_OUT ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile)

        # request to configure the file
        configure_file(${DOXYGEN_IN} ${DOXYGEN_OUT} @ONLY)
        message("Doxygen build started")

        # note the option ALL which allows to build the docs together with the application
        add_custom_target( doc_doxygen ALL
                COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYGEN_OUT}
                WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
                COMMENT "Generating API documentation with Doxygen"
                VERBATIM )
        else (DOXYGEN_FOUND)
        message("Doxygen need to be installed to generate the doxygen documentation")
        endif (DOXYGEN_FOUND)
endif(BUILD_DOC)