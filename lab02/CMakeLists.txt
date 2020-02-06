
cmake_minimum_required(VERSION "2.8.0")

project("lab02")

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

add_definitions("-std=c++11")

include_directories(
    ${OPENGL_INCLUDE_DIRS}
    ${GLEW_INCLUDE_DIRS}
    ${SDL2_INCLUDE_DIR}
    ${GLM_INCLUDE_DIRS}
    )

add_executable(lab02 lab02.cpp)

target_link_libraries(lab02
    ${OPENGL_LIBRARIES}
    ${GLEW_LIBRARIES}
    ${SDL2_LIBRARY}
)