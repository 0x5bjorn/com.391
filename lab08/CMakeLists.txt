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

find_package(SDL2_image REQUIRED)
if(SDL2_IMAGE_FOUND)
    include_directories(SYSTEM ${SDL2_IMAGE_INCLUDE_DIR})
endif(SDL2_IMAGE_FOUND)

find_package(GLM REQUIRED)
if(GLM_FOUND)
    include_directories(SYSTEM ${GLM_INCLUDE_DIRS})
endif(GLM_FOUND)

add_definitions("-g")

include_directories(
    ${OPENGL_INCLUDE_DIRS}
    ${GLEW_INCLUDE_DIRS}
    ${SDL2_INCLUDE_DIR}
    ${SDL2_IMAGE_INCLUDE_DIR}
    ${GLM_INCLUDE_DIRS}
    "./include"
)

set(AUR_SOURCES include/scene/scene.hpp
                include/objects/object.hpp
                include/objects/camera.hpp
                include/objects/mesh.hpp
                include/geometries/vertex.hpp
                include/geometries/geometry.hpp
                include/geometries/es2_geometry.hpp
                include/geometries/geometry_generators.hpp
                include/materials/material.hpp
                include/materials/constant_material.hpp
                include/materials/es2_constant_material.hpp
                include/materials/phong_material.hpp
                include/materials/es2_phong_material.hpp
                include/lights/ambient_light.hpp
                include/lights/light.hpp
                include/lights/directional_light.hpp
                include/lights/point_light.hpp
                include/lights/spot_light.hpp
                include/textures/texture.hpp
                include/textures/es2_texture.hpp
                include/renderer/renderer.hpp
                include/renderer/es2_renderer.hpp
                include/renderer/shader.hpp
                include/renderer/es2_shader.hpp
                include/window/window.hpp
                include/vendor/imgui_impl_sdl.h
                include/vendor/imgui_impl_opengl.h
                include/imgui/imgui.h
                include/imgui/imconfig.h
                include/imgui/imgui.cpp
                include/imgui/imgui_demo.cpp
                include/imgui/imgui_draw.cpp
                include/imgui/imgui_internal.h
                include/imgui/imgui_widgets.cpp
                include/imgui/imstb_rectpack.h
                include/imgui/imstb_textedit.h
                include/imgui/imstb_truetype.h
                include/window/sdl_window.hpp
                include/utilities/utilities.hpp
                include/aur.hpp)

add_executable(window_test ${AUR_SOURCES} tests/window_test.cpp)
target_link_libraries(window_test
    ${OPENGL_LIBRARIES}
    ${GLEW_LIBRARIES}
    ${SDL2_LIBRARY}
    ${SDL2_IMAGE_LIBRARY}
)

add_executable(textured_plane_test ${AUR_SOURCES} tests/textured_plane_test.cpp)
target_link_libraries(textured_plane_test
    ${OPENGL_LIBRARIES}
    ${GLEW_LIBRARIES}
    ${SDL2_LIBRARY}
    ${SDL2_IMAGE_LIBRARY}
)

add_executable(material_properties_test ${AUR_SOURCES} tests/material_properties_test.cpp)
target_link_libraries(material_properties_test
    ${OPENGL_LIBRARIES}
    ${GLEW_LIBRARIES}
    ${SDL2_LIBRARY}
    ${SDL2_IMAGE_LIBRARY}
)
