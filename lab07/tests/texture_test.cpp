#include "aur.hpp"

// [[noreturn]]
int main(int argc, char **argv)
{
    using namespace aur;

    auto window = std::make_shared<SDLWindow>("aur", 0, 0);

    // TODO
    // auto[plane_indices, plane_vertices] = geometry_generators::generate_plane_geometry_data(5, 3, 2, 2);
    // auto plane_geometry = std::make_shared<ES2Geometry>(plane_indices, plane_vertices);
    // auto plane_material = std::make_shared<ES2ConstantMaterial>();
    // auto[image_data, image_width, image_height, image_channels] = file_utilities::read_image_file("../data/images/photo.jpg");
    // auto photo_texture = std::make_shared<ES2Texture>(image_data, image_width, image_height, image_channels);
    // plane_material->set_texture(photo_texture);
    // auto plane = std:: make_shared<Mesh>(plane_geometry, plane_material);
    //
    std::vector<std::shared_ptr<Object>> objects{  };
    auto scene = std::make_shared<Scene>(objects);

    auto camera = scene->get_camera();
    camera->set_z(5.0f);

    ES2Renderer renderer(scene, window);
    for (;;) {
        window->poll();

        // TODO

        renderer.render();
    }
}
