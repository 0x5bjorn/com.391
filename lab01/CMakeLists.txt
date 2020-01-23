cmake_minimum_required(VERSION "2.8.0")

project("lab01")

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/") 

add_definitions("-std=c++11")

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

include_directories(
    ${OPENGL_INCLUDE_DIRS}
    ${GLEW_INCLUDE_DIRS}
    ${SDL2_INCLUDE_DIR}
    )

add_executable(lab01 lab01.cpp)

target_link_libraries(lab01
    ${OPENGL_LIBRARIES}
    ${GLEW_LIBRARIES}
    ${SDL2_LIBRARY}
)