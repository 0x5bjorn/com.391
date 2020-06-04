#include "aur.hpp"

// [[ noreturn ]]
int main(int argc, char **argv)
{
    using namespace aur;

    auto window = std::make_shared<SDLWindow>("aur", 0, 0);

    // TODO
    auto triangle_geometry_data = geometry_generators::generate_triangle_geometry_data(1.0f);
    triangle_geometry_data.second[0].color = glm::vec4{ 1.0f, 0.0f, 0.0f, 1.0f };
    triangle_geometry_data.second[1].color = glm::vec4{ 0.0f, 1.0f, 0.0f, 1.0f };
    triangle_geometry_data.second[2].color = glm::vec4{ 0.0f, 0.0f, 1.0f, 1.0f };
    auto triangle_geometry = std::make_shared<ES2Geometry>(triangle_geometry_data.first, triangle_geometry_data.second);
    triangle_geometry->set_type(Geometry::Type::TriangleFan);
    auto triangle_material = std::make_shared<ES2ConstantMaterial>();
    // triangle_material->set_emission_color(glm::vec4{ 1.0f, 0.0f, 0.0f, 1.0f });

    auto triangle = std::make_shared<Mesh>(triangle_geometry, triangle_material);
    triangle->set_scale(glm::vec3{4.0f});
    triangle->set_name("Triangle");

    std::vector<std::shared_ptr<Object>> objects;
    objects.push_back(triangle);

    auto scene = std::make_shared<Scene>(objects);
    auto root = scene->get_root();

    auto &camera = scene->get_camera();
    camera->set_z(5.0f);

    ES2Renderer renderer(scene, window);
    for (;;) {
        window->poll();

        // TODO
        triangle->set_rotation_z(triangle->get_rotation_z() + 0.1f);

        renderer.render();
    }
}
