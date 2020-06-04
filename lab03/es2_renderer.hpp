#ifndef ES2RENDERER_HPP
#define ES2RENDERER_HPP

#include "renderer.hpp"
#include <iostream>

#include <GL/glew.h>
#include <SDL2/SDL.h>
#include <glm/glm.hpp>

class ES2Renderer : public Renderer {
public:
    void setup(Scene &scene, Window &window) final {
        glm::vec4 clear_color = scene.get_clear_color();
        glClearColor(clear_color.r, clear_color.g, clear_color.b, clear_color.a);

        for (auto &object : scene.get_objects()) {
            Mesh *mesh = dynamic_cast<Mesh *>(object.get());

            const auto& geometry = mesh->get_geometry();
            const auto& material = mesh->get_material();
            glm::mat4 mvp_matrix { 1.0f };
            material->update(mvp_matrix);
            geometry->update(*mesh->get_material());
        }
    }

    void render(Scene &scene, Window &window) final {
        glViewport(0, 0, (GLsizei) window.get_width(), (GLsizei) window.get_height());
        glClear(GL_COLOR_BUFFER_BIT);

        Camera &camera = scene.get_camera();
        camera.update_model_matrix();
        camera.update_view_matrix();
        camera.update_projection_matrix();
        camera.update_view_projection_matrix();
        int count = 1;
        for (auto &object : scene.get_objects()) {
            std::cout << "Object: " << count << std::endl;
            if (auto mesh = std::dynamic_pointer_cast<Mesh>(object)) {
                auto geometry = mesh->get_geometry();
                auto material = mesh->get_material();

                std::cout << "PositionX: " <<mesh->get_position()[0] << std::endl;


                mesh->update_model_matrix();
                glm::mat4 mvp_matrix = camera.get_view_projection_matrix() * mesh->get_model_matrix();
                material->update(mvp_matrix);
                //std::cout << "MVP Matrix: " << mvp_matrix << std::endl;

                material->use();
                geometry->bind();


                glLineWidth(geometry->get_line_width());
                glDrawArrays(geometry->get_type(), 0, geometry->get_vertices().size());
            }
            count = count == 1 ? 2 : 1;
        }

        window.swap();
    }
};

#endif
