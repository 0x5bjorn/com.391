cmake_minimum_required(VERSION 3.0)

project(aur)

set(CMAKE_CXX_STANDARD 14)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/") 

find_package(OpenGL REQUIRED)
if(OPENGL_FOUND)
    include_directories(SYSTEM ${OPENGL_INCLUDE_DIRS})
endif(OPENGL_FOUND)

find_package(GLEW REQUIRED)
if(GLEW_FOUND)
    include_directories(SYSTEM ${GLEW_INCLUDE_DIRS})
endif(GLEW_FOUND)

find_package(SDL2 REQUIRED)
if(SDL2_FOUND)
    include_directories(SYSTEM ${SDL2_INCLUDE_DIR})
endif(SDL2_FOUND)

find_package(GLM REQUIRED)
if(GLM_FOUND)
    include_directories(SYSTEM ${GLM_INCLUDE_DIRS})
endif(GLM_FOUND)

add_definitions("-g")

include_directories(
    ${OPENGL_INCLUDE_DIRS}
    ${GLEW_INCLUDE_DIRS}
    ${SDL2_INCLUDE_DIR}
    ${GLM_INCLUDE_DIRS}
    "./include"
)

add_executable(aur
    include/scene/scene.hpp
    include/objects/object.hpp
    include/objects/camera.hpp
    include/objects/mesh.hpp
    include/geometries/geometry.hpp
    include/geometries/es2_geometry.hpp
    include/materials/material.hpp
    include/materials/constant_material.hpp
    include/materials/es2_constant_material.hpp
    include/renderer/renderer.hpp
    include/renderer/es2_renderer.hpp
    include/renderer/shader.hpp
    include/renderer/es2_shader.hpp
    include/window/window.hpp
    include/window/sdl_window.hpp
    include/utilities/utilities.hpp
    include/aur.hpp
    main.cpp
)

target_link_libraries(aur
    ${OPENGL_LIBRARIES}
    ${GLEW_LIBRARIES}
    ${SDL2_LIBRARY}
)